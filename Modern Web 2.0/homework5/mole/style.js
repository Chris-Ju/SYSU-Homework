$(function() {
    ing = false;
    BE = document.getElementById("BE");
    BE.addEventListener("click", runOrStop);
    time = document.getElementById("time");
    score = document.getElementById("score");
    lattern = document.getElementsByClassName("lattern");
    property = document.getElementById("property");
    for (var i = 0; i < lattern.length; i++) {
        lattern[i].addEventListener("click", _click);
    }
});

function getNext() {
    last = Math.floor(Math.random() * 60);
    lattern[last].style.backgroundColor = "#FF0000";
}

function Time() {
    --time.value;
    if (time.value == 0) {
        clearInterval(t);
        alert("Game over!\nYour score is " + score.value);
        ing = false;
        property.value = "Game Over";
        score.value = 0;
        lattern[last].style.backgroundColor = "#FFFFFF";
    }
}

function runOrStop() {
    if (!ing) {
        ing = true;
        time.value = 30;
        property.value = "Playing";
        getNext();
        t = setInterval(Time, 1000);
    } else {
        time.value = 0;
        ing = false;
        window.clearInterval(t);
        alert("Game over!\nYour score is " + score.value);
        property.value = "Game Over";
        score.value = 0;
        lattern[last].style.backgroundColor = "#FFFFFF";
    }
}

function _click() {
    if (ing) {
        if (this.style.backgroundColor == "rgb(255, 0, 0)") {
            score.value++;
            this.style.backgroundColor = "#FFFFFF";
            getNext();
        } else {
            score.value--;
        }
    }
}