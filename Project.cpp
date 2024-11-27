#include <iostream>
#include "MacUILib.h"
#include "objPos.h"

#include "GameMechs.h"
#include "Player.h"
#include "Food.h"

using namespace std;

#define DELAY_CONST 100000

GameMechs* gameMechs = nullptr; //Pointer to GameMechs Class
Player *myPlayer = nullptr; //Pointer to Player Class
Food *myFood = nullptr; 

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
    myFood = new Food();
    myFood->generateFood(myPlayer->getPlayerPos(),gameMechs->getBoardSizeX(), gameMechs->getBoardSizeY());  

}

void GetInput(void)
{
   gameMechs->ScanInput();
}

void RunLogic(void)
{
    myPlayer->updatePlayerDir();
    objPos playerPos = myPlayer->getPlayerPos()->getHeadElement();
    objPos foodPos = myFood->getFoodPos();

    myPlayer->movePlayer(myFood);

}

void DrawScreen(void)
{
    objPosArrayList* PlayerPos = myPlayer->getPlayerPos();
    objPos food = myFood->getFoodPos();

    int Board_Width = gameMechs->getBoardSizeX();
    int Board_Length = gameMechs->getBoardSizeY();
    MacUILib_clearScreen();    
    for (int y=0;y<Board_Length;y++){
        for(int x=0;x<Board_Width;x++){
           if(x==0 || x==Board_Width-1 || y==0 || y==Board_Length-1)
           {
                MacUILib_printf("%c", '#');  
           }
           else 
           {
                bool isPlayer = false;
                for (int i=0; i<PlayerPos->getSize();i++)
                {
                    if (x == PlayerPos->getElement(i).pos->x && y == PlayerPos->getElement(i).pos->y)
                    {
                        MacUILib_printf("%c",PlayerPos->getElement(i).symbol);
                        isPlayer = true;
                        break;
                    }
                }
                if(!isPlayer) {
                    if(x == food.pos->x && y == food.pos->y) {
                        MacUILib_printf("%c", food.symbol);
                        gameMechs->clearInput();
                    } else {
                    MacUILib_printf("%c", ' ');
                    }
                }
           }       
        }
        MacUILib_printf("%c", '\n');
    }   
    MacUILib_printf("Score: %d\n",gameMechs->getScore());
}


void LoopDelay(void)
{

    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();    

    if(gameMechs->getLoseFlagStatus())
    {
        MacUILib_printf("\nGame Over: Player Hit Themselves \n");
    }
    else if (gameMechs->getExitFlagStatus())
    {
        MacUILib_printf("\nGame Over: Force quit.\n");
    }

    delete gameMechs;
    delete myPlayer;
    delete myFood;
    myFood = nullptr;
    gameMechs = nullptr;
    myPlayer = nullptr;
    MacUILib_uninit();
}