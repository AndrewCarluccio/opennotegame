#include "GameState.h"

GameState::GameState() {
    health = 100.0;
    currentScore = 0.0;
    curItem = "";
    curWeapon = "";
    dying = false;
    isReset = false;
    firstTitle = true;
}

void GameState::addScore(double amount) {
    currentScore += amount;

    if (amount > 0) {
        if (currentScore > 100.0) {
            currentScore = 100.0;
        }
    } else {
        if (currentScore < 0.0) {
            currentScore = 0.0;
        }

    }
}

void GameState::changeHealth(double amount) {
    health += amount;

    if (amount > 0) {
        if (health > MAX_HEALTH) {
            health = MAX_HEALTH;
        }
    } else {
        if (health < 0.0) {
            lowHealth = true;
            health = 0.0;
            cout << "Game over!" << endl;
        } else if (health < LOW_THRESHOLD) {
            lowHealth = true;
        }

    }

}

void GameState::setCurItem(string itemId) {
    curItem = itemId;
}

void GameState::setCurWeapon(string weaponId) {
    curWeapon = weaponId;
}

void GameState::collectItem(string itemId) {
    collectedItems.push_back(itemId);
}

void GameState::defeatBoss(string bossId) {
    defeatedBosses.push_back(bossId);
}

void GameState::setDying(bool val) {
    dying = val;
}

void GameState::reset() {
    health = 100.0;
    dying = false;
    currentScore = 0.0;
    isReset = true;
}

bool GameState::wasReset() {
    return isReset;
}

void GameState::clearReset() {
    isReset = false;
}

void GameState::visitFirstTitle() {
    firstTitle = false;
}

double GameState::getScore() {
    return currentScore;
}

double GameState::getHealth() {
    return health;
}

string GameState::getCurItem() {
    return curItem;
}

string GameState::getCurWeapon() {
    return curWeapon;
}

vector<string> GameState::getCollectedItems() {
    return collectedItems;
}

vector<string> GameState::getDefeatedBosses() {
    return defeatedBosses;
}

bool GameState::hasCollectedItem(string itemId) {
    return find(collectedItems.begin(), collectedItems.end(), itemId) != collectedItems.end();

}

bool GameState::hasDefeatedBoss(string bossId) {
    return find(defeatedBosses.begin(), defeatedBosses.end(), bossId) != defeatedBosses.end();
}

bool GameState::isDead() {
    return dying;
}

bool GameState::isLowHealth() {
    return lowHealth;
}

bool GameState::isFirstTitle() {
    return firstTitle;
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