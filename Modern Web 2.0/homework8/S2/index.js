$(function () {
   init();
   $('#button').mouseleave(init);
});

function init() {
    $('.button').bind('click', getData);
    $('.button').addClass('canClick');
    $('.button').find('.number').html('');
    $('.button').find('.number').removeClass('appear').addClass('disappear');
    $('#info-bar').removeClass('canClick').addClass('grey');
    $('#info-bar').find('.info').html('');
    $('.apb').bind('click', robot);
    window.hasClick = [];
    window.number   = [];
    window.doing    = false;
}

function getData() {
    $buttonOnClick = $(this);
    window.doing   = true;
    if ($buttonOnClick.hasClass('canClick')) {
        $('.apb').unbind('click', robot);
        $buttonOnClick.parent().find('.button').removeClass('canClick');
        $buttonOnClick.parent().find('.button').unbind('click', getData);
        $buttonOnClick.find('.number').removeClass('disappear').addClass('appear');
        $buttonOnClick.find('.number').html('...');
        $.get('/', function (data) {
            $('.apb').bind('click', robot);
            if(!window.doing)
                return;
            $buttonOnClick.find('.number').html(data.toString());
            window.hasClick.push($buttonOnClick.html()[0]);
            window.number.push(parseInt(data));
            for(var i = 0; i < 5; i++) {
                if(window.hasClick.indexOf($($('.button')[i]).html()[0].toString()) !== -1) {
                    continue;
                } else {
                    $($('.button')[i]).addClass('canClick');
                    $($('.button')[i]).bind('click', getData);
                }
            }
            if(window.hasClick.length == 5)
            {
                $("#info-bar").bind('click', sum);
                $("#info-bar").removeClass('grey').addClass('canClick');
            }
        });
    } else {
        return false;
    }
}

function robot_getdata(index) {
    window.doing   = true;
    $buttonOnClick = $($('.button')[index]);
    if ($buttonOnClick.hasClass('canClick')) {
        $buttonOnClick.parent().find('.button').removeClass('canClick');
        $buttonOnClick.find('.number').removeClass('disappear').addClass('appear');
        $buttonOnClick.find('.number').html('...');
        $.get('/', function (data) {
            if(!window.doing)
                return;
            $buttonOnClick.find('.number').html(data.toString());
            window.hasClick.push($buttonOnClick.html()[0]);
            window.number.push(parseInt(data));
            for(var i = 0; i < 5; i++) {
                if(window.hasClick.indexOf($($('.button')[i]).html()[0].toString()) !== -1) {
                    continue;
                } else {
                    $($('.button')[i]).addClass('canClick');
                }
            }
            index++;
            if(window.hasClick.length == 5)
            {
                sum();
                return;
            }
            robot_getdata(index);
        });
    } else {
        return false;
    }
}


function sum() {
    $("#info-bar").removeClass('canClick').addClass('grey');
    $("#info-bar").find('.info').html(function () {
        var sum = 0;
        for(i in window.number) {
            sum += window.number[i];
        }
        return sum;
    });
}

function robot() {
    init();
    $('.apb').unbind('click', robot);
    $('.button').unbind('click', getData);
    var index = 0;
    robot_getdata(index);
   
}