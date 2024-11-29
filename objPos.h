#ifndef OBJPOS_H
#define OBJPOS_H


// Not really a C++ thing
typedef struct 
{
    int x;
    int y;
} Pos;

// Class to represent an object with a position and symbol
class objPos
{
    public:
        Pos* pos;        
        char symbol;

        objPos();           // Constructor
        objPos(int xPos, int yPos, char sym);
        
        ~objPos();         // Destructor
        objPos(const objPos& other);      // Copy constructor
        objPos& operator=(const objPos& other);      // Copy assignment operator
        objPos(objPos&& other) noexcept; // Move constructor
        objPos& operator=(objPos&& other) noexcept; // Move assignment operator

        void setObjPos(objPos o);        
        void setObjPos(int xPos, int yPos, char sym);  

        objPos getObjPos() const;
        char getSymbol() const;
        char getSymbolIfPosEqual(const objPos* refPos) const;
        
        bool isPosEqual(const objPos* refPos) const;
};
#endif