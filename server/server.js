const app = require("express")();
const bodyparser = require("body-parser");
const rfid = require('./routes/rfid');
const mongoose = require('mongoose');

mongoose.connect(
  '<URI>',
 { useNewUrlParser: true}, 
 (err) => {
  if(err) console.log(err);

  console.log("Connected to MongoDB database");
});

app.use(bodyparser.json());
app.use("/rfid", rfid);

app.listen(3000, () => {
  console.log("Listening on port 3000");
});
