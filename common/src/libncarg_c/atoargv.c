
/*
 *      $Id: atoargv.c,v 1.1 1992-04-09 23:42:21 clyne Exp $
 */
/*
 *	File:		atoargv.c
 *
 *	Author:		John Clyne
 *			National Center for Atmospheric Research
 *			PO 3000, Boulder, Colorado
 *
 *	Date:		Thu Apr 9 13:34:30 MDT 1992
 *
 *	Description:	Convert a string to an argument vector;
 */

#include <stdio.h>
#include <errno.h>
#include "ncarv.h"

static	char	*buf = NULL;	/* internal storage for string 	*/
static	int	bufSize = 0;
static	char	*tokenHead;
static	char	*tokenTail;

/*
 *	compile a string for parsing with next_token()
 */
static	int	compile_string(s)
	char	*s;
{
	if (bufSize < (strlen(s) + 1)) {
		if (buf) cfree(buf);
		buf = NULL;
		bufSize = 0;
	} 

	if (! buf) {
		if (! (buf = (char *) malloc (strlen(s) + 1))) {	
			ESprintf(errno, "malloc(%d)", strlen(s)+1);
			return(-1);
		}
		bufSize = strlen(s) + 1;
	}
	strcpy(buf, s);
	tokenHead = tokenTail = buf;
	return(1);
}

/*
 *	return the next token in the string compiled by compile_string()
 *	return NULL if no more tokens;
 */
static	char	*next_token()
{
	tokenHead = tokenTail;

	/*
	 * skip leading white space
	 */
	while (isspace(*tokenHead)) tokenHead++;

	if (! *tokenHead) return(NULL);	/* no token	*/

	tokenTail = tokenHead;

	while (*tokenTail && ! isspace(*tokenTail)) tokenTail++;

	if (*tokenTail) {
		*tokenTail = '\0';
		tokenTail++;
	}

	return(tokenHead);
}


/*
 *	return the number of tokens (args) in s
 */
static	int	num_tokens(s)
	char	*s;
{
	int	count = 0;

	while (isspace(*s)) s++;

	for(;;) {
		if (*s && ! isspace(*s)) {
			count++;
			while (*s && !isspace(*s)) s++;	/* skip token 	*/
		}
		else if (*s && isspace(*s)) {
			while (*s && isspace(*s)) s++;	/* skipe white space */
		}
		else {
			break;
		}
	}
	return(count);
}


/*
 *	AToArgv()
 *	PUBLIC
 *
 *	Converts a character string of space-separated arguments into
 *	an argument vector suitable for execv, .etc.
 *
 * on entry
 *	*str		: argument string
 *	*prog_name	: optional argv[0], i.e. program name.
 * on exit
 *	*argc		: if non null on entry contains arg count for argv
 *	return		: return argument vector if ok, else NULL and 
 *			  invoke ESprintf()
 */ 
char	**AToArgv(str, prog_name, argc)
	char	*str;
	char	*prog_name;
	int	*argc;
{
	char	**argv;
	int	argc_ = 0;
	char	*t;	/* token	*/
	int	i;

	if (! str) {
		ESprintf(EINVAL, "str is NULL");
		return((char **) NULL);
	}

	argc_ = num_tokens(str);
	if (prog_name) argc_++;

	if (! (argv = (char **) malloc ((argc_ + 1) * sizeof(char *)))) {
		ESprintf(errno, "malloc(%d)", (argc_ + 1) * sizeof (char *));
		return((char **) NULL);
	}

	if (prog_name) {
		if (! (argv[0] = (char *) malloc (strlen(prog_name) +1))) {
			ESprintf(errno, "malloc(%d)", strlen (prog_name)+1);
			return((char **) NULL);
		}
		(void) strcpy(argv[0], prog_name);
	}

	if (compile_string(str) < 0) return(NULL);

	i = prog_name ? 1 : 0;
	while (t = next_token()) {
		if (! (argv[i] = (char *) malloc (strlen(t) + 1))) {
			ESprintf(errno, "malloc(%d)", strlen(t) + 1);
			return((char **) NULL);
		}
		(void) strcpy(argv[i], t);
		i++;
	}

	argv[i] = NULL;

	if (argc) *argc = argc_;

	return(argv);
}

/*
 *	FreeArgv()
 *	PUBLIC
 *
 *	Free a argument vector returned by AToArgv()
 *
 * on entry
 *	**argv		: argument vector
 */
void	FreeArgv(argv)
	char	**argv;
{
	char	**argv_	= argv;

	while (*argv_) {
		free(*argv);
		argv_++;
	}
	free(argv);
}

