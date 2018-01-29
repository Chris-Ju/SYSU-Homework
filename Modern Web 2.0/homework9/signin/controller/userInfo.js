var data = require('../model/dataHandle');

function get(username, callback) {
    data.find(username, function (result) {
        callback(result);
    });
}

exports.get = get;