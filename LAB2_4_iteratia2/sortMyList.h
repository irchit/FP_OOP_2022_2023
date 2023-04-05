#pragma once
//
// Created by irchit on 3/29/2023.
//

#ifndef LAB2_4_ITER2_SORTMYLIST_H
#define LAB2_4_ITER2_SORTMYLIST_H

#include "myList.h"
#include <stdio.h>

typedef int(*compareFunction)(void* object1, void* object2);

void sortMyList(MyList* myList, compareFunction compare);
void testSort();
int compareByNameAndStockAscending(ElementType* element1, ElementType* element2);
int compareByNameAndStockDescending(ElementType* element1, ElementType* element2);

#endif //LAB2_4_ITER2_SORTMYLIST_H
