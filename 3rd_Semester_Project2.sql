--/*
USE MASTER;
GO

DROP DATABASE [HumanResources];
GO
--*/

CREATE DATABASE [HumanResources];
GO

USE [HumanResources]
GO

CREATE TABLE dbo.Departments(
	DepartmentID INT IDENTITY CONSTRAINT PK_Department PRIMARY KEY,
	DepartmentName NVARCHAR(150) NOT NULL,
	StreetAddress NVARCHAR(50) NOT NULL,
	City NVARCHAR(50) NOT NULL,
	Province NVARCHAR(50) NOT NULL,
	PostalCode CHAR(6) NOT NULL,
	MaxWorkstations INT NOT NULL CONSTRAINT DF_Departments_MaxWorkstations DEFAULT 1,
	CONSTRAINT CK_DepartmentNames_WorkStation CHECK(MaxWorkstations >= 0),
	CONSTRAINT AK_DepartmentNames_DepartmentName_UK UNIQUE(DepartmentName)

);

CREATE UNIQUE INDEX AK_DepartmentName_DepartmentName ON dbo.Departments (DepartmentName);

CREATE TABLE dbo.PhoneTypes(
	PhoneTypeID INT IDENTITY CONSTRAINT PK_PhoneTypes PRIMARY KEY,
	PhoneType NVARCHAR(50) NOT NULL,
);
  
CREATE TABLE dbo.Employees(
	EmployeeID INT IDENTITY CONSTRAINT PK_Employee PRIMARY KEY,
	FirstName NVARCHAR(50) NOT NULL,
	MiddleName NVARCHAR(50) NULL,
	LastName NVARCHAR(50) NOT NULL,
	DateofBirth DATE NOT NULL,
	SIN char(9) NOT NULL,
	DefaultDepartmentID  INT NOT NULL CONSTRAINT FK_Employees_Departments_Default REFERENCES dbo.Departments ( DepartmentID ),
    CurrentDepartmentID  INT NOT NULL CONSTRAINT FK_Employees_Departments_Current REFERENCES dbo.Departments ( DepartmentID ),
	ReportsToEmployeeID INT NULL CONSTRAINT FK_Employees_Employees REFERENCES dbo.Employees ( EmployeeID ),
	StreetAddress NVARCHAR(50) NULL,
	City NVARCHAR(50) NULL,
	Province NVARCHAR(50) NULL,
	PostalCode CHAR(6) NULL,
	StartDate  DATE NOT NULL,
	BaseSalary decimal(18, 2) NOT NULL CONSTRAINT DF_Employees_BaseSalary DEFAULT 0,
-- 	BonusPercent decimal(3, 2) NOT NULL -- Best not to Store, as this Can be calculated from Employee data

    CONSTRAINT CK_Employee_StartDate CHECK ( StartDate <=  GETDATE() ),
	CONSTRAINT CK_Employee_Birthday CHECK ( DateofBirth <=  GETDATE() ),
	CONSTRAINT CK_Employees_SIN CHECK ( LEN(SIN) = 9 AND ISNUMERIC(SIN) =1 ) 
);

CREATE UNIQUE INDEX AK_Employees_SIN ON dbo.Employees (SIN);
CREATE INDEX IX_Employees_City_PostalCode ON dbo.Employees ( PostalCode,City );
CREATE INDEX IX_Employees_City ON dbo.Employees ( City );
CREATE INDEX IX_Employees_DepartmentID ON dbo.Employees ( DefaultDepartmentID );
CREATE INDEX IX_Employees_CurrentDepartmentID ON dbo.Employees ( CurrentDepartmentID );

CREATE TABLE dbo.EmployeePhoneNumbers(
	EmployeePhoneNumberID INT IDENTITY CONSTRAINT PK_EmployeePhoneNumbers PRIMARY KEY,
	EmployeeID INT NOT NULL CONSTRAINT FK_EmployeePhoneNumbers_Employees REFERENCES dbo.Employees ( EmployeeID ),
	PhoneTypeID INT NOT NULL CONSTRAINT FK_EmployeePhoneNumbers_PhoneTypes REFERENCES dbo.PhoneTypes (PhoneTypeID ),
	PhoneNumber NVARCHAR(14) NULL
); 


CREATE TABLE dbo.BenefitTypes(
	BenefitTypeID INT IDENTITY CONSTRAINT PK_BenefitType PRIMARY KEY, 
	BenefitType NVARCHAR(100) NOT NULL,
	BenefitCompanyName NVARCHAR(100) NOT NULL,
    PolicyNumber INT NULL
);

CREATE UNIQUE INDEX AK_BenefitTypes_PolicyNumber ON dbo.BenefitTypes (PolicyNumber);

CREATE TABLE dbo.EmployeeBenefits(
	EmployeeBenefitID INT IDENTITY CONSTRAINT PK_EmployeeBenefits PRIMARY KEY, 
	EmployeeId INT NOT NULL CONSTRAINT FK_EmployeeBenefits_Employees REFERENCES dbo.Employees ( EmployeeID ),
	BenefitTypeID INT NOT NULL CONSTRAINT FK_EmployeeBenefits_BenefitTypes REFERENCES dbo.BenefitTypes ( BenefitTypeID  ),
    StartDate DATE NULL,
	CONSTRAINT CK_EmployeeBenefits_StartDate CHECK ( StartDate <=  GETDATE() )

	
);

CREATE TABLE dbo.Providers (
	ProviderID INT IDENTITY CONSTRAINT PK_Providers PRIMARY KEY, 
	ProviderName  NVARCHAR(50) NOT NULL,
	ProviderAddress NVARCHAR(50) NOT NULL,
	ProviderCity NVARCHAR(50) NOT NULL,
);

CREATE TABLE dbo.Claims(
	ClaimsID INT IDENTITY CONSTRAINT PK_Claims PRIMARY KEY, 
	ProviderID INT NOT NULL CONSTRAINT FK_Claims_Providers REFERENCES dbo.Providers ( ProviderID ),
	ClaimAmount decimal(18, 2) NOT NULL CONSTRAINT DF_Claims_ClaimAmount DEFAULT 0,
	ServiceDate DATE NOT NULL CONSTRAINT DF_Claims_ServiceDate DEFAULT GETDATE(),
	EmployeeBenefitID INT NULL CONSTRAINT FK_Claims_EmployeeBenefits REFERENCES dbo.EmployeeBenefits ( EmployeeBenefitID ),
	ClaimDate DATE NOT NULL CONSTRAINT DF_Claims_ClaimDate DEFAULT GETDATE(),
	
	CONSTRAINT CK_Claims_ServiceDate CHECK ( ServiceDate <=  GETDATE() ),
    CONSTRAINT CK_Claims_ClaimDate CHECK ( ClaimDate <=  GETDATE() )

);

CREATE INDEX IX_HumanResources_EmployeeID_BenefitType ON dbo.EmployeeBenefits (EmployeeID, BenefitTypeID);
CREATE INDEX IX_HumanResources_EmployeeID_PhoneType ON dbo.EmployeePhoneNumbers (EmployeeID, PhoneTypeID);
CREATE INDEX IX_HumanResources_Providers_EmployeeBenefits ON dbo.Claims (ProviderID, EmployeeBenefitID);
CREATE INDEX IX_HumanResources_BenefitType_EmployeeID ON dbo.EmployeeBenefits ( BenefitTypeID,EmployeeID);
CREATE INDEX IX_HumanResources_PhoneTypeEmployeeID ON dbo.EmployeePhoneNumbers ( PhoneTypeID,EmployeeID);
CREATE INDEX IX_HumanResources_EmployeeBenefits_Providers ON dbo.Claims ( EmployeeBenefitID,ProviderID);


GO

