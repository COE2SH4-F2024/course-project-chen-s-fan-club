#ifndef PLAYER_H
#define PLAYER_H

#include "GameMechs.h"
#include "objPos.h"
#include "objPosArrayList.h"
#include "Food.h"

// Player class representing the player in the game
class Player
{   
    public:
        enum Dir {UP, DOWN, LEFT, RIGHT, STOP};   // Enumeration for movement direction

        Player(GameMechs* thisGMRef);            // Constructor
        ~Player();                              // Destructor

        objPosArrayList* getPlayerPos() const;       
        void updatePlayerDir();
        void movePlayer(Food* Food);
        bool checkFoodConsumption(const objPos& playerHead); 
        void increasePlayerLength(); 
        bool checkSelfCollision(const objPos& playerHead); 

    private:
        objPosArrayList* playerPosList;     
        enum Dir myDir;
        Food* newFood; 
        int health;
        int score;
        int collectedItems;

        GameMechs* mainGameMechsRef;
};
#endif