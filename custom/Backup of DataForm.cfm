** END HEADER -- do not remove this line
class DataFormCForm of BASECFORM custom from :DT_Custom:Base.cfm
   set procedure to :DT_Custom:MyControls.cc additive
   set procedure to :FormControls:seeker.cc additive
   with (this)
      onOpen = class::FORM_ONOPEN
      left = 204.0
      top = 68.0
      text = "CustomDataForm"
      escExit = false
   endwith

   with (this.MYTITLETEXT1)
      text = "Data Form"
   endwith

   this.SEEKER1 = new SEEKER(this)
   with (this.SEEKER1)
      height = 22.0
      left = 135.0
      top = 14.0
      width = 414.0
      pageno = 2
   endwith

   this.MYTEXTLABEL1 = new MYTEXTLABEL(this)
   with (this.MYTEXTLABEL1)
      height = 22.0
      left = 54.0
      top = 15.0
      width = 68.0
      text = "Find:"
      pageno = 2
   endwith

   this.MYGRID1 = new MYGRID(this)
   with (this.MYGRID1)
      pageno = 2
      height = 392.0
      left = 35.0
      top = 52.0
      width = 588.0
   endwith

   this.MYTABBOX1 = new MYTABBOX(this)
   with (this.MYTABBOX1)
      height = 22.0
      left = 0.0
      top = 458.0
      width = 656.0
   endwith

   this.MYTOOLBAR1 = new MYTOOLBAR(this)
   with (this.MYTOOLBAR1)
      left = 135.0
      top = 41.0
      width = 377.0
      height = 44.0
   endwith


   function form_onOpen()
      if form.rowset # null
			// don't allow automatic editing
			form.rowset.autoEdit := false
			// assign this method to the rowset's canNavigate:
			form.rowset.canNavigate := class::rowset_canNavigate
			// go to the first row ...
			form.rowset.first()
		endif
		return

	function rowset_canNavigate()
		/*
		Check to save any changes before allowing navigation.
		For whatever reason, this gets called twice. If the
		user chooses Yes to Save, or No to abandon, then
		the next time through the rowset.modified property is
		false so there's no problem. If the user chooses to
		cancel the navigation, they'll get prompted twice.
		For that reason, we set a flag to indicate it's been
		here once. If the flag exists, we null it, if not we
		run the validation.
		BIG Note: If a future version of dBASE™ PLUS corrects the
		behavior so the canNavigate routine does NOT fire
		twice, this code will not work correctly.
		Applies to all dBASE builds through dBASE™ PLUS.
		Code by Gary White
		*/
		local bYes, nAnswer
		if type("_app.cancelNav") == "L" and _app.cancelNav
			_app.cancelNav := null
			bYes = false
		else
			bYes = true
			if this.modified
				nAnswer = msgbox("Save changes before leaving record?",;
										"Data has changed",32+3)
				DO CASE
					CASE nAnswer == 6 // Yes
						this.save()
					CASE nAnswer == 7 // No
						this.abandon()
					OTHERWISE // Cancel
						bYes := false
						_app.cancelNav = true
				ENDCASE
			endif
		endif
		return bYes
endclass

