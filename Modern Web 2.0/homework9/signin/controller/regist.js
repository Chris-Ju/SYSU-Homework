var data = require('../model/dataHandle');

function register(db) {
    data.insert(db);
}

function check(db, callback) {
    data.check(db, function (val) {
        callback(val);
    });
}


exports.register = register;
exports.check    = check;