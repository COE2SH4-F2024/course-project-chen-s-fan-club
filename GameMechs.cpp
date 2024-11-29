#include "GameMechs.h"
#include "MacUILib.h"
#include "objPos.h"
#include <iostream>

using namespace std;

// Constructor: initializes the game board with default size and initial values
GameMechs::GameMechs()
{
    boardSizeX = 30;          // Default board width
    boardSizeY = 15;         // Default board height
    input = '\0';           // Initialize input as null character
    exitFlag = false;      // Exit Flag (false as player has not exited yet) 
    loseFlag = false;     // Lose Flag (false as player has not lost yet) 
    score = 0;           // Initial score is zero
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

// Destructor: no dynamic memory allocation, so nothing to clean up
GameMechs::~GameMechs(){}

// Getter for exitFlag status
bool GameMechs::getExitFlagStatus() const
{
    return exitFlag;
}

// Getter for loseFlag status
bool GameMechs::getLoseFlagStatus() const
{
    return loseFlag;
}
    

// Getter for user input
char GameMechs::getInput() const
{
    return input;
}

// Getter for game score
int GameMechs::getScore() const
{
    return score;
}

// Increment score by a specified amount
void GameMechs::incrementScore(int amount)
{
    score+=amount;
}

// Getter for board width
int GameMechs::getBoardSizeX() const
{
    return boardSizeX;
}

// Getter for board height
int GameMechs::getBoardSizeY() const
{
    return boardSizeY;
}

// Setter: set the exitFlag to true to signal game termination
void GameMechs::setExitTrue()
{
    exitFlag = true;
}

// Setter: set the loseFlag to true when the player loses
void GameMechs::setLoseFlag()
{
    loseFlag = true;
}

// Setter: update the latest user input
void GameMechs::setInput(char this_input)
{
    input = this_input;
}

// Clear the stored input
void GameMechs::clearInput()
{
    input = '\0';            // Reset input to null character
}

// Scan and store user input from the console
void GameMechs::ScanInput() {
    if(MacUILib_hasChar()) {
        input = MacUILib_getChar();     // Read character input from the library
    }
    
    if (input == 27) {                // ASCII value 27 is the 'Escape' key
        setExitTrue();
    }
}

