using System;
using System.Collections.Generic;
using Microsoft.EntityFrameworkCore;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Diagnostics;
using System.Reflection;

namespace HelpdeskDAL
{
    public class EmployeeDAO
    {
        readonly IRepository<Employee> repository;

        public EmployeeDAO()
        {
            repository = new HelpdeskRepository<Employee>();
        }
        public async Task<Employee> GetByEmail(string email)
        {
            Employee selectedEmployee = null;
            try
            {
                selectedEmployee = await repository.GetOne(emp => emp.Email == email);
            }
            catch (Exception ex)
            {
                Debug.WriteLine("Problem in " + GetType().Name + " " + MethodBase.GetCurrentMethod().Name + " " + ex.Message);
                throw;
            }
            return selectedEmployee;
        }//end GetByEmail

        public async Task<Employee> GetById(int id)
        {
            Employee selectedEmployee = null;
            try
            {
                selectedEmployee = await repository.GetOne(emp => emp.Id == id);
            }
            catch (Exception ex)
            {
                Debug.WriteLine("Problem in " + GetType().Name + " " + MethodBase.GetCurrentMethod().Name + " " + ex.Message);
                throw;
            }
            return selectedEmployee;
        }//end GetById

        public async Task<List<Employee>> GetAll()
        {
            List<Employee> EmployeeList = null;
            try
            {
                EmployeeList = await repository.GetAll();
            }
            catch (Exception ex)
            {
                Debug.WriteLine("Problem in " + GetType().Name + " " + MethodBase.GetCurrentMethod().Name + " " + ex.Message);
                throw;
            }
            return EmployeeList;
        }//end GetAll

        public async Task<int> Add(Employee Emp)
        {
            try
            {
               await repository.Add(Emp);
            }
            catch (Exception ex)
            {
                Debug.WriteLine("Problem in " + GetType().Name + " " + MethodBase.GetCurrentMethod().Name + " " + ex.Message);
                throw;
            }
            return Emp.Id;
        }//end Add

        public async Task<UpdateStatus> Update(Employee updatedEmp)
        {
            UpdateStatus employeeUpdated = UpdateStatus.Failed;
            try
            {
                employeeUpdated = await repository.Update(updatedEmp);
            }
            catch (Exception ex)
            {
                Debug.WriteLine("Problem in " + GetType().Name + " " + MethodBase.GetCurrentMethod().Name + " " + ex.Message);
                throw;
            }
            return employeeUpdated;
        }//end Update

        public async Task<int> Delete(int id)
        {
            int numEmpDeleted = -1;
            try
            {
                numEmpDeleted = await repository.Delete(id);
            }
            catch (Exception ex)
            {
                Debug.WriteLine("Problem in " + GetType().Name + " " + MethodBase.GetCurrentMethod().Name + " " + ex.Message);
                throw;
            }
            return numEmpDeleted;
        }//end Delete
    }
}