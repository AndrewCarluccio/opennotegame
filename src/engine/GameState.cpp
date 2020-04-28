#include "GameState.h"

GameState::GameState() {
    currentScore = 0;
}

void GameState::incrementScore(double amount) {
    if (amount < 0) {
        cout << "GameState::incrementScore: increment amount must be positive" << endl;
        return;
    }

    currentScore += amount;
    if (currentScore > 100.0) {
        currentScore = 100.0;
    }
}
void GameState::decrementScore(double amount) {
    if (amount < 0) {
        cout << "GameState::decrementScore: decrement amount must be positive" << endl;
        return;
    }

    currentScore -= amount;
    if (currentScore < 0.0) {
        currentScore = 0.0;
    }
}

double GameState::getScore() {
    return currentScore;

}

string GameState::calculateGrade() {
    if (currentScore >= 97.0) {
        return "A+";
    } else if (currentScore >= 93.0) {
        return "A";
    } else if (currentScore >= 90.0) {
        return "A-";
    } else if (currentScore >= 87.0) {
        return "B+";
    } else if (currentScore >= 83.0) {
        return "B";
    } else if (currentScore >= 80.0) {
        return "B-";
    } else if (currentScore >= 77.0) {
        return "C+";
    } else if (currentScore >= 73.0) {
        return "C";
    } else if (currentScore >= 70.0) {
        return "C-";
    } else if (currentScore >= 67.0) {
        return "D+";
    } else if (currentScore >= 63.0) {
        return "D";
    } else if (currentScore >= 60.0) {
        return "D-";
    } else {
        return "F";
    }
}