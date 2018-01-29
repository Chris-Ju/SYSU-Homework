var express    = require('express');
var path       = require('path');
var bodyParser = require('body-parser');
var userinfo   = require('../controller/userInfo');
var router     = express.Router();

router.use('/', bodyParser.json());
router.use(bodyParser.urlencoded({ extended: false }));

router.post('/', function (req, res) {
    userinfo.get(req.body, function (result) {
        if(result.length == 0) {
            res.status(404);
            res.end();
        } else {
            if(!!req.cookies.warning) {
                result[0].warning = req.cookies.warning;
                res.clearCookie('warning');
            }
            res.send(result[0]);
            res.end();
        }
    });
})


module.exports = router;
