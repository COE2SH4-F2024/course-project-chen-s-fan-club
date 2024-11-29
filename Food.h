#ifndef FOOD_H
#define FOOD_H
#include <cstdlib>
#include <time.h>
#include "objPos.h"
#include "objPosArrayList.h"
#include "GameMechs.h"

using namespace std;

// Class to manage food generation and tracking in the game
class Food
{
    private:
        objPos foodPos;
        objPosArrayList* foodBucket;
    
    public:
        Food();          // Constructor
        ~Food();        // Destructor
        
        void generateFood(objPosArrayList* blockOff, int boardSizeX, int boardSizeY, int foodCount);
        objPos const getFoodPos();
        objPos getFoodAt(int index) const;
        int getFoodBucketSize() const;
};
#endif