$(function () {
    $("#getbutton").click(async (e) => { //Find student button event handler
        try {
            let lastname = $("#TextBoxFindLastname").val();
            $("#status").text("please wait...");
            $("#myModal").modal("toggle");
            let response = await fetch(`/api/student/${lastname}`);
            if (response.ok) {
                let data = await response.json();
                if (data.lastname != "Not found") {
                    $("#TextBoxEmail").val(data.email);
                    $("#TextBoxTitle").val(data.title);
                    $("#TextBoxFirstname").val(data.firstname);
                    $("#TextBoxLastname").val(data.lastname);
                    $("#TextBoxPhone").val(data.phoneno);
                    $("#status").text("Student found!");
                    //return these non-mutated values later
                    sessionStorage.setItem("id", data.id);
                    sessionStorage.setItem("divisionId", data.divisionId);
                    sessionStorage.setItem("timer", data.timer);
                }
                else {
                    $("#TextBoxFirstName").text("Not found!");
                    $("#TextBoxLastName").val("");
                    $("#TextBoxEmail").val("");
                    $("#TextBoxTitle").val("");
                    $("#TextBoxPhone").val("");
                    $("#status").text("No such student");
                }
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
    });//on click

    $("#updatebutton").click(async (e) => { //update button event handler
        try {
            stu = new Object();
            stu.title = $("#TextBoxTitle").val();
            stu.firstname = $("#TextBoxFirstname").val();
            stu.lastname = $("#TextBoxFindLastname").val();
            stu.phoneno = $("#TextBoxPhone").val();
            stu.email = $("#TextBoxEmail").val();
            stu.divisionName = "";
            stu.picture64 = "";
            stu.id = parseInt(sessionStorage.getItem("id"));
            stu.divisionId = parseInt(sessionStorage.getItem("divisionId"));
            stu.timer = sessionStorage.getItem("timer");

            let response = await fetch("/api/student",{
                method:"PUT",
                headers: { "Content-Type": "application/json; charset=utf-8"},
                body: JSON.stringify(stu)
            });
            if (response.ok) {
                let payload = await response.json();
                $("#status").text(payload.msg);
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
            console.table(error);
        }//try
    });//on click

});//jQuery

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