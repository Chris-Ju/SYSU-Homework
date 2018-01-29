var express      = require('express');
var cookieParser = require('cookie-parser');
var routes       = require('./routes/index');
var app          = express();

app.use(express.static(__dirname + '/public'));
app.use(cookieParser());
app.use('/', routes);
app.listen(8000);



