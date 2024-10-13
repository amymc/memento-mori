let expectancyData = { m: {}, f: {} };

Papa.parse("./data/expectancy.csv", {
  download: true,
  complete: function ({ data }) {
    // skip first array because it's the title row
    for (let i = 1; i < data.length - 1; i++) {
      // 0 index is the m/f column
      // 1 index is the age column
      // 2 index is the expectancy column

      // rounding expectancy value to nearest 0.5
      const roundedExpectancy = Math.round(data[i][2] * 2) / 2;
      expectancyData[data[i][0]][data[i][1]] = roundedExpectancy;
    }
  },
});

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
  if (
    select.value !== "" &&
    DOMPurify.sanitize(nameField.value) !== "" &&
    ageField.value !== ""
  ) {
    document.getElementById("btn").disabled = false;
  }
}

function submit(e) {
  e.preventDefault();
  const formData = new FormData(form);

  let participantData = {};
  for (const pair of formData.entries()) {
    participantData[pair[0]] = DOMPurify.sanitize(pair[1]);
  }

  fetch("https://bedbug-driven-cow.ngrok-free.app/participants", {
    method: "POST",
    body: JSON.stringify({
      name: participantData.name,
      expectancy: expectancyData[participantData.sex][participantData.age],
    }),
    mode: "cors",
    cache: "default",
  }).then((response) => {
    if (response.status === 200) {
      form.style.display = "none";
      document.getElementById("success").style.display = "block";
    } else {
      form.style.display = "none";
      document.getElementById("failure").style.display = "block";
    }
  });
}
