#ifndef PLAYER_H
#define PLAYER_H

#include "GameMechs.h"
#include "objPos.h"
#include "objPosArrayList.h"
#include "Food.h"
class Player
{

    // Construct the remaining declaration from the project manual.

    // Only some sample members are included here

    // You will include more data members and member functions to complete your design.

    
    public:
        enum Dir {UP, DOWN, LEFT, RIGHT, STOP};  // This is the direction state

        Player(GameMechs* thisGMRef);
        ~Player();

        objPosArrayList* getPlayerPos() const;       
        void updatePlayerDir();
        void movePlayer(Food* Food);
        bool checkFoodConsumption(const objPos& playerHead);  // Updated signature
        void increasePlayerLength();  // Updated signature
        bool checkSelfCollision(const objPos& playerHead); 
        // bool checkFoodConsumption();
        // void increasePlayerLength();
        // bool checkSelfCollision();
        //More methods to be added here

    private:
        objPosArrayList* playerPosList; // Upgrade this in iteration 3.       
        enum Dir myDir;
        Food* newFood; 
        int health;
        int score;
        int collectedItems;


        // Need a reference to the Main Game Mechanisms
        GameMechs* mainGameMechsRef;
};

#endif