//
// Created by irchit on 3/28/2023.
//

#include "sortMyList.h"

void sortMyList(MyList* myList, int reversed) {
    int lenghtOfMyList = getLenghtOfMyList(myList);
    for (int i = 0; i < lenghtOfMyList - 1; i++) {
        for (int j = i + 1; j < lenghtOfMyList; j++) {
            int needsSwapping = 0;
            ElementType ElementI = getElementFromMyList(myList, i);
            ElementType ElementJ = getElementFromMyList(myList, j);
            if (strcmp(ElementI.name, ElementJ.name) == 0)
                if ((ElementI.stock > ElementJ.stock) == !reversed)
                    needsSwapping = 1;
            if ((strcmp(ElementI.name, ElementJ.name) > 0) == !reversed)
                needsSwapping = 1;
            if (needsSwapping) {
                ElementType aux = ElementI;
                ElementI = ElementJ;
                ElementJ = aux;
                updateInMyList(myList, &ElementI, i);
                updateInMyList(myList, &ElementJ, j);
            }
        }
    }
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
    sortMyList(&copyMyList, 1);
    assert(getElementFromMyList(&copyMyList, 0).uniqueCode == 4);
    assert(getElementFromMyList(&copyMyList, 1).uniqueCode == 1);
    assert(getElementFromMyList(&copyMyList, 2).uniqueCode == 3);
    assert(getElementFromMyList(&copyMyList, 3).uniqueCode == 2);
    sortMyList(&copyMyList, 0);
    assert(getElementFromMyList(&copyMyList, 0).uniqueCode == 2);
    assert(getElementFromMyList(&copyMyList, 1).uniqueCode == 3);
    assert(getElementFromMyList(&copyMyList, 2).uniqueCode == 1);
    assert(getElementFromMyList(&copyMyList, 3).uniqueCode == 4);
}