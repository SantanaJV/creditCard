const router = require('express').Router();
const { Rfid } = require('../models/rfid');

router.get("/:uid", async (req, res) => {
    try {
        let uid = req.params.uid;

        console.log("Trying to find " + uid + "...");
        let rfid = await Rfid.findOne({ uid });

        if(!rfid) return res.status(200).send({ uid, registered: false });

        console.log(rfid);

        rfid.registered = true;
        res.status(200).send(rfid);
    } catch(err) {
        res.status(500).send("Internal error - check server log");
        console.log(err);
    }
});

router.post("/", async (req, res) => {
    try{
        let body = req.body;
        console.log(req.body);

        if(!body.uid || !body.name || !body.grade) return res.status(400).send("Invalid request.");

        let rfid = await Rfid.findOne({ uid: body.uid });
        if(rfid) return res.status(400).send("Rfid already exists, do a put request instead");

        rfid = new Rfid(body);
        await rfid.save();

        res.status(200).send(rfid);
    } catch(err) {
        res.status(500).send("Internal error - check server log");
        console.log(err);
    }
});

router.post("/update", async (req, res) => {
    try{
        let rfid = req.body;
        console.log(req.body);

        if(!rfid.uid || !rfid.name || !rfid.grade) return res.status(400).send("Invalid request.");

        rfid = await Rfid.findOneAndUpdate({ uid: rfid.uid }, rfid);

        if(!rfid) return res.status(404).send("Rfid with given UID was not found");

        res.status(200).send(rfid);
    } catch(err) {
        res.status(500).send("Internal error - check server log");
        console.log(err);
    }
});

router.post("/delete", async (req, res) => {
    try {
        let uid = req.body.uid;

        rfid = await Rfid.findOneAndRemove({ uid });

        if(!rfid) return res.status(404).send("Rfid with given UID was not found");

        res.status(200).send(rfid);
    } catch(err) {
        res.status(500).send("Internal error - check server log");
        console.log(err);
    }
});

module.exports = router;

