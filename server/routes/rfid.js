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
        res.status(500).send("Internal error - Check server log");
        console.log(err);
    }
});

module.exports = router;

