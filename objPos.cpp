#include "objPos.h"

// Constructor: initializes position to (0, 0) with a null character
objPos::objPos()
{
    pos = new Pos;        // Dynamically allocate memory for Pos structure
    pos->x = 0;          // Initialize x-coordinate to 0
    pos->y = 0;         // Initialize y-coordinate to 0
    symbol = 0;        // NULL
}


objPos::objPos(int xPos, int yPos, char sym)
{
    pos = new Pos;
    pos->x = xPos;
    pos->y = yPos;
    symbol = sym;
}

// Destructor: releases dynamically allocated memory for pos
objPos:: ~objPos()
{
    delete pos;
}

// Copy constructor: creates a deep copy of another objPos object
objPos:: objPos(const objPos& other)
{
    pos = new Pos;                    // Allocate memory for the new Pos object
    pos ->x=other.pos->x;            // Copy x-coordinate
    pos ->y=other.pos->y;           // Copy y-coordinate
    symbol = other.symbol;         // Copy symbol
}

// Copy assignment operator: assigns values from another objPos object
objPos& objPos::operator=(const objPos& other)
{
    if (this == &other)       // Check for self-assignment
        return *this;

    
    delete pos;             // Delete the current pos to prevent memory leaks
    pos = new Pos;
    pos->x = other.pos->x;
    pos->y = other.pos->y;
    symbol = other.symbol;

    return *this;
}

// Move constructor: transfers ownership of resources from another objPos object
objPos::objPos(objPos&& other) noexcept
    : pos(other.pos), symbol(other.symbol)      // Transfer ownership of resources
{
    other.pos = nullptr;                       // Nullify the source object's pos pointer to avoid double deletion
}

// Move assignment operator: transfers ownership of resources from another objPos object
objPos& objPos::operator=(objPos&& other) noexcept
{
    if (this == &other) 
        return *this;

    delete pos; 
    pos = other.pos;
    symbol = other.symbol;
    other.pos = nullptr; 
    return *this;
}

// Set position and symbol using another objPos object
void objPos::setObjPos(objPos o)
{
    pos->x = o.pos->x;
    pos->y = o.pos->y;
    symbol = o.symbol;
}

// Set position and symbol using individual values
void objPos::setObjPos(int xPos, int yPos, char sym)
{
    pos->x = xPos;         // Set x-coordinate
    pos->y = yPos;        // Set y-coordinate
    symbol = sym;        // Set symbol
}

// Get a copy of the current position and symbol
objPos objPos::getObjPos() const
{
    objPos returnPos;            // Create a new objPos object
    returnPos.pos->x = pos->x;
    returnPos.pos->y = pos->y;
    returnPos.symbol = symbol;
    
    return returnPos;
}

// Get the symbol associated with the position
char objPos::getSymbol() const
{
    return symbol;
}

// Check if the current position is equal to a reference position
bool objPos::isPosEqual(const objPos* refPos) const
{
    return (refPos->pos->x == pos->x && refPos->pos->y == pos->y);
}

// Return the symbol if the current position matches a reference position
char objPos::getSymbolIfPosEqual(const objPos* refPos) const
{
    if(isPosEqual(refPos))
        return symbol;
    else
        return 0;
}
