/*
     GenericMDIApp.CC
     From the dBASE Tutorial that was updated/maintained by
     Michael Nuwer for years ... 
	  
	  Minor update, July 2014 by Geep Howell 
	  (as noted) in the Close method, for
     current versions of dBASE (9.x).

     A simple custom class file that contains
     a "generic" MDI application object. This 
     object, when used properly, is subclassed
     and the subclass has the following:

     set procedure to genericMDIApp.cc additive
     class TestMDIApp of genericMDIApp()
        this.FrameWinText = "Some Text for _app.framewin"
        this.MenuClassName = "MenuClassname"
     endclass

     A startup program for this would assume that you
     have a "SETUP" program, which opens any custom
     control files necessary (and does whatever else
     may be needed), instantiates the subclassed
     MDI application object, and then starts it
     with the 'start' method:

     app = new TestMDIApp()
     return ( app.open() )
*/
class GenericMDIApp

   // This custom property should be overwritten
   // in a subclass, or after instantiation, but
   // before the Open() method is invoked:
   this.FrameWinText = "Generic MDI application"

   // The same goes for this custom property:
   this.MenuClassName = "MyMainMenu"

   // We assume here that every MDI app will have
   // a SETUP.PRG
   do setup

   // Assign a property to _app.frameWin, which is
   // a reference to this object: "this".
   _app.framewin.app = this

   function Open

      // set a reference to the menu
      private c
      c = 'this.rootMenu = new '+this.MenuClassName+'(_app.framewin,"Root")'
      &c.

      // Make sure no forms are open
      close forms

      // Make sure we're not in "design mode"
      set design off

      // set the <Escape> key "off" but store the 
      // current setting:
      this.OldEscape = set("ESCAPE")
      set escape off

      // Turn off the dBASE Plus shell, but 
      // leave the MDI frame window:
      shell( false, true )
      
      // Turn off the application's speedBar, statusBar, and tabBar
      // however, for a true MDI app, you may actually want
      // the tabBar turned on:
      _app.speedbar  := false
      _app.statusBar := false
      _app.tabBar    := false

      // Set the text property for the application's framewin
      _app.framewin.oldText = _app.framewin.text
      _app.framewin.text    := this.FrameWinText

   return

   Function close

      // close any forms that might have been left open
      close forms

      // set escape back to whatever it's previous
      // state was:
      cEscape = this.oldEscape
      set escape &cEscape.

      // set the shell back ...
      shell( true, true )

      // if we are in the "runtime" environment,
      // we want to "quit" (otherwise the framewin will
      // be left on screen)
      if ( "runtime" $ lower( version(0) ) )
         quit
      else
         // otherwise, let's reset some values:
         with ( _app )
            framewin.app  := null
            framewin.text := framewin.OldText
            speedBar      := true
            statusBar     := true
            tabBar        := true
         endwith

         // go back to design mode:
         set design on

	      // close any open procedures
         set procedure to

         // release the menu
         _app.framewin.root.release()

      endif

   return

endclass // don't forget this!
