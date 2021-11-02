$(function () { // employees.js

    // Get All method - Request data from database and load the employee list
    const getAll = async (msg) => {
        try {
            $("#employeesList").text("Finding employee Information...");
            //Request the employee data
            let response = await fetch(`api/employee`);
            //if the positive answer, load the data to the page by calling buildemployeesList() method.
            if (response.ok) {
                let payload = await response.json();  //returns a promise
                buildemployeesList(payload);
                msg === "" ? $("#status").text("Employees Loaded") : $("#status").text(`${msg} - Employees Loaded`);
            }
            else if (respose.status !== 404) {
                let problemJson = await response.json();
                errorRtn(problemJson, response.status);
            }
            else {
                $("#status").text("no such path on server");
            }
            //get department data
            response = await fetch(`api/department`);
            if (response.ok) {
                let deps = await response.json(); //returns a promise
                //save the data to sessionStorage to be easier to manipulate
                sessionStorage.setItem("alldepartments", JSON.stringify(deps));
            }
            else if (respose.status !== 404) {
                let problemJson = await response.json();
                errorRtn(problemJson, response.status);
            }
            else {
                $("#status").text("no such path on server");
            }
        }
        catch (error) {
            $("#status").text(error.message);
        }
    };//getAll

    //loadDepartmentDDL - load the drop-dow list for departments
    const loadDepartmentDDL = (depEmp) => {
        html = '';
        $('#ddlDepartments').empty();
        //create an array with all department data
        let alldepartments = JSON.parse(sessionStorage.getItem('alldepartments'));

        //traverse the array dynamicaly adding the options to the html variable
        for (dep of alldepartments) {
            html += `<option  value="${dep.id}">${dep.name}</option>`
        }
        $('#ddlDepartments').append(html); //add the options to the drop-down list html
        $('#ddlDepartments').val(depEmp); //set the current option to the parameter received
    };//loadDepartmentDDL

    //method to clear the modal form fields 
    const clearModalFields = () => {
        loadDepartmentDDL(-1);
        $("#TextBoxTitle").val("");
        $("#TextBoxFirstname").val("");
        $("#TextBoxLastname").val("");
        $("#TextBoxPhone").val("");
        $("#TextBoxEmail").val("");
        sessionStorage.removeItem("id");
        sessionStorage.removeItem("departmentId");
        sessionStorage.removeItem("timer");
    };//clear modal fields

    //method set the modal configuration for update
    const setupForUpdate = (id, data) => {
        $('#deletebutton').show();
        $("#actionbutton").val("Update");
        $("#modaltitle").html("<h4>Update Employee</h4>");
        clearModalFields();
        //traverse the data received and load fields
        data.map(employee => {
            if (employee.id === parseInt(id)) {
                $("#TextBoxTitle").val(employee.title);
                $("#TextBoxFirstname").val(employee.firstname);
                $("#TextBoxLastname").val(employee.lastname);
                $("#TextBoxPhone").val(employee.phoneno);
                $("#TextBoxEmail").val(employee.email);
                sessionStorage.setItem("id", employee.id);
                loadDepartmentDDL(employee.departmentId);
                sessionStorage.setItem("timer", employee.timer);

                $("#modalStatus").text("Update Data");
                $("#employeeModal").modal("toggle");
                $("#myModalLabel").text("Update");
            }
        });//map
    };//setupforupdate


    //method set the modal configuration for add
    const setupForAdd = () => {
        $("#actionbutton").val("Add");
        $("#modaltitle").html("<h4>Add Employee</h4>");
        $("#employeeModal").modal("toggle");
        $("#modalStatus").text("Add New Employee");
        $("#myModalLabel").text("Add");
        $('#deletebutton').hide();
        clearModalFields();
    };//setupForAdd


    //method to add an employee (when add button is clicked)
    const add = async () => {
        try {
            //create an object and copy the information from the modal fields to it
            emp = new Object();
            emp.title = $("#TextBoxTitle").val();
            emp.firstname = $("#TextBoxFirstname").val();
            emp.lastname = $("#TextBoxLastname").val();
            emp.phoneno = $("#TextBoxPhone").val();
            emp.email = $("#TextBoxEmail").val();
            emp.departmentId = parseInt($("#ddlDepartments").val());
            emp.id = -1;
            emp.timer = null;
            emp.staffpicture64 = null;
            //call the HTTP post method requesting to add the new employee
            let response = await fetch("/api/employee", {
                method: "POST",
                headers: { "Content-Type": "application/json; charset=utf-8" },
                body: JSON.stringify(emp) //convert the object emp to string before sending it
            });
            //if successfull - update the employee list with the new employee
            if (response.ok) {
                let data = await response.json();
                getAll(data.msg);
            }
            else if (response.status !== 404) {
                let problemJson = await response.json();
                errorRtn(problemJson, response.status);
            }
            else {
                $("#status").text("no such path on server");
            }
        } catch (error) {
            $("#status").text(error.message);
        }//try
        //close the modal
        $("#employeeModal").modal("toggle");
    };//add

    //delete method (when delete button is clicked)
    const _delete = async () => {
        try {
            //request to delete the employee using the id saved in the section storage
            let response = await fetch(`api/employee/${sessionStorage.getItem("id")}`, {
                method: 'DELETE',
                headers: { 'Content-Type': 'application/json;' }
            });
            //if successfull - update the employee list removing the employee deleted
            if (response.ok) {
                let data = await response.json();
                getAll(data.msg);
            }
            else {
                $('#status').text(`Status - ${response.status}, Problem on delete server side, see server console`);
            }
            $('#myModal').modal('toggle');
        }
        catch (error) {
            $('#status').text(error.message);
        }
        //close the modal
        $("#employeeModal").modal("toggle");
    };//delete

    //update method (when update button is clicked)
    const update = async () => { 
        try {
            //create an object and copy the information from the modal fields to it
            emp = new Object();
            emp.title = $("#TextBoxTitle").val();
            emp.firstname = $("#TextBoxFirstname").val();
            emp.lastname = $("#TextBoxLastname").val();
            emp.phoneno = $("#TextBoxPhone").val();
            emp.email = $("#TextBoxEmail").val();
 
            emp.id = parseInt(sessionStorage.getItem("id"));
            emp.departmentId = parseInt($("#ddlDepartments").val());
            emp.timer = sessionStorage.getItem("timer");
            emp.staffpicture64 = null;
            //request to update the employee
            let response = await fetch("/api/employee", {
                method: "PUT",
                headers: { "Content-Type": "application/json; charset=utf-8" },
                body: JSON.stringify(emp)
            });
            //if successfull - update the employee list
            if (response.ok) {
                let data = await response.json();
                getAll(data.msg);
            }
            else if (response.status !== 404) {
                let problemJson = await response.json();
                errorRtn(problemJson, response.status);
            }
            else {
                $("#status").text("no such path on server");
            }
        } catch (error) {
            $("#status").text(error.message);
        }//try
        //close the modal
        $("#employeeModal").modal("toggle");
    };//update 

    //update button on click (the same button is used to updade and add)
    $("#actionbutton").click(() => {
        $("#actionbutton").val() === "Update" ? update() : add();
    });

    //delete button on click event
    $("#deletebutton").click(() => {
        if (window.confirm('Are you sure?'))
            _delete();
    });

    //open the modal when user clicks the employee list
    $("#employeesList").click((e) => {
        clearModalFields();
        if (!e) e = window.event;
        let id = e.target.parentNode.id;
        if (id === "employeesList" || id === "") {
            id = e.target.id;
        }
        if (id !== "status" && id !== "heading") {
            let data = JSON.parse(sessionStorage.getItem("allemployees"));
            id === "0" ? setupForAdd() : setupForUpdate(id, data);//check the item id to decide what method to call
        }
        else {
            return false; //ignore if they clicked on heading or status
        }
    });//employeesListClick

    //method to build an employee list using dynamic html
   const buildemployeesList = (data) => {
        $("#employeesList").empty();
        div = $(`<div class="list-group-item text-white bg-info row d-flex" id="status">Employee Info</div>
                <div class= "list-group-item row d-flex text-center" id="heading">
                <div class="col-4 h4" id="columnTitle">Title</div>
                <div class="col-4 h4" id="columnFirst">First</div>
                <div class="col-4 h4" id="columnLast">Last</div>
         </div>`);
        div.appendTo($("#employeesList"));
       sessionStorage.setItem("allemployees", JSON.stringify(data));
       btn = $(`<button class="list-group-item row d-flex" id="0">...click to add employee</button>`);
       btn.appendTo($("#employeesList"));
        data.map(emp => {
            btn = $(`<button class="list-group-item row d-flex" id="${emp.id}">`);
            btn.html(`<div class="col-4" id="employeetitle${emp.id}">${emp.title}</div>
                      <div class="col-4" id="employeefname${emp.id}">${emp.firstname}</div>
                      <div class="col-4" id="employeelastnam${emp.id}">${emp.lastname}</div>`
            );
            btn.appendTo($("#employeesList"));
        });//map
    };//buildemployeeList

    getAll("");
}); // jQuery ready method

const errorRtn = (problemJson, status) => {
    if (status > 499) {
        $("#status").text("Problem server side, see debug console");
    }
    else {
        let keys = Object.keys(problemJson.error)
        problem = {
            status: status,
            statusText: problemJson.error[keys[0]][0],
        };
        $("#status").text("Problem client side, see browser console");
        console.log(problem);
    }
}