C NCLFORTSTART
      SUBROUTINE dgeevxint(BALANC,JOBVL,JOBVR,SENSE,N,A,EVLR,WR,WI,OPT)
      IMPLICIT NONE
c                                                      input
      INTEGER           N, OPT
      CHARACTER*(*)     BALANC, JOBVL, JOBVR, SENSE
ccccc CHARACTER*1       BALANC, JOBVL, JOBVR, SENSE
c                                                      input and output
      DOUBLE PRECISION  A(N,N)
c                                                      output
c                                                      (:,:,real/imag,left/right)     
      DOUBLE PRECISION  WR(N), WI(N), EVLR(N,N,2,2)
C NCLEND
C --------------------------------------------------------------------------------
C                                                      local dynamically allocated
      INTEGER LDA, ILO, IHI, INFO, I, J
     +      , LDVR, LDVL, LWORK, LIWORK, K , KP1
      DOUBLE PRECISION SCALEM(N), RCONDE(N), RCONDV(N)
      DOUBLE PRECISION ABNRM,  WORK(N*(N+6))
      INTEGER          IWORK(2*N-1)

c local: these will returned within the EVLR(N,N,2,2) array

      DOUBLE PRECISION VL(N,N), VR(N,N)

C just for consistency with LAPACK description   (make large)
      LDA     = N
      LDVR    = N
      LDVL    = N
      INFO    = 0   
      LWORK   = N*(N+6)
      LIWORK  = 2*N-1

      CALL DGEEVX( BALANC, JOBVL, JOBVR, SENSE, N, A, LDA, WR, WI,  
     &             VL, LDVL, VR, LDVR, ILO, IHI, SCALEM, ABNRM,
     &             RCONDE, RCONDV, WORK, LWORK, IWORK, INFO )

c
c This is the array returned to NCL | the WR & WI as attributes.
c
      k = 0
      do j=1,N 
         k = k+1
         if (wi(j).eq.0.0d0) then     !   not a complex conjugate
             do i=1,N
                EVLR(i,k,1,1) = VL(i,j) 
                EVLR(i,k,2,1) = 0.0d0   
                EVLR(i,k,1,2) = VR(i,j)
                EVLR(i,k,2,2) = 0.0d0  
             end do
         else if (WR(J).eq.WR(J+1) .and. WI(J).eq.-WI(J+1)) then  ! conjugate
              kp1 = k+1
              do i=1,N
                 EVLR(i,k  ,1,1) = VL(i,j)
                 EVLR(i,k  ,2,1) = VL(i,j+1) 
                 EVLR(i,k  ,1,2) = VR(i,j)
                 EVLR(i,k  ,2,2) = VR(i,j+1)

                 EVLR(i,kp1,1,1) = VL(i,j)
                 EVLR(i,kp1,2,1) = -VL(i,j+1)
                 EVLR(i,kp1,1,2) = VR(i,j)
                 EVLR(i,kp1,2,2) = -VR(i,j+1)
              end do
              k = kp1-1
         end if
      end do

      return
      end


