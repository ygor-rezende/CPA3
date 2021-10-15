$(function () { // employeesList.js
    const getAll = async (msg) => {
        try {
            $("#employeesList").text("Finding employee Information...");
            let response = await fetch(`api/employee`);
            if (response.ok) {
                let payload = await response.json();
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
        }
        catch (error) {
            $("#status").text(error.message);
        }
    };//getAll

    const setupForUpdate = (id, data) => {
        $("#actionbutton").val("update");
        $("#modaltitle").html("<h4>update employee</h4>");
        clearModalFields();
        data.map(employee => {
            if (employee.id === parseInt(id)) {
                $("#TextBoxTitle").val(employee.title);
                $("#TextBoxFirstname").val(employee.firstname);
                $("#TextBoxLastname").val(employee.lastname);
                $("#TextBoxPhone").val(employee.phoneno);
                $("#TextBoxEmail").val(employee.email);
                sessionStorage.setItem("id", employee.id);
                sessionStorage.setItem("departmentId", employee.divisionId);
                sessionStorage.setItem("timer", employee.timer);
                $("#modalstatus").text("update data");
                $("#employeeModal").modal("toggle");
                $("#myModalLabel").text("Update");
            }
        });//map
    };//setupforupdate

    const setupForAdd = () => {
        $("#actionbutton").val("add");
        $("#modaltitle").html("<h4>add employee</h4>");
        $("#theModal").modal("toggle");
        $("#modalstatus").text("add new employee");
        $("#myModalLabel").text("Add");
        clearModalFields();
    };//setupForAdd

    const clearModalFields = () => {
        $("#TextBoxTitle").val("");
        $("#TextBoxFirstname").val("");
        $("#TextBoxLastname").val("");
        $("#TextBoxPhone").val("");
        $("#TextBoxEmail").val("");
        sessionStorage.removeItem("id");
        sessionStorage.removeItem("departmentId");
        sessionStorage.removeItem("timer");
        $("#employeeModal").modal("toggle");
    };//clear modal fields

    const add = async () => {
        try {
            emp = new Object();
            emp.title = $("#TextBoxTitle").val();
            emp.firstname = $("#TextBoxFirstname").val();
            emp.lastname = $("#TextBoxLastname").val();
            emp.phoneno = $("#TextBoxPhone").val();
            emp.email = $("#TextBoxEmail").val();
            emp.departmentId = 100;
            emp.id = -1;
            emp.timer = null;
            emp.staffpicture64 = null;
            let response = await fetch("/api/employee", {
                method: "POST",
                headers: { "Content-Type": "application/json; charset=utf-8" },
                body: JSON.stringify(emp)
            });
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
        $("#employeeModal").modal("toggle");
    };//add

    const update = async () => { //update button event handler
        try {
            emp = new Object();
            emp.title = $("#TextBoxTitle").val();
            emp.firstname = $("#TextBoxFirstname").val();
            emp.lastname = $("#TextBoxLastname").val();
            emp.phoneno = $("#TextBoxPhone").val();
            emp.email = $("#TextBoxEmail").val();
 
            emp.id = parseInt(sessionStorage.getItem("id"));
            emp.departmentId = parseInt(sessionStorage.getItem("departmentId"));
            emp.timer = sessionStorage.getItem("timer");
            emp.staffpicture64 = null;

            let response = await fetch("/api/employee", {
                method: "PUT",
                headers: { "Content-Type": "application/json; charset=utf-8" },
                body: JSON.stringify(emp)
            });
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
        $("#employeeModal").modal("toggle");
    };//update 

    $("#actionbutton").click(() => {
        $("#actionbutton").val() === "update" ? update() : add();
    });

    $("#employeesList").click((e) => {
        clearModalFields();
        if (!e) e = window.event;
        let id = e.target.parentNode.id;
        if (id === "employeesList" || id === "") {
            id = e.target.id;
        }
        if (id !== "status" && id !== "heading") {
            let data = JSON.parse(sessionStorage.getItem("allemployees"));
            id === "0" ? setupForAdd() : setupForUpdate(id, data);
        }
        else {
            return false; //ignore if they clicked on heading or status
        }
    });//employeesListClick

   const buildemployeesList = (data) => {
        $("#employeesList").empty();
        div = $(`<div class="list-group-item text-white bg-secondary row d-flex" id="status">Employee Info</div>
                <div class= "list-group-item row d-flex text-center" id="heading">
                <div class="col-4 h4">Title</div>
                <div class="col-4 h4">First</div>
                <div class="col-4 h4">Last</div>
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