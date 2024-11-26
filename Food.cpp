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

void Food::generateFood(objPos blockOff, int boardSizeX, int boardSizeY)
{
    srand(time(NULL)); 
    int foodX = rand() % (boardSizeX - 2) + 1;
    int foodY = rand() % (boardSizeY - 2) + 1;
    while(foodX == blockOff.getObjPos().pos->x && foodY == blockOff.getObjPos().pos->y)
    {
        foodX = rand() % (boardSizeX - 2) + 1;
        foodY = rand() % (boardSizeY - 2) + 1;
    }
    foodPos.setObjPos(foodX,foodY,'*');
}
    
objPos const Food::getFoodPos()
{
    return foodPos.getObjPos();
}