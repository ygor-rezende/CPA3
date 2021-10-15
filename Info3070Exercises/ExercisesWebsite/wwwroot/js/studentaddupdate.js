$(function () { // studentaddupdate.js
    const getAll = async (msg) => {
        try {
            $("#studentList").text("Finding Student Information...");
            let response = await fetch(`api/student`);
            if (response.ok) {
                let payload = await response.json();
                buildStudentList(payload);
                msg === "" ? $("#status").text("Students Loaded") : $("#status").text(`${msg} - Students Loaded`);
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
        $("#modaltitle").html("<h4>update student</h4>");
        clearModalFields();
        data.map(student => {
            if (student.id === parseInt(id)) {
                $("#TextBoxTitle").val(student.title);
                $("#TextBoxFirstname").val(student.firstname);
                $("#TextBoxLastname").val(student.lastname);
                $("#TextBoxPhone").val(student.phoneno);
                $("#TextBoxEmail").val(student.email);
                sessionStorage.setItem("id", student.id);
                sessionStorage.setItem("divisionId", student.divisionId);
                sessionStorage.setItem("timer", student.timer);
                $("#modalstatus").text("update data");
                $("#myModal").modal("toggle");
                $("#myModalLabel").text("Update");
            }
        });//map
    };//setupforupdate

    const setupForAdd = () => {
        $("#actionbutton").val("add");
        $("#modaltitle").html("<h4>add student</h4>");
        $("#theModal").modal("toggle");
        $("#modalstatus").text("add new student");
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
        sessionStorage.removeItem("divisionId");
        sessionStorage.removeItem("timer");
        $("#myModal").modal("toggle");
    };//clear modal fields

    const add = async () => {
        try {
            stu = new Object();
            stu.title = $("#TextBoxTitle").val();
            stu.firstname = $("#TextBoxFirstname").val();
            stu.lastname = $("#TextBoxLastname").val();
            stu.phoneno = $("#TextBoxPhone").val();
            stu.email = $("#TextBoxEmail").val();
            stu.divisionId = 10;
            stu.id = -1;
            stu.timer = null;
            stu.picture64 = null;
            let response = await fetch("/api/student", {
                method: "POST",
                headers: { "Content-Type": "application/json; charset=utf-8" },
                body: JSON.stringify(stu)
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
        $("#myModal").modal("toggle");
    };//add

    const update = async() => { //update button event handler
        try {
            stu = new Object();
            stu.title = $("#TextBoxTitle").val();
            stu.firstname = $("#TextBoxFirstname").val();
            stu.lastname = $("#TextBoxLastname").val();
            stu.phoneno = $("#TextBoxPhone").val();
            stu.email = $("#TextBoxEmail").val();
 
            stu.id = parseInt(sessionStorage.getItem("id"));
            stu.divisionId = parseInt(sessionStorage.getItem("divisionId"));
            stu.timer = sessionStorage.getItem("timer");
            stu.picture64 = null;

            let response = await fetch("/api/student", {
                method: "PUT",
                headers: { "Content-Type": "application/json; charset=utf-8" },
                body: JSON.stringify(stu)
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
        $("#myModal").modal("toggle");
    };//update

    $("#actionbutton").click(() => {
        $("#actionbutton").val() === "update" ? update() : add();
    });

    $("#studentList").click((e) => {
        clearModalFields();
        if (!e) e = window.event;
        let id = e.target.parentNode.id;
        if (id === "studentList" || id === "") {
            id = e.target.id;
        }
        if (id !== "status" && id !== "heading") {
            let data = JSON.parse(sessionStorage.getItem("allstudents"));
            id === "0" ? setupForAdd() : setupForUpdate(id, data);
        }
        else {
            return false; //ignore if they clicked on heading or status
        }
    });//studentListClick

    const buildStudentList = (data) => {
        $("#studentList").empty();
        div = $(`<div class="list-group-item text-white bg-secondary row d-flex" id="status">Student Info</div>
                <div class= "list-group-item row d-flex text-center" id="heading">
                <div class="col-4 h4">Title</div>
                <div class="col-4 h4">First</div>
                <div class="col-4 h4">Last</div>
         </div>`);
        div.appendTo($("#studentList"));
        sessionStorage.setItem("allstudents", JSON.stringify(data));
        btn = $(`<button class="list-group-item row d-flex" id="0">...click to add student</button>`);
        btn.appendTo($("#studentList"));
        data.map(stu => {
            btn = $(`<button class="list-group-item row d-flex" id="${stu.id}">`);
            btn.html(`<div class="col-4" id="studenttitle${stu.id}">${stu.title}</div>
                      <div class="col-4" id="studentfname${stu.id}">${stu.firstname}</div>
                      <div class="col-4" id="studentlastnam${stu.id}">${stu.lastname}</div>`
            );
            btn.appendTo($("#studentList"));
        });//map
    };//buildstudentList

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
