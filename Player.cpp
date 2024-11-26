#include "Player.h"
#include <iostream>
#include "MacUILib.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    playerPosList = new objPosArrayList();
    objPos head(mainGameMechsRef->getBoardSizeX()/2,mainGameMechsRef->getBoardSizeY()/2, '@');
    playerPosList->insertHead(head);
    health = 100; 
    score = 0;
    collectedItems = 0;

}

Player::~Player()
{
    // No need to delete anything since we're not using dynamic memory allocation.
    delete playerPosList;
}

objPosArrayList* Player::getPlayerPos() const
{
    return playerPosList;
}

void Player::updatePlayerDir()
{
    char input = mainGameMechsRef->getInput();

    switch(input)
    {
        case 'W':
        case 'w':
            if(myDir == Dir::LEFT || myDir == Dir::RIGHT || myDir == Dir::STOP){
                myDir = Dir::UP;
            }
            break;
        case 'S':
        case 's':
            if(myDir == Dir::LEFT || myDir == Dir::RIGHT || myDir == Dir::STOP){
                myDir = Dir::DOWN;
            }
            break;
        case 'A':
        case 'a':
            if(myDir == Dir::UP || myDir == Dir::DOWN || myDir == Dir::STOP){
                myDir = Dir::LEFT;
            }
            break;
        case 'D':
        case 'd':
            if(myDir == Dir::UP || myDir == Dir::DOWN || myDir == Dir::STOP){
                myDir = Dir::RIGHT;
            }
            break;
            
        // case '+': // Increase speed
        //     if(speedLevel < maxSpeedLevel) {
        //         speedLevel++; // Increase speed level
        //     }
        //     break;

        // case '-': // Decrease speed
        //     if(speedLevel > 0) {
        //        speedLevel--; // Decrease speed level
        //     }
        //     break;
            
        default:
            break;   
    }
}


void Player::movePlayer(Food* Food)
{
    objPos playerPos = playerPosList->getHeadElement();
    newFood = Food;
    int Foodx = newFood->getFoodPos().pos->x;
    int Foody = newFood->getFoodPos().pos->y;
    int PosX = playerPos.pos->x;
    int PosY = playerPos.pos->y;
    int width = mainGameMechsRef->getBoardSizeX();
    int height = mainGameMechsRef->getBoardSizeY();

    switch(myDir){
        case Dir::UP:
           PosY = playerPos.pos->y-1;
           if(playerPos.pos->y < 1){
                PosY = height - 2;
            }
           break;
        case Dir::DOWN:
            PosY = playerPos.pos->y+1;
            if(playerPos.pos->y >= height - 1){
                PosY = 1;
            }
           break;
        case Dir::LEFT:
            PosX = playerPos.pos->x-1;
            if(playerPos.pos->x < 1){
                PosX = width - 2;
            }
           break;
        case Dir::RIGHT:
           PosX = playerPos.pos->x+1;
           if(playerPos.pos->x >= width - 1){
                PosX = 1;
            }
           break;
    }
    if(myDir!=STOP) {
        for(int i = 1; i < playerPosList->getSize(); i++)
        {
            objPos playerBody = playerPosList->getElement(i);
            if(playerBody.pos->x == playerPos.pos->x && playerBody.pos->y == playerPos.pos->y)
            {
                mainGameMechsRef->setLoseFlag();
            }
        }
        if(PosX == Foodx && PosY == Foody)
        {
            objPos nextObj(PosX,PosY,'@');
            playerPosList->insertHead(nextObj);
            newFood->generateFood(playerPos, mainGameMechsRef->getBoardSizeX(), mainGameMechsRef->getBoardSizeY());
            mainGameMechsRef->incrementScore();
        }
        else
        {
            objPos nextObj(PosX,PosY,'@');
            playerPosList->insertHead(nextObj);
            playerPosList->removeTail();
        }
    }
}


