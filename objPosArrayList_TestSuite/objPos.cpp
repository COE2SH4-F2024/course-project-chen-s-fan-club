#include "objPos.h"

objPos::objPos()
{
    pos = new Pos;
    pos->x = 0;
    pos->y = 0;
    symbol = 0; //NULL
}

//Contructor
objPos::objPos(int xPos, int yPos, char sym)
{
    pos = new Pos;
    pos->x = xPos;
    pos->y = yPos;
    symbol = sym;
}

//Destructor
objPos:: ~objPos()
{
    delete pos;
}

//Copy Constructor
objPos:: objPos(const objPos& other)
{
    pos = new Pos;
    pos ->x=other.pos->x;
    pos ->y=other.pos->y;
    symbol = other.symbol;
}

// Copy Assignment Operator
objPos& objPos::operator=(const objPos& other)
{
    if (this == &other) // Self-assignment check
        return *this;

    
    delete pos; // Free existing resource
    pos = new Pos;
    pos->x = other.pos->x;
    pos->y = other.pos->y;
    symbol = other.symbol;

    return *this;
}

// Move Constructor
objPos::objPos(objPos&& other) noexcept
    : pos(other.pos), symbol(other.symbol)
{
    other.pos = nullptr; // Leave the source object in a safe state
}

// Move Assignment Operator
objPos& objPos::operator=(objPos&& other) noexcept
{
    if (this == &other) // Self-assignment check
        return *this;

    delete pos; // Free existing resource
    pos = other.pos;
    symbol = other.symbol;
    other.pos = nullptr; 
    return *this;
}

void objPos::setObjPos(objPos o)
{
    pos->x = o.pos->x;
    pos->y = o.pos->y;
    symbol = o.symbol;
}

void objPos::setObjPos(int xPos, int yPos, char sym)
{
    pos->x = xPos;
    pos->y = yPos;
    symbol = sym;
}

objPos objPos::getObjPos() const
{
    objPos returnPos;
    returnPos.pos->x = pos->x;
    returnPos.pos->y = pos->y;
    returnPos.symbol = symbol;
    
    return returnPos;
}

char objPos::getSymbol() const
{
    return symbol;
}

bool objPos::isPosEqual(const objPos* refPos) const
{
    return (refPos->pos->x == pos->x && refPos->pos->y == pos->y);
}

char objPos::getSymbolIfPosEqual(const objPos* refPos) const
{
    if(isPosEqual(refPos))
        return symbol;
    else
        return 0;
}
