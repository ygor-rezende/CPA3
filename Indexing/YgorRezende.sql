USE [master]
GO
/****** Object:  Database [HumanResources]    Script Date: 10/3/2021 4:20:17 PM ******/
CREATE DATABASE [HumanResources]
 CONTAINMENT = NONE
 ON  PRIMARY 
( NAME = N'HumanResources', FILENAME = N'C:\Program Files\Microsoft SQL Server\MSSQL15.INFO5052\MSSQL\DATA\HumanResources.mdf' , SIZE = 8192KB , MAXSIZE = UNLIMITED, FILEGROWTH = 65536KB )
 LOG ON 
( NAME = N'HumanResources_log', FILENAME = N'C:\Program Files\Microsoft SQL Server\MSSQL15.INFO5052\MSSQL\DATA\HumanResources_log.ldf' , SIZE = 8192KB , MAXSIZE = 2048GB , FILEGROWTH = 65536KB )
 WITH CATALOG_COLLATION = DATABASE_DEFAULT
GO
ALTER DATABASE [HumanResources] SET COMPATIBILITY_LEVEL = 150
GO
IF (1 = FULLTEXTSERVICEPROPERTY('IsFullTextInstalled'))
begin
EXEC [HumanResources].[dbo].[sp_fulltext_database] @action = 'enable'
end
GO
ALTER DATABASE [HumanResources] SET ANSI_NULL_DEFAULT OFF 
GO
ALTER DATABASE [HumanResources] SET ANSI_NULLS OFF 
GO
ALTER DATABASE [HumanResources] SET ANSI_PADDING OFF 
GO
ALTER DATABASE [HumanResources] SET ANSI_WARNINGS OFF 
GO
ALTER DATABASE [HumanResources] SET ARITHABORT OFF 
GO
ALTER DATABASE [HumanResources] SET AUTO_CLOSE OFF 
GO
ALTER DATABASE [HumanResources] SET AUTO_SHRINK OFF 
GO
ALTER DATABASE [HumanResources] SET AUTO_UPDATE_STATISTICS ON 
GO
ALTER DATABASE [HumanResources] SET CURSOR_CLOSE_ON_COMMIT OFF 
GO
ALTER DATABASE [HumanResources] SET CURSOR_DEFAULT  GLOBAL 
GO
ALTER DATABASE [HumanResources] SET CONCAT_NULL_YIELDS_NULL OFF 
GO
ALTER DATABASE [HumanResources] SET NUMERIC_ROUNDABORT OFF 
GO
ALTER DATABASE [HumanResources] SET QUOTED_IDENTIFIER OFF 
GO
ALTER DATABASE [HumanResources] SET RECURSIVE_TRIGGERS OFF 
GO
ALTER DATABASE [HumanResources] SET  ENABLE_BROKER 
GO
ALTER DATABASE [HumanResources] SET AUTO_UPDATE_STATISTICS_ASYNC OFF 
GO
ALTER DATABASE [HumanResources] SET DATE_CORRELATION_OPTIMIZATION OFF 
GO
ALTER DATABASE [HumanResources] SET TRUSTWORTHY OFF 
GO
ALTER DATABASE [HumanResources] SET ALLOW_SNAPSHOT_ISOLATION OFF 
GO
ALTER DATABASE [HumanResources] SET PARAMETERIZATION SIMPLE 
GO
ALTER DATABASE [HumanResources] SET READ_COMMITTED_SNAPSHOT OFF 
GO
ALTER DATABASE [HumanResources] SET HONOR_BROKER_PRIORITY OFF 
GO
ALTER DATABASE [HumanResources] SET RECOVERY FULL 
GO
ALTER DATABASE [HumanResources] SET  MULTI_USER 
GO
ALTER DATABASE [HumanResources] SET PAGE_VERIFY CHECKSUM  
GO
ALTER DATABASE [HumanResources] SET DB_CHAINING OFF 
GO
ALTER DATABASE [HumanResources] SET FILESTREAM( NON_TRANSACTED_ACCESS = OFF ) 
GO
ALTER DATABASE [HumanResources] SET TARGET_RECOVERY_TIME = 60 SECONDS 
GO
ALTER DATABASE [HumanResources] SET DELAYED_DURABILITY = DISABLED 
GO
ALTER DATABASE [HumanResources] SET ACCELERATED_DATABASE_RECOVERY = OFF  
GO
EXEC sys.sp_db_vardecimal_storage_format N'HumanResources', N'ON'
GO
ALTER DATABASE [HumanResources] SET QUERY_STORE = OFF
GO
USE [HumanResources]
GO
/****** Object:  Table [dbo].[BenefitTypes]    Script Date: 10/3/2021 4:20:18 PM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[BenefitTypes](
	[BenefitTypeID] [int] IDENTITY(1,1) NOT NULL,
	[BenefitType] [nvarchar](100) NOT NULL,
	[BenefitCompanyName] [nvarchar](100) NOT NULL,
	[PolicyNumber] [int] NULL,
 CONSTRAINT [PK_BenefitType] PRIMARY KEY CLUSTERED 
(
	[BenefitTypeID] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY],
 CONSTRAINT [UK_BenefitTypes_PolicyNumber] UNIQUE NONCLUSTERED 
(
	[PolicyNumber] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[Claims]    Script Date: 10/3/2021 4:20:18 PM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[Claims](
	[ClaimsID] [int] IDENTITY(1,1) NOT NULL,
	[ProviderID] [int] NOT NULL,
	[ClaimAmount] [decimal](18, 2) NOT NULL,
	[ServiceDate] [date] NOT NULL,
	[EmployeeBenefitID] [int] NULL,
	[ClaimDate] [date] NOT NULL,
 CONSTRAINT [PK_Claims] PRIMARY KEY CLUSTERED 
(
	[ClaimsID] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[Departments]    Script Date: 10/3/2021 4:20:18 PM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[Departments](
	[DepartmentID] [int] IDENTITY(1,1) NOT NULL,
	[DepartmentName] [nvarchar](150) NOT NULL,
	[StreetAddress] [nvarchar](50) NOT NULL,
	[City] [nvarchar](50) NOT NULL,
	[Province] [nvarchar](50) NOT NULL,
	[PostalCode] [char](6) NOT NULL,
	[MaxWorkstations] [int] NOT NULL,
 CONSTRAINT [PK_Department] PRIMARY KEY CLUSTERED 
(
	[DepartmentID] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[EmployeeBenefits]    Script Date: 10/3/2021 4:20:18 PM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[EmployeeBenefits](
	[EmployeeBenefitID] [int] IDENTITY(1,1) NOT NULL,
	[EmployeeId] [int] NOT NULL,
	[BenefitTypeID] [int] NOT NULL,
	[StartDate] [date] NULL,
 CONSTRAINT [PK_EmployeeBenefits] PRIMARY KEY CLUSTERED 
(
	[EmployeeBenefitID] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[EmployeePhoneNumbers]    Script Date: 10/3/2021 4:20:18 PM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[EmployeePhoneNumbers](
	[EmployeePhoneNumberID] [int] IDENTITY(1,1) NOT NULL,
	[EmployeeID] [int] NOT NULL,
	[PhoneTypeID] [int] NOT NULL,
	[PhoneNumber] [nvarchar](14) NULL,
 CONSTRAINT [PK_EmployeePhoneNumbers] PRIMARY KEY CLUSTERED 
(
	[EmployeePhoneNumberID] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[Employees]    Script Date: 10/3/2021 4:20:18 PM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[Employees](
	[EmployeeID] [int] IDENTITY(1,1) NOT NULL,
	[FirstName] [nvarchar](50) NOT NULL,
	[MiddleName] [nvarchar](50) NULL,
	[LastName] [nvarchar](50) NOT NULL,
	[DateofBirth] [date] NOT NULL,
	[SIN] [char](9) NOT NULL,
	[DefaultDepartmentID] [int] NOT NULL,
	[CurrentDepartmentID] [int] NOT NULL,
	[ReportsToEmployeeID] [int] NULL,
	[StreetAddress] [nvarchar](50) NULL,
	[City] [nvarchar](50) NULL,
	[Province] [nvarchar](50) NULL,
	[PostalCode] [char](6) NULL,
	[StartDate] [date] NOT NULL,
	[BaseSalary] [decimal](18, 2) NOT NULL,
 CONSTRAINT [PK_Employee] PRIMARY KEY CLUSTERED 
(
	[EmployeeID] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY],
 CONSTRAINT [UK_Employees_SIN] UNIQUE NONCLUSTERED 
(
	[SIN] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[PhoneTypes]    Script Date: 10/3/2021 4:20:18 PM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[PhoneTypes](
	[PhoneTypeID] [int] IDENTITY(1,1) NOT NULL,
	[PhoneType] [nvarchar](50) NOT NULL,
 CONSTRAINT [PK_PhoneTypes] PRIMARY KEY CLUSTERED 
(
	[PhoneTypeID] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[Providers]    Script Date: 10/3/2021 4:20:18 PM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[Providers](
	[ProviderID] [int] IDENTITY(1,1) NOT NULL,
	[ProviderName] [nvarchar](50) NOT NULL,
	[ProviderAddress] [nvarchar](50) NOT NULL,
	[ProviderCity] [nvarchar](50) NOT NULL,
 CONSTRAINT [PK_Providers] PRIMARY KEY CLUSTERED 
(
	[ProviderID] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Index [IX_Claims_EmployeeBenefitID_ProviderID]    Script Date: 10/3/2021 4:20:18 PM ******/
CREATE NONCLUSTERED INDEX [IX_Claims_EmployeeBenefitID_ProviderID] ON [dbo].[Claims]
(
	[EmployeeBenefitID] ASC,
	[ProviderID] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, SORT_IN_TEMPDB = OFF, DROP_EXISTING = OFF, ONLINE = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
GO
/****** Object:  Index [IX_Claims_ProviderID_EmployeeBenefitID]    Script Date: 10/3/2021 4:20:18 PM ******/
CREATE NONCLUSTERED INDEX [IX_Claims_ProviderID_EmployeeBenefitID] ON [dbo].[Claims]
(
	[ProviderID] ASC,
	[EmployeeBenefitID] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, SORT_IN_TEMPDB = OFF, DROP_EXISTING = OFF, ONLINE = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
GO
SET ANSI_PADDING ON
GO
/****** Object:  Index [AK_Departments_DepartmentName]    Script Date: 10/3/2021 4:20:18 PM ******/
CREATE UNIQUE NONCLUSTERED INDEX [AK_Departments_DepartmentName] ON [dbo].[Departments]
(
	[DepartmentName] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, SORT_IN_TEMPDB = OFF, IGNORE_DUP_KEY = OFF, DROP_EXISTING = OFF, ONLINE = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
GO
/****** Object:  Index [IX_EmployeeBenefits_BenefitTypeID_EmployeeID]    Script Date: 10/3/2021 4:20:18 PM ******/
CREATE NONCLUSTERED INDEX [IX_EmployeeBenefits_BenefitTypeID_EmployeeID] ON [dbo].[EmployeeBenefits]
(
	[BenefitTypeID] ASC,
	[EmployeeId] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, SORT_IN_TEMPDB = OFF, DROP_EXISTING = OFF, ONLINE = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
GO
/****** Object:  Index [IX_EmployeeBenefits_EmployeeId_BenefitTypeID]    Script Date: 10/3/2021 4:20:18 PM ******/
CREATE NONCLUSTERED INDEX [IX_EmployeeBenefits_EmployeeId_BenefitTypeID] ON [dbo].[EmployeeBenefits]
(
	[EmployeeId] ASC,
	[BenefitTypeID] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, SORT_IN_TEMPDB = OFF, DROP_EXISTING = OFF, ONLINE = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
GO
/****** Object:  Index [IX_EmployeePhoneNumbers_EmployeeID_PhoneTypeID]    Script Date: 10/3/2021 4:20:18 PM ******/
CREATE NONCLUSTERED INDEX [IX_EmployeePhoneNumbers_EmployeeID_PhoneTypeID] ON [dbo].[EmployeePhoneNumbers]
(
	[EmployeeID] ASC,
	[PhoneTypeID] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, SORT_IN_TEMPDB = OFF, DROP_EXISTING = OFF, ONLINE = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
GO
/****** Object:  Index [IX_EmployeePhoneNumbers_PhoneTypeID_EmployeeID]    Script Date: 10/3/2021 4:20:18 PM ******/
CREATE NONCLUSTERED INDEX [IX_EmployeePhoneNumbers_PhoneTypeID_EmployeeID] ON [dbo].[EmployeePhoneNumbers]
(
	[PhoneTypeID] ASC,
	[EmployeeID] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, SORT_IN_TEMPDB = OFF, DROP_EXISTING = OFF, ONLINE = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
GO
SET ANSI_PADDING ON
GO
/****** Object:  Index [IX_Employees_City]    Script Date: 10/3/2021 4:20:18 PM ******/
CREATE NONCLUSTERED INDEX [IX_Employees_City] ON [dbo].[Employees]
(
	[City] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, SORT_IN_TEMPDB = OFF, DROP_EXISTING = OFF, ONLINE = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
GO
/****** Object:  Index [IX_Employees_CurrentDepartmentID]    Script Date: 10/3/2021 4:20:18 PM ******/
CREATE NONCLUSTERED INDEX [IX_Employees_CurrentDepartmentID] ON [dbo].[Employees]
(
	[CurrentDepartmentID] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, SORT_IN_TEMPDB = OFF, DROP_EXISTING = OFF, ONLINE = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
GO
/****** Object:  Index [IX_Employees_DefaultDepartmentID]    Script Date: 10/3/2021 4:20:18 PM ******/
CREATE NONCLUSTERED INDEX [IX_Employees_DefaultDepartmentID] ON [dbo].[Employees]
(
	[DefaultDepartmentID] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, SORT_IN_TEMPDB = OFF, DROP_EXISTING = OFF, ONLINE = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
GO
SET ANSI_PADDING ON
GO
/****** Object:  Index [IX_Employees_PostalCode_City]    Script Date: 10/3/2021 4:20:18 PM ******/
CREATE NONCLUSTERED INDEX [IX_Employees_PostalCode_City] ON [dbo].[Employees]
(
	[PostalCode] ASC,
	[City] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, SORT_IN_TEMPDB = OFF, DROP_EXISTING = OFF, ONLINE = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
GO
/****** Object:  Index [IX_Employees_ReportsToEmployeeID]    Script Date: 10/3/2021 4:20:18 PM ******/
CREATE NONCLUSTERED INDEX [IX_Employees_ReportsToEmployeeID] ON [dbo].[Employees]
(
	[ReportsToEmployeeID] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, SORT_IN_TEMPDB = OFF, DROP_EXISTING = OFF, ONLINE = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
GO
ALTER TABLE [dbo].[Claims] ADD  CONSTRAINT [DF_Claims_ClaimAmount]  DEFAULT ((0)) FOR [ClaimAmount]
GO
ALTER TABLE [dbo].[Claims] ADD  CONSTRAINT [DF_Claims_ServiceDate]  DEFAULT (getdate()) FOR [ServiceDate]
GO
ALTER TABLE [dbo].[Claims] ADD  CONSTRAINT [DF_Claims_ClaimDate]  DEFAULT (getdate()) FOR [ClaimDate]
GO
ALTER TABLE [dbo].[Departments] ADD  CONSTRAINT [DF_Departments_MaxWorkstations]  DEFAULT ((1)) FOR [MaxWorkstations]
GO
ALTER TABLE [dbo].[Employees] ADD  CONSTRAINT [DF_Employees_BaseSalary]  DEFAULT ((0)) FOR [BaseSalary]
GO
ALTER TABLE [dbo].[Claims]  WITH CHECK ADD  CONSTRAINT [FK_Claims_EmployeeBenefits] FOREIGN KEY([EmployeeBenefitID])
REFERENCES [dbo].[EmployeeBenefits] ([EmployeeBenefitID])
GO
ALTER TABLE [dbo].[Claims] CHECK CONSTRAINT [FK_Claims_EmployeeBenefits]
GO
ALTER TABLE [dbo].[Claims]  WITH CHECK ADD  CONSTRAINT [FK_Claims_Providers] FOREIGN KEY([ProviderID])
REFERENCES [dbo].[Providers] ([ProviderID])
GO
ALTER TABLE [dbo].[Claims] CHECK CONSTRAINT [FK_Claims_Providers]
GO
ALTER TABLE [dbo].[EmployeeBenefits]  WITH CHECK ADD  CONSTRAINT [FK_EmployeeBenefits_BenefitTypes] FOREIGN KEY([BenefitTypeID])
REFERENCES [dbo].[BenefitTypes] ([BenefitTypeID])
GO
ALTER TABLE [dbo].[EmployeeBenefits] CHECK CONSTRAINT [FK_EmployeeBenefits_BenefitTypes]
GO
ALTER TABLE [dbo].[EmployeeBenefits]  WITH CHECK ADD  CONSTRAINT [FK_EmployeeBenefits_Employees] FOREIGN KEY([EmployeeId])
REFERENCES [dbo].[Employees] ([EmployeeID])
GO
ALTER TABLE [dbo].[EmployeeBenefits] CHECK CONSTRAINT [FK_EmployeeBenefits_Employees]
GO
ALTER TABLE [dbo].[EmployeePhoneNumbers]  WITH CHECK ADD  CONSTRAINT [FK_EmployeePhoneNumbers_Employees] FOREIGN KEY([EmployeeID])
REFERENCES [dbo].[Employees] ([EmployeeID])
GO
ALTER TABLE [dbo].[EmployeePhoneNumbers] CHECK CONSTRAINT [FK_EmployeePhoneNumbers_Employees]
GO
ALTER TABLE [dbo].[EmployeePhoneNumbers]  WITH CHECK ADD  CONSTRAINT [FK_EmployeePhoneNumbers_PhoneTypes] FOREIGN KEY([PhoneTypeID])
REFERENCES [dbo].[PhoneTypes] ([PhoneTypeID])
GO
ALTER TABLE [dbo].[EmployeePhoneNumbers] CHECK CONSTRAINT [FK_EmployeePhoneNumbers_PhoneTypes]
GO
ALTER TABLE [dbo].[Employees]  WITH CHECK ADD  CONSTRAINT [FK_Employees_Departments_Current] FOREIGN KEY([CurrentDepartmentID])
REFERENCES [dbo].[Departments] ([DepartmentID])
GO
ALTER TABLE [dbo].[Employees] CHECK CONSTRAINT [FK_Employees_Departments_Current]
GO
ALTER TABLE [dbo].[Employees]  WITH CHECK ADD  CONSTRAINT [FK_Employees_Departments_Default] FOREIGN KEY([DefaultDepartmentID])
REFERENCES [dbo].[Departments] ([DepartmentID])
GO
ALTER TABLE [dbo].[Employees] CHECK CONSTRAINT [FK_Employees_Departments_Default]
GO
ALTER TABLE [dbo].[Employees]  WITH CHECK ADD  CONSTRAINT [FK_Employees_Employees] FOREIGN KEY([ReportsToEmployeeID])
REFERENCES [dbo].[Employees] ([EmployeeID])
GO
ALTER TABLE [dbo].[Employees] CHECK CONSTRAINT [FK_Employees_Employees]
GO
ALTER TABLE [dbo].[Claims]  WITH CHECK ADD  CONSTRAINT [CK_Claims] CHECK  (([ServiceDate]<=getdate() AND [ClaimDate]<=getdate()))
GO
ALTER TABLE [dbo].[Claims] CHECK CONSTRAINT [CK_Claims]
GO
ALTER TABLE [dbo].[Departments]  WITH CHECK ADD  CONSTRAINT [CK_Departments] CHECK  (([MaxWorkstations]>=(0)))
GO
ALTER TABLE [dbo].[Departments] CHECK CONSTRAINT [CK_Departments]
GO
ALTER TABLE [dbo].[EmployeeBenefits]  WITH CHECK ADD  CONSTRAINT [CK_EmployeesBenefits] CHECK  (([StartDate]<=getdate()))
GO
ALTER TABLE [dbo].[EmployeeBenefits] CHECK CONSTRAINT [CK_EmployeesBenefits]
GO
ALTER TABLE [dbo].[Employees]  WITH CHECK ADD  CONSTRAINT [CK_Employees] CHECK  (([DateofBirth]<=getdate() AND [StartDate]<=getdate()))
GO
ALTER TABLE [dbo].[Employees] CHECK CONSTRAINT [CK_Employees]
GO
USE [master]
GO
ALTER DATABASE [HumanResources] SET  READ_WRITE 
GO
