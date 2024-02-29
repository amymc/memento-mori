const SerialPort = require("serialport").SerialPort;
const express = require("express");
const bodyParser = require("body-parser");
const fs = require("fs");
const { parse } = require("csv-parse");
let expectancyData = { m: {}, f: {} };

const readData = () => {
  fs.readFile("expectancy.csv", "utf-8", (err, data) => {
    parse(data, { columns: false, trim: true }, function (err, rows) {
      // skip first array because it's the title row
      for (let i = 1; i < rows.length; i++) {
        // 0 index is the m/f column
        // 1 index is the age column
        // 2 index is the expectancy column

        // rounding expectancy value to nearest 0.5
        const roundedExpectancy = Math.round(rows[i][2] * 2) / 2;
        expectancyData[rows[i][0]][rows[i][1]] = roundedExpectancy;
      }
    });
  });
};

const { ReadlineParser } = require("@serialport/parser-readline");

var serialPort = new SerialPort({
  path: "/dev/tty.usbserial-0001",
  baudRate: 19200,
});

const parser = new ReadlineParser();
serialPort.pipe(parser);
parser.on("data", (line) => console.log(line));

var app = express();
app.use(bodyParser.urlencoded({ extended: false }));
app.use(bodyParser.json());

app.post("/sms", function (req, res) {
  const [name, age, sex] = req.body.Body.split(" ");
  const userExpectancy = expectancyData[sex][age];

  serialPort.write(`${name} ${userExpectancy}`);
});

serialPort.open(function () {
  app.listen(3000, "127.0.0.1", function () {
    readData();
  });

  console.log("Listening on port 3000");
});
