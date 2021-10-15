using System;
using System.Collections.Generic;
using System.Threading.Tasks;
using ExercisesDAL;
using System.Diagnostics;
using Xunit;


namespace ExerciseTests
{
    public class DAOTests
    {
        [Fact]
        public async Task Student_GetByLastnameTest()
        {
            StudentDAO dao = new StudentDAO();
            Student selectedStudent = await dao.GetByLastname("Pet");
            Assert.NotNull(selectedStudent);
        }

        [Fact]

        public async Task Student_GetByIdTest()
        {
            StudentDAO dao = new StudentDAO();
            Student selectedStudent = await dao.GetById(1);
            Assert.NotNull(selectedStudent);
        }

        [Fact]
        public async Task Student_GetAllTest()
        {
            StudentDAO dao = new StudentDAO();
            List<Student> List1 = await dao.GetAll();
            Assert.NotNull(List1);
        }

        [Fact]
        public async Task Student_AddTest()
        {
            StudentDAO dao = new StudentDAO();
            Student newStudent = new Student {
                FirstName = "Anakin",
                LastName = "Skywalker",
                PhoneNo = "(555)-555-4321",
                Title = "Mr.",
                DivisionId = 20,
                Email = "as@sameschool.com"
            };
            int response = await dao.Add(newStudent);
            Assert.True(response != -1);
        }

        [Fact]
        public async Task Student_UpdateTest()
        {
            StudentDAO dao = new StudentDAO();
            Student studentForUpdate = await dao.GetByLastname("Skywalker");
            if(studentForUpdate != null){
                string oldPhoneNo = studentForUpdate.PhoneNo;
                string newPhoneNo = oldPhoneNo == "555-555-4321" ? "555-555-5555" : "555-555-4321";
                studentForUpdate.PhoneNo = newPhoneNo;
                }
            Assert.True(await dao.Update(studentForUpdate) == UpdateStatus.Ok);
        }

        [Fact]
        public async Task Student_DeleteTest()
        {
            StudentDAO dao = new StudentDAO();
            int response = await dao.Delete(5005);
            Assert.True(response != -1);
        }

        [Fact]
        public async Task Student_ConcurrencyTest()
        {
            StudentDAO dao1 = new StudentDAO();
            StudentDAO dao2 = new StudentDAO();
            Student studentForUpdate1 = await dao1.GetByLastname("Skywalker");
            Student studentForUpdate2 = await dao2.GetByLastname("Skywalker");

            if(studentForUpdate1 != null)
            {
                string oldPhoneNo = studentForUpdate1.PhoneNo;
                string newPhoneNo = oldPhoneNo == "555-555-4321" ? "555-555-5555" : "555-555-4321";
                studentForUpdate1.PhoneNo = newPhoneNo;
                if (await dao1.Update(studentForUpdate1) == UpdateStatus.Ok)
                {
                    studentForUpdate2.PhoneNo = "777-777-7777";
                    Assert.True(await dao2.Update(studentForUpdate2) == UpdateStatus.Stale);
                }
                else
                    Assert.True(false);
            }
        }
    }
}
