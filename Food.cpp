#include "Food.h"
#include "MacUILib.h"
#include "GameMechs.h"

// Constructor: initializes food position and creates an empty food bucket
Food::Food()
{
    // Set initial food position to an invalid location (-10, -10) with symbol '*'
    foodPos.setObjPos(-10,-10,'*');

    // Allocate memory for the dynamic food bucket (a list of food positions)
    foodBucket = new objPosArrayList();
}

// Destructor: releases dynamically allocated memory for the food bucket
Food::~Food()
{
    delete foodBucket;
}

// Generates food items at random positions on the board
void Food::generateFood(objPosArrayList* blockOff, int boardSizeX, int boardSizeY, int foodCount)
{
    srand(time(NULL));
    foodBucket->clear();   // Clear the current food list to generate new food items

    // Generate special food item ('$') at a random position not occupied by blocked areas
    int specialFoodX, specialFoodY;
    do
    {
        specialFoodX = rand() % (boardSizeX - 2) + 1;    // Random x-coordinate within board bounds
        specialFoodY = rand() % (boardSizeY - 2) + 1;   // Random y-coordinate within board bounds
    } while (blockOff->contains(specialFoodX, specialFoodY));   // Ensure the position is not blocked

    objPos specialFood(specialFoodX, specialFoodY, '$');    // Create special food object   
    foodBucket->insertHead(specialFood);                   // Add special food to the bucket

    // Generate remaining normal food items ('*')
    for (int i = 1; i < foodCount; ++i)
    {
        int foodX, foodY;
        do
        {
            foodX = rand() % (boardSizeX - 2) + 1;
            foodY = rand() % (boardSizeY - 2) + 1;
        } while (blockOff->contains(foodX, foodY) || (foodX == specialFoodX && foodY == specialFoodY)); // Avoid collisions with blocked areas and special food

        objPos normalFood(foodX, foodY, '*');   // Create normal food object
        foodBucket->insertHead(normalFood);    // Add normal food to the bucket
    }
}
    
// Returns the current position of the special food
objPos const Food::getFoodPos()
{
    return foodPos.getObjPos();
}

// Returns the food object at the specified index in the food bucket
objPos Food::getFoodAt(int index) const
{
    return foodBucket->getElement(index);
}

// Returns the number of food items in the bucket
int Food::getFoodBucketSize() const
{
    return foodBucket->getSize();
}