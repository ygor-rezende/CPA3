$(function () {
    $("#getbutton").click(async (e) => {
        try {
            let email = $("#TextBoxEmail").val();
            $("#status").text("please wait...");
            let response = await fetch(`/api/employee/${email}`);
            if (response.ok) {
                let data = await response.json();
                if (data.email != "Not found") {
                    $("#lastname").text(data.lastname);
                    $("#title").text(data.title);
                    $("#firstname").text(data.firstname);
                    $("#phone").text(data.phoneno);
                    $("#status").text("Employee found!");
                }
                else {
                    $("#firstname").text("Not found!");
                    $("#email").text("");
                    $("#title").text("");
                    $("#phone").text("");
                    $("#status").text("No such employee");
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