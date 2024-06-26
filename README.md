<a href='http://www.recurse.com' title='Made with love at the Recurse Center'><img src='https://cloud.githubusercontent.com/assets/2883345/11325206/336ea5f4-9150-11e5-9e90-d86ad31993d8.png' height='20px'/></a>

Life expectancy data taken from https://usa.mortality.org/national.php?national=USA

Set up:\
<img src="https://github.com/amymc/memento-mori/assets/1708243/654edb66-6499-4b3d-91e9-99093e1267e5" data-canonical-src="(https://github.com/amymc/memento-mori/assets/1708243/654edb66-6499-4b3d-91e9-99093e1267e5)" width="400" />

Somewhat based on this tutorial - https://www.twilio.com/en-us/blog/go-old-school-build-a-pager-using-arduino-node-js-and-twilio-html

- Upload the memento sketch to the board.
- Close the arduino IDE. otherwise you won't be able to communicate with the serial port from the node script.
- Run the app.js script `node app.js`
- Use ngrok to expose your local server to the world. Create a static ngrok domain so that you can use the same url every time - https://ngrok.com/blog-post/free-static-domains-ngrok-users
- Run the command with the domain flag `ngrok http 3000 --domain=your-domain-name.ngrok-free.app`
- In your Twilio account set the webook url for receiving sms to be your static domain /sms - `your-domain-name.ngrok-free.app/sms`
- Text your Twilio number with your name, age, and f or m for female or male. They have to be in that order and seperated by spaces
e.g. `Jane 30 f`
- Take the receipt that shows how much estimated time you have left!

<img src="https://github.com/amymc/memento-mori/assets/1708243/8860e294-d8fd-4634-b973-d555ff25adca" data-canonical-src="(https://github.com/amymc/memento-mori/assets/1708243/654edb66-6499-4b3d-91e9-99093e1267e5)" width="400" />
