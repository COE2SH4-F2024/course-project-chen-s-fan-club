#include <iostream>
#include "MacUILib.h"
#include "objPos.h"

using namespace std;

#define DELAY_CONST 100000
#define Board_Length 20
#define Board_Width 10

char grid[Board_Width][Board_Length];
char input;
bool exitFlag;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



int main(void)
{

    Initialize();

    while(exitFlag == false)  
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

    exitFlag = false;
    objPos border;
    for (int x=0;x<Board_Width;x++){
        for(int y=0;y<Board_Length;y++){
            border = objPos(x,y,' ');
            if(x==0 || x==Board_Width-1 || y==0 || y==Board_Length-1){
                border.setObjPos(x,y,'#');
            }
            grid[x][y]= border.getSymbol();
        }
    }
}

void GetInput(void)
{
   if(MacUILib_hasChar())
    {
        input = MacUILib_getChar();
    }
}

void RunLogic(void)
{
    if(input != 0)  // if not null character
    {
        switch(input)
        {                      
            case 27:  // exit
                exitFlag = 1;
                break;
        }
    }
}

void DrawScreen(void)
{
    MacUILib_clearScreen();    
    for (int x=0;x<Board_Width;x++){
        for(int y=0;y<Board_Length;y++){
           cout<<grid[x][y];
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
}
