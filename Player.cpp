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

void Player::movePlayer(Food* Food)
{
    objPos playerPos = playerPosList->getHeadElement(); 
    newFood = Food;
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

    if(checkFoodConsumption(playerPos))
    {
        increasePlayerLength();  
        newFood->generateFood(playerPosList, width, height); 
        mainGameMechsRef->incrementScore(); 
    }
    else
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



// void Player::movePlayer(Food* Food)
// {
//     bool moved = false;
//     objPos playerPos = playerPosList->getHeadElement();  // Get the current head position
//     newFood = Food;
//     int Foodx = newFood->getFoodPos().pos->x;
//     int Foody = newFood->getFoodPos().pos->y;
//     int width = mainGameMechsRef->getBoardSizeX();
//     int height = mainGameMechsRef->getBoardSizeY();

//     switch(myDir)
//     {
//         case Dir::UP:
//             playerPos.pos->y--;
//             if(playerPos.pos->y < 1){
//                 playerPos.pos->y = height - 2;  
//             } 
//             moved = true;
//             break;
        
//         case Dir::DOWN:
//             playerPos.pos->y++;
//             if(playerPos.pos->y >= height - 1){
//                 playerPos.pos->y = 1;
//             } 
//             moved = true;
//             break;
        
//         case Dir::LEFT:
//             playerPos.pos->x--;
//             if(playerPos.pos->x < 1){
//                 playerPos.pos->x = width - 2; 
//             } 
//             moved = true;
//             break;
        
//         case Dir::RIGHT:
//             playerPos.pos->x++;
//             if(playerPos.pos->x >= width - 1){
//                 playerPos.pos->x = 1;  
//             } 
//             moved = true;
//             break;

//         case Dir::STOP:
//             break;
//     }

//     if(myDir != STOP)
//     {
//         for(int i = 1; i < playerPosList->getSize(); i++) 
//         {
//             objPos playerBody = playerPosList->getElement(i);
//             if(playerBody.pos->x == playerPos.pos->x && playerBody.pos->y == playerPos.pos->y)
//             {
//                 mainGameMechsRef->setLoseFlag(); 
//                 return;
//             }
//         }

//         if(playerPos.pos->x == Foodx && playerPos.pos->y == Foody)
//         {
//             objPos nextObj(playerPos.pos->x, playerPos.pos->y, '@');  
//             playerPosList->insertHead(nextObj); 
//             newFood->generateFood(playerPosList, mainGameMechsRef->getBoardSizeX(), mainGameMechsRef->getBoardSizeY()); 
//             mainGameMechsRef->incrementScore(); 
//         }
//         else
//         {
//             objPos nextObj(playerPos.pos->x, playerPos.pos->y, '@');
//             playerPosList->insertHead(nextObj);  
//             playerPosList->removeTail();  
//         }
//     }
// }


// bool Player::checkFoodConsumption()
// {
//     objPos playerPos = playerPosList->getHeadElement(); 
//     static int xPos = playerPos.pos->x, yPos = playerPos.pos->y;
//     static int xFood = newFood->getFoodPos().pos->x, yFood = newFood->getFoodPos().pos->y; //Steph, interation 3.2

//     if(xPos == xFood && yPos == yFood)
//         {
//             return true;
//         }
// }
// void Player::increasePlayerLength()
// {
//     objPos playerPos = playerPosList->getHeadElement(); 
//     static int xPos = playerPos.pos->x, yPos = playerPos.pos->y;

//     objPos nextObj(xPos,yPos,'@');
//     playerPosList->insertHead(nextObj);
// }

// bool Player::checkSelfCollision()
// {
//     // PPA3 Finite State Machine logic
//     objPos playerHead = playerPosList->getHeadElement(); 
//     for(int i = 0; i < playerPosList->getSize(); i++)
//     {
//         objPos playerBody = playerPosList->getElement(i);
//         if(playerBody.pos->x == playerHead.pos->x && playerBody.pos->y == playerHead.pos->y)
//         {
//             mainGameMechsRef->setLoseFlag();
//             return mainGameMechsRef->getLoseFlagStatus();
//         }
//     }

// }
