/*
 *	$Id: text.c,v 1.23 1993-01-22 01:10:35 clyne Exp $
 */
/***********************************************************************
*                                                                      *
*                          Copyright (C)  1990                         *
*            University Corporation for Atmospheric Research           *
*                          All Rights Reserved                         *
*                                                                      *
*                      NCAR View V3.01 - UNIX Release                  *
*                                                                      *
***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <errno.h>
#include <ncarg/c.h>
#include "ctrans.h"
#include "cgmc.h"
#include "ctrandef.h"
#include "text.h"
#include "readfont.h"
#include "default.h"


/* 	text.c: 
 *		Author : John clyne
 *		3/21/88
 *
 *		This file contains the font processing routines that handle 
 *	CGM commands for text. The file works in conjunction with readfont.c.
 *	text.c uses information stored in the fontcap to produce the necessary
 *	CGMC commands to stroke text via polylines. The data stored in the 
 *	fontcap must first be decoded by readfont.c and stored in the table
 *	"fcap_template". After text.c is initialized and the fontcap is decoded
 *	text processing may begin. The coordinates for the stroke sequences 
 *	stored in fcap_template must be transformed in response to character
 *	control commands received from the CGM. The transformed version of 
 *	fcap_template is stored in fcap_current.
 *
 *	Note to programmer:
 *		In order to understand these routines one must first understand
 *	the meaning of the CGM text commands as described in ISO/DIS 1. In 
 *	particular the commands; Text, Character Expansion Factor, Character 
 *	Spacing, Character Height, Character Orientation, Text Path, and Text
 *	Alignment.
 */	


/* coordinate transformation matrix necessary for scaling and rotating of
 * characters within each characters space. The matrix is global in order
 * to avoid recalculating its value for each "text" command if it is not 
 * explicitly changed.
 */
static	float	matrix[2][2];	



/* globals which retain information necessary for coordinate transformation
 *from one invocation of the font processing routines to the next
 */
static	int	X_spacing, Y_spacing;	/* character spacing		*/
static	int	Width;			/* the absolute width of a 
					 * string  after appropriate spacing 
					 * has  been added.
					 */
static	int	Spacing;		/* spacing added to the character body
					 * in the x or y direction
					 */

static	int	Widtharray2[WDTH_SPACE];/* array containing widths of each
					 * character for variable space fonts
					 */	
/*
 * arrays containing left and right extent of each character 
 * for variable space fonts
 */
static	int	leftExtent2[WDTH_SPACE];
static	int	rightExtent2[WDTH_SPACE];

static	boolean FontIsInit = FALSE;	/* fontcap sucessfully processed? */

static	float	cosBase,
		sinBase,	/* sin and cos of angle of rotation of 
				 * base vector	
				 */
		cosUp,
		sinUp;		/* sin and cos of angle of rotation of 
				 * "up vector" with  respect to the y 
				 * coordinate  of the screen.
			 	 */
static	float	X_scale(height)
	int	height;
{
	float	mag1;
	float	mag2;
	
	mag1 = MAG(CHAR_X_BASE, CHAR_Y_BASE); 
	mag2 = MAG(CHAR_X_UP, CHAR_Y_UP);

	return (((float) CHAR_HEIGHT / (float) height) 
		* CHAR_EXPAN * (mag1 / mag2));
}

/* 	make_matrix:
 *		This routine calculates the transformation matrix necessary
 *		for handling character orientation, character expansion and
 *		character height. 
 *	on entry:
		fcap_template has been filled in
 *	on exit
 *		matrix : contains data necessary to compute transformations
 */
static	make_matrix()
{
	float	sx,sy;		/* scale in x and y direction	*/


	sy = Y_SCALE(F_CHAR_HEIGHT(fcap_template));
	sx = X_scale(F_CHAR_HEIGHT(fcap_template)); 


	/* The origin of the font coordinate system body must be at
	 * x = y = 0
	 */

	cosBase = (float) CHAR_X_BASE / MAG(CHAR_X_BASE,CHAR_Y_BASE);
	sinBase = (float) CHAR_Y_BASE / MAG(CHAR_X_BASE,CHAR_Y_BASE);
	cosUp = (float)   CHAR_Y_UP / MAG(CHAR_X_UP,CHAR_Y_UP);
	sinUp = (float) -(CHAR_X_UP) / MAG(CHAR_X_UP,CHAR_Y_UP);

	/* calculate transformation matrix	*/
	matrix[0][0] = sx * cosBase; 
	matrix[0][1] = sx * sinBase; 
	matrix[1][0] = -sy * sinUp; 
	matrix[1][1] = sy * cosUp; 
}
  
/* 	trans_coord:
 *		perform coordinate transformations on list of character strokes
 *		using the transformation matrix.
 *	on entry
 *		f1 : a pointer to the un altered font table as it is represented
 *			in the fontcap.
 *	on exit
 *		f2 : transformed version of f1 via the transformation matrix
 */
static trans_coord(f1,f2)
	Fcap	*f1, *f2;	/* font lists	*/
{
	int	i,k;
	float	yscale = Y_SCALE(f1->char_height);
	float xscale = X_scale(f1->char_height);

	for (i = 0; i < F_NUMCHAR(*f1); i++) {
		for (k = 0; k < F_NUMSTROKE(*f1, i); k++) {

			F_X_COORD(*f2, i, k) = 
				(F_X_COORD(*f1, i, k) * matrix[0][0]) 
				+ (F_Y_COORD(*f1, i, k) * matrix[1][0]);

			F_Y_COORD(*f2, i, k) = 
				(F_X_COORD(*f1, i, k) * matrix[0][1]) 
				+ (F_Y_COORD(*f1, i, k) * matrix[1][1]); 
		}

	}


	/* if variable spacing is desired	*/
	if (var_space) {
		/* scale widths of individual characters	*/
		for (i=0;i<F_NUMCHAR(*f1) ;i++)  {
			leftExtent2[i] = xscale * leftExtent1[i];
			rightExtent2[i] = xscale * rightExtent1[i];
			Widtharray2[i] = rightExtent2[i] - leftExtent2[i];
		}
	}



	/* scale other portions of font coordinate system 
	 * note: only scaling is done here. Rotation is done in the alignment
	 * routines
	 */

	F_CHAR_HEIGHT(*f2) = F_CHAR_HEIGHT(*f1) * yscale;

	F_CHAR_WIDTH(*f2) = F_CHAR_WIDTH(*f1) * xscale;
	

		/* scale y coordinates parameters*/
	F_FONT_TOP(*f2) = F_FONT_TOP(*f1) * yscale;
	F_FONT_CAP(*f2) = F_FONT_CAP(*f1) * yscale;
	F_FONT_HALF(*f2) = F_FONT_HALF(*f1) * yscale;
	F_FONT_BASE(*f2) = F_FONT_BASE(*f1) * yscale;
	F_FONT_BOTTOM(*f2) = F_FONT_BOTTOM(*f1) * yscale;

		/*scale x coordinates parameters*/
	F_FONT_RIGHT(*f2) = F_FONT_RIGHT(*f1) * xscale;

}

/* 	Init_Font:
 *		This is the initialization routine for the font processor. It
 *		must be invoked with a fontcap file name and path prior to
 *		any font processing
 */
int	Init_Font(fontcap)
	char *fontcap;
{
	static	char	*fontCap = NULL;
	char	*f = fontcap;
	int	status = 0;


	FontIsInit = FALSE;

	if (Init_Readfont(f) != 0) {
		status = -1;

		/*
		 * try and use previous fontcap if it exists
		 */
		if (fontCap) {
			f = fontCap;
			if (Init_Readfont(f) < 0) {
				return (status);
			}
		}
		else return(status);
	}

	FontIsInit = TRUE;

	/*
	 * record name of the fontcap
	 */
	if (fontCap) free((Voidptr) fontCap);
	if (! (fontCap = malloc((unsigned) strlen(f) + 1))) {
		ESprintf(errno, "malloc(%d)", strlen(f) + 1);
		return(-1);
	}
	(void) strcpy(fontCap, f);

	return (status);
}

/* 	path_spacing:
 *		Determine necessary spacing between characters (either 
 *		horizontal or vertical depending on path ) based on "text 
 *		path" and "character spacing". These values are effected and
 *		therefore scaled appropriately by "Character Height", "Character
 *		expansion" and "Character Orientation".				
 *	on exit
 *		Y_spacing,
 *		X_spacing : contain spacing in x and/or y directions. 
 *			    NOTE : This spacing is in the along the Untranslated
 *				    coordinate system, not along base and up 
 *				    vector.
 *		Width :   if mono space font or if path is up or down then 
 *				contain height of and width of character width 
 *			   	appropriate spacing added.
 *			  else contain spacing between characters
 *		Spacing:	the amount of space added to the character
 *				body in either the x or y direction depending
 *				on the path
 *		
 */
static path_spacing ()
{
	int	dir = 1;

	switch (TEXT_PATH) { 
		case PATH_LEFT: 
			dir = -1;	/* negate value	*/
		case PATH_RIGHT:
			Spacing = (int) ((CHAR_SPACE * CHAR_HEIGHT) 
				* (MAG(CHAR_X_BASE,CHAR_Y_BASE) 
				/ MAG(CHAR_X_UP,CHAR_Y_UP)));

			Width = ((var_space) ? 0
				: F_FONT_RIGHT(fcap_current)) + Spacing;

			X_spacing = (int) ( 
				Width * ((float) CHAR_X_BASE / 
					MAG(CHAR_X_BASE,CHAR_Y_BASE)) 
				* dir);

			Y_spacing = (int) ( 
				Width * ((float) CHAR_Y_BASE / 
					MAG(CHAR_X_BASE,CHAR_Y_BASE))
				 * dir);

			break;

		case PATH_DOWN:
			dir = -1;	/* negate value	*/
		case PATH_UP:
			Spacing = CHAR_SPACE * CHAR_HEIGHT;

			/*
			 * this should be "width = top + spacing" if the
			 * font coordinate system truly began at (0,0)
			 */
			Width = (F_FONT_TOP(fcap_current) -
				F_FONT_BOTTOM(fcap_current) + Spacing);


			X_spacing = (int) (
				Width * (CHAR_X_UP / MAG(CHAR_X_UP,CHAR_Y_UP))
				* dir);

			Y_spacing = (int) ( 
				Width * (CHAR_Y_UP / MAG(CHAR_X_UP,CHAR_Y_UP))
				* dir);
			break;
		default:
			break;
	  }
}


/* 	modified:
 *		Test character attribute values against their values at
 *	last invocation. If any changes modify appropriate transformation
 *	tables.
 */
static modified ()
{

	if (TEXT_ATT_DAMAGE) {
		make_matrix();
		trans_coord(&fcap_template,&fcap_current);
		path_spacing();
		TEXT_ATT_DAMAGE = TEXT_F_IND_DAMAGE = FALSE;
	}
}

/*	left_most:
 *		This function finds the right-most extented character
 *		in a string and returns its right extent.
 *		It assumes that the coordinate origin is on the left side.
 *
 * on entry
 *	*s		: the string
 *	strlen		: length of s
 * on exit
 *	return 		= left-most extent
 */
static	int	left_most(s, strlen)
	const char	*s;
	int		strlen;
{
	int	i;
	int	index;
	unsigned	min;

	if (! var_space) return (0);


	for (i=0, min=~0; i<strlen; i++) {
		index = s[i] - F_CHAR_START(fcap_template);
		min = MIN(leftExtent2[index], min);
	}

	return((int) min);
}

/*	right_most:
 *		This function finds the right-most extented character
 *		in a string and returns its right extent.
 *		It assumes that the coordinate origin is on the right side.
 *
 * on entry
 *	*s		: the string
 *	strlen		: length of s
 * on exit
 *	return 		= right-most extent
 */
static	int	right_most(s, strlen)
	const char	*s;
	int		strlen;
{
	int	i;
	int	max, index;

	if (! var_space) return (F_FONT_RIGHT(fcap_current));

	for (i=0, max=0; i<strlen; i++) {
		index = s[i] - F_CHAR_START(fcap_template);
		max = MAX(rightExtent2[index], max);
	}

	return(max);
}

/*	middle_most:
 *		This function finds the right-most extented character
 *		and the left-most extended charcter in a string and returns 
 *		the middle of these two characters.
 *		It assumes that the coordinate origin is on the right side.
 *
 * on entry
 *	*s		: the string
 *	strlen		: length of s
 * on exit
 *	return 		= middle 
 */
static	int	middle_most(s, strlen)
	const char	*s;
	int		strlen;
{
	int	i;
	int	left, right;

	if (! var_space) return (F_FONT_RIGHT(fcap_current) / 2);

	left = left_most(s, strlen);
	right = right_most(s, strlen);
	return (left + ((right - left) / 2));
}

/*	left_extent:
 *
 *	Return the left extent of the given character.
 *
 * on entry
 *	c		: the character
 * on exit
 *	return 		= left extent of character
 */
static	int	left_extent(c)
	char	c;
{
	int	index;

	if (! var_space) return (0);

	index = c - F_CHAR_START(fcap_template);
	return(leftExtent2[index]);
}

/*	right_extent:
 *
 *	Return the right extent of the given character.
 *
 * on entry
 *	c		: the character
 * on exit
 *	return 		= right extent of character
 */
static	int	right_extent(c)
	char	c;
{
	int	index;

	if (! var_space) return (F_FONT_RIGHT(fcap_current));

	index = c - F_CHAR_START(fcap_template);
	return(rightExtent2[index]);
}

/*	txt_ext_width:
 *
 *	Calculate the width of the text extent rectangle bounding the
 *	given string.
 *
 * on entry
 *	var_space 	: true or false;
 *	strlen 		: length of string to print
 *	Width  		: amount of additional spacing to add due to
 *			  CHAR_SPACING if var_space is true, else it is
 *			  the with of a mono space character.
 * on exit
 *	return 		= Width of text extent rectangle
 */
static	int	text_extent_width(s,strlen)
	char	*s;
	int	strlen;
{
	int	i;
	int	index;
	int	total = 0;

	if (! strlen) return(0);

	if (! var_space) return ((Width * strlen) - Spacing);

	for (i=0;i<strlen;i++) {
		index = s[i] - F_CHAR_START(fcap_template);
		total += (Widtharray2[index] + Width);
	}
	total += (strlen - 1) * X_spacing;	/* add text spacing	*/
	return(total);
}

/*	str_width:
 *		This function calculates the translation along baseline that
 *	in necessary for horizontal  alignment of  the text. The value returned
 *	must be "rotated" to accommodate the rotation of the string due to 
 *	orientation and path.
 *	
 *	on entry:
 *		strlen : length of the text string.
 *		s	: the string
 *		Width  : if mono space font or path is up or down 
 *				absolute Width of string along base vector
 *			 else  contain spacing between characters
 *	on exit:
 *		return = x translation value along  base vector.
 *		 
 */ 

static int	str_width(strlen, s)
	int	strlen;		
	char	*s;
{

	/*switch on horizontal alignment	*/
	switch (TEXT_ALI_H) {

	/*normal alignment see ISO/DIS 8632/1 description on Text Alignment*/
	case A_NORM_H :	
		switch (TEXT_PATH) {
		case PATH_RIGHT :	/*left align*/
			return(left_extent(s[0]));

		case PATH_LEFT 	: 	/*right align*/
			return(right_extent(s[0]));

		case PATH_UP 	:   	/*centre align*/ 
		case PATH_DOWN 	: 
			return(middle_most(s, strlen));
		}

	case A_LEFT :	/* align left	*/
		switch (TEXT_PATH) {
		case PATH_LEFT  : 
			return(- text_extent_width(s+1,strlen-1));

		case PATH_RIGHT : 
			return(left_extent(s[0]));
		case PATH_UP    : 
		case PATH_DOWN  : return(left_most(s, strlen));
		}

	case A_CENTER :	/*align center	*/
		switch (TEXT_PATH) {
		case PATH_RIGHT : 
			return((text_extent_width(s,strlen) / 2) +
				left_extent(s[0]));

		case PATH_LEFT 	: 
			return(-((text_extent_width(s,strlen) / 2) -
					F_FONT_RIGHT(fcap_current)));
		case PATH_UP 	: 
		case PATH_DOWN  : return(middle_most(s, strlen));
		}

	case A_RIGHT  : 	/*align right	*/
		switch (TEXT_PATH) {
		case PATH_RIGHT : 
			return(text_extent_width(s,strlen) + 
				left_extent(s[0]));
		case PATH_LEFT 	:  
			return(right_extent(s[0]));
		case PATH_UP	: 
		case PATH_DOWN 	:  return(right_most(s,strlen));
		}
	default    :
		return(0);
	}
}

/*	str_heigth:
 *		This function calculates the translation along the up 
 *	vector that is necessary for vertical alignment of the text. 
 *	The value returned must be "rotated" to accommodate the rotation 
 *	of the string due to orientation and path.
 *	
 *	on entry:
 *		strlen 	: the length of the string.
 *		fcap_current has been filled in.
 *		Width  : if mono space font or path is up or down 
 *				absolute Width of string along base vector
 *			 else  contain spacing between characters
 *	on exit:
 *		return = y translation value along up vector.
 *		 
 */ 
static int	str_height(strlen)
	int	strlen;
{
	switch (TEXT_ALI_V) {
	case A_NORM_V :
		switch (TEXT_PATH) {
		case PATH_RIGHT : 
		case PATH_LEFT : 
		case PATH_UP :  return(F_FONT_BASE(fcap_current));
		case PATH_DOWN : return (F_FONT_TOP(fcap_current));
		}
	case A_TOP : 
		switch(TEXT_PATH) {
		case PATH_RIGHT :
		case PATH_LEFT :
		case PATH_DOWN :
			return (F_FONT_TOP(fcap_current));
		case PATH_UP :  
			return((Width * (strlen-1)) + F_FONT_TOP(fcap_current));
		}

	case A_CAP :
		switch(TEXT_PATH) {
		case PATH_RIGHT :
		case PATH_LEFT :
		case PATH_DOWN : 
			return (F_FONT_CAP(fcap_current));
		case PATH_UP :  
			return((Width * (strlen-1)) + F_FONT_CAP(fcap_current)); 
		}
	case A_HALF : 
		switch(TEXT_PATH) {
		case PATH_RIGHT :
		case PATH_LEFT :
			return (F_FONT_HALF(fcap_current));
		case PATH_DOWN : 
			return (-((((strlen * Width) - Spacing) / 2)
				- F_FONT_TOP(fcap_current)));
		case PATH_UP :  
			return(((Width * strlen) - Spacing) / 2); 
		}
	case A_BASE : 
		switch(TEXT_PATH) {
		case PATH_RIGHT :
		case PATH_LEFT :
		case PATH_UP :  
			return (F_FONT_BASE(fcap_current));
		case PATH_DOWN : 
			return(-((Width * (strlen-1)) - 
				F_FONT_BASE(fcap_current))); 
		}
	case A_BOTTOM : 
		switch(TEXT_PATH) {
		case PATH_RIGHT :
		case PATH_LEFT :
		case PATH_UP :  
			return (F_FONT_BOTTOM(fcap_current));
		case PATH_DOWN : 
			return(-((Width * (strlen-1)) - 
				F_FONT_BOTTOM(fcap_current))); 
		}
	default :
		return(0);
	}
}
 
/*	text_align:
 *		This routine calculates the necessary rotation and translation
 *	necessary to support text alignment.
 *
 *	on entry:
 *		strlen : length of string of text
 *		s      : the string
 *	on exit:
 *		transx : calculated adjustment of x coordinate
 *		transy : calculated adjustment of y coordinate
 */
static void	text_align(transx,transy, strlen,s)

	long	*transx,*transy;
	int	strlen;
	char	*s;
{
	float	x,y;	/*temp storage	*/

	x = (float) str_width(strlen,s);	/*translation of x	*/
	y = (float) str_height(strlen);		/*translation of y	*/


	*transx = -((x * cosBase) - (y * sinUp));
	*transy = -((x * sinBase) + (y * cosUp)); 
}




/*
 *	store old polyline attributes. We stroke text by calling the CGM
 *	polyline command. Hence we need to set polyline attributes to 
 *	match the desired text attributes. When we're finished stroking
 *	text we need to restore the original polyline attributes
 */
Rtype	lineWidthSave;
IXtype 	lineTypeSave;
CItype	lineColourSave;

/*
 *	initialize the line drawing code
 *	Mostly the routine is responsible for setting the aforementioned
 *	text attributes correctly and saving the original polyline attributes
 */
static	int	open_line_draw()
{
	CGMC	cgmc;

	/*
	 * space for the various attributes
	 */
	Rtype	r_array[1];	
	IXtype	ix_array[1];
	CItype	ci_array[1];

	/*
	 * store polyline attributes
	 */
	lineWidthSave = LINE_WIDTH;
	lineTypeSave = LINE_TYPE;
	lineColourSave = LINE_COLOUR.index;

	cgmc.r = &r_array[0];
	cgmc.ix = &ix_array[0];
	cgmc.ci = &ci_array[0];
	
	/*set line width */
	cgmc.class = ATT_ELEMENT;
	cgmc.command = LINE_WIDTH_ID;
	cgmc.r[0] = 1.0;
	cgmc.Rnum = 1;
	if (Process(&cgmc) != OK) return(-1);

	/*set line type	*/
	cgmc.class = ATT_ELEMENT;
	cgmc.command = LINE_TYPE_ID;
	cgmc.ix[0] = 1;
	cgmc.IXnum = 1;
	if (Process(&cgmc) != OK) return(-1);

	/*set line colour to text colour	*/
	cgmc.class = ATT_ELEMENT;
	cgmc.command = LINE_COLOUR_ID;
	cgmc.ci[0] = TEXT_COLOUR.index;
	cgmc.CInum = 1;
	if (Process(&cgmc) != OK) return(-1);

	return(0);
}

/*
 *	cleanup the line drawing code.
 *	i.e. restore the original polyline attributes
 */
static	int	close_line_draw()
{
	CGMC	cgmc;

	Rtype	r_array[1];
	IXtype	ix_array[1];
	CItype	ci_array[1];

	cgmc.r = &r_array[0];
	cgmc.ix = &ix_array[0];
	cgmc.ci = &ci_array[0];
	
	/*	restore line width */
	cgmc.class = ATT_ELEMENT;
	cgmc.command = LINE_WIDTH_ID;
	cgmc.r[0] = lineWidthSave;
	cgmc.Rnum = 1;
	if (Process(&cgmc) != OK) return(-1);

	/*	restore line type	*/
	cgmc.class = ATT_ELEMENT;
	cgmc.command = LINE_TYPE_ID;
	cgmc.ix[0] = lineTypeSave;
	cgmc.IXnum = 1;
	if (Process(&cgmc) != OK) return(-1);

	/*	restore line colour */
	cgmc.class = ATT_ELEMENT;
	cgmc.command = LINE_COLOUR_ID;
	cgmc.ci[0] = lineColourSave;
	cgmc.CInum = 1;
	if (Process(&cgmc) != OK) return(-1);

	return(0);
}

/*
 *	draw a polyline by calling the CGM Polyline handler
 */
static	int	line_draw(p, n)
	Ptype	*p;
{
	CGMC	cgmc;

	if (n < 1) return(0);

	cgmc.class = GRP_ELEMENT;
	cgmc.command = POLYLINE_ID;
	cgmc.more = FALSE;
	cgmc.p = p;
	cgmc.Pnum = n;

	if (Process(&cgmc) != OK) return(-1);
	
	return(0);
}
	


/* 	Text:
 *		This function translates the CGM command "text" into the
 *	polylines necessary to stroke the text character codes.
 *	The cgmc's thus contain completely transformed polylines,
 *	no further scaling, rotating or translation is necessary.
 *	Hence, Text is able to invoke Process with cgmc's as arguments
 *
 *	Note:
 *		Characters contained in the text that are note described
 *	in the fontcap are ignored. This INCLUDES any control
 *	characters. eg. newline, tab.
 *
 *	on entry
 *		cgmc : contains a "text" command and its data
 *		X_spacing, Y_spacing : contain spacing in x and y direction
 */

int	Text(cgmc)
	CGMC	*cgmc;
{
	int	index;		/* index into the transformed fontlist	*/
	int	x_space = 0;	/* spacing in x and y direction		*/
	int	y_space = 0;
	int	i,k;
	long	trans_x, trans_y;
	int	numstroke;	/* number of strokes making up the font	*/
	int	char_ind;
	int	str_ind;	/* index to the current string		*/
	int	status = 0;

	static	char *string = NULL;	/* the string currently being stroked */
	static	unsigned str_space = 0;	/* size of string array		*/

	static	Ptype	pStart; 	/* point of origin of text	*/
	static	Ptype	p[1024];	/* point buffer array		*/

	/*
	 * make sure font has not changed
	 */
	if (TEXT_F_IND_DAMAGE) {
		if (setFont(TEXT_F_IND) < 0) status = -1;
		TEXT_F_IND_DAMAGE = FALSE;
	}

	if (! FontIsInit)
		return(0);	/* no font, nothing to do	*/

	if (open_line_draw() < 0) return(-1);

	modified();	/* recalc transformation values if attributes changed*/


	/*
	 *	process each string in the cgmc
	 */
	for (str_ind = 0; str_ind < cgmc->Snum; str_ind++) {

	/* make sure their is sufficient space in s.string	*/
	if (( i = cgmc->s->string_space[str_ind]) > str_space) {
		if (string != (char *) NULL) free ((Voidptr) string);
		string = (char *) malloc ((unsigned) i * sizeof(char));
		if (! string) {
			ESprintf(errno, "malloc(%d)", i * sizeof(char));
			return(-1);
		}
		str_space = i;
	}

	(void) strcpy(string,cgmc->s->string[0]);

	/*
	 * make sure every character in the string has a definition. If
	 * not change that character to a space so we can do something 
	 * reasonable when computing the alignment of the entire string
	 */
	for (i=0; i<strlen(string); i++) {

		index = string[i] - F_CHAR_START(fcap_template);	
		numstroke = F_NUMSTROKE(fcap_current, index);
		if (numstroke <= 1) {
			string[i] = ' ';
		}
	}

		

	/* calculate text alignment	*/
	text_align(&trans_x, &trans_y, strlen(string), string); 

	/*store contents of cgmc	*/
	pStart.x = cgmc->p[0].x + trans_x; 
	pStart.y = cgmc->p[0].y + trans_y;


	/* transform text in to cgmc polylines	*/
	for (char_ind=0; char_ind<strlen(string); char_ind++) {

		k = i = 0;	/* stroke index in Fontable and cgmc	*/

		/* index into Fontable*/
		index = string[char_ind] - F_CHAR_START(fcap_template);	

		if (index < 0 || index >= F_NUMCHAR(fcap_template)){
			continue;
		}

		/* number of strokes making up a character.	*/
		numstroke = F_NUMSTROKE(fcap_current, index);


		if (numstroke) {

			p[k].x = F_X_COORD(fcap_current, index, i)
				+ x_space + pStart.x;

			p[k].y = F_Y_COORD(fcap_current, index, i)
				+ y_space + pStart.y;

			k++; i++; 


			for (;i < numstroke;i++) { 
				if (!(F_PEN(fcap_template, index, i))) {

					if (line_draw(p, k) < 0) {
						status = -1;
					}

					k = 0;
				} 

				p[k].x = F_X_COORD(fcap_current, index, i)					+ x_space + pStart.x;

				p[k].y = F_Y_COORD(fcap_current, index, i)
					+ y_space + pStart.y;
				k++; 
			}

			if (line_draw(p, k) < 0) {
				status = -1;
			}
			k = 0;

		}	/* if numstroke	*/

		/* calculate possistion of NEXT character for
		 * for variable space font
		 */
		if (var_space && (TEXT_PATH == PATH_RIGHT))  {
			x_space += X_spacing 
				+ (Widtharray2[index] 
			* CHAR_X_BASE/MAG(CHAR_X_BASE,CHAR_Y_BASE));

			y_space += Y_spacing 
				+ (Widtharray2[index] 
			* CHAR_Y_BASE/MAG(CHAR_X_BASE,CHAR_Y_BASE));
		}

		if (var_space && (TEXT_PATH == PATH_LEFT))  {
			x_space += (X_spacing 
				- (Widtharray2[index] 
				* CHAR_X_BASE/MAG(CHAR_X_BASE,CHAR_Y_BASE)));

			y_space += (Y_spacing 
				- (Widtharray2[index] 
				* CHAR_Y_BASE/MAG(CHAR_X_BASE,CHAR_Y_BASE)));
		}
	
		/* calculate possistion of next character for
		 * for mono space font
		 */
		if (!(var_space) || (TEXT_PATH == PATH_UP)
			|| (TEXT_PATH == PATH_DOWN)) {
			x_space += X_spacing; 
			y_space += Y_spacing;
		}

	}


	}	/* for loop	*/

	if (close_line_draw() < 0) return(-1);

	return (status);
}
 



#ifdef	DEBUG_TEXT
/* 	draw:
 *		debuging routine that prints values of points in computed
 *	polyline
 */
draw (cgmc)
	CGMC	*cgmc;
{
	int i;
	for (i=0;i<cgmc->Pnum;i++) {
		(void) fprintf(stderr,"x coord = %d, y coord = %d\n", cgmc->p[i].x, cgmc->p[i].y);
	}
	(void) fprintf(stderr,"\n");
}
#endif


