var express    = require('express');
var path       = require('path');
var bodyParser = require('body-parser');
var router     = express.Router();

router.use('/', bodyParser.json());
router.use(bodyParser.urlencoded({ extended: false }));

router.get('/', function (req, res) {
    res.clearCookie('username');
    res.end();
});




module.exports = router;