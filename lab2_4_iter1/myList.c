//
// Created by irchit on 3/28/2023.
//
#include "myList.h"

MyList createMyList(){
    MyList newList;
    newList.lenght = 0;
    return newList;
}

void deleteMyList(MyList* thisList)
{
    thisList->lenght = 0;
}

int addToMyList(MyList* thisList, ElementType* newMedicine)
{
    if (thisList->lenght >= MAX_VALUES_LENGHT)
        return 5;
    thisList->values[thisList->lenght] = *newMedicine;
    thisList->lenght ++;
    return 0;
}

int updateInMyList(MyList *thisList, ElementType *modifiedMedicine, int position)
{
    if (thisList->lenght <= position)
        return 6;
    thisList->values[position] = *modifiedMedicine;
    return 0;
}

int deleteFromMyList(MyList* thisList, int uniqueCode)
{
    int elementTypeFound = -1;
    for (int i = 0; i < thisList->lenght; i ++)
        if (thisList->values[i].uniqueCode == uniqueCode)
        {
            elementTypeFound = i;
            break;
        }
    if (elementTypeFound == -1)
        return 6;
    for (int i = elementTypeFound; i < thisList->lenght - 1; i ++)
        thisList->values[i] = thisList->values[i+1];
    thisList->lenght --;
    return 0;
}

ElementType getElementFromMyList(MyList* thisList, int position)
{
    if (position >= thisList->lenght)
        return createMedicine(-1, "", 0, 0);
    return thisList->values[position];
}

MyList copyOfMyList(MyList* thisList)
{
    MyList newList = createMyList();
    for (int i = 0; i < thisList->lenght; i ++) {
        ElementType currentElement = copyMedicine(&thisList->values[i]);
        addToMyList(&newList, &currentElement);
    }
    return newList;
}

int getLenghtOfMyList(MyList* thisList)
{
    return thisList->lenght;
}

void testsMyList(){

    //Create MyList
    MyList myList = createMyList();
    assert(myList.lenght == 0);

    //Add Element
    myList.lenght = MAX_VALUES_LENGHT;
    Medicine medicine = createMedicine(1, "Insulin", 300, 10000);
    Medicine medicine1 = createMedicine(2, "NoSPA", 100, 100000);
    assert(addToMyList(&myList, &medicine) == 5);
    myList.lenght = 0;
    assert(addToMyList(&myList, &medicine) == 0);
    assert(addToMyList(&myList, &medicine1) == 0);

    //Get Lenght
    assert(getLenghtOfMyList(&myList) == 2);

    //Update Element
    Medicine medicine_does_not_exist = createMedicine(13, "Insulin", 130, 10000);
    assert(updateInMyList(&myList, &medicine_does_not_exist, 6) == 6);
    Medicine medicine_same_unique_code = createMedicine(1, "Aspirin", 100, 10000);
    assert(updateInMyList(&myList, &medicine_same_unique_code, 0) == 0);

    //Get Element
    assert(getElementFromMyList(&myList, 2).uniqueCode == -1);
    assert(getElementFromMyList(&myList, 0).uniqueCode == 1);

    //Copy List
    MyList copyList = copyOfMyList(&myList);
    assert(copyList.lenght == myList.lenght);
    for (int i = 0; i < copyList.lenght; i ++)
    {
        assert(copyList.values[i].uniqueCode == myList.values[i].uniqueCode);
        assert(copyList.values[i].concentration == myList.values[i].concentration);
        assert(copyList.values[i].stock == myList.values[i].stock);
        assert(strcmp(copyList.values[i].name, myList.values[i].name) == 0);
    }

    //Delete Element
    assert(deleteFromMyList(&myList, 1) == 0);
    assert(deleteFromMyList(&myList, 111) == 6);
    assert(getLenghtOfMyList(&myList) == 1);

    //Delete MyList
    deleteMyList(&myList);
    assert(myList.lenght == 0);
}