window.onload = function()
{
	load = false;
	last = 0;
	tmp = 0;
	S = document.getElementById('S');
	E = document.getElementById('E');
	roads = document.getElementsByClassName("roads");
	walls = document.getElementsByClassName("walls");
	warning = document.getElementById("warning");
	map = document.getElementById("map");
	S.addEventListener("mouseover", start, false);
	E.addEventListener("mouseover", end, false);
	map.addEventListener("mouseleave", leave, false);
	for(var i = 0; i < roads.length; i++)
	{
		roads[i].addEventListener("mouseover", pass(i), false);
	}
	for(var j = 0; j < walls.length; j++)
	{
		walls[j].addEventListener("mouseover", lose, false);
	}
}

function leave()
{
	var tmp = document.getElementsByClassName("walls");
	for(var k = 0; k < tmp.length; k++)
	{
		tmp[k].style.backgroundColor = "#EAEAEA";
	}
}

function start() 
{
	load = true;
	last = 0;
	leave();
	warning.style.opacity = 0;
}

function end() 
{
	if(last == 10)
	{
		win();
	}
	else
	{
		cheat();
	}

}



function pass(ele) 
{
	return function(){
		last = (ele == 11 ? last : ele);
	}
}

function win() 
{
	if(load)
	{
		warning.innerHTML = "You win!";
		warning.style.opacity = 1;
	}
	load = false;
}

function lose() 
{
	if(load)
	{
		warning.innerHTML = "You lose!";
		warning.style.opacity = 1;
		this.style.backgroundColor = "#FF0000";
	}
	load = false;
}

function cheat() 
{
	if(load)
	{
		warning.innerHTML = "Don't cheat, you should start form the 'S' and move to the 'E' inside the maze!";
		warning.style.opacity = 1;
	}
	load = false;
}








