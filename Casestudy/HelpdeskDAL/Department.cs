﻿using System;
using System.Collections.Generic;

#nullable disable

namespace HelpdeskDAL
{
    public partial class Department : HelpdeskEntity
    {
        public Department()
        {
            Employees = new HashSet<Employee>();
        }
                
        public string DepartmentName { get; set; }
        
        public virtual ICollection<Employee> Employees { get; set; }
    }
}
