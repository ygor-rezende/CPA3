using System;
using Xunit;
using HelpdeskDAL;
using System.Threading.Tasks;
using System.Collections.Generic;

namespace CaseStudyTests
{
    public class DAOTests
    {
        [Fact]
        public async Task Employee_GetByEmailTest()
        {
            EmployeeDAO dao = new EmployeeDAO();
            Employee selectedEmployee = await dao.GetByEmail("bs@abc.com");
            Assert.NotNull(selectedEmployee);
        }

        [Fact]

        public async Task Employee_GetByIdTest()
        {
            EmployeeDAO dao = new EmployeeDAO();
            Employee selectedEmployee = await dao.GetById(1);
            Assert.NotNull(selectedEmployee);
        }

        [Fact]
        public async Task Employee_GetAllTest()
        {
            EmployeeDAO dao = new EmployeeDAO();
            List<Employee> List1 = await dao.GetAll();
            Assert.NotNull(List1);
        }

        [Fact]
        public async Task Employee_AddTest()
        {
            EmployeeDAO dao = new EmployeeDAO();
            Employee newEmployee = new Employee
            {
                FirstName = "Ygor",
                LastName = "Rezende",
                PhoneNo = "(555)-555-4321",
                Title = "Mr.",
                DepartmentId = 100,
                Email = "yr@abc.com"
            };
            int response = await dao.Add(newEmployee);
            Assert.True(response != -1);
        }

        [Fact]
        public async Task Employee_UpdateTest()
        {
            EmployeeDAO dao = new EmployeeDAO();
            Employee EmployeeForUpdate = await dao.GetByEmail("yr@abc.com");
            if (EmployeeForUpdate != null)
            {
                string oldPhoneNo = EmployeeForUpdate.PhoneNo;
                string newPhoneNo = oldPhoneNo == "(555)-555-1234" ? "(555)-555-5555" : "(555)-555-1234";
                EmployeeForUpdate.PhoneNo = newPhoneNo;
            }
            Assert.True(await dao.Update(EmployeeForUpdate) == UpdateStatus.Ok);
        }

        [Fact]
        public async Task Employee_DeleteTest()
        {
            EmployeeDAO dao = new EmployeeDAO();
            int response = await dao.Delete(2002);
            Assert.True(response != -1);
        }

        [Fact]
        public async Task Employee_ConcurrencyTest()
        {
            EmployeeDAO dao1 = new EmployeeDAO();
            EmployeeDAO dao2 = new EmployeeDAO();
            Employee EmployeeForUpdate1 = await dao1.GetByEmail("yr@abc.com");
            Employee EmployeeForUpdate2 = await dao2.GetByEmail("yr@abc.com");

            if (EmployeeForUpdate1 != null)
            {
                string oldPhoneNo = EmployeeForUpdate1.PhoneNo;
                string newPhoneNo = oldPhoneNo == "555-555-4321" ? "555-555-5555" : "555-555-4321";
                EmployeeForUpdate1.PhoneNo = newPhoneNo;
                if (await dao1.Update(EmployeeForUpdate1) == UpdateStatus.Ok)
                {
                    EmployeeForUpdate2.PhoneNo = "555-777-7777";
                    Assert.True(await dao2.Update(EmployeeForUpdate2) == UpdateStatus.Stale);
                }
                else
                    Assert.True(false);
            }
        }
    }
}
