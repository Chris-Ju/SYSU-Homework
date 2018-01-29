var http = require('http'),
    url  = require('url'),
    method = require('./method.js');


function startServer(PORT) {
    var createServer = http.createServer(function(request, response) {
        var reqUrlJSON = {}, chunks = [];
        //console.log(request);
        reqUrlJSON = url.parse(request.url, true);
        request.on('data', function(chunk) {
            chunks.push(chunk);
        });
        request.on('end', function() {
           chunks = Buffer.concat(chunks).toString();
           method.method(request.method, response, reqUrlJSON, chunks);
        });
    });

    createServer.listen(PORT);
    console.log("Server runing at port: " + PORT + ".");
}

exports.startServer = startServer;