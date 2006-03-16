C
C	$Id: conrec.f,v 1.5 2006-03-16 18:30:43 kennison Exp $
C                                                                      
C                Copyright (C)  2000
C        University Corporation for Atmospheric Research
C                All Rights Reserved
C
C This file is free software; you can redistribute it and/or modify
C it under the terms of the GNU General Public License as published
C by the Free Software Foundation; either version 2 of the License, or
C (at your option) any later version.
C
C This software is distributed in the hope that it will be useful, but
C WITHOUT ANY WARRANTY; without even the implied warranty of
C MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
C General Public License for more details.
C
C You should have received a copy of the GNU General Public License
C along with this software; if not, write to the Free Software
C Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
C USA.
C
      SUBROUTINE CONREC (Z,L,M,N,FLO,HI,FINC,NSET,NHI,NDOT)
C
C     DIMENSION OF           Z(L,N)
C     ARGUMENTS
C
C     PURPOSE                CONRECSUPR draws a contour map from data
C                            stored in a rectangular array, labeling
C                            the lines.  This is the so-called "super"
C                            version, which smooths contour lines and
C                            removes crowded lines.
C
C     USAGE                  If the following assumptions are met, use
C
C                              CALL EZCNTR (Z,M,N)
C
C                              ASSUMPTIONS:
C                                  --All of the array is to be contoured.
C                                  --Contour levels are picked
C                                    internally.
C                                  --Contouring routine picks scale
C                                    factors.
C                                  --Highs and lows are marked.
C                                  --Negative lines are drawn with a
C                                    dashed line pattern.
C                                  --EZCNTR calls FRAME after drawing the
C                                    contour map.
C
C                            If these assumptions are not met, use
C
C                              CALL CONREC (Z,L,M,N,FLO,HI,FINC,NSET,
C                                           NHI,NDOT)
C
C     ARGUMENTS
C
C     ON INPUT               Z
C     FOR EZCNTR               M by N array to be contoured.
C
C                            M
C                              First dimension of Z.
C
C                            N
C                              Second dimension of Z.
C
C     ON OUTPUT              All arguments are unchanged.
C     FOR EZCNTR
C
C     ON INPUT               Z
C     FOR CONREC               The (origin of the) array to be
C                              contoured.  Z is dimensioned L by N.
C
C                            L
C                              The first dimension of Z in the calling
C                              program.
C
C                            M
C                              The number of data values to be contoured
C                              in the X-direction (the first subscript
C                              direction).  When plotting an entire
C                              array, L = M.
C
C                            N
C                              The number of data values to be contoured
C                              in the Y-direction (the second subscript
C                              direction).
C
C                            FLO
C                              The value of the lowest contour level.
C                              If FLO = HI = 0., a value rounded up from
C                              the minimum Z is generated by CONREC.
C
C                            HI
C                              The value of the highest contour level.
C                              If HI = FLO = 0., a value rounded down
C                              from the maximum Z is generated by
C                              CONREC.
C
C                            FINC
C                              > 0  Increment between contour levels.
C                              = 0  A value, which produces between 10
C                                   and 30 contour levels at nice values,
C                                   is generated by CONREC.
C                              < 0  The number of levels generated by
C                                   CONREC is ABS(FINC).
C
C                            NSET
C                              Flag to control scaling.
C                              = 0  CONREC automatically sets the
C                                   window and viewport to properly
C                                   scale the frame to the standard
C                                   configuration.
C                                   The GRIDAL entry PERIM is
C                                   called and tick marks are placed
C                                   corresponding to the data points.
C                              > 0  CONREC assumes that the user
C                                   has set the window and viewport
C                                   in such a way as to properly
C                                   scale the plotting
C                                   instructions generated by CONREC.
C                                   PERIM is not called.
C                              < 0  CONREC generates coordinates so as
C                                   to place the (untransformed) contour
C                                   plot within the limits of the
C                                   user's current window and
C                                   viewport.  PERIM is not called.
C
C                            NHI
C                              Flag to control extra information on the
C                              contour plot.
C                              = 0  Highs and lows are marked with an H
C                                   or L as appropriate, and the value
C                                   of the high or low is plotted under
C                                   the symbol.
C                              > 0  The data values are plotted at
C                                   each Z point, with the center of
C                                   the string indicating the data
C                                   point location.
C                              < 0  Neither of the above.
C
C                            NDOT
C                              A 10-bit constant designating the desired
C                              dashed line pattern.
C                              If ABS(NDOT) = 0, 1, or 1023, solid lines
C                              are drawn.
C                              > 0 NDOT pattern is used for all lines.
C                              < 0 ABS(NDOT) pattern is used for nega-
C                                tive-valued contour lines, and solid is
C                                used for positive-valued contours.
C                                CONREC converts NDOT
C                                to a 16-bit pattern and DASHDB is used.
C                                See DASHDB comments in the DASHLINE
C                                documentation for details.
C
C
C
C     ON OUTPUT              All arguments are unchanged.
C     FOR CONREC
C
C
C     ENTRY POINTS           CONREC, CLGEN, REORD, STLINE, CRDRLN,
C                            MINMAX, PNTVAL, CALCNT, EZCNTR, CONBD
C
C     COMMON BLOCKS          INTPR, SPRINT, CONRE1, CONRE2, CONRE3,
C                            CONRE4,CONRE5
C
C     REQUIRED LIBRARY       GRIDAL, the ERPRT77 package and the SPPS.
C     ROUTINES               DASHSUPR is also needed.
C
C     REQUIRED GKS LEVEL     0A
C
C     NOTE FOR NCAR USERS    This routine is NOT part of the default
C                            libraries at NCAR.  CONRECSUPR must be
C                            be acquired, compiled and loaded to be
C                            used at NCAR.
C
C     I/O                    Plots contour map.
C
C     PRECISION              Single
C
C     LANGUAGE               FORTRAN 77
C
C     HISTORY
C
C     ALGORITHM              Each line is followed to completion.  Points
C                            along a line are found on boundaries of the
C                            (rectangular) cells. These points are
C                            connected by line segments using the
C                            software dashed line package, DASHSUPR.
C                            DASHSUPR is also used to label the
C                            lines.  In this version, a model of
C                            the plotting plane is maintained.  If a
C                            line to be drawn will overlap previously
C                            drawn lines, it is omitted.
C
C     NOTE                   To draw non-uniform contour levels, see
C                            the comments in CLGEN.  To make special
C                            modifications for specific needs see the
C                            explanation of the internal parameters
C                            below.
C
C     TIMING                 Varies widely with size and smoothness of
C                            Z.
C
C     INTERNAL PARAMETERS    NAME   DEFAULT         FUNCTION
C                            ----   -------         --------
C
C                            ISIZEL   1      Size of line labels,
C                                            as per the size definitions
C                                            given in the SPPS
C                                            documentation for WTSTR.
C
C                            ISIZEM   2      size of labels for minimums
C                                            and maximums as per the
C                                            size definitions given in
C                                            the SPPS documentation for
C                                            WTSTR.
C
C                            ISIZEP   0      Size of labels for data
C                                            point values as per the size
C                                            definitions given in the SPPS
C                                            documentation for WTSTR.
C
C                            NLA      16     Approximate number of
C                                            contour levels when
C                                            internally generated.
C
C                            NLM      40     Maximum number of contour
C                                            levels.  If this is to be
C                                            increased, the dimensions
C                                            of CL and RWORK in CONREC
C                                            must be increased by the
C                                            same amount.
C
C                            XLT      .05    Left hand edge of the plot
C                                            (0.0 is the left edge of
C                                            the frame and 1.0 is the
C                                            right edge of the frame.)
C
C                            YBT      .05    Bottom edge of the plot
C                                            (0.0 is the bottom of the
C                                            frame and 1.0 is the top
C                                            of the frame.)
C
C                            SIDE     0.9    Length of longer edge of
C                                            plot (see also EXT).
C
C                            NREP     6      Number of repetitions of
C                                            the dash pattern between
C                                            line labels.
C
C                            NCRT     4      Number of CRT units per
C                                            element (bit) in the dash
C                                            pattern.
C
C                            ILAB     1      Flag to control the drawing
C                                            of line labels.
C                                            . ILAB non-zero means label
C                                              the lines.
C                                            . ILAB = 0 means do not
C                                              label the lines.
C
C                            NULBLL   3      Number of unlabeled lines
C                                            between labeled lines.  For
C                                            example, when NULBLL = 3,
C                                            every fourth level is
C                                            labeled.
C
C                            IOFFD    0      Flag to control
C                                            normalization of label
C                                            numbers.
C                                            . IOFFD = 0 means include
C                                              decimal point when
C                                              possible (do not
C                                              normalize unless
C                                              required).
C                                            . IOFFD non-zero means
C                                              normalize all label
C                                              numbers and output a
C                                              scale factor in the
C                                              message below the graph.
C
C                            EXT      .25    Lengths of the sides of the
C                                            plot are proportional to M
C                                            and N (when CONREC sets
C                                            the window and viewport).
C                                            In extreme cases, when
C                                            MIN(M,N)/MAX(M,N) is less
C                                            than EXT, CONREC
C                                            produces a square plot.
C
C                            IOFFP      0    Flag to control special
C                                            value feature.
C                                            . IOFFP = 0 means special
C                                              value feature not in use.
C                                            . IOFFP non-zero means
C                                              special value feature in
C                                              use.  (SPVAL is set to the
C                                              special value.)  Contour
C                                              lines will then be
C                                              omitted from any cell
C                                              with any corner equal to
C                                              the special value.
C
C                            SPVAL    0.     Contains the special value
C                                            when IOFFP is non-zero.
C
C                            IOFFM    0      Flag to control the message
C                                            below the plot.
C                                            . IOFFM = 0  if the message
C                                              is to be plotted.
C                                            . IOFFM non-zero if the
C                                              message is to be omitted.
C
C                            ISOLID   1023   Dash pattern for
C                                            non-negative contour lines.
C
C                            IHILO    3      Flag to control labelling
C                                            of highs, lows, or both:
C                                            if NHI = 0 , then
C                                            . IHILO = 0 means do not
C                                              label highs nor lows
C                                            . IHILO = 1 means highs are
C                                              labelled, lows are not
C                                            . IHILO = 2 means lows are
C                                              labelled, highs are not
C                                            . IHILO = 3 means both
C                                              highs and lows are labelled
C
C
C
C
      EXTERNAL        CONBD
      SAVE
      CHARACTER*1     ISOL       ,IGAP       ,RCHAR
      CHARACTER       IWORK*126  ,ENCSCR*22
      DIMENSION       LNGTHS(5)  ,HOLD(5)
      DIMENSION       VIEW(4)    ,WIND(4)    ,LASF(13)    ,RECT(4)
      DIMENSION       Z(L,N)     ,CL(40)     ,RWORK(40)
      COMMON /INTPR/  IPD1       ,FPART      ,RPD1        ,IPD2       ,
     1                RPD2       ,IPD3       ,RPD3        ,RPD4       ,
     2                IPD4       ,IPD5
      COMMON /CONRE1/ IOFFP      ,SPVAL      ,IHILO
      COMMON /CONRE3/ IXBITS     ,IYBITS
      COMMON /CONRE5/ SCLY
      COMMON /SPRINT/ ISPRMJ     ,ISPRMN     ,ISPRTX
      DATA  LNGTHS /12,3,20,9,17/
      DATA ISIZEL,ISIZEM,ISIZEP,NLA,NLM,XLT,YBT,SIDE,ISOLID,NREP,NCRT/
     1       1,  2,   0, 16, 40,.05,.05,  .9,  1023,   6,   4/
      DATA EXT,IOFFD,NULBLL,IOFFM,ILAB/.25,0,3,0,1/
      DATA  ISOL, IGAP /'$', ''''/
C
C
C
C
C THE FOLLOWING CALL IS FOR GATHERING STATISTICS ON LIBRARY USE AT NCAR
C
      CALL Q8QST4 ( 'GRAPHX', 'CONRECSUPR', 'CONREC', 'VERSION 01')
C
C SUPER VERSION
C
      CALL RESET
      IXBITS = 0
      DO 101 I=1,24
         IF (M .LE. (2**I-1)) GO TO 102
         IXBITS = I+1
  101 CONTINUE
  102 IYBITS = 0
      DO 103 I=1,24
         IF (N .LE. (2**I-1)) GO TO 104
         IYBITS = I+1
  103 CONTINUE
  104 IF ((IXBITS*IYBITS).GT.0 .AND. (IXBITS+IYBITS).LE.24) GO TO 105
C
C REPORT ERROR NUMBER ONE
C
      IWORK =    'CONREC  - DIMENSION ERROR - M*N .GT. (2**IARTH) -  M =
     +            N = '
      WRITE (IWORK(56:62),'(I6)') M
      WRITE (IWORK(73:79),'(I6)') N
      CALL SETER (IWORK,1,1)
      RETURN
  105 CONTINUE
C
C INQUIRE CURRENT TEXT AND LINE COLOR INDEX
C
      CALL GQTXCI (IERR, ITXCI)
      CALL GQPLCI (IERR, IPLCI)
C
C SET LINE AND TEXT ASF TO INDIVIDUAL
C
      CALL GQASF (IERR, LASF)
      LSV3  = LASF(3)
      LSV10 = LASF(10)
      LASF(3)  = 1
      LASF(10) = 1
      CALL GSASF (LASF)
C
      GL = FLO
      HA = HI
      GP = FINC
      MX = L
      NX = M
      NY = N
      IDASH = NDOT
      NEGPOS = SIGN(1,IDASH)
      IDASH = ABS(IDASH)
      IF (IDASH.EQ.0 .OR. IDASH.EQ.1) IDASH = ISOLID
C
C SET CONTOUR LEVELS.
C
      CALL CLGEN (Z,MX,NX,NY,GL,HA,GP,NLA,NLM,CL,NCL,ICNST)
C
C FIND MAJOR AND MINOR LINES
C
      IF (ILAB .NE. 0) CALL REORD (CL,NCL,RWORK,NML,NULBLL+1)
      IF (ILAB .EQ. 0) NML = 0
C
C Save the current SET parameters.
C
      CALL GETSET (VIEW(1),VIEW(2),VIEW(3),VIEW(4),
     +             WIND(1),WIND(2),WIND(3),WIND(4),IOLLS)
C
C SET UP SCALING
C
      CALL GETUSV ('YF',IYVAL)
      SCLY = 1.0/ISHIFT(1,15-IYVAL)
C
      IF (NSET) 106,107,111
C
  106 X1 = VIEW(1)
      X2 = VIEW(2)
      Y1 = VIEW(3)
      Y2 = VIEW(4)
C
C
C
C
C
C DEFINE NORMALIZATION TRANS AND LOG SCALING
C
      CALL SET(X1,X2,Y1,Y2,1.0,REAL(NX),1.0,REAL(NY),1)
      GO TO 111
  107 X1 = XLT
      X2 = XLT+SIDE
      Y1 = YBT
      Y2 = YBT+SIDE
      X3 = NX
      Y3 = NY
      IF (MIN(X3,Y3)/MAX(X3,Y3) .LT. EXT) GO TO 110
      IF (NX-NY) 108,110,109
  108 X2 = SIDE*X3/Y3+XLT
      GO TO 110
  109 Y2 = SIDE*Y3/X3+YBT
C
C
C
C
C
C DEFINE NORMALIZATION TRANS 1 AND LOG SCALING
C
  110 CALL SET(X1,X2,Y1,Y2,1.0,X3,1.0,Y3,1)
C
C DRAW PERIMETER
C
      CALL PERIM (NX-1,1,NY-1,1)
  111 IF (ICNST .NE. 0) GO TO 124
C
C SET UP LABEL SCALING
C
      IOFFDT = IOFFD
      IF (GL.NE.0.0 .AND. (ABS(GL).LT.0.1 .OR. ABS(GL).GE.1.E5))
     1    IOFFDT = 1
      IF (HA.NE.0.0 .AND. (ABS(HA).LT.0.1 .OR. ABS(HA).GE.1.E5))
     1    IOFFDT = 1
      ASH = 10.**(3-INT(ALOG10(MAX(ABS(GL),ABS(HA),ABS(GP)))
     1                                                  -4999.999)-5000)
      IF (IOFFDT .EQ. 0) ASH = 1.
      IF (IOFFM .NE. 0) GO TO 115
      IWORK = 'CONTOUR FROM              TO              CONTOUR INTERVA
     +L OF              PT(3,3)=              LABELS SCALED BY'
  112 CONTINUE
      HOLD(1) = GL
      HOLD(2) = HA
      HOLD(3) = GP
      HOLD(4) = Z(3,3)
      HOLD(5) = ASH
      NCHAR = 0
      DO 114 I=1,5
         WRITE ( ENCSCR, '(G13.5)' ) HOLD(I)
         NCHAR = NCHAR+LNGTHS(I)
         DO 113 J=1,13
            NCHAR = NCHAR+1
            IWORK(NCHAR:NCHAR) = ENCSCR(J:J)
  113    CONTINUE
  114 CONTINUE
      IF (ASH .EQ. 1) NCHAR = NCHAR-13-LNGTHS(5)
C
C SET TEXT INTENSITY TO LOW, AND WRITE TITLE
C
      CALL GSTXCI (ISPRTX)
C
      CALL GQCLIP (IERR,ICLP,RECT)
      CALL GSCLIP (0)
      CALL WTSTR (CFUX(.5),CFUY(.015625),IWORK(1:NCHAR),0,0,0)
      CALL GSCLIP (ICLP)
C
C
C FIND RELATIVE MINIMUMS AND MAXIMUMS IF WANTED, AND MARK VALUES IF
C WANTED.
C
  115 IF (NHI .EQ. 0) CALL MINMAX (Z,MX,NX,NY,ISIZEM,ASH,IOFFDT)
      IF (NHI .GT. 0) CALL MINMAX (Z,MX,NX,NY,ISIZEP,-ASH,IOFFDT)
C
C PROCESS EACH LEVEL
C
      FPART = .5
      DO 123 I=1,NCL
         CONTR = CL(I)
         NDASH = IDASH
         IF (NEGPOS.LT.0 .AND. CONTR.GE.0.) NDASH = ISOLID
C
C CHANGE 10 BIT PATTERN TO 10 CHARACTER PATTERN.
C
         DO 116 J=1,10
            IBIT = IAND(ISHIFT(NDASH,(J-10)),1)
            RCHAR = IGAP
            IF (IBIT .NE. 0) RCHAR = ISOL
            IWORK(J:J) = RCHAR
  116    CONTINUE
         IF (I .GT. NML) GO TO 121
C
C SET UP MAJOR LINE (LABELED)
C
C
C NREP REPITITIONS OF PATTERN PER LABEL.
C
         NCHAR = 10
         IF (NREP .LT. 2) GO TO 119
         DO 118 J=1,10
            NCHAR = J
            RCHAR = IWORK(J:J)
            DO 117 K=2,NREP
               NCHAR = NCHAR+10
               IWORK(NCHAR:NCHAR) = RCHAR
  117       CONTINUE
  118    CONTINUE
  119    CONTINUE
C
C PUT IN LABEL.
C
         CALL ENCD (CONTR,ASH,ENCSCR,NCUSED,IOFFDT)
         DO 120 J=1,NCUSED
            NCHAR = NCHAR+1
            IWORK(NCHAR:NCHAR) = ENCSCR(J:J)
  120    CONTINUE
         GO TO 122
C
C SET UP MINOR LINE (UNLABELED).
C
  121    CONTINUE
C
C SET LINE INTENSITY TO LOW
C
         CALL GSPLCI (ISPRMN)
         NCHAR = 10
  122    CALL DASHDC (IWORK(1:NCHAR),NCRT,ISIZEL)
C
C
C DRAW ALL LINES AT THIS LEVEL.
C
         CALL STLINE (Z,MX,NX,NY,CONTR)
C
C SET LINE INTENSITY TO HIGH
C
         CALL GSPLCI (ISPRMJ)
C
C                       * * * * * * * * * *
C                       * * * * * * * * * *
C
C
  123 CONTINUE
      FPART = 1.
      GO TO 127
  124 CONTINUE
         IWORK = 'CONSTANT FIELD'
  125 CONTINUE
      WRITE ( ENCSCR, '(G22.14)' ) GL
      DO 126 I=1,22
         IWORK(I+14:I+14) = ENCSCR(I:I)
  126 CONTINUE
C
C WRITE TITLE
C
      CALL GQCLIP (IERR,ICLP,RECT)
      CALL GSCLIP (0)
      CALL WTSTR (CFUX(.09765),CFUY(.48825),IWORK(1:36),3,0,-1)
      CALL GSCLIP (ICLP)
  127 CONTINUE
C
C RESTORE NORMALIZATION TRANS 1, LINE AND TEXT INTENSITY TO ORIGINAL
C VALUES
C
      IF (NSET.LE.0)
     +    CALL SET(VIEW(1),VIEW(2),VIEW(3),VIEW(4),
     +             WIND(1),WIND(2),WIND(3),WIND(4),IOLLS)
C
      CALL GSTXCI (ITXCI)
      CALL GSPLCI (IPLCI)
C
C Restore the original aspect source flags.
C
C
      LASF(3)  = LSV3
      LASF(10) = LSV10
      CALL GSASF (LASF)
      RETURN
C
C
      END
