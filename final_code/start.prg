/*
    START.PRG
    Author: Ken Mayer
    Date  : January 13, 2017

    Tutorial project START program

    This program is used to start the TUTORIAL 
    application. 

    There is a reference to another .CC, which is
    the genericMDIApp.CC file -- this contains
    the generic application object, and below we 
    subclass it ...

    The idea is that you have a lot of "things" that
    you always do for any application that is
    an MDI app. You create one object that handles
    all of that, and then you subclass that for
    the specifics for an application, as each is
    at least slightly different.
*/

   //update this for application version changes:
   #define AppVersion "4.0" // Version 4 of this tutorial project
   set talk off

   // set the private directory for the BDE
   // uses BDE (IDAPI) API Code below the TutorialApp
   // definition -- this uses a default folder,
   // no need to pass a value:
   setPrivateDir()

   // set up the application object:
   local app
   set procedure to GenericMDIApp.cc
   app = new TutorialApp()
   app.open()

return 

/*
   TutorialApp is a subclass of the "GenericMDIApp" contained
   in the .cc file of the same name:
*/
class TutorialApp of GenericMDIApp
   // set any specific code for the subclassed
   // MDI application here - note this uses the AppVersion constant
   // created above for the version number:
   this.FrameWinText = "dBASE Plus Tutorial Project -- vers. " + AppVersion

   // note this is not the file name -- the 
   // SETUP program must execute "set procedure ..." that
   // will open the file "Tutorial.mnu" ... the class
   // will be available from that point on. This is
   // the classname of the menu:
   this.MenuClassName = "TutorialMenu"

endclass

/*
   Code that deals with setting the private folder for the BDE
   to write _QSQLnnnn.dbf files, this is API code and a bit involved.
   Provided by Wian in the dBASE newsgroups, but appears to have
   been originally provided by Rick Miller.
*/
function setPrivateDir( cPath )
   if not type("DbiSetPrivateDir") == "FP"
      extern CUSHORT DbiSetPrivateDir(CSTRING) idapi32 from "DbiSetPrivateDir"
   endif

   Local cDir
   if type("argVector(1)") == "C"
      cDir  =  cPath
   else
      // when cDir == null, reset to default.
      cDir  =  null
   endif
return iif( DbiSetPrivateDir( cDir ) == 0, true, false )
