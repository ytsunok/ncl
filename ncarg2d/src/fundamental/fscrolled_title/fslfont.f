C
C OPEN GKS, OPEN WORKSTATION OF TYPE 1, ACTIVATE WORKSTATION
C
      CALL GOPKS (6,IDUM) 
      CALL GOPWK (1, 2, 1)
      CALL GACWK (1) 
C
C INVOKE DEMO DRIVER
C
      CALL SLFONT(IERR)
C
C     DEACTIVATE AND CLOSE WORKSTATION, CLOSE GKS.
C
      CALL GDAWK (1)
      CALL GCLWK (1)
      CALL GCLKS
      STOP
      END
      SUBROUTINE SLFONT (IERROR)
C
C PURPOSE                To provide a simple demonstration of the
C                        routine SLFONT.
C
C USAGE                  CALL SLFONT (IERROR)
C
C ARGUMENTS
C
C ON OUTPUT              IERROR
C                          An integer variable
C                            = 0  If there is a normal exit from SLFONT
C                            = 1  Otherwise
C
C I/O                    If there is a normal exit from SLFONT,
C                        the message
C
C                          SLFONT TEST SUCCESSFUL . . . SEE PLOTS TO
C                          VERIFY PERFORMANCE
C
C                        is written on unit 6
C
C PRECISION              SINGLE
C
C REQUIRED LIBRARY       SLFONT
C FILES
C
C LANGUAGE               FORTRAN
C
C HISTORY                Written  by members of the
C                        Scientific Computing Division of NCAR,
C                        Boulder Colorado
C
C PORTABILITY            FORTRAN 77
C
C
      CHARACTER*80    CARDS(6)
C
C Initialize the error parameter.
C
      IERROR = 1
C
C Store character strings in array CARDS.  These strings contain text,
C plus information regarding character size and location of the text
C on the scroll.
C
      NCARDS = 4
      CARDS(1) = '  512  760    1  1.5Demonstration'
      CARDS(2) = '  512  600    1  1.5Plot'
      CARDS(3) = '  512  440    1  1.0for'
      CARDS(4) = '  512  280    1  1.5SLFONT'
C
C Employ the new high quality filled fonts in PLOTCHAR
C
      CALL PCSETC('FN','times-roman')
C
C Define the remaining inputs to routine SLFONT.  Note that the
C output produced (a single frame with no scrolling to appear for
C 6.0 seconds) could equally well have been produced by FTITLE.
C We call SLFONT in this demo to avoid reading the input lines.
C
      NYST  = 512
      NYFIN = 512
      TST   = 0.0
      TMV   = 0.0
      TFIN  = 6.0
      MOVIE =   1
C
C Call SLFONT.
C
      CALL SLFONT (CARDS,NCARDS,NYST,NYFIN,TST,TMV,TFIN,MOVIE)
      IERROR = 0
      WRITE (6,1001)
      RETURN
C
 1001 FORMAT ('     SLFONT TEST SUCCESSFUL',24X,
     1        'SEE PLOTS TO VERIFY PERFORMANCE')
C
      END
