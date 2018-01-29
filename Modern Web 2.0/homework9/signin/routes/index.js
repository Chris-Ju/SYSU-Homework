var express    = require('express');
var path       = require('path');
var register   = require('./register');
var bodyParser = require('body-parser');
var login      = require('../controller/login');
var userinfo   = require('./userInfo');
var signout    = require('./signout');
var router     = express.Router();

router.use('/',bodyParser.json());
router.use(bodyParser.urlencoded({ extended: true }));
router.use('/regist', register);
router.use('/getUserInfo', userinfo);
router.use('/signout', signout);

router.get('/', function(req, res) {
    if(!!req.cookies.username && req.cookies.username != req.query.username) {
        if(!!req.query.username) {
            console.log("There is a son who wants to look other's information.")
            res.cookie('warning', "只能查看自己的信息");
            res.redirect("http://localhost:8000?username=" + req.cookies.username);
        } else {
            res.redirect("http://localhost:8000?username=" + req.cookies.username);
        }
    } else {
        if(!req.query.username){
            console.log("Someone opens the homepage.");
            res.sendFile(path.join(__dirname, '../views/', 'index.html'));
        } else {
            res.sendFile(path.join(__dirname, '../views/', 'userInfo.html'));
        }
    }
});

router.post('/', function(req, res) {
    login.check(req.body, function (val) {
        if(val) {
            res.status(200);
            console.log("Someone logins successfully.");
            res.cookie('username', req.body.username, { maxAge : 24 * 60 * 60 * 1000});
        }
        else {
            res.status(404);
        }
        res.end();
    });
});



module.exports = router;
