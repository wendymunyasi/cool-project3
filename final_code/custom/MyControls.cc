class MYENTRYFIELD(parentObj) of ENTRYFIELD(parentObj) custom
   with (this)
      onGotFocus = {;this.keyboard( "{Home}" )}
      height = 22.0
      left = 21.0
      top = 22.0
      width = 124.0
      metric = 6        // Pixels
      colorHighLight = "WindowText/0x80ffff"
      value = "MyEntryfield"
      selectAll = false
   endwith

endclass

class MYTEXT(parentObj) of TEXT(parentObj) custom
   with (this)
      height = 22.0
      left = 19.0
      top = 57.0
      width = 84.0
      metric = 6        // Pixels
      text = "MyText"
      borderStyle = 10        // Etched Out
   endwith

endclass

class MYTEXTLABEL(parentObj) of TEXTLABEL(parentObj) custom
   with (this)
      height = 22.0
      left = 21.0
      top = 90.0
      width = 87.0
      metric = 6        // Pixels
      transparent = true
      text = "MyTextLabel"
      fontBold = true
      alignHorizontal = 2        // Right
   endwith

endclass
class MYPUSHBUTTON(parentObj) of PUSHBUTTON(parentObj) custom
   with (this)
      height = 24.0
      left = 19.0
      top = 121.0
      width = 107.0
      text = "Button"
      metric = 6        // Pixels
      mousePointer = 13        // Hand
   endwith

endclass

class MYSPINBOX(parentObj) of SPINBOX(parentObj) custom
   with (this)
      onGotFocus = {;this.keyboard("{Home}")}
      height = 22.0
      left = 23.0
      top = 155.0
      width = 65.0
      metric = 6        // Pixels
      picture = "99999"
      colorHighLight = "WindowText/0x80ffff"
      rangeMax = 100
      rangeMin = 1
      value = 1
      selectAll = false
   endwith

endclass

class MYCOMBOBOX(parentObj) of COMBOBOX(parentObj) custom
   with (this)
      onGotFocus = class::MYCOMBOBOX_ONGOTFOCUS
      onChange = class::MYCOMBOBOX_ONCHANGE
      height = 22.0
      left = 21.0
      top = 187.0
      width = 143.0
      metric = 6        // Pixels
      colorHighLight = "WindowText/0x80ffff"
      style = 2        // DropDownList
      dropDownHeight = 132.0
      autoDrop = true
   endwith

   function MYCOMBOBOX_onGotFocus()
      this.savedValue = this.value
   return

function MYCOMBOBOX_onChange()
      // this = combobox
      // datalink = field
      // parent = field array
      // parent = rowset
      if this.datalink.parent.parent.state == 1
         this.value = this.savedValue
         this.datalink.parent.parent.modified = false
         this.datalink.parent.parent.abandon()
      endif
   return
endclass

class MYRADIOBUTTON(parentObj) of RADIOBUTTON(parentObj) custom
   with (this)
      transparent = true
      height = 24.0
      left = 27.0
      top = 224.0
      width = 110.0
      text = "MyRadiobutton"
      metric = 6        // Pixels
   endwith

endclass

class MYCONTAINER(parentObj) of CONTAINER(parentObj) custom
   with (this)
      transparent = true
      left = 172.0
      top = 21.0
      width = 248.0
      height = 71.0
      metric = 6        // Pixels
      borderStyle = 4        // Single
   endwith

endclass

class MYGRID(parentObj) of GRID(parentObj) custom
   with (this)
      bgColor = "white"
      cellHeight = 22.0
      rowSelect = true
      colorRowSelect = "WindowText/0x80ffff"
      allowEditing = false
      allowAddRows = false
      height = 66.0
      left = 173.0
      top = 96.0
      width = 247.0
      metric = 6        // Pixels
   endwith

endclass

class MYIMAGE(parentObj) of IMAGE(parentObj) custom
   with (this)
      height = 88.0
      left = 178.0
      top = 170.0
      width = 111.0
      metric = 6        // Pixels
      alignment = 3        // Keep Aspect Stretch
   endwith

endclass

class MYEDITOR(parentObj) of EDITOR(parentObj) custom
   with (this)
      key = class::MYEDITOR_KEY
      height = 88.0
      left = 294.0
      top = 171.0
      width = 140.0
      metric = 6        // Pixels
      value = ""
      colorHighLight = "WindowText/0x80ffff"
      evalTags = false
      popupEnable = false
   endwith

   function MYEDITOR_key(nChar, nPosition,bShift,bControl)
       /*
          This code by Gary White is provided to
          get around a problem with rowsets that
          have the autoEdit property set to false,
          and editors. The editor seems to be immune
          to this property once you make a change
          in it -- if you then save or abandon, you
          can actually edit the contents of the editor
          object ...
       */
       // this = editor
       // dataLink = field
       // parent = fieldArray
       // parent = rowset
       if type( "this.datalink.parent.parent" ) # "U"
          r = this.datalink.parent.parent
          if r.autoEdit == false and ;
             ( r.state # 2 and r.state # 3 )
             return 0
          endif
       endif
   return
endclass

class MYDISABLEDENTRYFIELD(parentObj) of MYENTRYFIELD(parentObj) custom
   with (this)
      when = {;return false}
      height = 22.0
      left = 73.0
      top = 270.0
      width = 124.0
      colorNormal = "White/Maroon"
      mousePointer = 12        // No
   endwith

endclass

class MYTITLETEXT(parentObj) of MYTEXT(parentObj) custom
   with (this)
      height = 28.0
      left = 256.0
      top = 269.0
      width = 121.0
      colorNormal = "Blue/BtnFace"
      alignHorizontal = 1        // Center
      fontSize = 14.0
      fontBold = true
      text = "Title"
      borderStyle = 1        // Raised
   endwith

endclass

class MYTABBOX(parentObj) of TABBOX(parentObj) custom
   with (this)
      onSelChange = class::MYTABBOX_ONSELCHANGE
      onOpen = class::MYTABBOX_ONOPEN
      id = 110
      height = 22.0
      left = 0.0
      top = 350.0
      width = 465.0
      metric = 6        // Pixels
      //colorNormal = "blue"
      colorHighLight = "WindowText/0x80ffff"
      dataSource = 'ARRAY {"Individual Record","Find Record"}'
   endwith

   function MYTABBOX_onSelChange()
      form.pageNo := this.curSel
   return
   
   function MYTABBOX_onOpen()
      this.curSel := 1
      form.pageNo := 1
   return
endclass

class MYTOOLBAR(parentObj) of CONTAINER(parentObj) custom
   with (this)
      left = 10.0
      top = 301.0
      width = 377.0
      height = 34.0
      metric = 6	// Pixels
      borderStyle = 4	// Single
   endwith

   this.PBNEW = new MYPUSHBUTTON(this)
   with (this.PBNEW)
      onClick = class::PBNEW_ONCLICK
      height = 24.0
      left = 4.0
      top = 4.0
      width = 62.0
      text = "&New"
      upBitmap = "filename :Glyfx:\Aero\CE\Dbase Aero\PNG\16x16\favourites_16.png"
      fontSize = 8.0
      speedTip = "Add a new record"
      pageno = 0
   endwith

   this.PBEDIT = new MYPUSHBUTTON(this)
   with (this.PBEDIT)
      onClick = class::PBEDIT_ONCLICK
      height = 24.0
      left = 65.0
      top = 4.0
      width = 62.0
      text = "&Edit"
      upBitmap = "filename :Glyfx:\Aero\CE\Dbase Aero\PNG\16x16\document_open_16.png"
      fontSize = 8.0
      speedTip = "Edit current record"
      pageno = 0
   endwith

   this.PBSAVE = new MYPUSHBUTTON(this)
   with (this.PBSAVE)
      onClick = class::PBSAVE_ONCLICK
      height = 24.0
      left = 126.0
      top = 4.0
      width = 62.0
      text = "&Save"
      upBitmap = "filename :Glyfx:\Aero\CE\Dbase Aero\PNG\16x16\save_16.png"
      fontSize = 8.0
      speedTip = "Save current record"
      pageno = 0
   endwith

   this.PBCANCEL = new MYPUSHBUTTON(this)
   with (this.PBCANCEL)
      onClick = class::PBCANCEL_ONCLICK
      height = 24.0
      left = 187.0
      top = 4.0
      width = 62.0
      text = "&Cancel"
      upBitmap = "filename :Glyfx:\Aero\CE\Dbase Aero\PNG\16x16\stop_16.png"
      fontSize = 8.0
      speedTip = "Cancel changes"
      pageno = 0
   endwith

   this.PBDELETE = new MYPUSHBUTTON(this)
   with (this.PBDELETE)
      onClick = class::PBDELETE_ONCLICK
      height = 24.0
      left = 248.0
      top = 4.0
      width = 62.0
      text = "&Delete"
      upBitmap = "filename :Glyfx:\Aero\CE\Dbase Aero\PNG\16x16\delete_16.png"
      fontSize = 8.0
      speedTip = "Delete current record"
      pageno = 0
   endwith

   this.PBPREV = new MYPUSHBUTTON(this)
   with (this.PBPREV)
      onClick = class::PBPREV_ONCLICK
      height = 24.0
      left = 316.0
      top = 4.0
      width = 27.0
      text = ""
      upBitmap = "filename :Glyfx:\Aero\CE\Dbase Aero\PNG\16x16\arrow_left_16.png"
      speedTip = "Previous record"
      pageno = 0
   endwith

   this.PBNEXT = new MYPUSHBUTTON(this)
   with (this.PBNEXT)
      onClick = class::PBNEXT_ONCLICK
      height = 24.0
      left = 342.0
      top = 4.0
      width = 27.0
      text = ""
      upBitmap = "filename :Glyfx:\Aero\CE\Dbase Aero\PNG\16x16\arrow_right_16.png"
      speedTip = "Next record"
      pageno = 0
   endwith

   function PBNEXT_onClick()
      if ( not form.rowset.next() )
         form.rowset.next( -1 )
         msgbox( "At end of rowset", "Can't Navigate", 64 )
      endif
   return
   
   function PBNEW_onClick()
      form.rowset.beginAppend()
   return
   
   function PBPREV_onClick()
		if ( not form.rowset.next(-1) )
			form.rowset.next()
			msgbox( "At beginning of rowset", "Can't Navigate", 64 )
		endif
   return
   
   function PBCANCEL_onClick()
		if form.rowset.modified
			if msgbox( "Abandon changes to this row?", "Abandon changes?", 36 ) == 6
				form.rowset.abandon()
			endif
		else
			form.rowset.abandon()
		endif      
   return
   
   function PBEDIT_onClick()
      form.rowset.beginEdit()
   return
   
   function PBDELETE_onClick()
      if msgbox( "Delete this row?", "Delete Row?", 36 ) == 6
                  form.rowset.delete()
       endif
   return
   
   function PBSAVE_onClick()
      form.rowset.save()
   return
endclass
