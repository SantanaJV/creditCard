const mongoose = require('mongoose');

const rfidSchema = new mongoose.Schema({
    uid: {
        type: String,
        required: true,
        max: 50
    },
    name: {
        type: String,
        required: true,
        max: 255
    },
    grade: {
        type: String,
        required: true,
        max: 255
    },
    balance: {
        type: Number,
        default: 0
    }
});

module.exports.Rfid = mongoose.model("Rfid", rfidSchema, 'rfid');