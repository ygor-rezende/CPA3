using ExercisesViewModels;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using System;
using System.Diagnostics;
using System.Reflection;
using System.Threading.Tasks;
using System.Collections.Generic;

namespace ExercisesWebsite.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    public class StudentController : ControllerBase
    {
        [HttpGet("{lastname}")]
        public async Task<IActionResult> GetByLastname(string lastname)
        {
            try
            {
                StudentViewModel viewmodel = new StudentViewModel
                {
                    Lastname = lastname
                };
                await viewmodel.GetByLastname();
                return Ok(viewmodel);
            }
            catch(Exception ex)
            {
                Debug.WriteLine("Problem in " + GetType().Name + " " + MethodBase.GetCurrentMethod().Name + " " + ex.Message);
                return StatusCode(StatusCodes.Status500InternalServerError);
            }
        }
        [HttpPut]
        public async Task<ActionResult> Put(StudentViewModel viewModel)
        {
            try
            {
                int retVal = await viewModel.Update();
                return retVal switch
                {
                    1 => Ok(new { msg = "Student " + viewModel.Lastname + " udated!" }),
                    -1 => Ok(new { msg = "Student " + viewModel.Lastname + "not updated!" }),
                    -2 => Ok(new { msg = "Data is stale for " + viewModel.Lastname + ". Student not updated!" }),
                    _ => Ok(new { msg = "Student " + viewModel.Lastname + "not updated!" }),
                };
            }
            catch (Exception ex)
            {
                Debug.WriteLine("Problem in " + GetType().Name + " " + MethodBase.GetCurrentMethod().Name + " " + ex.Message);
                return StatusCode(StatusCodes.Status500InternalServerError);
            }
        }

        [HttpGet]
        public async Task<IActionResult> GetAll()
        {
            try
            {
                StudentViewModel viewModel = new StudentViewModel();
                List<StudentViewModel> allStudents = await viewModel.GetAll();
                return Ok(allStudents);
            }
            catch (Exception ex)
            {
                Debug.WriteLine("Problem in " + GetType().Name + " " + MethodBase.GetCurrentMethod().Name + " " + ex.Message);
                return StatusCode(StatusCodes.Status500InternalServerError);
            }
        }

        [HttpPost]
        public async Task<ActionResult> Post(StudentViewModel viewModel)
        {
            try
            {
                await viewModel.Add();
                return viewModel.Id > 1
                    ? Ok(new { msg = "Student " + viewModel.Lastname + " added!" })
                    : Ok(new { msg = "Student " + viewModel.Lastname + " not added!" });
            }
            catch(Exception ex)
            {
                Debug.WriteLine("Problem in " + GetType().Name + " " + MethodBase.GetCurrentMethod().Name + " " + ex.Message);
                return StatusCode(StatusCodes.Status500InternalServerError);
            }
        }
    }
}
