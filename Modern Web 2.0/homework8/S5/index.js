$(function() {
    init();
    $('#button').mouseleave(init);
});

function init() {
    $('#text').html('');
    $('#banner').html('');
    $('.button').find('.number').html('');
    $('.button').find('.number').removeClass('appear').addClass('disappear');
    $('#info-bar').addClass('grey');
    $('#info-bar').find('.info').html('');
    $('.apb').bind('click', robot);
    $('#words').html('');
    window.doing = false;
}


function AHandle(preSum, callback) {
    var $buttonOnClick = $($('.button')[0]);
    $buttonOnClick.find('.number').removeClass('disappear').addClass('appear');
    $buttonOnClick.find('.number').html('...');
    $.ajax({
            url: '/',
            type: 'GET',
            timeout: Math.floor(1000 + Math.random() * 2000)
        })
        .done(function(data) {
            if(!window.doing)
                return;
            $("#text").html('这是个天大的秘密');
            $buttonOnClick.find('.number').html(data.toString());
            callback(parseInt(data) + preSum);
        })
        .fail(function() {
            if(!window.doing)
                return;
            $("#text").html('这根本不是个秘密');
            $buttonOnClick.find('.number').html('N/A');
            callback(preSum);
        })
}

function BHandle(preSum, callback) {
    var $buttonOnClick = $($('.button')[1]);
    $buttonOnClick.find('.number').removeClass('disappear').addClass('appear');
    $buttonOnClick.find('.number').html('...');
    $.ajax({
            url: '/',
            type: 'GET',
            timeout: Math.floor(1000 + Math.random() * 2000)
        })
        .done(function(data) {
            if(!window.doing)
                return;
            $("#text").html('我不知道');
            $buttonOnClick.find('.number').html(data.toString());
            callback(parseInt(data) + preSum);
        })
        .fail(function() {
            if(!window.doing)
                return;
            $("#text").html('我知道');
            $buttonOnClick.find('.number').html('N/A');
            callback(preSum);
        })
}

function CHandle(preSum, callback) {
    var $buttonOnClick = $($('.button')[2]);
    $buttonOnClick.find('.number').removeClass('disappear').addClass('appear');
    $buttonOnClick.find('.number').html('...');
    $.ajax({
            url: '/',
            type: 'GET',
            timeout: Math.floor(1000 + Math.random() * 2000)
        })
        .done(function(data) {
            if(!window.doing)
                return;
            $("#text").html('你不知道');
            $buttonOnClick.find('.number').html(data.toString());
            callback(parseInt(data) + preSum);
        })
        .fail(function() {
            if(!window.doing)
                return;
            $("#text").html('你知道');
            $buttonOnClick.find('.number').html('N/A');
            callback(preSum);
        })
}

function DHandle(preSum, callback) {
    var $buttonOnClick = $($('.button')[3]);
    $buttonOnClick.find('.number').removeClass('disappear').addClass('appear');
    $buttonOnClick.find('.number').html('...');
    $.ajax({
            url: '/',
            type: 'GET',
            timeout: Math.floor(1000 + Math.random() * 2000)
        })
        .done(function(data) {
            if(!window.doing)
                return;
            $("#text").html('他不知道');
            $buttonOnClick.find('.number').html(data.toString());
            callback(parseInt(data) + preSum);
        })
        .fail(function() {
            if(!window.doing)
                return;
            $("#text").html('他知道');
            $buttonOnClick.find('.number').html('N/A');
            callback(preSum);
        })
}

function EHandle(preSum, callback) {
    var $buttonOnClick = $($('.button')[4]);
    $buttonOnClick.find('.number').removeClass('disappear').addClass('appear');
    $buttonOnClick.find('.number').html('...');
    $.ajax({
            url: '/',
            type: 'GET',
            timeout: Math.floor(1000 + Math.random() * 2000)
        })
        .done(function(data) {
            if(!window.doing)
                return;
            $("#text").html('才怪');
            $buttonOnClick.find('.number').html(data.toString());
            callback(parseInt(data) + preSum);
        })
        .fail(function() {
            if(!window.doing)
                return;
            $("#text").html('!(才怪)');
            $buttonOnClick.find('.number').html('N/A');
            callback(preSum);
        })
}

function BuddleHandle(preSum) {
    setTimeout(function() {
        $("#info-bar").removeClass('canClick').addClass('grey');
        $("#text").html('楼主异步调用战斗力感人，目测不超过' + preSum.toString());
        $("#info-bar").find('.info').html(preSum.toString());
    }, 1000);
}

function robot() {
    init();
    $('.apb').unbind('click', robot);
    var sum = 0;
    var index = [0, 1, 2, 3, 4];
    var run = [AHandle, BHandle, CHandle, DHandle, EHandle];
    window.doing = true;
    index.sort(function() {
        return 0.5 - Math.random();
    });
    var banner = '';
    for (i in index) {
        banner += String.fromCharCode(index[i] + 65) + ' ';
    }
    $('#banner').html(banner);
    run[index[0]](sum, function(sum) {
        run[index[1]](sum, function(sum) {
            run[index[2]](sum, function(sum) {
                run[index[3]](sum, function(sum) {
                    run[index[4]](sum, function(sum) {
                        BuddleHandle(sum);
                    })
                })
            })
        })
    })
}