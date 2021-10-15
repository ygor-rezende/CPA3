using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using HelpdeskViewModels;
using System.Diagnostics;
using Xunit;

namespace CaseStudyTests
{
    public class EmployeeViewModelTests
    {
        [Fact]
        public async Task Employee_GetByEmailTest()
        {
            EmployeeViewModel vm = null;
            try
            {
                vm = new EmployeeViewModel { Email = "pp@abc.com" };
                await vm.GetByEmail();
            }
            catch (Exception ex)
            {
                Debug.WriteLine("Error - " + ex.Message);
            }
            Assert.NotNull(vm.Firstname);
        }

        [Fact]
        public async Task Employee_GetByIdTest()
        {
            EmployeeViewModel vm = null;
            try
            {
                vm = new EmployeeViewModel { Id = 1 };
                await vm.GetById();
            }
            catch (Exception ex)
            {
                Debug.WriteLine("Error - " + ex.Message);
            }
            Assert.NotNull(vm.Firstname);
        }

        [Fact]
        public async Task Employee_GetAllTest()
        {
            List<EmployeeViewModel> empList = new List<EmployeeViewModel>();
            try
            {
                EmployeeViewModel vm = new EmployeeViewModel();
                empList = await vm.GetAll();
            }
            catch (Exception ex)
            {
                Debug.WriteLine("Error - " + ex.Message);
            }
            Assert.NotNull(empList);
        }

        [Fact]
        public async Task Employee_AddTest()
        {
            EmployeeViewModel vm1 = null;
            try
            {
                EmployeeViewModel vm = new EmployeeViewModel
                {
                    Title = "Mr.",
                    Firstname = "Ygor",
                    Lastname = "Rezende",
                    Phoneno = "(555)-555-5555",
                    Email = "yr@abc.com",
                    DepartmentId = 200,
                };
                await vm.Add();
                //checking if the the Employee was added
                vm1 = new EmployeeViewModel { Email = "yr@abc.com" };
                await vm1.GetByEmail();
            }
            catch (Exception ex)
            {
                Debug.WriteLine("Error - " + ex.Message);
            }
            //checking if the the Employee was added
            Assert.NotNull(vm1.Firstname);
        }

        [Fact]
        public async Task Employee_UpdateTest()
        {
            int response = -1;
            try
            {
                EmployeeViewModel vm = new EmployeeViewModel { Email = "yr@abc.com" };
                await vm.GetByEmail();
                vm.Phoneno = vm.Phoneno == "(555)-555-5551" ? "(555)-555-5552" : "(555)-555-5551";
                response = await vm.Update();
            }
            catch (Exception ex)
            {
                Debug.WriteLine("Error - " + ex.Message);
            }
            Assert.True(response >= 0);
        }

        [Fact]
        public async Task Employee_DeleteTest()
        {
            int response = -1;
            try
            {
                EmployeeViewModel vm = new EmployeeViewModel { Email = "yr@abc.com" };
                await vm.GetByEmail();
                response = await vm.Delete();
            }
            catch (Exception ex)
            {
                Debug.WriteLine("Error - " + ex.Message);
            }
            Assert.True(response >= 0);
        }
    }
}

