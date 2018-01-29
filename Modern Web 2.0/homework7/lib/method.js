var userHandle = require('./userHandle.js');

function method(method, response, reqUrlJSON, chunks) {
    if (method == 'GET') {
        //console.log('Method : GET');
        var usernameToQuery = reqUrlJSON.query.username;
        if (reqUrlJSON.pathname == '/') {
            if (!!(usernameToQuery)) {
                console.log('UserHandle : Get user info');
                userHandle.getUserInfo(response, usernameToQuery);
            } else {
                console.log('UserHandle : Register');
                userHandle.registerPage(response);
            } 
        } else {
            //console.log("UserHandle : Get MIME data");
            userHandle.mimeDate(response, reqUrlJSON.pathname);
        }
    }
    else { 
        //console.log('Method : POST');
        userHandle.register(response, chunks);
    }
}

exports.method = method;