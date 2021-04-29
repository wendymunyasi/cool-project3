class MYENTRYFIELD(parentObj) of ENTRYFIELD(parentObj) custom
   with (this)
      onGotFocus = {;this.keyboard( "{Home}" )}
      height = 22.0
      left = 21.0
      top = 33.0
      width = 84.0
      metric = 6        // Pixels
      colorHighLight = "WindowText/0x80ffff"
      value = "MyEntryfield"
      selectAll = false
   endwith

endclass

class MYTEXT(parentObj) of TEXT(parentObj) custom
   with (this)
      height = 22.0
      left = 21.0
      top = 66.0
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
      top = 99.0
      width = 84.0
      metric = 6        // Pixels
      transparent = true
      text = "MyTextlabel"
      fontBold = true
      alignHorizontal = 2        // Right
   endwith

endclass

class MYPUSHBUTTON(parentObj) of PUSHBUTTON(parentObj) custom
   with (this)
      height = 24.0
      left = 21.0
      top = 121.0
      width = 88.0
      text = "Button"
      metric = 6        // Pixels
   endwith

endclass

class MYSPINBOX(parentObj) of SPINBOX(parentObj) custom
   with (this)
      onGotFocus = {;this.keyboard("{Home}")}
      height = 22.0
      left = 28.0
      top = 165.0
      width = 70.0
      metric = 6        // Pixels
      picture = '"99999"'
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
      top = 231.0
      width = 88.0
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
      left = 21.0
      top = 275.0
      width = 98.0
      text = "Radiobutton1"
      metric = 6        // Pixels
      value = true
   endwith

endclass

class MYCONTAINER(parentObj) of CONTAINER(parentObj) custom
   with (this)
      transparent = true
      left = 350.0
      top = 22.0
      width = 266.0
      height = 110.0
      metric = 6        // Pixels
      borderStyle = 4        // Single
   endwith

endclass

class MYGRID(parentObj) of GRID(parentObj) custom
   with (this)
      bgColor = "white"
      headingHeight = 22.0
      cellHeight = 22.0
      rowSelect = true
      colorRowSelect = "WindowText/0x80ffff"
      allowEditing = false
      height = 187.0
      left = 266.0
      top = 99.0
      width = 343.0
      metric = 6        // Pixels
   endwith

endclass

class MYTABBOX(parentObj) of TABBOX(parentObj) custom
   with (this)
      onSelChange = class::MYTABBOX_ONSELCHANGE
      onOpen = class::MYTABBOX_ONOPEN
      id = 110
      height = 22.0
      left = 0.0
      top = 483.0
      width = 638.0
      metric = 6        // Pixels
      colorHighLight = "WindowText/0x80ffff"
      dataSource = 'ARRAY {"Individual Record", "Find Record"}'
   endwith

   function MYTABBOX_onSelChange()
      form.pageNo := this.curSel
      return
   function MYTABBOX_onOpen()
      this.curSel := 1
                form.pageNo := 1
      return
endclass


class MYEDITOR(parentObj) of EDITOR(parentObj) custom
   with (this)
      key = class::MYEDITOR_KEY
      height = 121.0
      left = 427.0
      top = 319.0
      width = 182.0
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
      left = 287.0
      top = 451.0
      width = 84.0
      value = "MyDisabledEntryfield"
      mousePointer = 12        // No
   endwith

endclass

class MYTITLETEXT(parentObj) of MYTEXT(parentObj) custom
   with (this)
      height = 28.0
      left = 490.0
      top = 451.0
      width = 84.0
      colorNormal = "Blue/BtnFace"
      alignHorizontal = 1        // Center
      fontSize = 14.0
      fontBold = true
      text = "Title"
      borderStyle = 1        // Raised
   endwith

endclass

class MYTOOLBAR(parentObj, name) of CONTAINER(parentObj, name) custom
   with (this)
      left = 133.0
      top = 517.0
      width = 377.0
      height = 44.0
      metric = 6        // Pixels
      borderStyle = 4        // Single
   endwith

   this.PBNEW = new MYPUSHBUTTON(this)
   with (this.PBNEW)
      onClick = class::PBNEW_ONCLICK
      height = 24.0
      left = 6.0
      top = 10.0
      width = 62.0
      text = "&New"
      upBitmap = "filename :Glyfx:\Aero\CE\Dbase Aero\PNG\16x16\favourites_16.png"
      fontSize = 8.0
      speedTip = '"Add new record"'
      pageno = 0
   endwith

   this.PBEDIT = new MYPUSHBUTTON(this)
   with (this.PBEDIT)
      onClick = class::PBEDIT_ONCLICK
      height = 24.0
      left = 69.0
      top = 10.0
      width = 62.0
      text = "&Edit"
      upBitmap = "filename :Glyfx:\Aero\CE\Dbase Aero\PNG\16x16\document_open_16.png"
      fontSize = 8.0
      speedTip = '"Edit current record"'
      pageno = 0
   endwith

   this.PBSAVE = new MYPUSHBUTTON(this)
   with (this.PBSAVE)
      onClick = class::PBSAVE_ONCLICK
      height = 24.0
      left = 132.0
      top = 10.0
      width = 62.0
      text = "&Save"
      upBitmap = "filename :Glyfx:\Aero\CE\Dbase Aero\PNG\16x16\save_16.png"
      fontSize = 8.0
      speedTip = '"Save current record"'
      pageno = 0
   endwith

   this.PBCANCEL = new MYPUSHBUTTON(this)
   with (this.PBCANCEL)
      onClick = class::PBCANCEL_ONCLICK
      height = 24.0
      left = 195.0
      top = 10.0
      width = 62.0
      text = "&Cancel"
      upBitmap = "filename :Glyfx:\Aero\CE\Dbase Aero\PNG\16x16\stop_16.png"
      fontSize = 8.0
      speedTip = '"Cancel changes"'
      pageno = 0
   endwith

   this.PBDELETE = new MYPUSHBUTTON(this)
   with (this.PBDELETE)
      onClick = class::PBDELETE_ONCLICK
      height = 24.0
      left = 258.0
      top = 10.0
      width = 62.0
      text = "&Delete"
      upBitmap = "filename :Glyfx:\Aero\CE\Dbase Aero\PNG\16x16\delete_16.png"
      fontSize = 8.0
      speedTip = '"Delete current record"'
      pageno = 0
   endwith

   this.PBPREV = new MYPUSHBUTTON(this)
   with (this.PBPREV)
      onClick = class::PBPREV_ONCLICK
      height = 24.0
      left = 328.0
      top = 10.0
      width = 21.0
      text = ""
      upBitmap = "filename :Glyfx:\Aero\CE\Dbase Aero\PNG\16x16\arrow_left_16.png"
      speedTip = '"Previous record"'
      pageno = 0
   endwith

   this.PBNEXT = new MYPUSHBUTTON(this)
   with (this.PBNEXT)
      onClick = class::PBNEXT_ONCLICK
      height = 24.0
      left = 349.0
      top = 10.0
      width = 21.0
      text = ""
      upBitmap = "filename :Glyfx:\Aero\CE\Dbase Aero\PNG\16x16\arrow_right_16.png"
      speedTip = '"Next record'
      pageno = 0
   endwith

   function PBEDIT_onClick()
      form.rowset.beginedit()
      return
   function PBDELETE_onClick()
      if msgbox( "Delete this row?", "Delete row?", 36 ) == 6
                        form.rowset.delete()
                endif
      return
   function PBSAVE_onClick()
      form.rowset.save()
      return
   function PBNEXT_onClick()
                if ( not form.rowset.next() )
                        form.rowset.next(-1)
                        msgbox( "At the end of rowset", "Can't Navigate", 64 )
                        endif
      return
   function PBNEW_onClick()
      form.rowset.beginappend()
      return
   function PBPREV_onClick()
      if ( not form.rowset.next(-1) )
                        form.rowset.next()
                        msgbox( "At the beginning of rowset", "Can't Navigate", 64 )
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
endclass
class MYIMAGE(parentObj, name) of IMAGE(parentObj, name) custom
   with (this)
      height = 88.0
      left = 294.0
      top = 297.0
      width = 84.0
      metric = 6	// Pixels
      alignment = 3	// Keep Aspect Stretch
   endwith

endclass
