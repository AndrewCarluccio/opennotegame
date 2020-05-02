#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

class GameState {
    public:
        GameState();
        void addScore(double amount);
        void changeHealth(double amount);
        void setCurItem(string item);
        void setCurWeapon(string weapon);
        void collectItem(string itemId);
        void defeatBoss(string bossId);
        void setDying(bool val);
        void visitFirstTitle(bool val);
		void visitFirstTitle();
        void reset();
        void clearReset();
        void startDeathTransition();

        double getScore();
        double getHealth();
        string getCurItem();
        string getCurWeapon();
        vector<string> getCollectedItems();
        vector<string> getDefeatedBosses();
        bool wasReset();
        bool hasCollectedItem(string itemId);
        bool hasDefeatedBoss(string bossId);
        bool isDead();
        bool isTransitioning();
        bool isLowHealth();
        bool isFirstTitle();



        string calculateGrade();
    private:
        double MAX_HEALTH = 100.0;
        double LOW_THRESHOLD = 30.0;
        double health;
        bool dying;
        bool lowHealth;
		bool firstTitle;
        bool isReset;
        bool transitioning;
        double currentScore;
        string curItem;
        string curWeapon;
        vector<string>collectedItems;
        vector<string>defeatedBosses;

};

#endif