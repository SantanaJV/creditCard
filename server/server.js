const app = require("express")();
const bodyparser = require("body-parser");
const rfid = require('./routes/rfid');

app.use(bodyparser.json());
app.use("/rfid", rfid);

app.listen(3000, () => {
  console.log("Listening on port 3000");
});
