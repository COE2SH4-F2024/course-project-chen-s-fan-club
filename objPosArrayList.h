#ifndef OBJPOS_ARRAYLIST_H
#define OBJPOS_ARRAYLIST_H
#define ARRAY_MAX_CAP 50

#include "objPos.h"

// Class representing a dynamic array list of objPos objects
class objPosArrayList
{
    private:
        objPos* aList;             // Pointer to the dynamically allocated array
        int listSize;             // Current number of elements in the list
        int arrayCapacity;       // Maximum capacity of the list

    public:
        objPosArrayList();       // Constructor
        ~objPosArrayList();     // Destructor
        objPosArrayList(const objPosArrayList &list);    // Copy constructor

        int getSize() const;
        void insertHead(objPos thisPos);
        void insertTail(objPos thisPos);
        void removeHead();
        void removeTail();
        
        objPos getHeadElement() const;
        objPos getTailElement() const;
        objPos getElement(int index) const;
        bool contains(int x, int y) const;
        void clear();
};
#endif