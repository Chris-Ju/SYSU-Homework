$(function() {
    $('#signin').click(function(event) {
        event.preventDefault();
        var userName = $('#userName').val();
        var passWord = $('#password').val();
        $.ajax({
            url: '/',
            type: 'POST',
            dataType: "jsonp",
            data: {
                username: userName,
                password: passWord.MD5(32)
            },
            statusCode: {
                200: function() {
                    $("#warning").find("input").val("");
                    $("#warning").css("opacity", "0");
                    window.location.href = "http://localhost:8000?username=" + userName;
                },
                404: function() {
                    $("#warning").css("opacity", "1");
                    $('#warning').find('input').val('错误的用户名或者密码');
                }
            }
        });
    });
    $('#register').click(function(event) {
        event.preventDefault();
        window.location.href = "http://localhost:8000/regist";
    })
});