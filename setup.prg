/*
	SETUP.PRG
	The "setup program" for the MDI Tutorial
	application ... open any and all files
	needed to run the application and/or develop
	the application.
*/
// These always get me -- if the program
// crashes, and they usually do while developing --
// (due to programmer error), the speedBar and the
// statusBar in the IDE is not available ... this
// just puts them back. the MDI application class turns
// them back off ...
_app.speedbar := true
_app.statusBar := true
_app.tabBar := true
// this can also cause problems:
set design on
// Set procedures ...:
set procedure to start
// make sure the menu is available:
set procedure to Tutorial.mnu
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