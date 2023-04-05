#pragma once
//
// Created by irchit on 3/29/2023.
//

#ifndef LAB2_4_ITER2_MYLIST_H
#define LAB2_4_ITER2_MYLIST_H

#define MAX_VALUES_LENGHT 10000

#include "medicine.h"

typedef Medicine ElementType;
typedef struct {
    ElementType* values;
    int lenght;
    int capacity;
} MyList;

MyList createMyList();
void deleteMyList(MyList* thisList);
int addToMyList(MyList* thisList, ElementType* newMedicine);
int updateInMyList(MyList* thisList, ElementType* modifiedMedicine, int position);
int deleteFromMyList(MyList* thisList, int uniqueCode);
ElementType* getElementFromMyList(MyList* thisList, int position);
MyList copyOfMyList(MyList* thisList);
int getLenghtOfMyList(MyList* thisList);
void testsMyList();
#endif //LAB2_4_ITER2_MYLIST_H
