#pragma once
//
// Created by irchit on 3/29/2023.
//
#include "sortMyList.h"

void sortMyList(MyList* myList, compareFunction compare)
{
    int lenghtOfMyList = getLenghtOfMyList(myList);
    for (int i = 0; i < lenghtOfMyList - 1; i++)
        for (int j = i + 1; j < lenghtOfMyList; j++)
        {
            void* medicineI = getElementFromMyList(myList, i);
            void* medicineJ = getElementFromMyList(myList, j);
            if (compare(medicineI, medicineJ) > 0)
            {
                ElementType aux = *(ElementType*)medicineI;
                *(ElementType*)medicineI = *(ElementType*)medicineJ;
                *(ElementType*)medicineJ = aux;
            }
        }
}

int compareByNameAndStockAscending(ElementType* element1, ElementType* element2) {
    int result = strcmp(element1->name, element2->name);
    if (result == 0)
        return element1->stock - element2->stock;
    return result;
}
int compareByNameAndStockDescending(ElementType* element1, ElementType* element2) {
    int result = strcmp(element2->name, element1->name);
    if (result == 0)
        return element2->stock - element1->stock;
    return result;
}

void testSort()
{
    MyList myList = createMyList();
    Medicine medicine1 = createMedicine(1, "Paracetamol", 10, 10);
    Medicine medicine2 = createMedicine(2, "Aspirina", 20, 20);
    Medicine medicine3 = createMedicine(3, "Ibuprofeno", 30, 30);
    Medicine medicine4 = createMedicine(4, "Paracetamol", 40, 40);
    addToMyList(&myList, &medicine1);
    addToMyList(&myList, &medicine2);
    addToMyList(&myList, &medicine3);
    addToMyList(&myList, &medicine4);
    MyList copyMyList = copyOfMyList(&myList);
    sortMyList(&copyMyList, (compareFunction)compareByNameAndStockDescending);
    assert(getElementFromMyList(&copyMyList, 0)->uniqueCode == 4);
    assert(getElementFromMyList(&copyMyList, 1)->uniqueCode == 1);
    assert(getElementFromMyList(&copyMyList, 2)->uniqueCode == 3);
    assert(getElementFromMyList(&copyMyList, 3)->uniqueCode == 2);
    sortMyList(&copyMyList, (compareFunction)compareByNameAndStockAscending);
    assert(getElementFromMyList(&copyMyList, 0)->uniqueCode == 2);
    assert(getElementFromMyList(&copyMyList, 1)->uniqueCode == 3);
    assert(getElementFromMyList(&copyMyList, 2)->uniqueCode == 1);
    assert(getElementFromMyList(&copyMyList, 3)->uniqueCode == 4);
    deleteMyList(&myList);
    deleteMyList(&copyMyList);
}
