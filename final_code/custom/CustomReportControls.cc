/*

    CustomReportConrols.cc 
    This file is part of the dBASE tutorial project. 

    Author...: Ken Mayer
    Date.....: January 11, 2017

    These controls are a subset of the Custom Form Controls
    found in REPCNTL.CC in the dUFLP, and renamed.

    Controls included are:

    MyReportTitleText -- A larger font text object used for a main title
                    on a report
    MyDateText   -- prints "Date:" followed by the current date

    MyStandardText -- base class for most of the following
                    text controls
    MyFieldText  -- Used to display actual field, need to set
                    the codeblock appropriately ...
    MyFieldHeadingText -- Bold text used to display a field
                        heading
    MyRectangleShape -- base class for other shape controls
       
    MyLine       -- basic line object
*/

class MyReportTitleText(parentObj) of TEXT(parentObj) custom
   with (this)
      alignHorizontal        := 1	// Center
      alignVertical          := 1	// Middle
      fontItalic             := true
      fontName               := "Arial"
      fontSize               := 18
      height                 := 0.3229
      metric                 := 3	// Inches
      text                   := "This is a Main Report Title"
      transparent            := true
      width                  := 3.5313
      wrap                   := true
   endwith

endclass

/*
   this is a standard text control that most of the others
   here are subclassed from ...
*/
class MyStandardText(parentObj) of TEXT(parentObj) custom
   with (this)
      alignHorizontal        := 0 // Left
      alignVertical          := 0 // Top
      fontName               := "Arial"
      fontSize               := 10
      height                 := 0.18
      metric                 := 3	// Inches
      text                   := "MyStandardText"
      transparent            := true
      width                  := 1.1667
   endwith
endclass

/*
   Basic text and date combination ... nice thing about
   VdBASE 7 is the auto casting of types, so that
   we can display the date without having to add the DTOC()
   function ... of course, if you want more detail, like
   character month, and such, you would need to code for
   it ...
*/
class MyDateText(parentObj) of MyStandardText(parentObj) custom
   with (this)
      alignHorizontal        := 1 // center
      alignVertical          := 1	// Middle
      text                   := {||"Date: "+date()}
   endwith
endclass

/* 
   want the text on this one to be bold and line up on the
   right side ...
*/
class MyFieldHeadingText(parentObj) of MyStandardText(parentObj) custom
   with (this)
      height          := 0.18
      width           := 0.75
      alignHorizontal := 2 // Right
      text            := "FieldHeading: "
      fontBold        := true
   endwith
endclass

/*
    FieldText: Suggestion -- place this on the report,
    and then bring up the text property in the codeblock
    editor. Standard text controls are "datalinked" by
    the TEXT codeblock:

      form.streamSource1.rowset.fields["fieldName"].value

    So, replace "field codeblock" with the above,
    and of course insert the proper fieldName, and
    you should be fine.

    In addition, you may want to pass the field through
    the string object, particularly if you have
    the potential of nulls and you are doing a
    calculated field, so your codeblock *might* look
    like:

     new String( form.streamSource1.rowset.fields["fieldName"].value ) +;
     " " + ;
     new String( form.streamSource1.rowset.fields["fieldName2"].value )

*/
class MyFieldText(parentObj) of MyStandardText(parentObj) custom
   with (this)
      width           := 1.2188
      variableHeight  := true
      // This needs to be modified for each object ... obviously
      text            := {||"field codeblock"}
   endwith

endclass


/*
   The standard Rectangle doesn't function properly -- this is a
   bug in the software -- if you render the report on screen,
   a rectangle works like you might expect. However, if you
   print it (at least to the several HP Laserjets I've tried
   it with), the rectangle will print offset (up/left) from
   where it should. The shape object, however, doesn't do this --
   so you can generate a rectangle using the shape and have it
   work properly.
*/

// Start with a base shape class:
class MyRectangleShape(parentObj) of SHAPE(parentObj) custom
   with (this)
      width       := 2.9479
      height      := 0.4063
      metric      := 3	// Inches
      colorNormal := "BLACK/WHITE"
      penStyle    := 0 // Solid
      penWidth    := 2
      shapeStyle  := 1	// Rectangle
   endwith
endclass

/*
    Basic line, but I set the width to 2, because
    when photocopying, I've found that a width
    of 1 often gets lost ...
*/
class MyLine(parentObj) of LINE(parentObj) custom
   with (this)
      left            := 0
      right           := 4.4722
      top             := 0
      bottom          := this.top
      fixed           := false
      width           := 2
      metric          := 3	// Inches
   endwith

endclass


