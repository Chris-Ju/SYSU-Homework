$(function() {
    var url = document.location.toString();
    var arrUrl = url.split("?");
    var para = arrUrl[1].split("username=");
    $.ajax({
        url: '/getUserInfo',
        type: 'POST',
        dataType: "jsonp",
        data: { username: para[1] },
        statusCode: {
            200: function(data) {
                var result = JSON.parse(data.responseText);
                $('#userName').find('input').val(result.username);
                $('#studentId').find('input').val(result.studentId);
                $('#phone').find('input').val(result.phone);
                $('#email').find('input').val(result.email);
                if(!!result.warning) {
                    $("#warning").css("opacity", "1");
                    $("#warning").find("input").val(result.warning);
                }
            },
            404: function () {
                window.location.href = "http://localhost:8000";
            }
        }
    });
    $('#signout').click(function(event) {
        event.preventDefault();
        $.ajax({
            url: '/signout',
            type: 'GET',
            success: function () {
                window.location.href = "http://localhost:8000";
            }
        });
    });
});