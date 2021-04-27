// This file is copied from the dUFLP folder, so that for the tutorial
// it is not necessary to install and have the dUFLP available.

/*
   File...: BDEALIAS.CC
   Author.: Romain Strieff
   Date...: 09/21/1998 (turned into a .CC by Ken Mayer)
            02/10/1999 added databaseFound method
            02/12/1999 moved BDECFG_FILE(), localShare(), and
                       fromUnicode() from MISCAPI.PRG to here.
            March 28, 1999 --
                       Fixed some minor things and added
                       the cTableFormat parameter to the 
                       createAlias() method.
            March 29, 1999 -- 
                       Gary fixed databaseFound a bit,
                       added databaseDir()
            January 29, 2002 --
                       Fred (Meuler?) from the dBASE
                       Newsgroups found a fix for
                       the localShare method's return
                       statement (a bug was there). 
            April 17, 2002 --
                       KM -- added ListAliases method,
                       which uses the databases getSchema,
                       and returns a one or two column array
                       of database aliases (and their paths).
            April 26, 2002 --
                       KM -- added ListTables method,
                       which uses database getSchema, and
                       returns a single-column array
                       of the table names in the alias
                       provided.
            September 12, 2002 --
                       Added ListViews and ListProcedures methods,
                       which can be used in some SQL Database 
                       servers to list any Views or Stored Procedures
                       in the alias.

            April 20, 2011 --
                       Added IsDbaseUACSupported() and GetCurrentSessionHandle() methods.
            			  Added support for dBPLUS v2.7 to CreateAlias() and DeleteAlias() methods.

   This allows you to delete or create a BDE Alias without
   having to exit Visual dBASE and run the BDE Administrator
   application. This uses the BDE API ...

   Useful for deployment of an application ...

   Methods included here:

      databaseFound() -- returns logical value based on whether
        or not the BDE Alias you are looking for is set in your
        installation of the BDE or not. Can be used to determine
        if you should create it or not ...
      createAlias() -- creates a BDE Alias
      deleteAlias() -- deletes a BDE Alias
      BDECFG_File() -- returns the name of the BDE configuration
                       file "in use" by the BDE at that time.
      localShare()  -- returns a logical based on the state
                       of this setting in the BDE.
      DatabaseDir() -- returns the directory of an alias supplied
                       as a parameter
      ListAliases() -- returns an array of BDE Alias names and
                       their paths.
      ListTables( cAlias ) -- returns array of tables in a
                       specific BDE Alias
      ListViews( cAlias ) -- returns array of Views (some databases
                       allow these) in a specific BDE Alias -- if
                       array.size is zero, there are no views.
      ListProcedures( cAlias ) -- returns array of procedures
                       in a specific alias (some databases 
                       allow stored procedures) -- if array.size is
                       zero, there are no procedures.

   Examples:

      set procedure to bdealias.cc additive
      b = new BDEAlias()
      ? b.databaseFound( "MYALIAS" )
      ? b.DeleteAlias( "MYALIAS" )
      ? b.CreateAlias( "MYALIAS", "C:\TEST" )
      ? b.BDECFG_File()
      ? b.localShare()
      ? b.databaseDir( "MYALIAS" )
      aAliases = b.ListAliases( [<lPaths>] )
      i.e.,
      aAliases = b.ListAliases()
        // returns a single column array of alias names
        // or:
      aAliases = b.ListAliases( true )
        // returns a two-column array of names and paths
      ? aAliases[1,1] // Alias Name
      ? aAliases[1,2] // Alias path
        // or alternatively
        for i = 1 to aAliases.size/2
            ? aAliases[i,1], aAliases[i,2]
        next
      aTables = b.ListTables( "MYALIAS" )
        for i = 1 to aTables.size
            ? aTables[ i ]
        next

      // -------------------------------------------------
      // example of creating an InterBase alias in detail:
      cIPath = "c:\MyTest;"+;
               "SERVER NAME:c:\MyTest\testdata.gdb;"+;
               "USER NAME:SYSDBA;"+;
               "LANGDRIVER:'ascii' ANSI;"+;
               "SQLQRYMODE:SERVER;"+;
               "SQLPASSTHRU MODE:SHARED NOAUTOCOMMIT"
     b.createAlias( "MYINTERBASE", cIPath, "INTRBASE" )
*/

class BDEALias

   //	Andrew Shimmin 19-Apr-2011

   #define DBIERR_NONE               0

   #define sesCFGMODE2               0x0002000C                            // new CFGMode (virtual, persistent, session)

   #define cfgmNone                    0x00
   #define cfgmVirtual                 0x01
   #define cfgmPersistent              0x02
   #define cfgmSession                 0x04
   #define cfgmAll                     cfgmVirtual+cfgmPersistent+cfgmSession

  function dataBaseFound( cDatabase )
      // Code by Gary White
      local d, dbArray, lFound, i
      d = new database()
      dbArray=d.getschema( "Databases" )
      release object d
      lFound = false
      for i = 1 to dbArray.size
         if upper( cDatabase ) == upper( dbArray[i] )
            lFound := true
            exit
         endif
      endfor
   return lFound

   function DatabaseDir
      parameters cDatabase
      local oDatabase
      /*
         Returns the path for the alias supplied
         as a parameter (null if it does not exist)

         Based on code posted by Romain Strieff 
         in the Visual dBASE Newsgroups

         Modified to accept a string for an alias name
         instead of a database object by Gary White
      */
      cRet = null
      if type("cDatabase") == "C" and not empty(cDatabase)
         if this.databaseFound( cDatabase )
            if type("GetAliasPath") # "FP"
               extern cint GetAliasPath(cHandle,cString,;
                  cString,cString);
                  IDAPI32 from "DbiFormFullName"
            endif
            cRet=space(261)
            oDatabase = new database()
            oDatabase.databaseName := cDatabase
            oDatabase.active := true
            if ( GetAliasPath(oDatabase.handle,"DummyTableName","",cRet ) == 0 )
               cRet=cRet.left(cRet.lefttrim().lastindexof("\"))
               else
               cRet=""
            endif
            oDatabase.active := false
            release object oDatabase
         endif
      endif
   return cRet

   function CreateAlias(cAliasName, cPath, cTableFormat)
   /*

		cAliasName 	= the Alias name that the database is to be referred to
  		cPath      	= the full path to the database
  		cTableFormat = the table format (i.e., INTRBASE, DBASE, etc.)

      2011/04/20  Andrew Shimmin

      	Added dBPLUS v2.7 support.

   */

      if pCount() < 3
        	cTableFormat = [DBASE]
      endif

      if type([DbiAddAlias]) # [FP]
        	extern cushort DbiAddAlias(chandle,cptr,cptr,cptr,clogical) idapi32
      endif

      return (DbiAddAlias(null,class::ToUnicode(cAliasName),class::ToUnicode(cTableFormat),class::ToUnicode([PATH:]+cPath),TRUE)==0)

   function DeleteAlias(cAliasName)

   /*

      Romain Strieff

      Deletes an existing Alias

      2007/05/11  Marc Van den Berghen

         Changed to use oem() function in place of unicode functions to
         provide correct behaviour with diacritical characters.

      2011/04/20  Andrew Shimmin

      	Added dBPLUS v2.7 support.

   */

      if type([DbiDeleteAlias]) # [FP]
         extern cushort DbiDeleteAlias(chandle,cptr) idapi32
      endif

      if type([DbiGetCurrSession]) # [FP]
         extern cushort DbiGetCurrSession(cptr cLong) idapi32
      endif

      if type([DbiGetCfgMode2Prop]) # [FP]
         extern cushort DbiGetCfgMode2Prop(chandle,culong,cptr culong,cushort,cptr cushort) idapi32 from [DbiGetProp]
      endif

      if type([DbiSetProp]) # [FP]
         extern cushort DbiSetProp(chandle,clong,clong) idapi32 from [DbiSetProp]
      endif

      local bSuccess,hSession,nSesCfgMode2

      bSuccess = false
      hSession = 0
      nSesCfgMode2 = 0

      do case
         case  class::IsDbaseUACSupported()                                   // >= v2.7
               if class::GetCurrentSessionHandle(hSession)
                  if (DbiGetCfgMode2Prop(hSession,sesCFGMODE2,nSesCfgMode2,null,null) == DBIERR_NONE)
                     if (DbiSetProp(hSession,sesCFGMODE2,cfgmPersistent) == DBIERR_NONE)
                        bSuccess := (DbiDeleteAlias(null,class::ToUnicode(cAliasName)) == DBIERR_NONE)
                        DbiSetProp(hSession,sesCFGMODE2,nSesCfgMode2)
                     endif
                  endif
               endif
         otherwise                                                            // < v2.7
               bSuccess := (DbiDeleteAlias(null,class::ToUnicode(cAliasName)) == DBIERR_NONE)
      endcase

      return (bSuccess)

   function IsDbaseUACSupported()
      return (type([_app.useUACPaths]) # [U])

   function GetCurrentSessionHandle(nHandle)
      return (DbiGetCurrSession(nHandle) == DBIERR_NONE)

   function BDECFG_File
      /*
         BDECFG_File -- returns the name of the currently
         used BDE Configuration file. (Uses BDE API)
         Note: this uses fromUnicode() below ...

         Posted by Romain Strieff in the Visual dBASE Newsgroups
         February 2, 1999
      */

      if type( "DbiGetSysConfig" ) # "FP"
         extern cInt DbiGetSysConfig( cPtr ) IDAPI32
      endif
      cBuffer = space( 256 )
      DbiGetSysConfig( cBuffer )
      // minor code fix noted by Lane Coddington
      cRet = substr( this.fromUnicode( cBuffer ), 54, 128 )
      cRet = left( cRet, at(chr(0), cRet ) - 1 )
   return cRet

   function LocalShare
      /*
         LocalShare -- returns a logical true/false based on
         the localShare setting of the BDE. 
         Note: this uses fromUnicode() below ...

         Posted by Romain Strieff in the Visual dBASE Newsgroups
         February 2, 1999
      */

      if type( "DbiGetSysConfig" ) # "FP"
         extern cInt DbiGetSysConfig( cPTR ) idapi32
      endif

      cBuffer = space( 256 )
      DbiGetSysConfig( cBuffer )

   return asc( left( this.fromUnicode( cBuffer ), 1 ) ) == 1

   function fromUnicode( c )
      /*
         fromUnicode returns standard characters rather than
         the Unicode character set (which is larger).

         Posted by Romain Strieff in the Visual dBASE Newsgroups
         February 2, 1999
      */
       local cText, nLen, nInd
       nLen = len( c )
       cText = ""
       for nInd = 0 to nLen - 1
           cText += chr( c.getByte( nInd ) )
       endfor

   return cText

   // Converts to Unicode
   Function ToUnicode(c)
      LOCAL cTemp, x

      cTemp = Replicate(Chr(0), ((Len(c) + 1) / 2) + ;
                                ((Len(c) + 1) % 2))
      For x = 1 To Len(c)
         cTemp.SetByte(x - 1, Asc(SubStr(c, x)))
      EndFor

   RETURN cTemp

   function ListAliases
      /*
          This method returns a two-column array of
          BDE Aliases and their paths, which can be used
          by the developer to do whatever is needed
          from there. 

          Ken Mayer, April 17, 2002

          The lPaths parameter will return the second
          column with the path. Without it, you get
          a single column array of just the names ...
      */
      parameter lPaths

      // Get the names of the aliases:
      aSchema = _app.databases.current.getSchema("Databases")

      if pCount() > 0 and lPaths == true
         // add a column, and leave data where it is
         aSchema.resize( aSchema.size, 2, 1 )
         for i = 1 to (aSchema.size/2)
             aSchema[ i, 2 ] = this.DatabaseDir( aSchema[ i, 1 ] )
         next
      endif

   return aSchema

   function ListTables
      /*
          This method returns a single-column array of
          Tables in a BDE Aliases which can be used
          by the developer to do whatever is needed
          from there. 

          Ken Mayer, April 26, 2002
      */
      parameter cAlias

      // Get the names of the tables:
      local dData
      try
          dData = new database( cAlias )
      // catch error, particularly if the BDE Alias does
      // not exist ...
      catch( Exception E )
          msgbox( "Error: "+e.message, "BDEAlias::Error", 16 )
          return
      endtry
      aSchema = dData.getSchema( "Tables" )
      // cleanup
      dData.active := false
      release object dData
      dData := null

   return aSchema

   function ListViews
      /*
          This method returns a single-column array of
          Views in a BDE Alias which can be used
          by the developer to do whatever is needed
          from there. 

          Ken Mayer, September 12, 2002
      */
      parameter cAlias

      // Get the names of the tables:
      local dData
      try
          dData = new database( cAlias )
      // catch error, particularly if the BDE Alias does
      // not exist ...
      catch( Exception E )
          msgbox( "Error: "+e.message, "BDEAlias::Error", 16 )
          return
      endtry
      aSchema = dData.getSchema( "VIEWS" )
      // cleanup
      dData.active := false
      release object dData
      dData := null

   return aSchema

   function ListProcedures
      /*
          This method returns a single-column array of
          Stored Procedures in a BDE Alias which can be used
          by the developer to do whatever is needed
          from there. 

          Ken Mayer, September 12, 2002
      */
      parameter cAlias

      // Get the names of the tables:
      local dData
      try
          dData = new database( cAlias )
      // catch error, particularly if the BDE Alias does
      // not exist ...
      catch( Exception E )
          msgbox( "Error: "+e.message, "BDEAlias::Error", 16 )
          return
      endtry
      aSchema = dData.getSchema( "PROCEDURES" )
      // cleanup
      dData.active := false
      release object dData
      dData := null

   return aSchema
endclass

/*
    End of File: BDEALIAS.CC
*/

