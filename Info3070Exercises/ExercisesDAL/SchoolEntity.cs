﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.ComponentModel.DataAnnotations;

namespace ExercisesDAL
{
    public class SchoolEntity
    {
        public int Id { get; set; }

        [Timestamp]
        public byte[] Timer { get; set; }
    }
}
