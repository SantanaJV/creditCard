const app = require("express")();
const bodyparser = require("body-parser");

app.use(bodyparser.json());

app.get("/", (req, res) => {
  response = {
    data: "samba"
  };
  res.send(response);
});

app.post("/", (req, res) => {
  let body = req.body;
  res.send(body);
});

app.listen(3000, () => {
  console.log("Listening on port 3000");
});
