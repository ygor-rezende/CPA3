using System;
using System.Collections.Generic;
using System.Threading.Tasks;
using Microsoft.EntityFrameworkCore;
using System.Diagnostics;
using System.Reflection;


namespace ExercisesDAL
{
    public class StudentDAO
    {
        readonly IRepository<Student> repository;

        public StudentDAO()
        {
            repository = new SomeSchoolRepository<Student>();
        }

        public async Task<Student> GetByLastname (string name)
        {
            Student selectedStudent = null;
            try
            {
                selectedStudent = await repository.GetOne(stu => stu.LastName == name);
            }
            catch (Exception ex)
            {
                Debug.WriteLine("Problem in " + GetType().Name + " " + MethodBase.GetCurrentMethod().Name + " " + ex.Message);
                throw;
            }
            return selectedStudent;
        }// end of GetByLastname

        public async Task<Student> GetById (int id)
        {
            Student selectedStudent = null;
            try
            {
                selectedStudent = await repository.GetOne(stu => stu.Id == id);
            }
            catch(Exception ex)
            {
                Debug.WriteLine("Problem in " + GetType().Name + " " + MethodBase.GetCurrentMethod().Name + " " + ex.Message);
                throw;
            }
            return selectedStudent;
        }// end GetById

        public async Task<List<Student>> GetAll()
        {
            List<Student> allStudents = new List<Student>();
            try
            {
                
                allStudents = await repository.GetAll();
            }
            catch(Exception ex)
            {
                Debug.WriteLine("Problem in " + GetType().Name + " " + MethodBase.GetCurrentMethod().Name + " " + ex.Message);
                throw;
            }
            return allStudents;
        }// end GetAll

        public async Task<int> Add(Student newStudent)
        {
            try
            {
                await repository.Add(newStudent);
            }
            catch(Exception ex)
            {
                Debug.WriteLine("Problem in " + GetType().Name + " " + MethodBase.GetCurrentMethod().Name + " " + ex.Message);
                throw;
            }
            return newStudent.Id;
        }// end Add

        public async Task<UpdateStatus> Update(Student updatedStudent)
        {
            UpdateStatus studentUpdated = UpdateStatus.Failed;
            try
            {
                studentUpdated = await repository.Update(updatedStudent);
            }
            catch (Exception ex)
            {
                Debug.WriteLine("Problem in " + GetType().Name + " " + MethodBase.GetCurrentMethod().Name + " " + ex.Message);
                throw;
            }
            return studentUpdated;
        }// end Update

        public async Task<int> Delete(int id)
        {
            int studentsDeleted = -1;
            try
            {
                studentsDeleted = await repository.Delete(id); //return # rows deleted
            }
            catch (Exception ex)
            {
                Debug.WriteLine("Problem in " + GetType().Name + " " + MethodBase.GetCurrentMethod().Name + " " + ex.Message);
                throw;
            }
            return studentsDeleted;
        }
    }
}
