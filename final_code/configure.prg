/*
   ----------------------------------------------------------------------------
   configure.prg
   Basic configuration program designed to make sure the working environment
   for the developer working on the tutorial is "back to normal", written for:
   
   The dBASE Plus Tutorial: Developing An Application
   January, 2017, Ken Mayer
   
   Permission is granted to use this in your own applications, with the caveat
   that credit be given appropriately.
   ----------------------------------------------------------------------------
*/
_app.speedbar  := true
_app.statusBar := true
_app.tabBar    := true // only works in dBASE Plus 8 or later
set design on

// Setup custom controls for use with forms
set procedure to :DT_Custom:mycontrols.cc
set procedure to :FormControls:seeker.cc

//  Setup custom controls for use the reports
set procedure to :DT_Custom:CustomReportControls.cc
set procedure to :ReportControls:report.cc
