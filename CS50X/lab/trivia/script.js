function checkAnswer(selectedOption) {
    let correctAnswer = "CPU";
    let userAnswer = selectedOption.textContent;

    let feedbackElement = document.getElementById("mc-feedback");

    if (userAnswer === correctAnswer) {
        selectedOption.style.backgroundColor = "green";
        feedbackElement.textContent = "Correct!";
    } else {
        selectedOption.style.backgroundColor = "red";
        feedbackElement.textContent = "Incorrect";
    }
}

function checkFreeResponse() {
    let correctAnswer = "Hard Drive";
    let userAnswer = document.getElementById("fr-answer").value;

    let feedbackElement = document.getElementById("fr-feedback");

    if (userAnswer.toLowerCase() === correctAnswer.toLowerCase()) {
        document.getElementById("fr-answer").style.backgroundColor = "green";
        feedbackElement.textContent = "Correct!";
    } else {
        document.getElementById("fr-answer").style.backgroundColor = "red";
        feedbackElement.textContent = "Incorrect";
    }
}
