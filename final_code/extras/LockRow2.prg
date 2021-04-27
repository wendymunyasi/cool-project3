/*
   ----------------------------------------------------------------------------
   LockRow.prg
   A program to show the basics of using the default session object in
   dBASE with some code to deal with record locks, and a table with
   a _dBASELock field ... see instructions in "Part 11" of the tutorial 
   to copy the customer table and 'convert' it.
   
   The dBASE Plus Tutorial: Developing An Application
   April, 2017, Ken Mayer
   
   Permission is granted to use this in your own applications, with the caveat
   that credit be given appropriately.
   ----------------------------------------------------------------------------
*/
// lock row
_app.session.lockRetryInterval := 1 // one second between attempts to retry the lock
_app.session.lockRetryCount := 1 // make only one attempt to lock the row

d = new database()
d.databaseName := "dbasetutorial"
d.active       := true

qCust = new query()
qCust.database := d
qCust.sql      := "select * from customer2"
qCust.active   := true

if qCust.rowset.lockRow() // attempt to lock the record now:
   qCust.rowset.beginEdit() // edit it
else
   cUser     = qCust.rowset.fields["_DBASELOCK"].user
   cDateTime = qCust.rowset.fields["_DBASELOCK"].lock
   msgbox( "The row is locked by '" + cUser + "' who locked "+;
           "it at: "+cDateTime+"! Try again later!",;
           "Cannot Lock Row", 16 )
   return
endif
wait