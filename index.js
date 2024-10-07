const form = document.getElementById("form");
form.addEventListener("submit", submit);

const select = document.getElementById("sex-select");
const nameField = document.getElementById("name");
const ageField = document.getElementById("age");

document.getElementById("sex-select").style.borderColor = "green";
select.onchange = checkField;
nameField.onkeyup = checkField;
ageField.onkeyup = checkField;

function checkField() {
  if (select.value !== "" && nameField.value !== "" && ageField.value !== "") {
    document.getElementById("btn").disabled = false;
  }
}

function submit(e) {
  e.preventDefault();
  const formData = new FormData(form);

  let partitipantData = {};
  for (const pair of formData.entries()) {
    partitipantData[pair[0]] = pair[1];
  }

  fetch("https://bedbug-driven-cow.ngrok-free.app/participants", {
    method: "POST",
    body: JSON.stringify(partitipantData),
    mode: "cors",
    cache: "default",
    headers: {
      "Content-type": "application/json",
    },
  }).then((response) => {
    console.log(response.status);
    if (response.status === 200) {
      form.style.display = "none";
      document.getElementById("success").style.display = "block";
    } else {
      form.style.display = "none";
      document.getElementById("failure").style.display = "block";
    }
  });
}
