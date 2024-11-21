#include "objPosArrayList.h"
#include <iostream>
using namespace std;
// Check lecture contents on general purpose array list construction, 
// and modify it to support objPos array list construction.

objPosArrayList::objPosArrayList()
{
    listSize = 0;  // no data at first
    arrayCapacity = 50;  // 50
    aList = new objPos[arrayCapacity];
}

objPosArrayList::~objPosArrayList()
{
    delete[] aList;
}
objPosArrayList::objPosArrayList(const objPosArrayList &list)
{
    arrayCapacity = list.arrayCapacity;
    listSize = list.listSize;
    aList = new objPos[arrayCapacity];

    for(int i = 0; i < listSize; i++)
        aList[i] = list.aList[i];
}
int objPosArrayList::getSize() const
{
    return listSize;
}

void objPosArrayList::insertHead(objPos thisPos)
{
    if (listSize == arrayCapacity) // Check if array is full
    {
        cout << "Array full..";
        return;
    }
    
    // Shift elements to the right
    for (int i = listSize; i > 0; i--)
    {
        aList[i] = aList[i - 1];
    }

    // Insert at the head
    aList[0] = thisPos;
    listSize++;
}

void objPosArrayList::insertTail(objPos thisPos)
{
    if(listSize == arrayCapacity)
    {
        cout << "array full..";
        return;
    }
        
    aList[listSize++] = thisPos;
}

void objPosArrayList::removeHead()
{
    if (listSize == 0) // Check if list is empty
    {
        cout << "Array is empty.";
        return;
    }
    
    // Shift elements to the left
    for (int i = 0; i < listSize - 1; i++)
    {
        aList[i] = aList[i + 1];
    }

    listSize--;
}

void objPosArrayList::removeTail()
{
    if (listSize == 0) // Check if list is empty
    {
        cout << "Array is empty.";
        return;
    }

    listSize--;
}

objPos objPosArrayList::getHeadElement() const
{
    if (listSize == 0) // Check if list is empty
    {
        throw std::out_of_range("List is empty.");
    }

    return objPos(aList[0]);
}

objPos objPosArrayList::getTailElement() const
{
    if (listSize == 0) // Check if list is empty
    {
        throw std::out_of_range("List is empty.");
    }

    return objPos(aList[listSize - 1]);
}

objPos objPosArrayList::getElement(int index) const
{
    if (index < 0)
    {
        index = 0;
    } 
    if (index >= listSize) 
    {
        index=listSize-1;
    }

    return objPos(aList[index]);
}
