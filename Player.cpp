#include "Player.h"
#include <iostream>
#include "MacUILib.h"

// Constructor: Initializes the player with a reference to the game mechanics
Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;        // Set game mechanics reference
    myDir = STOP;                       // Initialize player direction as stopped

    playerPosList = new objPosArrayList();            // Create a list to track player position

    // Set initial position at the center of the board with '@' symbol
    objPos head(mainGameMechsRef->getBoardSizeX()/2,mainGameMechsRef->getBoardSizeY()/2, '@');
    playerPosList->insertHead(head);

    health = 100; 
    score = 0;
    collectedItems = 0;
}

// Destructor: Frees dynamically allocated memory for the position list
Player::~Player()
{
    delete playerPosList; 
}

// Get the current player position list
objPosArrayList* Player::getPlayerPos() const
{
    return playerPosList;
}


// Update the player's direction based on user input
void Player::updatePlayerDir()
{
    char input = mainGameMechsRef->getInput();

    // Change direction based on input
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
        default:
            break;   
    }
}

// Move the player in the current direction and handle food consumption and collisions
void Player::movePlayer(Food* FoodBucket)
{
    objPos playerPos = playerPosList->getHeadElement();    // Get current head position
    newFood = FoodBucket;                                 // Set reference to the food bucket

    int width = mainGameMechsRef->getBoardSizeX();
    int height = mainGameMechsRef->getBoardSizeY();

    // Update position based on current direction
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

    // Check for self-collision
    if(checkSelfCollision(playerPos))
    {
        mainGameMechsRef->setLoseFlag(); 
        return;
    }

    bool foodConsumed = false;   // Flag to track food consumption

    // Check if player has consumed food
    for (int i = 0; i < newFood->getFoodBucketSize(); ++i)
    {
        objPos food = newFood->getFoodAt(i);

        if (playerPos.pos->x == food.pos->x && playerPos.pos->y == food.pos->y)
        {
            foodConsumed = true;

            // Increase score based on food type
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

    // If no food consumed, move the player by inserting a new head and removing the tail
    if (!foodConsumed)
    {
        objPos nextObj(playerPos.pos->x, playerPos.pos->y, '@');
        playerPosList->insertHead(nextObj);  
        playerPosList->removeTail(); 
    }
    

}

// Check for food consumption
bool Player::checkFoodConsumption(const objPos& playerHead)
{
    
    objPos foodPos = newFood->getFoodPos();
    return (playerHead.pos->x == foodPos.pos->x && playerHead.pos->y == foodPos.pos->y);
}

// Increase the player's length by adding a new head segment
void Player::increasePlayerLength()
{
    objPos playerPos = playerPosList->getHeadElement(); 
    objPos nextObj(playerPos.pos->x, playerPos.pos->y, '@');
    playerPosList->insertHead(nextObj); 
}

// Check for self-collision (collision with player's own body)
bool Player::checkSelfCollision(const objPos& playerHead)
{
    for(int i = 1; i < playerPosList->getSize(); i++)
    {
        objPos playerBody = playerPosList->getElement(i);
        if(playerBody.pos->x == playerHead.pos->x && playerBody.pos->y == playerHead.pos->y)
        {
            return true;  // Collision detected
        }
    }
    return false;        // No collision detected
}



