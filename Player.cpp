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
    delete playerPosList; //nothing yet
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

void Player::movePlayer(Food* FoodBucket)
{
    objPos playerPos = playerPosList->getHeadElement(); 
    newFood = FoodBucket;

    int width = mainGameMechsRef->getBoardSizeX();
    int height = mainGameMechsRef->getBoardSizeY();

    switch(myDir)
    {
        case Dir::UP:
            playerPos.pos->y--;
            if(playerPos.pos->y < 1){
                playerPos.pos->y = height - 2;  
            } 
            break;
        
        case Dir::DOWN:
            playerPos.pos->y++;
            if(playerPos.pos->y >= height - 1){
                playerPos.pos->y = 1;
            } 
            break;
        
        case Dir::LEFT:
            playerPos.pos->x--;
            if(playerPos.pos->x < 1){
                playerPos.pos->x = width - 2; 
            } 
            break;
        
        case Dir::RIGHT:
            playerPos.pos->x++;
            if(playerPos.pos->x >= width - 1){
                playerPos.pos->x = 1;  
            } 
            break;

        case Dir::STOP:
            break;
    }

    if(checkSelfCollision(playerPos))
    {
        mainGameMechsRef->setLoseFlag(); 
        return;
    }
    bool foodConsumed = false;
    for (int i = 0; i < newFood->getFoodBucketSize(); ++i)
    {
        objPos food = newFood->getFoodAt(i);

        if (playerPos.pos->x == food.pos->x && playerPos.pos->y == food.pos->y)
        {
            foodConsumed = true;

            if (food.symbol == '$') 
            {
                mainGameMechsRef->incrementScore(50); 
            }
            else 
            {
                mainGameMechsRef->incrementScore(10);
            }

            increasePlayerLength(); 
            newFood->generateFood(playerPosList, width, height, 5); 
            break;
        }
    }

    if (!foodConsumed)
    {
        objPos nextObj(playerPos.pos->x, playerPos.pos->y, '@');
        playerPosList->insertHead(nextObj);  
        playerPosList->removeTail(); 
    }
    

}

bool Player::checkFoodConsumption(const objPos& playerHead)
{
    
    objPos foodPos = newFood->getFoodPos();
    return (playerHead.pos->x == foodPos.pos->x && playerHead.pos->y == foodPos.pos->y);
}

void Player::increasePlayerLength()
{
    objPos playerPos = playerPosList->getHeadElement(); 
    objPos nextObj(playerPos.pos->x, playerPos.pos->y, '@');
    playerPosList->insertHead(nextObj); 
}

bool Player::checkSelfCollision(const objPos& playerHead)
{
    for(int i = 1; i < playerPosList->getSize(); i++)
    {
        objPos playerBody = playerPosList->getElement(i);
        if(playerBody.pos->x == playerHead.pos->x && playerBody.pos->y == playerHead.pos->y)
        {
            return true; 
        }
    }
    return false;  
}



