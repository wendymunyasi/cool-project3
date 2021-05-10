_app.speedbar := true
_app.statusBar := true
_app.tabBar := true // only works in dBASE™ PLUS 8 or later
set design on

// Setup custom controls for use with forms
set procedure to :DT_custom:mycontrols.cc
set procedure to :FormControls:seeker.cc

// Setup custom controls for use the reports
set procedure to :DT_Custom:CustomReportControls.cc
set procedure to :ReportControls:report.cc