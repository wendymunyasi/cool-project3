/*
   ----------------------------------------------------------------------------
   LockRow.prg
   A program to show the basics of using the default session object in
   dBASE with some code to deal with record locks.
   
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
qCust.sql      := "select * from customer"
qCust.active   := true

if qCust.rowset.isRowLocked() // see if it is locked
   msgbox( "This record is already locked, try again later!",;
           "Cannot Edit Row", 16 )
   return
else
   if qCust.rowset.lockRow() // attempt to lock the record now:
      qCust.rowset.beginEdit() // edit it
   else
      msgbox( "The record is locked, try again later!",;
              "Cannot Lock Row", 16 )
      return
   endif
endif
wait