using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Diagnostics;
using System.Reflection;

namespace HelpdeskDAL
{
    public class DepartmentDAO
    {
        readonly IRepository<Department> repository;

        public DepartmentDAO()
        {
            repository = new HelpdeskRepository<Department>();
        }

        public async Task<List<Department>> GetAll()
        {
            List<Department> DepartmentList = null;
            try
            {
                DepartmentList = await repository.GetAll();
            }
            catch (Exception ex)
            {
                Debug.WriteLine("Problem in " + GetType().Name + " " + MethodBase.GetCurrentMethod().Name + " " + ex.Message);
                throw;
            }
            return DepartmentList;
        }//end GetAll

    }
}
