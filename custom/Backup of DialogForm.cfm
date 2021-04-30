** END HEADER -- do not remove this line
class DialogFormCForm of BaseCForm custom from :DT_Custom:Base.cfm
   set procedure to :DT_Custom:MyControls.cc additive
   with (this)
      height = 261.0
      left = 131.0
      top = 183.0
      width = 334.0
      text = "CustomDialogForm"
      clientEdge = true
      autoCenter = true
      mdi = false
      escExit = false
   endwith

   with (this.MYTITLETEXT1)
      text = "Dialog Form"
   endwith

   this.PBSAVE = new MYPUSHBUTTON(this)
   with (this.PBSAVE)
      onClick = class::PBSAVE_ONCLICK
      height = 24.0
      left = 54.0
      top = 205.0
      width = 88.0
      text = "&OK"
      speedTip = '"Save"'
   endwith

   this.MYPUSHBUTTON2 = new MYPUSHBUTTON(this)
   with (this.MYPUSHBUTTON2)
      height = 1.0
      left = 173.0
      top = 204.0
      width = 1.0
   endwith

   this.PBCANCEL = new MYPUSHBUTTON(this)
   with (this.PBCANCEL)
      height = 24.0
      left = 185.0
      top = 205.0
      width = 88.0
      text = "&Cancel"
      speedTip = '"Cancel"'
   endwith


   function PBSAVE_onClick()
      // Save and close the form
		if form.rowset # NULL
			form.rowset.save()
		endif
		form.close()
      return

   endclass

