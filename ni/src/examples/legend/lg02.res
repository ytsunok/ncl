!
! Example:  This resource file shows all Legend resources and
!           their default values.
!
!  ==============================================================
!  The following resources relate to the viewport on the drawing
!  canvas.
!  ==============================================================
!
!       Height in NDC (0. to 1.) of the viewport
! *lg02Work.Legend.vpHeightF                   : 0.8
!
!       Switch to allow the plot X to Y aspect ratio to remain fixed
!       when resizing or moving the object.
! *lg02Work.Legend.vpKeepAspect                : False
!
!       Save this graphical object as a GKS segment
! *lg02Work.Legend.vpUseSegments               : False
!
!       Width in NDC (0. to 1.) of the viewport
! *lg02Work.Legend.vpWidthF                    : 0.8
!
!       NDC (0. to 1.) X location of the upper left corner of the plot
! *lg02Work.Legend.vpXF                        : 0.1
!
!       NDC (0. to 1.) Y location of the upper left corner of the plot
! *lg02Work.Legend.vpYF                        : 0.9
!
! ----------------------
! THE COMPOSITE LEGEND
! ----------------------
!
!       Switch to turn on/off drawing of the legend
! *lg02Work.Legend.lgLegend              : True
!
!       Is title and label sizing to be done automatically
! *lg02Work.Legend.lgAutoManage          : True
!
!       Should the legend be HORIZONTAL or VERTICAL
! *lg02Work.Legend.lgOrientation         : VERTICAL
!
!   When the legend changes size the justification determines
!   a fixed point about which the size change occurs. Any of the
!   corners, the center of any edge, or the current center of the
!   Legend may be set to the fixed justification point.
!
!       TOPLEFT
!       CENTERLEFT
!       BOTTOMLEFT
!       TOPCENTER
!       CENTERCENTER
!       BOTTOMCENTER
!       TOPRIGHT
!       CENTERRIGHT
!       BOTTOMRIGHT
! *lg02Work.Legend.lgJustification       : BOTTOMLEFT
!
!       Distance from Legend perimeter to the Legend information
!       as a fraction of the smaller perim dimension.
! *lg02Work.Legend.lgLeftMarginF         : .05
!
!       Distance from Legend perimeter to the Legend information
!       as a fraction of the smaller perim dimension.
! *lg02Work.Legend.lgRightMarginF        : .05
!
!       Distance from Legend perimeter to the Legend information
!       as a fraction of the smaller perim dimension.
! *lg02Work.Legend.lgBottomMarginF       : .05
!
!       Distance from Legend perimeter to the Legend information
!       as a fraction of the smaller perim dimension.
! *lg02Work.Legend.lgTopMarginF          : .05
!
! ------------------
! THE LEGEND TITLE
! ------------------
!
!       Draw the legend title (default is True)
! *lg02Work.Legend.lgDrawTitle           : 1
!
!       If a string is set DrawTitle defaults to True.  Else
!       DrawTitle defaults to False.  If DrawTitle is set to
!       True, but no string is entered into TitleString, then
!       a title consisting of the name of the current instantiation
!       of the object is inserted into TitleString.
!
*lg02Work.Legend.lgTitleString          : A Marker Type Legend
!
!       Determines where the title goes relative to the legend object.
!       Options are TOP, BOTTOM, LEFT, and RIGHT.
! *lg02Work.Legend.lgTitlePosition        : TOP
!
!       Determines the NDC distance between the title and the label/box info.
! *lg02Work.Legend.lgTitleOffsetF         : .03
!
!       NDC extent allocated for the title when AutoManage is on.
! *lg02Work.Legend.lgMaxTitleExtentF      : .15
!
!       Rotation angle of the title
! *lg02Work.Legend.lgTitleAngleF          : 0.
!
!       Direction the title is to be drawn
!       Defaults to ACROSS when TitlePosition = TOP or BOTTOM
!       Defaults to DOWN when TitlePosition = LEFT or RIGHT
! *lg02Work.Legend.lgTitleDirection       : ACROSS
!
!       How the title text is justified within the text bounding box
!       TOPLEFT
!       CENTERLEFT
!       BOTTOMLEFT
!       TOPCENTER
!       CENTERCENTER
!       BOTTOMCENTER
!       TOPRIGHT
!       CENTERRIGHT
!       BOTTOMRIGHT
! *lg02Work.Legend.lgTitleJust           : CENTERCENTER
!
!       The type of character font where the options include:
! |-------------------------------------------------------|
! | INDEX | TYPE          | NAME                          |
! |=======================================================|
! |  0    | stroked       | pwritx_database               |
! |-------------------------------------------------------|
! |  1    | stroked       | default                       |
! |-------------------------------------------------------|
! |  2    | stroked       | cartographic_roman            |
! |-------------------------------------------------------|
! |  3    | stroked       | cartographic_greek            |
! |-------------------------------------------------------|
! |  4    | stroked       | simplex_roman                 |
! |-------------------------------------------------------|
! |  5    | stroked       | simplex_greek                 |
! |-------------------------------------------------------|
! |  6    | stroked       | simplex_script                |
! |-------------------------------------------------------|
! |  7    | stroked       | complex_roman                 |
! |-------------------------------------------------------|
! |  8    | stroked       | complex_greek                 |
! |-------------------------------------------------------|
! |  9    | stroked       | complex_script                |
! |-------------------------------------------------------|
! | 10    | stroked       | complex_italic                |
! |-------------------------------------------------------|
! | 11    | stroked       | complex_cyrillic              |
! |-------------------------------------------------------|
! | 12    | stroked       | duplex_roman                  |
! |-------------------------------------------------------|
! | 13    | stroked       | triplex_roman                 |
! |-------------------------------------------------------|
! | 14    | stroked       | triplex_italic                |
! |-------------------------------------------------------|
! | 15    | stroked       | gothic_german                 |
! |-------------------------------------------------------|
! | 16    | stroked       | gothic_english                |
! |-------------------------------------------------------|
! | 17    | stroked       | gothic_italian                |
! |-------------------------------------------------------|
! | 18    | stroked       | math_symbols                  |
! |-------------------------------------------------------|
! | 19    | stroked       | symbol_set1                   |
! |-------------------------------------------------------|
! | 20    | stroked       | symbol_set2                   |
! |-------------------------------------------------------|
! | 21    | filled        | helvetica                     |
! |-------------------------------------------------------|
! | 22    | filled        | helvetica-bold                |
! |-------------------------------------------------------|
! | 25    | filled        | times-roman                   |
! |-------------------------------------------------------|
! | 26    | filled        | times-bold                    |
! |-------------------------------------------------------|
! | 29    | filled        | courier                       |
! |-------------------------------------------------------|
! | 30    | filled        | courier-bold                  |
! |-------------------------------------------------------|
! | 33    | filled        | greek                         |
! |-------------------------------------------------------|
! | 34    | filled        | math-symbols                  |
! |-------------------------------------------------------|
! | 35    | filled        | text-symbols                  |
! |-------------------------------------------------------|
! | 36    | filled        | weather1                      |
! |-------------------------------------------------------|
! | 37    | filled        | weather2                      |
! +-------------------------------------------------------+
! The default pwritx_database font contains many characters
! (564) which can be accessed using the FuncCode resource.
!
*lg02Work.Legend.lgTitleFont            : 25
!
!     Color indices are taken from the default HLU colormap.  Choices are:
!
!     Index   Color     Index   Color    Index  Color       Index   Color
!
!       1-4   white      5-18  yellows   19-21  tans        22-24   oranges
!     29-32   magentas     34  lavender  40-50  reds           57   gray
!     60-66   cyans     70-80  greens    81-90  dark grns  91-100   blues
!   106-114   blacks
!
*lg02Work.Legend.lgTitleFontColor       : 10
!
!       The character height in NDCs of the text to be written
*lg02Work.Legend.lgTitleFontHeightF     : .050
!
!       The height/width aspect ratio of the text to be written
! *lg02Work.Legend.lgTitleFontAspectF     : 1.0
!
!       The width of the lines that form the text outline
*lg02Work.Legend.lgTitleFontThicknessF  : 3.0
!
!       The degree of quality of the text to be written (LOW,MEDIUM,HIGH)
! *lg02Work.Legend.lgTitleFontQuality     : HIGH
!
!       The spacing between characters of the text to be written
! *lg02Work.Legend.lgTitleConstantSpacingF: 0.0
!
!       A process for accessing the many characters of the default
!       pwritx font.
! *lg02Work.Legend.lgTitleFuncCode        : :
!
!
! ------------------
! THE LEGEND PERIM
! ------------------
!
!       Draw the legend perim   (0 is off, 1 is on)
! *lg02Work.Legend.lgDrawPerim           : 1
!
!       Color of the legend perim
! *lg02Work.Legend.lgPerimColor          : FOREGROUND
!
!       Fill sytle of the legend perim
! *lg02Work.Legend.lgPerimFill           : FOREGROUND
!
!       Fill color of the legend perim
! *lg02Work.Legend.lgPerimFillColor      : FOREGROUND
!
!       Width of the legend perim
! *lg02Work.Legend.lgPerimThicknessF     : 1.0
!
!       Dash pattern of the legend perim
! *lg02Work.Legend.lgPerimDashPattern    : 0
!
!       Length of dash segments of the legend perim
! *lg02Work.Legend.lgPerimDashSegLenF    : 0.15
!
! ------------------------
! THE LEGEND ITEM BOXES
! ------------------------
!
!   The color index used for the background of all the boxes in
!   the Legend when the fill type is not solid.
! *lg02Work.Legend.lgBoxBackground       : TRANSPARENT
!
!       A relative box width.  0. = no width, 1. = touching boxes
! *lg02Work.Legend.lgBoxMajorExtentF     : 1.0
!
!       A relative box length in a box + label pair.
!       If set to 1.0 it crowds out the label.
! *lg02Work.Legend.lgBoxMinorExtentF     : 0.33
!
!       Draw the box perimeters  (0 is off, 1 is on)
! *lg02Work.Legend.lgDrawBoxLines        : 0
!
!       Color of the box perimeter
! *lg02Work.Legend.lgBoxLineColor          : FOREGROUND
!
!       Width of the box perimeter
! *lg02Work.Legend.lgBoxLineThicknessF     : 1.0
!
!       Dash pattern of the box perimeter
! *lg02Work.Legend.lgBoxLineDashPattern    : 0
!
!       Length of dash segments of the box perimeter
! *lg02Work.Legend.lgBoxLineDashSegLenF    : 0.15
!
! ------------------------
! THE LEGEND ITEM LABELS
! ------------------------
!
!       Quick switch for turning labels on/off  (default is on)
! *lg02Work.Legend.lgDrawLabels              : 1
!
!       Determines the position of the labels with respect to the
!  Legend boxes.  If orientation is HORIZONTAL valid values are TOP,
!  CENTER, or BOTTOM.  If the orientation is VERTICAL valid values are
!  LEFT, CENTER, and RIGHT.
! *lg02Work.Legend.lgLabelPosition           : RIGHT
!
!       Angle at which the scale labels are drawn
! *lg02Work.Legend.lgLabelAngleF             : 0.0
!
!  LabelAlignment determines the alignment of the labels to the boxes.
!       BOXCENTERS    - BoxCount labels centered at the boxes.
!       INTERIOREDGES - BoxCount-1 labels starting at the bottom of box 1.
!       EXTERNALEDGES - BoxCount+1 labels starting at the top of box 1.
! *lg02Work.Legend.lgLabelAlignment          : BOXCENTERS
!
!       Direction in which scale labels are drawn (UP,DOWN,ACROSS)
!       Normal direction is across for all axes.
! *lg02Work.Legend.lgLabelDirection          : ACROSS
!
!       How label text is justified in a text extent rectangle
! *lg02Work.Legend.lgLabelJust               : CENTERCENTER
!
!       The font style to use for labels
*lg02Work.Legend.lgLabelFont               : 25
!
!       The color for label text
! *lg02Work.Legend.lgLabelFontColor          : FOREGROUND
!
!       The NDC (0. to 1.) height of the label text
! *lg02Work.Legend.lgLabelFontHeightF        : .02
!
!       The height to width aspect ratio of label characters
! *lg02Work.Legend.lgLabelFontAspectF        : 1.0
!
!       The width of the lines that form the text outline
! *lg02Work.Legend.lgLabelFontThicknessF      : 1.0
!
!       The degree of quality of the text to be written (LOW,MEDIUM,HIGH)
! *lg02Work.Legend.lgLabelFontQuality         : HIGH
!
!       The spacing between characters of the text to be written
! *lg02Work.Legend.lgLabelConstantSpacingF    : 0.0
!
!       A process for accessing the many characters of the default
!       pwritx font.
! *lg02Work.Legend.lgLabelFuncCode            : :
!
!       The stride between labeled bars
! *lg02Work.Legend.lgLabelStride             : 1
!
!       Fractional distance between the box and the label
! *lg02Work.Legend.lgLabelOffsetF            : 0.
!
!       An array of label strings
! *lg02Work.Legend.lgLabelStrings            : Label_
!
! ----------------
! THE LEGEND ITEMS
! ----------------
!
!       An array containing an index value for each Legend item.
!       The meaning of the index depends on the ItemType:
!       If the type is NhllgLINES, then a dash pattern.
!       Else it is a marker index.
! *lg02Work.Legend.lgItemIndexes            : 1 to ItemCount
!
!       Number of items in the Legend.
*lg02Work.Legend.lgItemCount              : 5
!
!       Items can be uniformly spaced or explicitly placed
!       using UNIFORMPLACEMENT or EXPLICITPLACEMENT.
! *lg02Work.Legend.lgItemPlacement          : UNIFORMPLACEMENT
!
!       When ItemPlacement is EXPLICITPLACEMENT the positions are a
!        monotonically increasing sequence in the range 0.0 to 1.0
! *lg02Work.Legend.lgItemPositions          : NULL
!
!       Used with ItemIndexes and ItemType to define lines or markers.
! *lg02Work.Legend.lgItemStrings            : NULL
!
!       Items are set to either LINES or Markers, whichever is
!       the first element of the ItemTypes array.
! *lg02Work.Legend.lgMonoItemType           : True
!
!       Not implemented yet
! *lg02Work.Legend.lgItemType               :
!
!       Currently either LINES or MARKERS.
! *lg02Work.Legend.lgItemTypes              : NULL
!
!       When set True, all items in the Legend are set to a single
!       color defined by the value of the first element of array
!       ItemColors.
! *lg02Work.Legend.lgMonoItemColor          : False
!
!       ItemColor has not been implemented yet
! *lg02Work.Legend.lgItemColor              :
!
!       Each item is assigned a color index
! *lg02Work.Legend.lgItemColors             : 1 to ItemCount
!
!       When set True, all items in the Legend are given a line
!       thickness equal to that specified in the first element
!       of array ItemThicknesses.
! *lg02Work.Legend.lgMonoItemThickness      : True
!
!       ItemThickness has not been implemented yet
! *lg02Work.Legend.lgItemThickness          :
!
!       Each item is assigned a line or glyph thickness.
! *lg02Work.Legend.lgItemThicknesses        : NULL
!
!       When set True, all items in the Legend are given a line
!       label or glyph height equal to that specified in the first
!       element of array ItemTextHeights.
! *lg02Work.Legend.lgMonoItemTextHeight     : True
!
!       ItemTextHeight has not been implemented yet
! *lg02Work.Legend.lgItemTextHeight         :
!
!       Each item is assigned a line label or glyph height in NDCs.
! *lg02Work.Legend.lgItemTextHeights        : NULL
!
!       When set True, all items are given a single color which is
!       in element one of array ItemStringColors.
! *lg02Work.Legend.lgMonoItemStringColor     : True
!
!       ItemStringColor has not been implemented yet
! *lg02Work.Legend.lgItemStringColor         :
!
!       Each item is assigned a color index of the HLU color table.
! *lg02Work.Legend.lgItemStringColors        : NULL
!
!       A boolean flag determining whether to draw internal line
!       labels within Legend line items.
! *lg02Work.Legend.lgDrawLineLabels          : True
!
!       The length in NDC units of the dash pattern used for Legend
!       line items.
! *lg02Work.Legend.lgLineDashSegLenF         : 0.15
!
!       The font type to use for item line labels or marker glyphs.
*lg02Work.Legend.lgItemStringFont            : 25
!
!   The height to width aspect ratio of item characters
! *lg02Work.Legend.lgItemStringFontAspectF     : 1.0
!
!   The width of the lines that form the text outline
*lg02Work.Legend.lgItemStringFontThicknessF  : 2.0
!
!   The degree of quality of the text to be written (LOW,MEDIUM,HIGH)
! *lg02Work.Legend.lgItemStringFontQuality     : HIGH
!
!   The spacing between characters of the text to be written
! *lg02Work.Legend.lgItemStringConstantSpacingF: 0.0
!
!   A process for accessing the many characters of the default
!   pwritx font.
! *lg02Work.Legend.lgItemStringFuncCode        : :
!
