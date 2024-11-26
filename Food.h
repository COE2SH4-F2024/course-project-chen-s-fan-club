#ifndef FOOD_H
#define FOOD_H
#include <cstdlib>
#include <time.h>
#include "objPos.h"
#include "objPosArrayList.h"
#include "GameMechs.h"
using namespace std;
class Food
{
    private:
        objPos foodPos;
    
    public:
        Food();
        ~Food(); 
        
        void generateFood(objPosArrayList* blockOff, int boardSizeX, int boardSizeY);
        objPos const getFoodPos();
};
#endif