//
// Created by irchit on 3/28/2023.
//

#ifndef LAB2_4_ITER1_MYLIST_H
#define LAB2_4_ITER1_MYLIST_H

#define MAX_VALUES_LENGHT 1000

#include "medicine.h"

typedef Medicine ElementType;
typedef struct{
    ElementType values[MAX_VALUES_LENGHT];
    int lenght;
} MyList;

MyList createMyList();
void deleteMyList(MyList* thisList);
int addToMyList(MyList* thisList, ElementType* newMedicine);
int updateInMyList(MyList *thisList, ElementType *modifiedMedicine, int position);
int deleteFromMyList(MyList* thisList, int uniqueCode);
ElementType getElementFromMyList(MyList* thisList, int position);
MyList copyOfMyList(MyList* thisList);
int getLenghtOfMyList(MyList* thisList);
void testsMyList();

#endif //LAB2_4_ITER1_MYLIST_H
