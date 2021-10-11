CREATE OR REPLACE PACKAGE BODY practicum2_pkg AS
PROCEDURE p_get_orders_for_cust(cust_in IN Customers.customerID%type) IS
o_id number;
o_date VARCHAR2(20);
status VARCHAR2(30);
total_order VARCHAR2(30);

CURSOR cursor_practice IS
SELECT od.orderid AS "Order #", TO_CHAR(o.orderdate,'dd/MON/yyyy') AS "Date", NVL2(o.ShippedDate, 'Shipped','Not Shipped') AS "Status",
TO_CHAR(SUM(od.unitprice* od.quantity* (1-od.discount)),'$99,999.99') AS "Order_Total" 
FROM Orders o INNER JOIN OrderDetails od ON o.orderID= od.orderID
WHERE o.CustomerID=cust_in
Group BY od.orderID, o.orderDate,o.shippedDate
Order BY 4 Desc ;
BEGIN 
dbms_output.put_line('Statistics for '||get_cust_name(cust_in)||' '||'06/AUG/2021  -  ' ||'Agnita Paul'|| chr(10));
dbms_output.put_line(RPAD('Order #',13)|| '  '||RPAD('Order Date    ',13)||'  '||RPAD(' Status',17)||'  '||RPAD('Order Total',13)|| chr(10));
OPEN cursor_practice;
LOOP 
FETCH cursor_practice into o_id, o_date, status,total_order;
EXIT WHEN cursor_practice%notfound;
dbms_output.put_line(RPAD(o_id,13)||'  '|| RPAD(o_date,13) || '  '||RPAD(status,17)||' '||RPAD(total_order,13 ));
END LOOP;
CLOSE cursor_practice;
dbms_output.put_line(' ');
dbms_output.put_line('AVG. Order amount for Customer: '||'                '||get_avg_order_amount(cust_in));
dbms_output.put_line(' ');
dbms_output.put_line('AVG. Order amount for Company: '||'                 '||get_avg_company);
dbms_output.put_line(' ');
dbms_output.put_line('# of orders this customers has shipped: '||'          '||get_avg_ship_count(cust_in));
END;

FUNCTION get_cust_name(cust_in IN Customers.customerID%type)
RETURN VARCHAR2 AS
cust_companyName VARCHAR2(30);
BEGIN 
SELECT customers.companyName INTO cust_companyName
FROM Customers
WHERE customers.customerID= cust_in;
RETURN cust_companyName;
end get_cust_name;

FUNCTION get_avg_order_amount(cust_in IN Customers.customerID%type)
RETURN VARCHAR2  AS
average VARCHAR2(30);
BEGIN 
SELECT TO_CHAR(avg(sum(orderDetails.unitprice*orderDetails.quantity*(1-orderDetails.discount))),'$99,999.99') INTO average
FROM Orders
INNER JOIN OrderDetails on Orders.orderID=orderDetails.orderID
WHERE orders.customerID=cust_in
GROUP BY orderDetails.orderID;
RETURN average;
END; 

FUNCTION get_avg_ship_count(cust_in IN Customers.customerID%type)
RETURN VARCHAR2  AS
shipped_count VARCHAR2(30);
BEGIN 
SELECT COUNT(sum(orderDetails.unitprice*orderDetails.quantity*(1-orderDetails.discount))) INTO shipped_count
FROM Orders
INNER JOIN OrderDetails on Orders.orderID=orderDetails.orderID
WHERE orders.customerID=cust_in AND orders.shippedDate IS NOT NULL
GROUP BY orderDetails.orderID;
RETURN shipped_count;
END; 

FUNCTION get_avg_company
RETURN VARCHAR2  AS
average VARCHAR2(30);
BEGIN 
SELECT TO_CHAR(avg(sum(orderDetails.unitprice*orderDetails.quantity*(1-orderDetails.discount))),'$99,999.99') INTO average
FROM Orders
INNER JOIN OrderDetails on Orders.orderID=orderDetails.orderID
GROUP BY orderDetails.orderID;
RETURN average;
END; 

END practicum2_pkg;