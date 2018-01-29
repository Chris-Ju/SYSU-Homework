var fs = require('fs');

var fileData = '../data/data.json';

function readFileData() {
    var retJSONData;
    try {
        retJSONData = fs.readFileSync(fileData, 'utf-8');
        //console.log("JSON : Get JSON Data");
        return JSON.parse(retJSONData);
    } catch (e) {
        console.log(e.message);
        fs.writeFileSync(fileData, "[]", 'utf-8');
        return [];
    }
}

function checkExist(username, studentId, phone, email, data) {
    var warning = ["用户名存在", "学号存在", "电话存在", "邮箱存在"];
    for(i in data) {
        if (data[i].username == username) {
            return warning[0];
        } else if (data[i].studentId == studentId) {
            return warning[1];
        } else if (data[i].phone == phone) {
            return warning[2];
        } else if (data[i].email == email) {
            return warning[3];
        } 
    }
    return true;
}

function insert(postJSONData) {
    var JSONDate  = readFileData();
    var username  = postJSONData.username,
        studentId = postJSONData.studentId,
        phone     = postJSONData.phone,
        email     = postJSONData.email;
    var flag = checkExist(username, studentId, phone, email, JSONDate);
    delete postJSONData.warning;
    delete postJSONData.submit;
    if(flag === true) {
        JSONDate.push(postJSONData);
        fs.writeFileSync(fileData, JSON.stringify(JSONDate), 'utf-8');
        return true;
    } else {
        return flag;
    }
}

function UserInfo(username) {
    var JSONDate  = readFileData();
    for(i in JSONDate) {
        if(JSONDate[i].username == username)
            return JSONDate[i];
    }
    return false;
}


exports.insert   = insert;
exports.UserInfo = UserInfo;