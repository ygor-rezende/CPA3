using HelpdeskViewModels;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using System;
using System.Diagnostics;
using System.Reflection;
using System.Threading.Tasks;
using System.Collections.Generic;

namespace CasestudyWebsite.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    public class EmployeeController : ControllerBase
    {
        [HttpGet("{email}")]
        public async Task<IActionResult> GetByEmail(string email)
        {
            try
            {
                EmployeeViewModel viewmodel = new EmployeeViewModel
                {
                    Email = email
                };
                await viewmodel.GetByEmail();
                return Ok(viewmodel);
            }
            catch (Exception ex)
            {
                Debug.WriteLine("Problem in " + GetType().Name + " " + MethodBase.GetCurrentMethod().Name + " " + ex.Message);
                return StatusCode(StatusCodes.Status500InternalServerError);
            }
        }//get email
        
        [HttpPut]
        public async Task<ActionResult> Put(EmployeeViewModel viewModel)
        {
            try
            {
                int retVal = await viewModel.Update();
                return retVal switch
                {
                    1 => Ok(new { msg = "Employee " + viewModel.Lastname + " udated!" }),
                    -1 => Ok(new { msg = "Employee " + viewModel.Lastname + "not updated!" }),
                    -2 => Ok(new { msg = "Data is stale for " + viewModel.Lastname + ". Employee not updated!" }),
                    _ => Ok(new { msg = "Employee " + viewModel.Lastname + "not updated!" }),
                };
            }
            catch (Exception ex)
            {
                Debug.WriteLine("Problem in " + GetType().Name + " " + MethodBase.GetCurrentMethod().Name + " " + ex.Message);
                return StatusCode(StatusCodes.Status500InternalServerError);
            }
        }//update

        [HttpGet]
        public async Task<IActionResult> GetAll()
        {
            try
            {
                EmployeeViewModel viewModel = new EmployeeViewModel();
                List<EmployeeViewModel> allEmployees = await viewModel.GetAll();
                return Ok(allEmployees);
            }
            catch (Exception ex)
            {
                Debug.WriteLine("Problem in " + GetType().Name + " " + MethodBase.GetCurrentMethod().Name + " " + ex.Message);
                return StatusCode(StatusCodes.Status500InternalServerError);
            }
        }//getall

        [HttpPost]
        public async Task<ActionResult> Post(EmployeeViewModel viewModel)
        {
            try
            {
                await viewModel.Add();
                return viewModel.Id > 1
                    ? Ok(new { msg = "Employee " + viewModel.Lastname + " added!" })
                    : Ok(new { msg = "Employee " + viewModel.Lastname + " not added!" });
            }
            catch (Exception ex)
            {
                Debug.WriteLine("Problem in " + GetType().Name + " " + MethodBase.GetCurrentMethod().Name + " " + ex.Message);
                return StatusCode(StatusCodes.Status500InternalServerError);
            }
        }


    }//controller base
}
