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
    public class DepartmentViewModel
    {
        readonly private DepartmentDAO _dao;

        public int Id { get; set; }
        public string Name { get; set; }
        public string Timer { get; set; }

        //constructor
        public DepartmentViewModel()
        {
            _dao = new DepartmentDAO();
        }

        public async Task<List<DepartmentViewModel>> GetAll()
        {
            List<DepartmentViewModel> allVms = new List<DepartmentViewModel>();
            try
            {
                List<Department> allDepartments = await _dao.GetAll();
                foreach (Department dep in allDepartments)
                {
                    DepartmentViewModel depVm = new DepartmentViewModel
                    {
                        
                        Name = dep.DepartmentName,
                        Id = dep.Id,
                        Timer = Convert.ToBase64String(dep.Timer)
                    };
                    allVms.Add(depVm);
                }
            }
            catch (Exception ex)
            {
                Debug.WriteLine("Problem in " + GetType().Name + " " + MethodBase.GetCurrentMethod().Name + " " + ex.Message);
                throw;
            }
            return allVms;
        }//end GetAll

    }
}
