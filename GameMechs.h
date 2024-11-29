#ifndef GAMEMECHS_H
#define GAMEMECHS_H

#include <cstdlib>
#include <time.h>
#include "objPos.h"
#include "objPosArrayList.h"

using namespace std;


// Class to manage game mechanics and state
class GameMechs
{
    private:
        char input;
        bool exitFlag;
        bool loseFlag;
        int score;

        int boardSizeX;        // Width of the game board
        int boardSizeY;       // Height of the game board

        objPos food;         // Position of the food object 

    public:
        GameMechs();        // Constructor
        GameMechs(int boardX, int boardY);
        ~GameMechs();      // Destructor
        
        // Getter and setter functions for game state variables
        bool getExitFlagStatus() const; 
        void setExitTrue();
        bool getLoseFlagStatus() const;
        void setLoseFlag();

        char getInput() const;
        void ScanInput();
        void setInput(char this_input);
        void clearInput();

        int getBoardSizeX() const;
        int getBoardSizeY() const;
        
        int getScore() const;
        void incrementScore(int amount);
        

};

#endif