.\"
.\"	$Id: ncargf77.m,v 1.12 2002-06-05 22:02:19 haley Exp $
.\"
.TH NCARGF77 1NCARG "March 1993" NCAR "NCAR GRAPHICS"
.SH NAME
ncargf77 \- Command for compiling Fortran code that uses the NCAR Graphics
low-level utilities
.SH SYNOPSIS
\fBncargf77\fP 
[\fB\-ngmath\fR]
[\fB\-smooth\fR]
[\fB\-quick\fR]
[\fB\-super\fR]
[\fB\-agupwrtx\fR]
[\fB\-ictrans\fR]
[\fB\-noX11\fR] ...
.SH DESCRIPTION
\fIncargf77\fP is a script that invokes the FORTRAN 77 compiler/linker
with the proper NCAR Graphics LLU (low-level utility) libraries.
Arguments presented above are associated with NCAR Graphics.  All
other arguments and options are identical to the f77 command on your
particular machine; arguments that include quoted strings may have to
be enclosed in single quotes.
.sp
NOTE: \fIncargf77\fP cannot be used to compile NCAR Graphics Fortran
programs that call the HLUs (high-level utilities).  You must use
\fInhlf77\fP instead.  See the \fInhlf77\fP man page for more
information.
.sp
In order to run \fIncargf77\fP, you must have your NCARG_ROOT
environment variable set to the directory pathname where the NCAR
Graphics libraries, binaries, and include files were installed.  If
you are not sure what NCARG_ROOT should be set to, please check with 
your system administrator or the site representative for NCAR Graphics.
If the NCAR Graphics libraries, binaries, and include files were not
installed under one root directory, then you will need to set the 
environment variables NCARG_LIB, NCARG_BIN, and NCARG_INCLUDE instead.
Please see "man ncargintro" for more information.
.sp
Note that, on some systems, if you supply your own binary libraries in
addition to the ones automatically referenced by \fIncargf77\fR, all the
libraries must have been created in a similar fashion.
.sp
.I OPTIONS
.IP "\-ngmath"
Links in the NCAR Graphics ngmath library.
.sp
.IP "\-smooth"
Link in the "smooth" objects.
.sp
.IP "\-quick"
Link in the "quick" objects.
.sp
.IP "\-super"
Link in the "super" objects.
.sp
.IP "\-agupwrtx"
Link in the "agupwrtx" library.
.IP "\-ictrans"
When \fIncargf77\fR is invoked with the this option, the resulting
executable will, upon invocation, send its metafile output to the translator 
\fBictrans\fR  . The environment variable GRAPHCAP must be set to a valid
graphics output device whenever the executable is executed.
.sp
.sp
.IP "\-noX11"
Do not link in the X library when linking the code.
.sp
By default, \fIncargf77\fR will load the X11 library when linking
your Fortran program.  This is because the GKS library now has an
X11 driver.  If you try running \fIncargf77\fR and the
compiler complains that it cannot find the library for X11, then try
running \fIncargf77 -L/xxx/yyy/zzz program.f\fP where \fI/xxx/yyy/zzz\fP 
is the path leading to your X11 library.  If you do not have the X11 library,
or else you just don't want it to be loaded, you can use the \fB\-noX11\fR
option.
.sp
.SH SEE ALSO
Online:
.BR ictrans(1NCARG),
.BR gcaps(1NCARG),
.BR ncargcc(1NCARG),
.BR nhlcc(1NCARG),
.BR nhlf77(1NCARG),
.BR ncargintro(5NCARG)
.sp
Hardcopy:
NCAR Graphics Fundamentals, UNIX Version
.SH COPYRIGHT
Copyright (C) 1987-2002
.br
University Corporation for Atmospheric Research
.br

This documentation is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License as published
by the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This software is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
General Public License for more details.

You should have received a copy of the GNU General Public License
along with this software; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
USA.
