const router = require('express').Router();
const { Rfid } = require('../models/rfid');

router.get("/:uid", async (req, res) => {
    try {
        let uid = req.params.uid;

        console.log("Trying to find " + uid + "...");
        let rfid = await Rfid.find({ uid });

        if(!rfid) return res.status(200).send({ uid, registered: false });

        rfid.registered = true;
        res.status(200).send(rfid);
    } catch(err) {
        res.status(500).send("Internal error - check server log");
        console.log(err);
    }
});

router.post("/", async (req, res) => {
    try{
        let rfid = req.body;
        console.log(req.body);

        if(!rfid.uid || !rfid.name || !rfid.grade) return res.status(400).send("Invalid request.");

        rfid = new Rfid(rfid);
        await rfid.save();

        res.status(200).send(rfid);
    } catch(err) {
        res.status(500).send("Internal error - check server log");
        console.log(err);
    }
});

module.exports = router;

