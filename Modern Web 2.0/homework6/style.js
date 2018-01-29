/*
 * 点击start，如果点击确定，则是地域模式，反之为普通模式；地狱模式每过10s会进行随机移动。
 */
var seconds = 0;
var steps   = 0;
var arrLeft = [];
var	arrTop  = [];
var	val     = false;
var t       = 0;
window.onload = function ()
{
	
	for(var i = 0; i < 16; i++)
	{
		var html   = '<div class="inner" id="panda_' + i.toString() + '"></div>';
		var left   = (i % 4) * 88 + i % 4 + 1 + "px";
		var height = Math.floor(i / 4) * 88 + Math.floor(i / 4) + 1 + "px";
		$("#photo").append(html);
		$("#panda_" + i).css("background-position", "-" + left + " -" + height);
		$("#panda_" + i).css("left", left);
		$("#panda_" + i).css("top", height);
		$("#panda_" + i).click(move);
		arrLeft[i] = left;
		arrTop[i]  = height;
	}
	$("#panda_15").css("background", "0");
	$("#panda_15").css("border", "0");
	$("#start").click(select);
	$("#end").click(end);
}



function move()
{
	if(!val)
		return;
	var that = this;
	var tmp  = function() 
	{
		var left = that.style.left;
		var top  = that.style.top;
		if(panda_15.style.left == left &&  Math.abs(parseInt(panda_15.style.top) - parseInt(top)) == 89  || panda_15.style.top == top && Math.abs(parseInt(panda_15.style.left) - parseInt(left)) == 89)
		{
			that.style.left     = panda_15.style.left;
			that.style.top      = panda_15.style.top;
			panda_15.style.left = left;
			panda_15.style.top  = top;
			steps++;
			document.getElementById("step").innerHTML = steps;
		}
	}
	tmp();
	var conclude = function()
	{
		for(var i = 0; i < 16; i++)
		{
			if($(".inner")[i].style.left != arrLeft[i] || $(".inner")[i].style.top != arrTop[i])
			{
				return false;
			}
		}
		return true;
	}
	if(conclude() && val)
	{
		setTimeout('alert("You win!  " + "Time: " + seconds + "s  " + "Steps: " + steps)', 400);
		val = false;
		clearInterval(t);
	}
}	

function start_1()
{
	seconds = 0;
	steps   = 0;
	document.getElementById("time").innerHTML = seconds;
	document.getElementById("step").innerHTML = 0;
	if(t != 0)
		clearInterval(t);
	t = setInterval(time, 1000);
	for(var i = 0; i < 1000; i++)
	{
		var that = $(".inner")[Math.floor(Math.random() * 15)];
		var left = that.style.left;
		var top  = that.style.top;
		if(panda_15.style.left == left &&  Math.abs(parseInt(panda_15.style.top) - parseInt(top)) == 89  || panda_15.style.top == top && Math.abs(parseInt(panda_15.style.left) - parseInt(left)) == 89)
		{
			that.style.left     = panda_15.style.left;
			that.style.top      = panda_15.style.top;
			panda_15.style.left = left;
			panda_15.style.top  = top;
		}
	}
	
	function time()
	{
		seconds = seconds + 1;
		document.getElementById("time").innerHTML = seconds;
	}
	val = true;
}

function start_2()
{
	seconds = 0;
	steps   = 0;
	document.getElementById("time").innerHTML = seconds;
	document.getElementById("step").innerHTML = 0;
	if(t != 0)
		clearInterval(t);
	t = setInterval(time, 1000);
	for(var i = 0; i < 300; i++)
	{
		var that = $(".inner")[Math.floor(Math.random() * 15)];
		var left = that.style.left;
		var top  = that.style.top;
		if(panda_15.style.left == left &&  Math.abs(parseInt(panda_15.style.top) - parseInt(top)) == 89  || panda_15.style.top == top && Math.abs(parseInt(panda_15.style.left) - parseInt(left)) == 89)
		{
			that.style.left     = panda_15.style.left;
			that.style.top      = panda_15.style.top;
			panda_15.style.left = left;
			panda_15.style.top  = top;
		}
	}
	
	function time()
	{
		seconds = seconds + 1;
		document.getElementById("time").innerHTML = seconds;
		if(seconds % 10 == 0)
		{
			for(var i = 0; i < 100; i++)
			{
				var that = $(".inner")[Math.floor(Math.random() * 15)];
				var left = that.style.left;
				var top  = that.style.top;
				if(panda_15.style.left == left &&  Math.abs(parseInt(panda_15.style.top) - parseInt(top)) == 89  || panda_15.style.top == top && Math.abs(parseInt(panda_15.style.left) - parseInt(left)) == 89)
				{
					that.style.left     = panda_15.style.left;
					that.style.top      = panda_15.style.top;
					panda_15.style.left = left;
					panda_15.style.top  = top;
				}
			}
		}
	}
	val = true;
}

function end()
{
	if(!val)
		return;
	clearInterval(t);
	seconds = 0;
	steps   = 0;
	alert("Stupid guy! Look at me!");
	document.getElementById("time").innerHTML = seconds;
	document.getElementById("step").innerHTML = 0;
	for(var i = 0; i < 16; i++)
	{
		$(".inner")[i].style.left = arrLeft[i];
		$(".inner")[i].style.top  = arrTop[i];
	}
		
}

function select()
{
	var sel = confirm("Do you want a hell mode?")
	if(sel == true)
	{
		start_2();
	}
	else
	{
		start_1();
	}
}