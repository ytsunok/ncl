.TH WMGETC 3NCARG "January 1995" UNIX "NCAR GRAPHICS"
.na
.nh
.SH NAME
WMGETC -  
Retrieves the current character value of an internal parameter of
type character.
.SH SYNOPSIS
CALL WMGETC (PNAM,CVAL)
.SH C-BINDING SYNOPSIS
#include <ncarg/ncargC.h>
.sp
void c_wmgetc (char *pnam, char *cval, int len)
.SH DESCRIPTION 
.IP PNAM 12
(an input constant or variable of type CHARACTER) specifies the name of the
parameter to get. The name must appear as the first three
characters of the string. 
.IP CVAL 12
(an output variable of type CHARACTER) is the name of the variable
into which the value of the internal parameter specified by PNAM
is to be retrieved.
.SH C-BINDING DESCRIPTION
The C-binding argument descriptions are the same as the FORTRAN 
argument descriptions with the following exception:
.IP len 12
The size of cval as dimensioned in the calling program.
.SH USAGE
This routine allows you to retrieve the current value of
Wmap parameters.  For a complete list of parameters available
in this utility, see the wmap_params man page.
.SH ACCESS
To use WMGETC, load the NCAR Graphics libraries ncarg, ncarg_gks, 
and ncarg_c, preferably in that order.  To use c_wmgetc, load the 
NCAR Graphics libraries ncargC, ncarg, ncarg_gksC, ncarg_gks, and ncarg_c,
preferably in that order.
.SH SEE ALSO
Online: 
wmap, wmdflt, wmgetr, wmgeti, wmlabs, wmsetc, wmseti, wmsetr, wmap_params
.sp
Hardcopy: 
WMAP - A Package for Producing Daily Weather Maps and Plotting Station 
Model Data
.SH COPYRIGHT
(c) Copyright 1995 University Corporation for Atmospheric Research
.br
All Rights Reserved
