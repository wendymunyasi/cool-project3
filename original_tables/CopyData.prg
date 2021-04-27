/*
   CopyData.prg
   
   Author: Ken Mayer
   Updated: January, 2017
	
   A simple program specifically created for dBASE Tutorial
   to copy the data to the tables created by the person 
	using the tutorial, so that they do not have to create 
	data for this application ...

   USAGE: Double-click the icon in the navigator.
   That's all you should have to do, unless an error
   occurs ...

   ***********************************************
   DEPENDENCIES: BFILE.CC, DBF7FILE.CC
     these files must be in the same directory as
     this program and the tables!!
	  These have been copied from the dUFLP,
	  rather than requiring the user of the 
	  tutorial have the dUFLP set up on their
	  system.
   ***********************************************
*/

close database
clear // empty output pane of Command Window

/* set up the database object
   to refer to the tutorial
   database:
*/
try
	d = new database()
	d.databaseName := "dBASETutorial"
	d.active       := true
catch( exception e )
   // the most obvious issue is that the name of the 
	// database object is not correct, or the database
	// alias was not created (using the instructions
	// in the tutorial itself, for a User BDE Alias)
	msgbox( "The database name 'dBASETutorial' does not "+;
           "exist. Either it was misspelled or you skipped "+;
           "that step of the tutorial. Please go back "+;
			  "to the database section of the tutorial, and "+;
			  "complete the instructions for setting up "+;
			  "the database alias.",;
           "Won't work!", 16 )
   return
endtry

/*
   Check to see if we even have the tables necessary
   to do anything ... this program is only supposed
   to be used at the end of the second part of the
   tutorial project ...
*/
if not d.tableExists( "INVENTORY.DBF" )
   msgbox( "You need to create the tables necessary "+;
           "for the tutorial before you try running "+;
           "this program. It's going to blow up otherwise ...",;
           "Won't work!", 16 )
   return
endif


/*
   Empty the tables out, in case tester has tinkered 
	or if they need to re-set the data:
*/
? "Emptying Tables (in case you added some data ...)"
d.emptyTable( "country" )
d.emptyTable( "customer" )
d.emptyTable( "inventory" )
d.emptyTable( "invoice" )
d.emptyTable( "lineitem" )
d.emptyTable( "state" )
d.emptyTable( "supplier" )

/*
   Deal with autoincrement -- if user added any rows,
   the autoincrement value will be wrong, and when
   we copy data from the original tables, we will have 
	incorrect data (the id fields that link tables won't 
   match) ...
*/
? "Setting AutoIncrement values to 1"
set procedure to dbf7file.cc additive
b = new dbf7file( ":dBASETutorial:customer.dbf" )
b.SetNextAutoIncValue("customer id", 1)

b = new dbf7file( ":dBASETutorial:inventory.dbf" )
b.SetNextAutoIncValue("item id", 1)

b = new dbf7file( ":dBASETutorial:invoice.dbf" )
b.SetNextAutoIncValue("invoice id", 1)

b = new dbf7file( ":dBASETutorial:supplier.dbf" )
b.SetNextAutoIncValue("supplier id", 1)

b=null
close procedure dbf7file.cc

/* --------------------------------------------------------
   append the data using the updateSet object in dBASE Plus
   The code below is a complete rewrite of the original
   code to use pure OODML methods. We're using arrays
   for the tables to make it easier to loop through lists.
   UpdateSet requires two queries/rowsets, one for the
   source, one for the destination.
*/

aTables = new array()
aTables.add( "country" )
aTables.add( "customer" )
aTables.add( "inventory" )
aTables.add( "invoice" )
aTables.add( "lineitem" )
aTables.add( "state" )
aTables.add( "supplier" )

// loop through array
for i = 1 to aTables.size
	 ? "Copying "+aTables[i]+" data"
	 q1 = new query()
	 // source tables have a '1' at the end of the filename
	 q1.sql := "select * from "+aTables[i]+"1"
	 q1.active := true
 	 q2 = new query()
	 q2.database := d
	 q2.sql := "select * from "+aTables[i]
	 q2.active := true
	 u = new updateSet()
	 u.source := q1.rowset
	 u.destination:= q2.rowset
	 u.append()
next

msgbox( "The tables should now have data in them, and you "+;
        "can move on in the tutorial project ...","Done", 64 )

// cleanup data objects
q1.active := false
release object q1
q1 = null
q2.active := false
release object q2
q2 = null
release object u
u = null
d.active := false
release object d
d = null

/*
   End of Program; CopyData.prg
*/
