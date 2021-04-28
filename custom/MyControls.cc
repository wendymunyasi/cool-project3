class MYENTRYFIELD(parentObj, name) of ENTRYFIELD(parentObj, name) custom
   with (this)
      onGotFocus = {;this.keyboard( "{Home}" )}
      height = 22.0
      left = 21.0
      top = 33.0
      width = 84.0
      metric = 6	// Pixels
      colorHighLight = "WindowText/0x80ffff"
      value = "MyEntryfield"
      selectAll = false
   endwith

endclass

class MYTEXT(parentObj, name) of TEXT(parentObj, name) custom
   with (this)
      height = 22.0
      left = 21.0
      top = 66.0
      width = 84.0
      metric = 6	// Pixels
      text = "MyText"
      borderStyle = 10	// Etched Out
   endwith

endclass

class MYTEXTLABEL(parentObj, name) of TEXTLABEL(parentObj, name) custom
   with (this)
      height = 22.0
      left = 21.0
      top = 99.0
      width = 84.0
      metric = 6	// Pixels
      transparent = true
      text = "MyTextlabel"
      fontBold = true
      alignHorizontal = 2	// Right
   endwith

endclass

class MYPUSHBUTTON(parentObj, name) of PUSHBUTTON(parentObj, name) custom
   with (this)
      height = 24.0
      left = 21.0
      top = 121.0
      width = 88.0
      text = "Button"
      metric = 6	// Pixels
   endwith

endclass

class MYSPINBOX(parentObj, name) of SPINBOX(parentObj, name) custom
   with (this)
      onGotFocus = {;this.keyboard("{Home}")}
      height = 22.0
      left = 28.0
      top = 165.0
      width = 70.0
      metric = 6	// Pixels
      picture = '"99999"'
      colorHighLight = "WindowText/0x80ffff"
      rangeMax = 100
      rangeMin = 1
      value = 1
      selectAll = false
   endwith

endclass

class MYCOMBOBOX(parentObj, name) of COMBOBOX(parentObj, name) custom
   with (this)
      onGotFocus = class::MYCOMBOBOX_ONGOTFOCUS
      onChange = class::MYCOMBOBOX_ONCHANGE
      height = 22.0
      left = 21.0
      top = 231.0
      width = 88.0
      metric = 6	// Pixels
      colorHighLight = "WindowText/0x80ffff"
      style = 2	// DropDownList
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

class MYRADIOBUTTON(parentObj, name) of RADIOBUTTON(parentObj, name) custom
   with (this)
      transparent = true
      height = 24.0
      left = 21.0
      top = 275.0
      width = 98.0
      text = "Radiobutton1"
      metric = 6	// Pixels
      value = true
   endwith

endclass

class MYCONTAINER(parentObj, name) of CONTAINER(parentObj, name) custom
   with (this)
      transparent = true
      left = 350.0
      top = 22.0
      width = 266.0
      height = 110.0
      metric = 6	// Pixels
      borderStyle = 4	// Single
   endwith

endclass

class MYGRID(parentObj, name) of GRID(parentObj, name) custom
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
      metric = 6	// Pixels
   endwith

endclass

class MYTABBOX(parentObj, name) of TABBOX(parentObj, name) custom
   with (this)
      onSelChange = class::MYTABBOX_ONSELCHANGE
      onOpen = class::MYTABBOX_ONOPEN
      id = 110
      height = 22.0
      left = 0.0
      top = 483.0
      width = 638.0
      metric = 6	// Pixels
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

class MYIMAGE(parentObj, name) of IMAGE(parentObj, name) custom
   with (this)
      height = 88.0
      left = 294.0
      top = 319.0
      width = 84.0
      metric = 6	// Pixels
      alignment = 3	// Keep Aspect Stretch
   endwith

endclass

class MYEDITOR(parentObj, name) of EDITOR(parentObj, name) custom
   with (this)
      key = class::MYEDITOR_KEY
      height = 121.0
      left = 427.0
      top = 319.0
      width = 182.0
      metric = 6	// Pixels
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

class MYDISABLEDENTRYFIELD(parentObj, name) of MYENTRYFIELD(parentObj, name) custom
   with (this)
      when = {;return false}
      height = 22.0
      left = 287.0
      top = 451.0
      width = 84.0
      value = "MyDisabledEntryfield"
      mousePointer = 12	// No
   endwith

endclass

class MYTITLETEXT(parentObj, name) of MYTEXT(parentObj, name) custom
   with (this)
      height = 28.0
      left = 490.0
      top = 451.0
      width = 84.0
      colorNormal = "Blue/BtnFace"
      alignHorizontal = 1	// Center
      fontSize = 14.0
      fontBold = true
      text = "Title"
      borderStyle = 1	// Raised
   endwith

endclass
