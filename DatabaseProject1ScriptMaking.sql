DROP TABLE Categories CASCADE CONSTRAINTS;
DROP TABLE Customers CASCADE CONSTRAINTS;
DROP TABLE Employees CASCADE CONSTRAINTS;
DROP TABLE OrderDetails CASCADE CONSTRAINTS;
DROP TABLE Orders CASCADE CONSTRAINTS;
DROP TABLE Products CASCADE CONSTRAINTS;
DROP TABLE Suppliers CASCADE CONSTRAINTS;
DROP TABLE Shippers CASCADE CONSTRAINTS;

ALTER SESSION SET NLS_DATE_FORMAT = 'YYYY-MM-DD';

CREATE TABLE Customers (
	CustomerId CHAR(5),
	CompanyName VARCHAR2 (40) NOT NULL ,
	ContactName VARCHAR2 (30) ,
	CONTACTTITLE VARCHAR2(30) ,
	Address VARCHAR2 (60) ,
	City VARCHAR2 (15)  ,
	Region VARCHAR2 (15)  ,
	PostalCode VARCHAR2 (10)  ,
	Country VARCHAR2 (15)  ,
	Phone VARCHAR2 (24) , 
	Fax VARCHAR2 (24) ,
	Email VARCHAR2 (50) ,
	CONSTRAINT Customers_CustomerID_PK PRIMARY KEY(CustomerId),
    CONSTRAINT Customers_Email_UK UNIQUE(Email) 
);

CREATE TABLE Employees (
	EmployeeID NUMBER(8,0),
	LastName VARCHAR2 (20) NOT NULL ,
	FirstName VARCHAR2 (10) NOT NULL ,
	TITLE VARCHAR2(30) ,
	TITLEOFCOURTESY VARCHAR2(25) ,
	BirthDate DATE ,
	HireDate DATE,
	Address VARCHAR2 (60)  ,
	City VARCHAR2 (15)  ,
	Region VARCHAR2 (15)  ,
	PostalCode VARCHAR2 (10)  ,
	Country VARCHAR2 (15)  ,
	HomePhone VARCHAR2 (24) , 
	Extension VARCHAR2 (4) ,
	Notes VARCHAR2 (600) ,
	ReportsTo NUMBER(8,0)   ,
	PhotoPath VARCHAR2 (255) ,
	SIN CHAR(9),
	CONSTRAINT Employees_EmloyeeID_PK PRIMARY KEY(EmployeeID),
    CONSTRAINT Employees_Employees_fk FOREIGN KEY(ReportsTo) REFERENCES Employees(EmployeeId),
    CONSTRAINT Employees_SIN_UK UNIQUE(SIN)
 
);

CREATE TABLE Shippers (
	ShipperID NUMBER(8,0),
	CompanyName VARCHAR2 (40) NOT NULL ,
	Phone VARCHAR2 (24)  ,
	CONSTRAINT Shippers_ShipperID_PK PRIMARY KEY(ShipperID)

);

CREATE TABLE Suppliers (
	SupplierId NUMBER(8,0),
	CompanyName VARCHAR2 (40) NOT NULL ,
	ContactName VARCHAR2 (30)  ,
	CONTACTTITLE VARCHAR2(30) ,
	Address VARCHAR2 (60) ,
	City VARCHAR2 (15)  ,
	Region VARCHAR2 (15) ,
	PostalCode VARCHAR2 (10)  ,
	Country VARCHAR2 (15)  ,
	Phone VARCHAR2 (24), 
	Fax VARCHAR2 (24) ,
	HomePage VARCHAR2 (200) ,
	CONSTRAINT Suppliers_SupplierID_PK PRIMARY KEY(SupplierId) 
);




CREATE TABLE Categories (
	CategoryId NUMBER(8,0),
	CategoryName VARCHAR(15) NOT NULL, 
	CategoryCode NUMBER(6,0) ,
	Description VARCHAR2 (300)  ,
	CONSTRAINT Categories_CategorieID_PK PRIMARY KEY(CategoryId),
    CONSTRAINT Categories_CategoryCode_UK UNIQUE(CategoryCode)
);





CREATE TABLE Orders (
	OrderId NUMBER(8,0),
	CustomerId CHAR(5) ,
	EmployeeId NUMBER ,
    TerritoryID VARCHAR(20),
	OrderDate DATE ,
	RequiredDate DATE,
	ShippedDate DATE ,
	ShipVia NUMBER(8,0),
	Freight NUMBER(8,2),
	ShipName VARCHAR(40),
	ShipAddress VARCHAR(60),
	ShipCity VARCHAR(15),
	ShipRegion VARCHAR(15),
	ShipPostalCode VARCHAR(20),
	ShipCountry VARCHAR(15),
	CONSTRAINT Orders_OrderId_PK PRIMARY KEY(OrderId),
    CONSTRAINT Orders_Customers_fk FOREIGN KEY(CustomerId) REFERENCES Customers(CustomerId),
    CONSTRAINT Orders_Employees_fk FOREIGN KEY(EmployeeId) REFERENCES Employees(EmployeeId),
    CONSTRAINT Orders_Shippers_fk FOREIGN KEY(ShipVia) REFERENCES Shippers(ShipperID) 
);

CREATE TABLE Products (
	ProductID NUMBER(8,0),
	ProductName VARCHAR2(40) NOT NULL ,
	SupplierID NUMBER(8,0),
	CategoryID NUMBER(8,0),
	QUANTITYPERUNIT VARCHAR2(20),
	UnitPrice NUMBER(8,2),
	UnitsInStock NUMBER(6,0),
	UnitsOnOrder NUMBER(6,0),
	ReOrderLevel NUMBER(6,0),
	DisContinued NUMBER(1,0),
	CONSTRAINT Products_ProductID_PK PRIMARY KEY(ProductID),
    CONSTRAINT Products_Supplier_fk FOREIGN KEY(SupplierId) REFERENCES Suppliers(SupplierId),
    CONSTRAINT Products_Categories_fk FOREIGN KEY(CategoryID) REFERENCES Categories(CategoryID),
    CONSTRAINT Products_UnitPrice_CK CHECK(UnitPrice >= 0),
    CONSTRAINT Products_ReOrderLevel_CK CHECK(ReOrderLevel >= 0),
    CONSTRAINT Products_UnitsInStock_CK CHECK(UnitsInStock >= 0),
    CONSTRAINT Products_UnitsOnOrder_CK CHECK(UnitsOnOrder >= 0)

);

CREATE TABLE OrderDetails (
	OrderId NUMBER,
	ProductId NUMBER NOT NULL ,
	UnitPrice NUMBER(8,2)  NOT NULL  ,
	Quantity NUMBER(6,0)  NOT NULL , 
	Discount NUMBER(2,2) NOT NULL ,
	CONSTRAINT OrderDetails_OID_PID_pk PRIMARY KEY (OrderID, ProductID),
    CONSTRAINT OrderDetails_Order_fk FOREIGN KEY(OrderId) REFERENCES Orders(OrderId),
    CONSTRAINT OrderDetails_Product_fk FOREIGN KEY(ProductId) REFERENCES Products(ProductId),
    CONSTRAINT OrderDetails_Discount_CK CHECK(Discount >= 0 AND Discount<=1),
    CONSTRAINT OrderDetails_Quantity_CK CHECK(Quantity > 0),
    CONSTRAINT OrderDetails_UnitPrice_CK CHECK(UnitPrice >= 0)
);



