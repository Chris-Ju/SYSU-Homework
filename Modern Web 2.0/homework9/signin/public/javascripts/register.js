val = [false, false, false, false, false, false];
db  = {};
$(function() {
    $("#userName").blur(checkAll);
    $("#studentId").blur(checkAll);
    $("#password").blur(checkAll);
    $("#Rpassword").blur(checkAll);
    $("#phone").blur(checkAll);
    $("#email").blur(checkAll);
    $("#reset").bind('click', deleteWarning);
    $("#submit").bind('click', checkAll);
});


function checkUserName() {
    var userName = $("#userName").val();
    var reg = /^[a-zA-Z][a-zA-Z0-9_]{5,17}$/;
    if (db.username != userName) {
        val[0] = false;
    }
    if (userName == '') {
        val[0] = false;
        return false;
    } else if (reg.test(userName)) {
        if (val[0]) {
            return true;
        }
        val[0] = true;
        $.ajax({
            url: '/regist/username',
            type: 'POST',
            dataType: 'jsonp',
            data: {
                username: userName
            },
            statusCode: {
                200: function() {
                    $("#warning").css("opacity", "0");
                    db.username = userName;
                    return true;
                },
                404: function() {
                    $("#warning").css("opacity", "1");
                    $("#warning").find("input").val("用户名已被注册");
                    return false;
                }
            }
        });
    } else if (/[^a-zA-Z0-9_]/.test(userName)) {
        $("#warning").css("opacity", "1");
        $("#warning").find("input").val("用户名只能由英文字母、数字或者下划线组成");
        val[0] = false;
        return false;
    } else if (/^[^a-zA-Z]/.test(userName)) {
        $("#warning").css("opacity", "1");
        $("#warning").find("input").val("用户名开头应为英文字母");
        val[0] = false;
        return false;
    } else if (userName.length < 6 || userName.length > 18) {
        $("#warning").css("opacity", "1");
        $("#warning").find("input").val("用户名长度应为6-18个字符");
        val[0] = false;
        return false;
    }
}

function checkPassword() {
    var password = $("#password").val();
    var reg = /[A-Za-z0-9\-\_]{6,12}$/;
    if (password == "") {
        val[1] = false;
        return false;
    } else if (reg.test(password)) {
        $("#warning").css("opacity", "0");
        val[1] = true;
        return true;
    } else if (/[^A-Za-z0-9\-\_]/.test(password)) {
        $("#warning").css("opacity", "1");
        $("#warning").find("input").val("密码只能由数字、字母、下划线或中划线组成");
        val[1] = false;
        return false;
    } else if (password.length > 12 || password.length < 6) {
        $("#warning").css("opacity", "1");
        $("#warning").find("input").val("密码应为6-12位");
        val[1] = false;
        return false;
    }
}

function checkRpassword() {
    var Rpassword = $("#Rpassword").val();
    var password = $("#password").val();
    if (Rpassword == "" || !checkPassword()) {
        $("#Rpassword").parent().find($('.r_password')).css('background-position', '0px -200px');
        val[2] = false;
        return false;
    } else if (Rpassword == password) {
        $("#warning").css("opacity", "0");
        $("#Rpassword").parent().find($('.r_password')).css('background-position', '0px -166px');
        val[2] = true;
        return true;
    } else {
        $("#warning").css("opacity", "1");
        $("#Rpassword").parent().find($('.r_password')).css('background-position', '0px -200px');
        $("#warning").find("input").val("两次密码输入不一致");
        val[2] = false;
        return false;
    }
}

function checkStudentId() {
    var studentId = $("#studentId").val();
    var reg = /^[^0][0-9]{7}$/;
    if (db.studentId != studentId) {
        val[3] = false;
    }
    if (studentId == "") {
        val[3] = false;
        return false;
    } else if (reg.test(studentId)) {
        if (val[3]) {
            return true;
        }
        val[3] = true;
        $.ajax({
            url: '/regist/studentID',
            type: 'POST',
            dataType: 'jsonp',
            data: {
                studentid: studentId
            },
            statusCode: {
                200: function() {
                    $("#warning").css("opacity", "0");
                    db.studentId = studentId;
                    return true;
                },
                404: function() {
                    $("#warning").css("opacity", "1");
                    $("#warning").find("input").val("学号已被注册");
                    return false;
                }
            }
        });
    } else if (/[^0-9]/.test(studentId)) {
        $("#warning").css("opacity", "1");
        $("#warning").find("input").val("学号应为数字");
        val[3] = false;
        return false;
    } else if (studentId.length != 8) {
        $("#warning").css("opacity", "1");
        $("#warning").find("input").val("学号应为8位");
        val[3] = false;
        return false;
    } else if (/^[0]/.test(studentId)) {
        $("#warning").css("opacity", "1");
        $("#warning").find("input").val("学号开头不能为0");
        val[3] = false;
        return false;
    }
}

function checkPhone() {
    var phone = $("#phone").val();
    var reg = /^[^0][0-9]{10}$/;
    if (db.phone != phone) {
        val[4] = false;
    }
    if (phone == "") {
        val[4] = false;
        return false;
    } else if (reg.test(phone)) {
        if (val[4]) {
            return true;
        }
        val[4] = true;
        $.ajax({
            url: '/regist/phone',
            type: 'POST',
            dataType: 'jsonp',
            data: {
                phone: phone
            },
            statusCode: {
                200: function() {
                    $("#warning").css("opacity", "0");
                    db.phone = phone;
                    return true;
                },
                404: function() {
                    $("#warning").css("opacity", "1");
                    $("#warning").find("input").val("电话已被注册");
                    return false;
                }
            }
        });
    } else if (/[^0-9]/.test(phone)) {
        $("#warning").css("opacity", "1");
        $("#warning").find("input").val("电话应为数字");
        val[4] = false;
        return false;
    } else if (phone.length != 11) {
        $("#warning").css("opacity", "1");
        $("#warning").find("input").val("电话应为11位");
        val[4] = false;
        return false;
    } else if (/^[0]/.test(phone)) {
        $("#warning").css("opacity", "1");
        $("#warning").find("input").val("电话开头不能为0");
        val[4] = false;
        return false;
    }
}

function checkEmail() {
    var email = $("#email").val();
    var reg = /^[0-9a-zA-Z_\-]+@(([a-zA-Z_\-])+\.)+[a-zA-Z]{2,4}$/;
    if (db.email != email) {
        val[0] = false;
    }
    if (email == "") {
        val[5] = false;
        return false;
    } else if (reg.test(email)) {
        if (val[5]) {
            return true;
        }
        val[5] = true;
        $.ajax({
            url: '/regist/email',
            type: 'POST',
            dataType: 'jsonp',
            data: {
                email: email
            },
            statusCode: {
                200: function() {
                    $("#warning").css("opacity", "0");
                    db.email = email;
                    return true;
                },
                404: function() {
                    $("#warning").css("opacity", "1");
                    $("#warning").find("input").val("邮箱已被注册");
                    return false;
                }
            }
        });
    } else {
        $("#warning").css("opacity", "1");
        $("#warning").find("input").val("请输入正确的邮箱地址");
        val[5] = false;
        return false;
    }
}


function checkAll() {
    var arr = [checkUserName, checkPassword, checkRpassword, checkStudentId, checkPhone, checkEmail];
    switch (this.id) {
        case "userName":
            break;
        case "password":
            [arr[0], arr[1]] = [arr[1], arr[0]];
            break;
        case "Rpassword":
            [arr[0], arr[2]] = [arr[2], arr[0]];
            break;
        case "studentId":
            [arr[0], arr[3]] = [arr[3], arr[0]];
            break;
        case "phone":
            [arr[0], arr[4]] = [arr[4], arr[0]];
            break;
        case "email":
            [arr[0], arr[5]] = [arr[5], arr[0]];
            break;
        default:
            break;
    };
    if (arr[0]() && arr[1]() && arr[2]() && arr[3]() && arr[4]() && arr[5]()) {
        $("#submit").unbind('click', checkAll);
        var username = $("#userName").val();
        var password = $("#password").val();
        var studentID = $("#studentId").val();
        var phone = $("#phone").val();
        var email = $("#email").val();
        $.ajax({
            url: '/regist',
            type: 'POST',
            dataType: 'jsonp',
            data: {
                username: username,
                password: password.MD5(32),
                studentId: studentID,
                phone: phone,
                email: email
            },
            statusCode: {
                200: function() {
                    window.location.href = "http://localhost:8000?username=" + username;
                },
                404: function() {}
            }
        });
    }
}

function deleteWarning() {
    $("#warning").find("input").val("");
    $("input").val("");
    $("#warning").css("opacity", "0");
}