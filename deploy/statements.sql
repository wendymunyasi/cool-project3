--Database:dbasetutorial
Select CUSTOMER."Last Name",
  INVOICE."Order Date",
  CUSTOMER.*,
  INVOICE.*,
  LINEITEM.*
From CUSTOMER
  Inner Join INVOICE On CUSTOMER."Customer ID" = INVOICE."Customer ID"
  Inner Join LINEITEM On INVOICE."Invoice ID" = LINEITEM."Invoice ID"
Order By CUSTOMER."Last Name",
  CUSTOMER."Customer ID",
  INVOICE."Order Date"