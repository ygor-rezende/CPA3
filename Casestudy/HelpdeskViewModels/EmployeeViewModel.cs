using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using HelpdeskDAL;
using System.Diagnostics;
using System.Reflection;

namespace HelpdeskViewModels
{
    public class EmployeeViewModel
    {
        readonly private EmployeeDAO _dao;

        public string Title { get; set; }
        public string Firstname { get; set; }
        public string Lastname { get; set; }
        public string Email { get; set; }
        public string Phoneno { get; set; }
        public string Timer { get; set; }
        public int DepartmentId { get; set; }
        public string DepartmentName { get; set; }
        public int Id { get; set; }
        public bool? IsTech { get; set; }
        public string StaffPicture64 { get; set; }

        //constructor
        public EmployeeViewModel()
        {
            _dao = new EmployeeDAO();
        }

        public async Task GetByEmail()
        {
            try
            {
                Employee emp = await _dao.GetByEmail(Email);
                Title = emp.Title;
                Firstname = emp.FirstName;
                Lastname = emp.LastName;
                Phoneno = emp.PhoneNo;
                Email = emp.Email;
                Id = emp.Id;
                DepartmentId = emp.DepartmentId;
                IsTech = emp.IsTech;
                if (emp.StaffPicture != null)
                {
                    StaffPicture64 = Convert.ToBase64String(emp.StaffPicture);
                }
                Timer = Convert.ToBase64String(emp.Timer);
            }
            catch (NullReferenceException nex)
            {
                Debug.WriteLine(nex.Message);
                Email = "Not found";
            }
            catch (Exception ex)
            {
                Email = "not found";
                Debug.WriteLine("Problem in " + GetType().Name + " " + MethodBase.GetCurrentMethod().Name + " " + ex.Message);
                throw;
            }

        }//end getByEmail

        public async Task GetById()
        {
            try
            {
                Employee emp = await _dao.GetById(Id);
                Title = emp.Title;
                Firstname = emp.FirstName;
                Lastname = emp.LastName;
                Phoneno = emp.PhoneNo;
                Email = emp.Email;
                Id = emp.Id;
                DepartmentId = emp.DepartmentId;
                IsTech = emp.IsTech;
                if (emp.StaffPicture != null)
                {
                    StaffPicture64 = Convert.ToBase64String(emp.StaffPicture);
                }
                Timer = Convert.ToBase64String(emp.Timer);
            }
            catch (NullReferenceException nex)
            {
                Debug.WriteLine(nex.Message);
                Email = "Not found";
            }
            catch (Exception ex)
            {
                Email = "not found";
                Debug.WriteLine("Problem in " + GetType().Name + " " + MethodBase.GetCurrentMethod().Name + " " + ex.Message);
                throw;
            }

        }//end getById

        //retrieve all employees
        public async Task<List<EmployeeViewModel>> GetAll()
        {
            List<EmployeeViewModel> allVms = new List<EmployeeViewModel>();
            try
            {
                List<Employee> allEmployees = await _dao.GetAll();
                foreach (Employee emp in allEmployees)
                {
                    EmployeeViewModel empVm = new EmployeeViewModel
                    {
                        Title = emp.Title,
                        Firstname = emp.FirstName,
                        Lastname = emp.LastName,
                        Phoneno = emp.PhoneNo,
                        Email = emp.Email,
                        Id = emp.Id,
                        DepartmentId = emp.DepartmentId,
                        DepartmentName = emp.Department.DepartmentName,
                        IsTech = emp.IsTech,
                        Timer = Convert.ToBase64String(emp.Timer)
                    };
                    allVms.Add(empVm);
                }
            }
            catch (Exception ex)
            {
                Debug.WriteLine("Problem in " + GetType().Name + " " + MethodBase.GetCurrentMethod().Name + " " + ex.Message);
                throw;
            }
            return allVms;
        }//end GetAll

        public async Task Add()
        {
            Id = -1;
            try
            {
                Employee emp = new Employee
                {
                    Title = Title,
                    FirstName = Firstname,
                    LastName = Lastname,
                    PhoneNo = Phoneno,
                    Email = Email,
                    DepartmentId = DepartmentId,
                };
                Id = await _dao.Add(emp);
            }
            catch (Exception ex)
            {
                Debug.WriteLine("Problem in " + GetType().Name + " " + MethodBase.GetCurrentMethod().Name + " " + ex.Message);
                throw;
            }
        }//end Add

        public async Task<int> Update()
        {
            UpdateStatus status = UpdateStatus.Failed;
            try
            {
                Employee emp = new Employee
                {
                    Title = Title,
                    FirstName = Firstname,
                    LastName = Lastname,
                    PhoneNo = Phoneno,
                    Email = Email,
                    Id = Id,
                    DepartmentId = DepartmentId,
                    IsTech = IsTech,
                };
                if (StaffPicture64 != null)
                {
                    emp.StaffPicture = Convert.FromBase64String(StaffPicture64);
                }
                emp.Timer = Convert.FromBase64String(Timer);
                status = await _dao.Update(emp);
            }
            catch (Exception ex)
            {
                Debug.WriteLine("Problem in " + GetType().Name + " " + MethodBase.GetCurrentMethod().Name + " " + ex.Message);
                throw;
            }
            return Convert.ToInt16(status);
        }//end Update

        public async Task<int> Delete()
        {
            int employeeDeleted = -1;
            try
            {
                employeeDeleted = await _dao.Delete(Id);
            }
            catch (Exception ex)
            {
                Debug.WriteLine("Problem in " + GetType().Name + " " + MethodBase.GetCurrentMethod().Name + " " + ex.Message);
                throw;
            }
            return employeeDeleted;
        }//end Delete
    }
}
