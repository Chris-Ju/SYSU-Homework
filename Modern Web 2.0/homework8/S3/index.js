$(function() {
    init();
    $('#button').mouseleave(init);
});

function init() {
    $('.button').addClass('canClick');
    $('.button').bind('click', getData);
    $('.button').find('.number').html('');
    $('.button').find('.number').removeClass('appear').addClass('disappear');
    $('#info-bar').removeClass('canClick').addClass('grey');
    $('#info-bar').find('.info').html('');
    $('.apb').bind('click', robot);
    window.hasClick = [];
    window.number = [];
    window.doing = false;
    window.robot_doing = false;
}

function getData() {
    $buttonOnClick = $(this);
    $('.apb').unbind('click', robot);
    window.doing = true;
    if ($buttonOnClick.hasClass('canClick')) {
        $buttonOnClick.parent().find('.button').removeClass('canClick');
        $buttonOnClick.parent().find('.button').unbind('click', getData);
        $buttonOnClick.find('.number').removeClass('disappear').addClass('appear');
        $buttonOnClick.find('.number').html('...');
        $.get('/', function(data) {
            $('.apb').bind('click', robot);
            if (!window.doing || window.robot_doing)
                return;
            $buttonOnClick.find('.number').html(data.toString());
            window.hasClick.push($buttonOnClick.html()[0]);
            window.number.push(parseInt(data));
            for (var i = 0; i < 5; i++) {
                if (window.hasClick.indexOf($($('.button')[i]).html()[0].toString()) !== -1) {
                    continue;
                } else {
                    $($('.button')[i]).addClass('canClick');
                    $($('.button')[i]).bind('click', getData);
                }
            }
            if (window.hasClick.length == 5) {
                $("#info-bar").bind('click', sum);
                $("#info-bar").removeClass('grey').addClass('canClick');
            }
        });
    } else {
        return false;
    }
}

function robot_getData(index, callback) {
    window.doing = true;
    if ($($('.button')[index]).hasClass('canClick')) {
        $($('.button')[index]).find('.number').removeClass('disappear').addClass('appear');
        $($('.button')[index]).find('.number').html('...');
        $.ajax({
                url: '/',
                type: 'GET',
                cache: false
            })
            .done(function(data) {
                if (!window.doing || !window.robot_doing)
                    return;
                var $buttonOnClick = $($('.button')[index]);
                $buttonOnClick.find('.number').html(data.toString());
                window.hasClick.push($buttonOnClick.html()[0]);
                window.number.push(parseInt(data));
                if (window.hasClick.length == 5) {
                    sum();
                }
            });

        if (index != 4)
            callback(index + 1, robot_getData);
        $('.button').removeClass('canClick');
    }
}


function sum() {
    $("#info-bar").removeClass('canClick').addClass('grey');
    $("#info-bar").find('.info').html(function() {
        var sum = 0;
        for (i in window.number) {
            sum += window.number[i];
        }
        return sum;
    });
}

function robot() {
    init();
    window.robot_doing = true;
    $('.button').unbind('click', getData);
    $('.apb').unbind('click', robot);
    robot_getData(0, robot_getData);

}