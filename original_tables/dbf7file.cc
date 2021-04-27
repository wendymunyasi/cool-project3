// NOTE: This is a copy *from* the dUFLP, and references to
// the BDEAlias.cc file that use the source alias have been
// modified to remove those. KJM

// -- File: DBF7File.Cc
class DBF7File(cDBF) of BFile from "BFile.Cc"
/*
   --------------------------------------------------------------------

   Programmer...: Bowen Moursund
   Last modified: February 28, 2005
   Written for..: Visual dBASE 7.01

   Note: Jay Parsons started the original work on this,
         sent it to Ken Mayer -- neither of us could get
         it to function quite correctly. Bowen, after
         a discussion at ICon 98 on Undocumented Features
         dug this code up and finished it the day after
         the conference was over. (This was after I (Ken)
         had explained that to the best of my knowledge
         it wasn't possible to reset the autoincrement
         value ... figures <G>)

         Modified: June 25, 2003 -- Roland Wingerter, to 
                   allow the use of a BDE Alias with a table.

                   February 28, 2005 -- Ivar B. Jessen
                   added GetNextAutoIncValue(), to return
                   the next value to be used in a table ...

                   March 3, 2005 -- Ivar B. Jessen
                   modified both SetNextAutoIncValue and
                   NextAutoIncValue so that they do not
                   require the autoinc fieldname. Notice
                   that the code will work if you pass
                   the parameter (see below), but the
                   fieldname parameter is not required.
   --------------------------------------------------------------------

   Purpose:
   Extends Jim Sare's BFile class with level 7 DBF utility methods.

   --------------------------------------------------------------------

   Notes:
   The SetNextAutoIncValue method is based on information supplied by
   Jay Parsons and acquired second hand via Ken Mayer <g>. Ken's notes
   concerning Jay's info:

       According to Jay:
         "1. In a VdB7 .DBF, the main header is longer, 44h (68 bytes).
             The table of field descriptors starts next, at offset
             44h/68d.
          2. The field name comes first, as usual. The type byte
             indicating the type of the field is 32 bytes into the
             descriptor, which is 48 bytes long.
          3. The Autoinc type is marked by a "+" type byte, 2Bh.
          4. The next available autoinc number starts 10 bytes
             farther along and is stored in 4 bytes binary, least-
             significant first.

   --------------------------------------------------------------------
   Methods:
      SetNextAutoIncValue()
         Allows the developer to see the value of the next
         number returned by an AutoIncrement Field in a
         DBF 7 table. NOTE THIS WILL NOT WORK FOR OTHER
         TABLE TYPES (i.e., .DB, or SQL tables).
            This returns numeric values for errors, with
            a value of zero for success, so you could test
            to make sure it actually happened using something
            like the following:

            nRet = oDBF7File.SetNextAutoIncValue("FOO_ID", 10)
            // if > 0 we have an error:
            if nRet > 0
               do case
                  case nRet == 1
                       cMsg = "DBF not found"
                  case nRet == 2
                       cMsg = "Cannot open DBF"
                  case nRet == 5
                       cMsg = "No AutoInc Field in Table"
                  otherwise
                       cMsg = "Unknown Error"
               endcase
               msgbox( "Error: "+cMsg,;
                       "DBF7File error", 16 )
            endif
         

      GetNextAutoIncValue()
         Allows the developer to simply view the current
         setting for the field in question. It should be
         noted that if an error occurs, this method
         will return a character string. You may want to check
         for the type ... 
             x = oDBF7File.GetNextAutoIncValue("FOO_ID") 
             if type( "x" ) # "N"
                msgbox( "Error: "+x )
             else
                msgbox( "Next value: "+x )
             endif

      SetMDXFlag()
         Allows the developer to turn on/off the flag in
         the table header that notifies dBASE that there
         is a production .MDX. This can be useful if
         performing a long task that is slowed down by
         updating the index tags for your table for
         each record processed -- turn the flag off,
         when done, turn it back on and issue a reindex.
         This returns a numeric value as with the SetNextAutoIncValue()
         method, with zero indicating success, and any value
         greater than zero indicating an error. You could test
         for this with code along these lines:

            nRet = oDBF7File.SetMDXFlag(false)
            // if > 0 we have an error:
            if nRet > 0
               do case
                  case nRet == 1
                       cMsg = "DBF not found"
                  case nRet == 4
                       cMsg = "Cannot open DBF"
                  case nRet == 5
                       cMsg = "Low level seek failed"
                  otherwise
                       cMsg = "Unknown Error"
               endcase
               msgbox( "Error: "+cMsg,;
                       "DBF7File error", 16 )
            endif

    Examples of use:
         set procedure to DBF7File.CC additive
         oDBF7File = new DBF7File( "Foo.DBF" )
               OR
         oDBF7File = new DBF7File( ":MyBDEAlias:Foo.DBF" )

         // reset autoinc field
         oDBF7File.SetNextAutoIncValue( "FOO_ID", 1 ) 
            or // fieldname parameter is not required:
         oDBF7File.SetNextAutoIncValue( 1 ) 

         // get the next autoinc field (so you can check on it)
         oDBF7File.GetNextAutoIncValue( "FOO_ID" ) 
            or // fieldname parameter is not required:
         oDBF7File.GetNextAutoIncValue() 

         // detach production MDX
         oDBF7File.SetMDXFlag( false ) 

   ** Note that this cc file uses Source Aliasing, specifically the
   ** dUFLP source Alias. If you do not know how to set up
   ** a Source Alias, see the instructions in WHATS.NEW at
   ** the top of the file, or in README.TXT.
   ** Any files referenced by :dUFLP:filename  must be
   ** included in an executable if you are building 
   ** one ... make sure that your project includes these
   ** files.
   **
   ** This particular program uses:
   **           bfile.cc
   **           bdealias.cc
   --------------------------------------------------------------------
*/

   set procedure to BFile.Cc additive
   protect DBF, DBFDef

   class::SetDBF(cDBF)

   function SetDBF
      parameters cDBF
      local bSuccess

      bSuccess = false
      this.dbf = null

      if argCount() == 1 and type("cDBF") == "C" 
			if file(cDbf)      	
            this.DBF = cDBF
            bSuccess := true
         elseif cDBF.indexOf(":") = 0 and cDBF.lastIndexOf(":") > 1
        		// Maybe a database alias
        		set procedure to BDEAlias.CC additive
            local b, nAt, cAliasName, cTableName, cDatabasePath

				// Extract alias and tableName 
         	nAt 		  = cDBF.lastIndexOf(":")
            cAliasName = cDBF.substring(1,nAt)
            cTableName = cDBF.Right(cDBF.Length-nAt-1)

            // Get database path
		      b = new BDEAlias()
            cDatabasePath = b.databaseDir( cAliasname )
				if file( cDatabasePath + "\" + cTableName )
            	this.dbf = cDatabasePath + "\" + cTableName
               // ? "this.Dbf:", this.dbf
               bSuccess = true
            endif
            close procedure BDEAlias.CC
         endif
      endif
   return bSuccess

   function GetDBF
   return this.DBF

   function VerifyDBF
   return type("this.DBF") == "C" and file(this.DBF)

   function SetNextAutoIncValue( cFieldName, nNextValue )
      // revamp by Ivar b. Jessen -- the fieldname
      // is not 100% required here, as there is only
      // ever one autoinc field in a table, and frankly the name
      // isn't important. The information we need
      // is already in the table header. The code is designed 
      // to allow users of earlier versions
      // to use this with the fieldname, and just ignore it
      // if passed to the method:
      if not this.VerifyDBF()
         return 1 // DBF not found
      endif

      local nb

      // attempt to open the DBF file:
      try
         this.open( this.DBF, "RW" )
      catch (exception e)
         return 2 // Cannot open DBF
      endtry

      // if the number of parameters is 1, and it is
      // numeric, use that value, basically moving it
      // into the nNextValue parameter:
      if argcount() < 2 and type('argvector(1)') == "N"
         nNextValue := argvector(1)
      endif

      // go to field type in first field
      this.seek( 100, 0)
      nb = this.read(1)
      do
         // is it an autoInc field?
         if asc(nb) == 43 // autoinc
            // go to the NextAutoIncValue in the header
            this.seek(9, 1)
            nb = 13
            this.WriteLong( nNextValue ) // write new value
            this.close() // close the table!
            return 0 // Success!
         else
            // go to field type in following field, continue
            // until we find the autoinc field
            nb = this.read(1)
         endif
      until asc(nb) = 13
      this.close()
      // return error value:
   return 5 // no AutoInc field in table
   // End of Method: SetNextAutoIncValue

   function GetNextAutoIncValue( cFieldName )
      // Ivar B. Jessen (modified to return string for errors by KJM),
      // modified March 3, 2005 -- cFieldName is not
      // required and is ignored if passed to this method.
      if not this.VerifyDBF()
         return "DBF not found" 
      endif

      local nb, nValue

      // attempt to open table:
      try
         this.open( this.DBF, "R" )
      catch (exception e)
         return "Cannot open DBF"
      endtry

      // find the autoinc field
      // go to field type in first field
      this.seek(100, 0)
      nb = this.read(1)
      do
         // is it an autoinc field?
         if asc(nb) = 43
            // go to the NextAutoIncValue
            this.seek(9, 1)
            nb = 13
            nValue = this.readLong()
            this.close() // close table
            return nValue
         else
            // go to field type in following field
            // continue stepping through field descriptor array
//            this.seek(47, 1)
            nb = this.read(1)
         endif
      until asc(nb) = 13
      this.close() // close table
      // return error value:
   return "No AutoInc field in table"
   // End of Method: GetNextAutoIncValue

   function SetMDXFlag( bValue )
      if not this.VerifyDBF()
         return 1 // DBF not found
      endif
      try
         this.open(this.DBF, "RW")
      catch (exception e)
         return 4 // Cannot open DBF
      endtry
      if this.seek( 28, 0 ) <> 28
         this.close()
         return 5 // Low level seek failed
      endif
      this.write( iif(bValue, chr(1), chr(0)) )
      this.close()
   return 0 // Success!
   // End of Method: SetMDXFlag

endclass

/* -----------------------------------------------------------------------
   End of File: DBF7FILE.CC
   ----------------------------------------------------------------------- */