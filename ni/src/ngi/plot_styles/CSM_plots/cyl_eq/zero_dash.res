*ndvPlotStyleName : b/w with dashed lines below zero
*ndvPlotName      : bw_ce
*ndvData          : (/ cndata : 2 /)
*ndvFuncFiles     : (/ ../csm_utils.ncl /)

;
; Define the objects we created.
;
*ndvObjects : (/ \
  sf             : scalarFieldClass, \
  contour        : contourPlotClass, \
  map            : mapPlotClass, \
  tickmark       : logLinPlotClass, \
  left_title     : textItemClass, \
  center_title   : textItemClass, \
  right_title    : textItemClass \
/)   

;
; Describe the data.
;
*cndata@Pattern     : (/ /.*T.*/i , /.*/ /)
*cndata!-1@Pattern  : /.*lon.*/i
*cndata!-2@Pattern  : /.*lat.*/i
*cndata@Description : contour data
*cndata@Required    : True

;
; Scalar field setup.
;
*sf@sfDataArray         : FixLongitude($cndata$)
*sf@sfDataArray%Profile : (/ Name : Primary Data Var /)
*sf@sfXArray            : FixLongitudeCoord($cndata$&-1)
*sf@sfXArray%Profile    : (/ Name : Longitude /)
*sf@sfYArray            : $cndata$&-2
*sf@sfYArray%Profile    : (/ Name : Latitude /)

;
; map resources
;
*map@pmOverlays     : (/ $contour$, $tickmark$ /)
*map@pmAnnoViews    : (/ $left_title$, $center_title$, $right_title$ /)
*map@ndvUpdateFunc  : SetColormap($map$,"hlu_default")
*map@ndvUpdateFunc%Profile : (/ InitializeOnly : True, Name : Set Colormap /)
*map@ndvUpdateFunc2 : SetMapFillColors($map$,"white","transparent", \
                                  "lightgray","transparent")
*map@ndvUpdateFunc2%Profile : (/ Name : Set Map Fill Colors /)
*map@ndvUpdateFunc3 : PlotTitles($map$, $left_title$, $cndata$@long_name,\
                                         $center_title$, "", \
                                         $right_title$, $cndata$@units, \
                                         0.014,1)
*map@ndvUpdateFunc3%Profile : (/ Name : Plot Titles /)

*map*mpFillOn         : True
*map*mpPerimOn        : True
*map*mpOutlineOn      : False
*map*mpFillColors     : (/white,transparent,lightgray,transparent,transparent/)
*map*mpGridAndLimbOn  : False

;
; map tickmark resources
;
*tickmark@ndvUpdateFunc         : MapTickmarks($map$,$tickmark$)
*tickmark*tfDoNDCOverlay        : True
*tickmark*pmTickMarkDisplayMode : always
*tickmark*amZone                : 0
*tickmark*amResizeNotify        : True

;
; contour resources
;
*contour@cnScalarFieldData          : $sf$
*contour*cnLineLabelBackgroundColor : transparent
*contour@ndvUpdateFunc              : SetContourLevels($contour$,0.,0.,0.)
*contour@ndvUpdateFunc%Profile : (/ Name : Contour Level Control /)
*contour@ndvUpdateFunc2             : SetContourLevelThickness($contour$,0.,2.)
*contour@ndvUpdateFunc2%Profile : (/ Name : Contour Level Thickness /)
*contour@ndvUpdateFunc3             : LtGtContourDashPattern($contour$,0.,1,\
                                                                       0.,-1)
*contour@ndvUpdateFunc3%Profile : (/ Name : Contour Dash Patterns /)
;
; Title resources
;
*left_title*amZone             : 3
*left_title*amSide             : Top
*left_title*amParallelPosF     : 0.0
*left_title*amOrthogonalPosF   : 0.05
*left_title*amJust             : BottomLeft
*left_title*amResizeNotify     : True

*center_title*amZone           : 3
*center_title*amSide           : Top
*center_title*amParallelPosF   : 0.5
*center_title*amOrthogonalPosF : 0.05
*center_title*amJust           : BottomCenter
*center_title*amResizeNotify   : True

*right_title*amZone            : 3
*right_title*amSide            : Top
*right_title*amParallelPosF    : 1.0
*right_title*amOrthogonalPosF  : 0.05
*right_title*amJust            : BottomRight
*right_title*amResizeNotify    : True

;
; Other resources.
;
*vpXF                 : 0.1
*vpWidthF             : 0.85
*vpUseSegments        : True
*MaxLevelCount        : 20
*Font                 : helvetica-bold
*TextFuncCode         : ~
