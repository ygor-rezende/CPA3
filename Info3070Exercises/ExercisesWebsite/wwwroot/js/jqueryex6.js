$(function () {
    let data;

    $("#loadbutton").click(async e => {
        if (sessionStorage.getItem("studentData") === null) { //if not loaded get data from github
            const url = "https://raw.githubusercontent.com/elauersen/info3070/master/jqueryex5.json";
            $('#results').text('Locating student data on GitHub, please wait...');

            //fetch API is asynchronous, notice the use of await keyword
            try {
                let response = await fetch(url);
                if (!response.ok)
                    throw new Error(`Status - ${response.status}, Text - ${response.statusText}`);
                data = await response.json();
                sessionStorage.setItem("studentData", JSON.stringify(data));
                $('#results').text('Student data on GitHub loaded!');
            } catch (error) {
                $('#results').text(error.message);
            }
        }
        else {
            data = JSON.parse(sessionStorage.getItem("studentData"));
        }

        let html = "";
        data.map(student => {
            html += `<div id="${student.id}" class="list-group-item">${student.firstname},${student.lastname}</div>`;
        });
        $("#studentList").html(html);
        $("#loadbutton").hide();
        $("#inputstuff").show();
        $("#addbutton").show();
        $("#removebutton").show();

    }); //loadbutton.click()

    $("#studentList").click(e => {
        //finde the student the user has clicked on
        const student = data.find(s => s.id === parseInt(e.target.id));
        $("#results").text(`you selected ${student.firstname}, ${student.lastname}`);
    });//studentList div click

    //add button event handler
    $("#addbutton").click(e => {
        const first = $('#txtfirstname').val();
        const last = $('#txtlastname').val();

        if (first.length > 0 && last.length > 0) {
            if (data.length > 0) {
                const student = data[data.length - 1];
                data.push({ "id": student.id + 101, "firstname": first, "lastname": last });
                $("#results").text(`added student ${student.id + 101}`);
            }
            else {
                data.push({ "id": 101, "firstname": first, "lastname": last });
            }

            //clear out the textboxes
            $('#txtlastname').val("");
            $('#txtfirstname').val("");
            sessionStorage.setItem("studentData", JSON.stringify(data));
            let html = "";
            data.map(student => {
                html += `<div id="${student.id}" class="list-group-item">${student.firstname},${student.lastname}</div>`;
            });
            $("#studentList").html(html);
        }
   
       
    });

    //remove button event handler
    $("#removebutton").click(e => {
        if (data.length > 0) {
            const student = data[data.length - 1];
            data.splice(-1, 1); //remove last entry in array
            $("#results").text(`removed student ${student.id}`);
            sessionStorage.setItem("studentData", JSON.stringify(data));
            let html = "";
            data.map(student => {
                html += `<div id="${student.id}" class="list-group-item">${student.firstname},${student.lastname}</div>`;
            });
            $("#studentList").html(html);
        }
        else {
            $("#results").text(`no students to remove`);
        }
        
    });

}); //jQuery routine