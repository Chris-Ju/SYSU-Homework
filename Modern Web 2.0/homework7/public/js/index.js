$(function() {
    $("#userName").blur(checkAll);
    $("#studentId").blur(checkAll);
    $("#phone").blur(checkAll);
    $("#email").blur(checkAll);
    $("#reset").click(deleteWarning);
    $("#submit").click(checkAll);
});

function checkUserName() {
    var userName = $("#userName").val();
    var reg = /^[a-zA-Z][a-zA-Z0-9_]{5,17}$/;
    if (userName == '') {
        return false;
    } else if (reg.test(userName)) {
        $("#warning").css("opacity", "0");
        return true;
    } else if (/[^a-zA-Z0-9_]/.test(userName)) {
        $("#warning").find("input").val("用户名只能由英文字母、数字或者下划线组成");
        return false;
    } else if (/^[^a-zA-Z]/.test(userName)) {
        $("#warning").css("opacity", "1");
        $("#warning").find("input").val("用户名开头应为英文字母");
        return false;
    } else if (userName.length < 6 || userName.length > 18) {
        $("#warning").css("opacity", "1");
        $("#warning").find("input").val("用户名长度应为6-18个字符");
        return false;
    }
}

function checkStudentId() {
    var studentId = $("#studentId").val();
    var reg = /^[^0][0-9]{7}$/;
    if (studentId == "") {
        return false;
    } else if (reg.test(studentId)) {
        $("#warning").css("opacity", "0");
        return true;
    } else if (/[^0-9]/.test(studentId)) {
        $("#warning").css("opacity", "1");
        $("#warning").find("input").val("学号应为数字");
        return false;
    } else if (studentId.length != 8) {
        $("#warning").css("opacity", "1");
        $("#warning").find("input").val("学号应为8位");
        return false;
    } else if (/^[0]/.test(studentId)) {
        $("#warning").css("opacity", "1");
        $("#warning").find("input").val("学号开头不能为0");
        return false;
    }
}

function checkPhone() {
    var phone = $("#phone").val();
    var reg = /^[^0][0-9]{10}$/;
    if (phone == "") {
        return false;
    } else if (reg.test(phone)) {
        $("#warning").css("opacity", "0");
        return true;
    } else if (/[^0-9]/.test(phone)) {
        $("#warning").css("opacity", "1");
        $("#warning").find("input").val("电话应为数字");
        return false;
    } else if (phone.length != 11) {
        $("#warning").css("opacity", "1");
        $("#warning").find("input").val("电话应为11位");
        return false;
    } else if (/^[0]/.test(phone)) {
        $("#warning").css("opacity", "1");
        $("#warning").find("input").val("电话开头不能为0");
        return false;
    }
}

function checkEmail() {
    var email = $("#email").val();
    var reg = /^[0-9a-zA-Z_\-]+@(([a-zA-Z_\-])+\.)+[a-zA-Z]{2,4}$/;
    if (email == "") {
        return false;
    } else if (reg.test(email)) {
        $("#warning").css("opacity", "0");
        return true;
    } else {
        $("#warning").css("opacity", "1");
        $("#warning").find("input").val("请输入正确的邮箱地址");
        return false;
    }
}


function checkAll() {
    var arr = [checkUserName, checkStudentId, checkPhone, checkEmail];
    switch (this.id) {
        case "userName":
            break;
        case "studentId":
            [arr[0], arr[1]] = [arr[1], arr[0]];
            break;
        case "phone":
            [arr[0], arr[2]] = [arr[2], arr[0]];
            break;
        case "email":
            [arr[0], arr[3]] = [arr[3], arr[0]];
            break;
        default:
            break;
    };
    return arr[0]() && arr[1]() && arr[2]() && arr[3]();
}

function deleteWarning() {
    $("#warning").find("input").val("");
    $("#warning").css("opacity", "0");
}