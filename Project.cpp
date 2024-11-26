#include <iostream>
#include "MacUILib.h"
#include "objPos.h"

#include "GameMechs.h"
#include "Player.h"
using namespace std;

#define DELAY_CONST 100000

GameMechs* gameMechs = nullptr; //Pointer to GameMechs Class
Player *myPlayer = nullptr; //Pointer to Player Class


void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



int main(void)
{

    Initialize();

    while(!gameMechs->getExitFlagStatus() && !gameMechs->getLoseFlagStatus())  
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();

}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();

    gameMechs = new GameMechs(30, 15);
    myPlayer = new Player(gameMechs);

    gameMechs->generateFood(myPlayer->getPlayerPos());
}

void GetInput(void)
{
   gameMechs->ScanInput();
}

void RunLogic(void)
{
    myPlayer->updatePlayerDir();
    myPlayer->movePlayer();
    
    objPos foodPos = gameMechs->getFoodPos();

    if (myPlayer->getPlayerPos().isPosEqual(&foodPos))
    {
        gameMechs->incrementScore();
        gameMechs->generateFood(myPlayer->getPlayerPos());  
    }
        
}

void DrawScreen(void)
{
    objPos PlayerPos = myPlayer->getPlayerPos();
    objPos food = gameMechs->getFoodPos();

    int Board_Width = gameMechs->getBoardSizeX();
    int Board_Length = gameMechs->getBoardSizeY();
    MacUILib_clearScreen();    
    for (int y=0;y<Board_Length;y++){
        for(int x=0;x<Board_Width;x++){
           if(x==0 || x==Board_Width-1 || y==0 || y==Board_Length-1)
           {
            MacUILib_printf("%c", '#');  
           }
           else if (y == PlayerPos.pos->y && x== PlayerPos.pos->x)
           {
            MacUILib_printf("%c",PlayerPos.symbol);
           }
           else if (y == food.pos->y && x == food.pos->x)
           {
            MacUILib_printf("%c", food.getSymbol());
           }
           else
           {
            MacUILib_printf("%c", ' ');
           }
        }
        MacUILib_printf("%c", '\n');
    }

}

void LoopDelay(void)
{
    
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();    
    delete gameMechs;
    delete myPlayer;
    gameMechs = nullptr;
    myPlayer = nullptr;
    MacUILib_uninit();
}
