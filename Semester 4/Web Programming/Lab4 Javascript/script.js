document.getElementById("textinput").style.display = "none";

function inputBlur() {
    document.getElementById("textinput").style.display = "none";
    document.getElementById("comboBox").style.display = "block";
    let comboBox = document.getElementById("comboBox");
    let selectedIndex = comboBox.selectedIndex;
    let options = comboBox.options;
    options[selectedIndex].value = document.getElementById("textinput").value;
    options[selectedIndex].text = document.getElementById("textinput").value;
    document.getElementById("comboBox").value = document.getElementById("textinput").value;
}

function comboBoxClick() {
    document.getElementById("textinput").style.display = "block";
    document.getElementById("textinput").value = document.getElementById("comboBox").value;
    document.getElementById("textinput").textContent = document.getElementById("comboBox").value;
    document.getElementById("comboBox").style.display = "none";
    document.getElementById("textinput").focus();
}