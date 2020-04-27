#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <string>
#include <iostream>

using namespace std;

class GameState {
    public:
        GameState();
        void incrementScore(double amount);
        void decrementScore(double amount);
        double getScore();
        string calculateGrade();
    private:
        double currentScore;
};

#endif