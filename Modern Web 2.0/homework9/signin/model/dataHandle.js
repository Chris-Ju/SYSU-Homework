var MongoClient = require('mongodb').MongoClient;
var url = "mongodb://localhost:27017/mydb";

var insertData = function(client, data, callback) {
    var db = client.db('mytestingdb');
    var collection = db.collection('user');
    collection.insert(data, function(err, result) {
        if (err) {
            console.log('Error:' + err);
            return;
        }
        callback(result);
    });
}

var selectData = function(client, data, callback) {
    var db = client.db('mytestingdb');
    var collection = db.collection('user');
    collection.find(data).toArray(function(err, result) {
        if (err) {
            console.log('Error:' + err);
            return;
        }
        callback(result);
    });
}

var getData = function (client, data, callback) {
    var db = client.db('mytestingdb');
    var collection = db.collection('user');
    collection.find(data).toArray(function(err, result) {
        if (err) {
            console.log('Error:' + err);
            return;
        }
        callback(result);
    });
}

function find(username, callback) {
    MongoClient.connect(url, function(err, db) {
        getData(db, username, function(result) {
            if(result.length == 0)
                callback(result);
            else
                callback(result);
            db.close();
        });
    });
}

function insert(data) {
    MongoClient.connect(url, function(err, db) {
        insertData(db, data, function(result) {
            db.close();
        });
    });
}

function check(data, callback) {
    MongoClient.connect(url, function(err, db) {
        selectData(db, data, function(result) {
            if(result.length == 0)
                callback(true);
            else
                callback(false);
            db.close();
        });
    });
}

function checkPass(data, callback) {
    MongoClient.connect(url, function(err, db) {
        selectData(db, data, function(result) {
            if(result.length == 0)
                callback(false);
            else
                callback(true);
            db.close();
        });
    });
}

exports.insert    = insert;
exports.check     = check;
exports.checkPass = checkPass;
exports.find      = find;