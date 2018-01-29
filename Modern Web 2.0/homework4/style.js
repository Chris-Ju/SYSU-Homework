var text = "";
var val = false;

function testOnClick(button) {
    if (val && !(button.id == "+" || button.id == "-" || button.id == "*" || button.id == "/" || button.id == ".")) {
        text = "";
    } else
        text = document.getElementById("input").value;
    val = false;
    if (text[text.length - 1] == 0 && (text.length == 1 || !(text[text.length - 2] >= '1' && text[text.length - 2] <= '9')) && !(button.id == "+" || button.id == "-" || button.id == "*" || button.id == "/" || button.id == ".")) {
        text = text.substr(0, text.length - 1);
    }
    if (button.id == "B") {
        text = text.substr(0, text.length - 1);
    } else if (button.id == "CE") {
        text = "";
    } else if (button.id == "=") {
        conclude();
    } else {
        text += button.id;
    }
    document.getElementById("input").value = text;
}

function conclude() {
    text = document.getElementById("input").value;
    var stack = [];
    for (var i = 0, item; i < text.length; i++) {
        item = text.charAt(i);
        if ('(' === item) {
            stack.push('(');
        } else if (')' === item) {
            if (stack.length > 0) {
                stack.pop();
            }
        }
    }
    if (/\([\)]/.test(text)) {
        alert("Empty parentheses!");
        text = "";
    } else if (/[\+\-\*\/]{2,}/.test(text)) {
        alert("The operator appears twice in a row!");
        text = "";
    } else if (0 !== stack.length) {
        alert("Bracket mismatch!");
        text = "";
    } else if (/\([\*\/]/.test(text)) {
        alert("There is operator after the front parentheses!");
        text = "";
    } else if (/[\+\-\*\/]\)/.test(text)) {
        alert("There is operator before the back parentheses!");
        text = "";
    } else if (/[^\+\-\*\/\(]\(/.test(text)) {
        alert("There is no operator before the front parentheses!");
        text = "";
    } else if (/\)[^\+\-\*\/\)]/.test(text)) {
        alert("There is no operator after the back parentheses!");
        text = "";
    } else if (/[^0-9\+\-\*\/\(\)\.]/.test(text)) {
        alert("There is illegal character!");
        text = "";
    } else if (/^[^0-9\-\+\(]/.test(text)) {
        alert("There is operator in the begin!");
        text = "";
    } else if (/[^0-9\)]$/.test(text)) {
        alert("There is no number or the back parentheses in the end!");
        text = "";
    } else if (/[0-9]\.\d+\.[0-9]/.test(text)) {
        alert("Two point are be used!");
        text = "";
    } else {
        text = eval(text);
        text = numTofixed(text);
        val = true;
    }
}

function numTofixed(num) {
    num = parseFloat(num.toFixed(10))
    return num;
}