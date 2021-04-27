/*
   ----------------------------------------------------------------------------
   setup.prg
   The setup program written for:
   
   The dBASE Plus Tutorial: Developing An Application
   January, 2017, Ken Mayer
   
   Permission is granted to use this in your own applications, with the caveat
   that credit be given appropriately.
   
   This program makes sure the environment is normal, but then sets up the
   application object (based on GenericMDIApp.cc), and more.
   ----------------------------------------------------------------------------
*/
// These always get me -- if the program
// crashes, and they usually do while developing --
// (due to programmer error), the speedBar, the
// statusBar, and the tabBar in the IDE is not available ...  
// this just puts them back. The MDI application class turns 
// them back off and on as needed ...

_app.speedbar  := true
_app.statusBar := true
_app.tabBar    := true

// this can also cause problems:
set design on

// Set procedures ...:
set procedure to start

// make sure the menu is available:
set procedure to tutorial.mnu 

// custom controls used by the application
set procedure to :FormControls:seeker.cc
set procedure to :ReportControls:report.cc
set procedure to :DT_Custom:MyControls.cc
set procedure to :DT_Custom:CustomReportControls.cc
// add others as needed here:
set procedure to country.wfm 
set procedure to customer.wfm
set procedure to inventory.wfm
set procedure to invoice.wfm
set procedure to state.wfm
set procedure to supplier.wfm
set procedure to preview.wfm

