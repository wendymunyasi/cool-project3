** END HEADER -- do not remove this line


class DialogFormCForm of BASECFORM custom from :DT_Custom:base.cfm
   set procedure to :DT_Custom:MyControls.cc additive
   with (this)
      height = 202.0
      width = 509.0
      text = "CustomDialogForm"
      clientEdge = true
      autoCenter = true
      mdi = false
      smallTitle = true
      escExit = false
   endwith

   with (this.MYTITLETEXT1)
      text = "DialogForm"
   endwith

   this.PBSAVE = new MYPUSHBUTTON(this)
   with (this.PBSAVE)
      onClick = class::PBSAVE_ONCLICK
      height = 24.0
      left = 143.0
      top = 167.0
      width = 107.0
      text = "&OK"
      speedTip = "Save"
   endwith

   this.PBCANCEL = new MYPUSHBUTTON(this)
   with (this.PBCANCEL)
      onClick = class::PBCANCEL_ONCLICK
      height = 24.0
      left = 261.0
      top = 167.0
      width = 107.0
      text = "&Cancel"
      speedTip = "Cancel"
   endwith


   function PBCANCEL_onClick()
      // abandon changes and close the form:
      if form.rowset # NULL
         form.rowset.abandon()
      endif
      form.close()
   return

   function PBSAVE_onClick()
      // Save and close the form:
      if form.rowset # NULL
         form.rowset.save()
      endif
      form.close()
   return

endclass

