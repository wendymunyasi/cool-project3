/*
   ----------------------------------------------------------------------------
   lookup_oodml01.prg
   Example program written for:
   
   The dBASE Plus Tutorial: Developing An Application
   February, 2017, Ken Mayer

   Lookup Example -- OODML -- lookupSQL
   This is a simple example to show how a lookupRowset 
   works in dBASE Plus.
   ----------------------------------------------------------------------------
*/

// close any open databases
close databases

// set up the database object:
dTutorial = new database()
dTutorial.databaseName := "dbasetutorial"
dTutorial.active       := true

// set up the customer table as a query:
qCust = new query()
qCust.database := dTutorial
qCust.sql      := "select * from customer"
qCust.active   := true

// set the rowset's indexName:
qCust.rowset.indexName := "names"
qCust.rowset.exactMatch := false // otherwise it looks for full expression

// set the state id field's lookupSQL:
qCust.rowset.fields["state id"].lookupSQL := "select * from state order by state"

// find the customer:
qCust.rowset.findKey( "Simpson" )

// display the state:
? qCust.rowset.fields["state id"].value
// display the actual value being stored in the customer table:
? qCust.rowset.fields["state id"].lookupRowset.fields[1].value

// cleanup:
qCust.active := false
release object qCust
qCust = null
dTutorial.active := false
release object dTutorial
dTutorial = null
