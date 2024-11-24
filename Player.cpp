#include "Player.h"
#include <iostream>
#include "MacUILib.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    playerPos.setObjPos(10, 5, '@');

    health = 100; 
    score = 0;
    collectedItems = 0;

    speedLevel = 3;  
    maxSpeedLevel = 5;  

}

Player::~Player()
{
    // No need to delete anything since we're not using dynamic memory allocation.
}

objPos Player::getPlayerPos() const
{
    return playerPos;
}

void Player::updatePlayerDir()
{
    if(MacUILib_hasChar()){
        char input = MacUILib_getChar();

        if(input >= 'A' && input <= 'Z'){
            input += 32;
        }


        switch(input){
            case 'w':
                if(myDir == Dir::LEFT || myDir == Dir::RIGHT || myDir == Dir::STOP){
                    myDir = Dir::UP;
                }
                break;

            case 's':
                if(myDir == Dir::LEFT || myDir == Dir::RIGHT || myDir == Dir::STOP){
                    myDir = Dir::UP;
                }
                break;

            case 'a':
                if(myDir == Dir::LEFT || myDir == Dir::RIGHT || myDir == Dir::STOP){
                    myDir = Dir::UP;
                }
                break;

            case 'd':
                if(myDir == Dir::LEFT || myDir == Dir::RIGHT || myDir == Dir::STOP){
                    myDir = Dir::UP;
                }
                break;
            
            case '+': // Increase speed
            if (speedLevel > 0)
            {
                speedLevel--;
            }
            break;

        case '-': // Decrease speed
            if (speedLevel < maxSpeedLevel)
            {
                speedLevel++;
            }
            break;
            
        default:
            break;   
        }
    }          
}

void Player::movePlayer()
{
    bool moved = false;
    
    int width = mainGameMechsRef->getBoardSizeX();
    int height = mainGameMechsRef->getBoardSizeY();

    switch(myDir){
        case Dir::UP:
            playerPos.pos->y--;
            if(playerPos.pos->y < 1){
                playerPos.pos->y = height - 2;
            }
            moved = true;
            break;
        
        case Dir::DOWN:
            playerPos.pos->y++;
            if(playerPos.pos->y >= height - 1){
                playerPos.pos->y = 1;
            }
            moved = true;
            break;
        
        case Dir::LEFT:
            playerPos.pos->x--;
            if(playerPos.pos->x < 1){
                playerPos.pos->x = width - 2;
            }
            moved = true;
            break;
        
        case Dir::RIGHT:
            playerPos.pos->x++;
            if(playerPos.pos->x >= width - 1){
                playerPos.pos->x = 1;
            }
            moved = true;
            break;

        case Dir::STOP:
            break;
    }
}