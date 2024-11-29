#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"
#include "Food.h"

using namespace std;
#define DELAY_CONST 100000


GameMechs* gameMechs = nullptr;     //Pointer to GameMechs Class
Player *myPlayer = nullptr;        //Pointer to Player Class
Food *myFood = nullptr;           //Pointer to Food Class

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

    gameMechs = new GameMechs(30, 15);     // Create game mechanics with a board size of 30x15
    myPlayer = new Player(gameMechs);     // Create player and place at initial position

   // Create food and generate initial food items on the board 
    myFood = new Food();
    myFood->generateFood(myPlayer->getPlayerPos(),gameMechs->getBoardSizeX(), gameMechs->getBoardSizeY(),5);  

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

    int Board_Width = gameMechs->getBoardSizeX();
    int Board_Length = gameMechs->getBoardSizeY();
    MacUILib_clearScreen();  

    // Loop through each row and column of the board  
    for (int y=0;y<Board_Length;y++){
        for(int x=0;x<Board_Width;x++){

           // Draw border around the board
           if(x==0 || x==Board_Width-1 || y==0 || y==Board_Length-1)
           {
                MacUILib_printf("%c", '#');  
           }
           else 
           {
                bool isPlayer = false;

                // Check if the current position is part of the player
                for (int i=0; i<PlayerPos->getSize();i++)
                {
                    if (x == PlayerPos->getElement(i).pos->x && y == PlayerPos->getElement(i).pos->y)
                    {
                        MacUILib_printf("%c",PlayerPos->getElement(i).symbol);
                        isPlayer = true;
                        break;
                    }
                }

                // If not a player segment, check for food
                if(!isPlayer) {
                    bool isFood = false;
                    for (int i = 0; i < myFood->getFoodBucketSize(); i++)
                    {
                        objPos food = myFood->getFoodAt(i);
                        if (x == food.pos->x && y == food.pos->y)
                        {
                            MacUILib_printf("%c", food.symbol);
                            isFood = true;
                            break;
                        }
                    }

                    // If no player or food, print empty space
                    if (!isFood)
                    {
                        MacUILib_printf(" "); // Empty space
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
    
    MacUILib_printf("Final Score:%d\n",gameMechs->getScore());

    // Free dynamically allocated memory
    delete gameMechs;
    delete myPlayer;
    delete myFood;

    // Reset pointers to avoid dangling references
    myFood = nullptr;
    gameMechs = nullptr;
    myPlayer = nullptr;
    
    MacUILib_uninit();
}