C
C $Id: ctranf.f,v 1.2 2004-03-19 22:51:57 kennison Exp $
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
      FUNCTION CTRANF ()
C
C This function generates a sequence of "random" numbers.  Obviously,
C it repeats after the 100th such number.  This is not very important,
C because of the way in which these numbers are being used.
C
      DIMENSION RSEQ (100)
      SAVE ISEQ
      DATA RSEQ / .749,.973,.666,.804,.081,.483,.919,.903,.951,.960 ,
     +            .039,.269,.270,.756,.222,.478,.621,.063,.550,.798 ,
     +            .027,.569,.149,.697,.451,.738,.508,.041,.266,.249 ,
     +            .019,.191,.266,.625,.492,.940,.508,.406,.972,.311 ,
     +            .757,.378,.299,.536,.619,.844,.342,.295,.447,.499 ,
     +            .688,.193,.225,.520,.954,.749,.997,.693,.217,.273 ,
     +            .961,.948,.902,.104,.495,.257,.524,.100,.492,.347 ,
     +            .981,.019,.225,.806,.678,.710,.235,.600,.994,.758 ,
     +            .682,.373,.009,.469,.203,.730,.588,.603,.213,.495 ,
     +            .884,.032,.185,.127,.010,.180,.689,.354,.372,.429 /
      DATA ISEQ / 0 /
      ISEQ=MOD(ISEQ,100)+1
      CTRANF=RSEQ(ISEQ)
      RETURN
      END
