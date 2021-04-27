/*
   ----------------------------------------------------------------------------
   lookup_xdml.prg
   Example program written for:
   
   The dBASE Plus Tutorial: Developing An Application
   February, 2017, Ken Mayer

   Lookup Example -- XDML
   This sample program is designed to show how one might
   perform a lookup using XDML, versus the simpler and easier
   method used with OODML in dBASE Plus.
   ----------------------------------------------------------------------------
*/

// close any open databases
close databases

// open the database
open database dbasetutorial
// point to it so we can use it
set database to dbasetutorial

// open the customer table
use customer order names
// find a specific customer
locate for trim(:last name:) = "Simpson"
// get the state id
cState = :state id:

// open the state table:
use state order "state id" in 2
select 2
// find the state id:
locate for :state id: = cState
// display the name of the state:
? state

select 1
// back to customer table

// cleanup
set database to
close databases
