var express    = require('express');
var path       = require('path');
var bodyParser = require('body-parser');
var regist     = require('../controller/regist');
var router     = express.Router();

router.use('/', bodyParser.json());
router.use(bodyParser.urlencoded({ extended: false }));

router.get('/', function(req, res) {
    console.log("Someone enters the regist page.");
    res.sendFile(path.join(__dirname, '../views/', 'register.html'));
});

router.post('/', function(req, res) {
    console.log("Have another son.");
    regist.register(req.body);
    res.status(200);
    res.end();
});

router.post('/username', function(req, res) {
    console.log("A son wants to use '" + req.body.username + "' to be its username.");
    regist.check(req.body, function (val) {
        if(val)
            res.status(200);
        else
            res.status(404);
        res.end();
    });
});

router.post('/studentID', function(req, res) {
    console.log("A son wants to use '" + req.body.studentid + "' to be its StudentId.");
    regist.check(req.body, function (val) {
        if(val)
            res.status(200);
        else
            res.status(404);
        res.end();
    });
});

router.post('/phone', function(req, res) {
    console.log("A son wants to use '" + req.body.phone + "' to be its phone.");
    regist.check(req.body, function (val) {
        if(val)
            res.status(200);
        else
            res.status(404);
        res.end();
    });
});

router.post('/email', function(req, res) {
    console.log("A son wants to use '" + req.body.email + "' to be its email.");
    regist.check(req.body, function (val) {
        if(val)
            res.status(200);
        else
            res.status(404);
        res.end();
    });
});

module.exports = router;