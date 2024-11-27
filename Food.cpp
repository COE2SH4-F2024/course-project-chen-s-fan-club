#include "Food.h"
#include "MacUILib.h"
#include "GameMechs.h"

Food::Food()
{
    foodPos.setObjPos(-10,-10,'*');
}
Food::~Food()
{
}

void Food::generateFood(objPosArrayList* blockOff, int boardSizeX, int boardSizeY)
{
    srand(time(NULL)); 
    int foodX,foodY; 
    bool validPosition = false;
    while (!validPosition)
    {
        foodX = rand() % (boardSizeX - 2) + 1; 
        foodY = rand() % (boardSizeY - 2) + 1;
        validPosition = true; 

        for (int i = 0; i < blockOff->getSize(); ++i)
        {
            objPos currentSegment = blockOff->getElement(i);
            if (foodX == currentSegment.getObjPos().pos->x && foodY == currentSegment.getObjPos().pos->y)
            {
                validPosition = false; 
                break;
            }
        }
    }
    foodPos.setObjPos(foodX,foodY,'*');
}
    
objPos const Food::getFoodPos()
{
    return foodPos.getObjPos();
}