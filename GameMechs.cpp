#include "GameMechs.h"
#include "MacUILib.h"
#include "objPos.h"
#include <iostream>

using namespace std;

GameMechs::GameMechs()
{
    boardSizeX = 30;
    boardSizeY = 15;
    input = '\0';
    exitFlag = false;
    loseFlag = false;
    score = 0;
}

GameMechs::GameMechs(int boardX, int boardY)
{
    boardSizeX = boardX;
    boardSizeY = boardY;
    input = '\0';
    exitFlag = false;
    loseFlag = false;
    score = 0;

}

// do you need a destructor?
GameMechs::~GameMechs()
{
    //no dynamic memory allocation in constructor
}

bool GameMechs::getExitFlagStatus() const
{
    return exitFlag;
}

bool GameMechs::getLoseFlagStatus() const
{
    return loseFlag;
}
    

char GameMechs::getInput() const
{
    return input;
}

int GameMechs::getScore() const
{
    return score;
}

void GameMechs::incrementScore()
{
    score++;
}

int GameMechs::getBoardSizeX() const
{
    return boardSizeX;
}

int GameMechs::getBoardSizeY() const
{
    return boardSizeY;
}


void GameMechs::setExitTrue()
{
    exitFlag = true;
}

void GameMechs::setLoseFlag()
{
    loseFlag = true;

}

void GameMechs::setInput(char this_input)
{
    input = this_input;
}

void GameMechs::clearInput()
{
    input = '\0';
}

void GameMechs::ScanInput() {
    if(MacUILib_hasChar()) {
        input = MacUILib_getChar();
    }
    
    if (input == 27) {
        setExitTrue();
    }
}

void GameMechs::generateFood(objPos blockOff)
{
    static bool seeded = false;
    if (!seeded)
    {
        srand(time(0)); 
        seeded = true;
    }

    int foodX = rand() % (boardSizeX - 2) + 1;
    int foodY = rand() % (boardSizeY - 2) + 1;

    while (foodX == blockOff.getObjPos().pos->x && foodY == blockOff.getObjPos().pos->y)
    {
        foodX = rand() % (boardSizeX - 2) + 1;
        foodY = rand() % (boardSizeY - 2) + 1;
    }

    food.setObjPos(foodX, foodY, '@');
}

objPos GameMechs::getFoodPos() const{
    return food;
}
// More methods should be added here
