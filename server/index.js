const SerialPort = require("serialport").SerialPort;
const express = require("express");
const bodyParser = require("body-parser");
const fs = require("fs");
const { parse } = require("csv-parse");
const sanitizeHtml = require("sanitize-html");
var cors = require("cors");

// const { ReadlineParser } = require("@serialport/parser-readline");
let expectancyData = { m: {}, f: {} };

const readData = () => {
  fs.readFile("../data/expectancy.csv", "utf-8", (err, data) => {
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

// var serialPort = new SerialPort({
//   path: "/dev/tty.usbserial-0001",
//   baudRate: 19200,
// });

// const parser = new ReadlineParser();
// serialPort.pipe(parser);
// parser.on("data", (line) => console.log(line));

var app = express();
app.use(bodyParser.urlencoded({ extended: false }));
app.use(bodyParser.json());
app.use(cors());

app.post("/participants", function (req, res) {
  try {
    console.log("req", req);
    console.log("req", req.body);
    const { name, age, sex } = req.body;
    const userExpectancy = expectancyData[sanitizeHtml(sex)][sanitizeHtml(age)];
    console.log(`${name} ${userExpectancy}`);
    // console.log(`${name} ${age}`);

    // serialPort.write(`${sanitizeHtml(name)} ${userExpectancy}`);
    res.status(200).send();
  } catch (error) {
    console.error(error);

    res.status(500).send();
  }
});

// serialPort.open(function () {
app.listen(3000, "127.0.0.1", function () {
  readData();
});

console.log("Listening on port 3000");
// console.log(Printer.list());
// var printer = new Printer("Canon_G3020_series");

// var text = "Print text directly, when needed: e.g. barcode printers";
// var jobFromText = printer.printText(text);
// console.log(jobFromText);

// });
