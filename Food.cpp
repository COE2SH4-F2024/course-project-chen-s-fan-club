#include "Food.h"
#include "MacUILib.h"
#include "GameMechs.h"

Food::Food()
{
    foodPos.setObjPos(-10,-10,'*');
    foodBucket = new objPosArrayList();
}
Food::~Food()
{
    delete foodBucket;
}

void Food::generateFood(objPosArrayList* blockOff, int boardSizeX, int boardSizeY, int foodCount)
{
    srand(time(NULL));
    foodBucket->clear();

   
    int specialFoodX, specialFoodY;
    do
    {
        specialFoodX = rand() % (boardSizeX - 2) + 1;
        specialFoodY = rand() % (boardSizeY - 2) + 1;
    } while (blockOff->contains(specialFoodX, specialFoodY)); 

    objPos specialFood(specialFoodX, specialFoodY, '$');     
    foodBucket->insertHead(specialFood);


    for (int i = 1; i < foodCount; ++i)
    {
        int foodX, foodY;
        do
        {
            foodX = rand() % (boardSizeX - 2) + 1;
            foodY = rand() % (boardSizeY - 2) + 1;
        } while (blockOff->contains(foodX, foodY) || (foodX == specialFoodX && foodY == specialFoodY));

        objPos normalFood(foodX, foodY, '*');
        foodBucket->insertHead(normalFood);
    }
}
    
objPos const Food::getFoodPos()
{
    return foodPos.getObjPos();
}
objPos Food::getFoodAt(int index) const
{
    return foodBucket->getElement(index);
}
int Food::getFoodBucketSize() const
{
    return foodBucket->getSize();
}