#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
using namespace std;

#define DELAY_CONST 100000

char input;

GameMechs* gameMechs = nullptr; //Pointer to GameMechs Class

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
}

void GetInput(void)
{
   if(MacUILib_hasChar())
    {
        gameMechs->setInput(MacUILib_getChar());
    }
}

void RunLogic(void)
{
    input =gameMechs->getInput();
    if(input != 0)  // if not null character
    {
        switch(input)
        {                      
            case 'a':
                
                break;
            case 'd':
                
                break;
            case 'w':

                break;
            case 's':

                break;
            case 27:  // exit
                gameMechs->setExitTrue();
                break;
            default: 
                break;
        }     
    }
    gameMechs->clearInput(); //clears input
    
}

void DrawScreen(void)
{
    int Board_Width = gameMechs->getBoardSizeX();
    int Board_Length = gameMechs->getBoardSizeY();
    MacUILib_clearScreen();    
    for (int y=0;y<Board_Length;y++){
        for(int x=0;x<Board_Width;x++){
           objPos cell(x,y,' ');
           if(x==0 || x==Board_Width-1 || y==0 || y==Board_Length-1){
                cell.setObjPos(x,y,'#');
           }
           cout<< cell.getSymbol();
        }
        cout<<"\n";
    }
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();    
    MacUILib_uninit();
    delete gameMechs;
    gameMechs = nullptr;
}
