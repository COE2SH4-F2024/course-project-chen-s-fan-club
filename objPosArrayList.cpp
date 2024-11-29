#include "objPosArrayList.h"
#include <iostream>

using namespace std;

// Constructor: initializes the array list with a maximum capacity
objPosArrayList::objPosArrayList()
{
    listSize = 0;                         // Initialize the list size to 0
    arrayCapacity = ARRAY_MAX_CAP;       // Set the maximum capacity
    aList = new objPos[arrayCapacity];  // Allocate memory for the array
}

// Destructor: releases the dynamically allocated memory
objPosArrayList::~objPosArrayList()
{
    delete[] aList;
}

// Copy constructor: creates a deep copy of another objPosArrayList
objPosArrayList::objPosArrayList(const objPosArrayList &list)
{
    arrayCapacity = list.arrayCapacity;       // Copy the capacity
    listSize = list.listSize;                // Copy the list size
    aList = new objPos[arrayCapacity];      // Allocate new memory for the array

    // Copy each element from the source list
    for(int i = 0; i < listSize; i++)
        aList[i] = list.aList[i];
}

// Get the current size of the list
int objPosArrayList::getSize() const
{
    return listSize;
}

// Insert an element at the head (beginning) of the list
void objPosArrayList::insertHead(objPos thisPos)
{
    // Check if the list is full
    if (listSize == arrayCapacity) 
    {
        return;
    }
    
    // Shift elements to the right to make space at the head
    for (int i = listSize; i > 0; i--)
    {
        aList[i] = aList[i - 1];
    }

    aList[0] = thisPos;    // Insert the new element at the head
    listSize++;           // Increment the list size
}

// Insert an element at the tail (end) of the list
void objPosArrayList::insertTail(objPos thisPos)
{
    if(listSize == arrayCapacity)
    { 
        return;
    }
        
    aList[listSize++] = thisPos;     // Add the new element at the end and increment the size
}


// Remove the element at the head (beginning) of the list
void objPosArrayList::removeHead()
{
    // Check if the list is empty
    if (listSize == 0) 
    {
        return;
    }
    
    // Shift elements to the left to fill the gap
    for (int i = 0; i < listSize - 1; i++)
    {
        aList[i] = aList[i + 1];
    }

    listSize--;
}

// Remove the element at the tail (end) of the list
void objPosArrayList::removeTail()
{
    if (listSize == 0) 
    {
        return;
    }

    listSize--;
}

// Get the element at the head of the list
objPos objPosArrayList::getHeadElement() const
{
    // Return a default objPos if the list is empty
    if (listSize == 0){
        return objPos();
    }

    return aList[0];  // Return the first element
}

// Get the element at the tail of the list
objPos objPosArrayList::getTailElement() const
{
    if (listSize == 0){
        return objPos();
    }
    return aList[listSize - 1];   // Return the last element
}

// Get the element at the specified index
objPos objPosArrayList::getElement(int index) const
{
    // Return a default objPos if the index is out of bounds
    if (index < 0 || index >= listSize){
        return objPos();
    }

    return aList[index];   // Return the element at the specified index
}

// Check if the list contains a position with the specified x and y coordinates
bool objPosArrayList::contains(int x, int y) const
{
    // Iterate through the list to find a matching position
    for (int i = 0; i < this->getSize(); ++i)
    {
        objPos element = this->getElement(i);
        if (element.pos->x == x && element.pos->y == y)
        {
            return true;    // Return true if a match is found
        }
    }
    return false;         // Return false if no match is found
}

// Clear the list by removing all elements
void objPosArrayList::clear()
{
    // Remove elements from the tail until the list is empty
    while (this->getSize() > 0)
    {
        this->removeTail(); 
    }
}