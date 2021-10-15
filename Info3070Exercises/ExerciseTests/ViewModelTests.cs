using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using ExercisesViewModels;
using Xunit;
using System.Diagnostics;

namespace ExerciseTests
{
    public class ViewModelTests
    {
       [Fact]
       public async Task Student_GetByLastnameTest()
        {
            StudentViewModel vm = null;
            try
            {
                vm = new StudentViewModel { Lastname = "Rezende" };
                await vm.GetByLastname();
            }
            catch(Exception ex)
            {
                Debug.WriteLine("Error - " + ex.Message);
            }
            Assert.NotNull(vm.Firstname);
        }

        [Fact]
        public async Task Student_GetByIdTest()
        {
            StudentViewModel vm = null;
            try
            {
                vm = new StudentViewModel { Id = 1 };
                await vm.GetById();
            }
            catch (Exception ex)
            {
                Debug.WriteLine("Error - " + ex.Message);
            }
            Assert.NotNull(vm.Firstname);
        }

        [Fact]
        public async Task Student_GetAllTest()
        {
            List<StudentViewModel> StuList = new List<StudentViewModel>();
            try
            {
                StudentViewModel vm = new StudentViewModel();
                StuList = await vm.GetAll();
            }
            catch (Exception ex)
            {
                Debug.WriteLine("Error - " + ex.Message);
            }
            Assert.NotNull(StuList);
        }

        [Fact]
        public async Task Student_AddTest()
        {
            StudentViewModel vm1 = null;
            try
            {
                StudentViewModel vm = new StudentViewModel 
                {
                    Title = "Mr.",
                    Firstname = "Ygor",
                    Lastname = "Rezende",
                    Phoneno = "(555)-555-5555",
                    Email = "yr@someschool.ca",
                    DivisionId = 30,
                };
                await vm.Add();
                //checking if the the student was added
                vm1 = new StudentViewModel { Lastname = "Rezende" };
                await vm1.GetByLastname();
            }
            catch (Exception ex)
            {
                Debug.WriteLine("Error - " + ex.Message);
            }
            //checking if the the student was added
            Assert.NotNull(vm1.Firstname);
        }

        [Fact]
        public async Task Student_UpdateTest()
        {
            int response = -1;
            try
            {
                StudentViewModel vm = new StudentViewModel { Lastname = "Rezende" };
                await vm.GetByLastname();
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
        public async Task Student_ConcurrencyTest()
        {
            int studentsUpdated = -1;
            try
            {
                StudentViewModel vm1 = new StudentViewModel { Lastname = "Rezende" };
                StudentViewModel vm2 = new StudentViewModel { Lastname = "Rezende" };
                await vm1.GetByLastname();
                await vm2.GetByLastname();
                vm1.Phoneno = vm1.Phoneno == "(555)555-5551" ? "(555)555-5552" : "(555)555-5551";
                if (await vm1.Update() == 1)
                {
                    vm2.Phoneno = "(777)777-5551";
                    studentsUpdated = await vm2.Update();
                }
            }
            catch(Exception ex)
            {
                Debug.WriteLine("Error - " + ex.Message);
            }
            Assert.True(studentsUpdated == -2);
        }

        [Fact]
        public async Task Student_DeleteTest()
        {
            int response = -1;
            try
            {
                StudentViewModel vm = new StudentViewModel { Lastname = "Rezende" };
                await vm.GetByLastname();
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
