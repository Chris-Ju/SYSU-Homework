var data = require('../model/dataHandle');

function check(db, callback) {
    data.checkPass(db, function (val) {
        callback(val);
    })
}

exports.check = check;