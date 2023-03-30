//
// Created by irchit on 3/29/2023.
//
#include "service.h"

int isNumber(const char* string);

ServiceMedicine createServiceMedicine() {
    ServiceMedicine newServiceMedicine;
    newServiceMedicine.thisList = createMyList();
    return newServiceMedicine;
}

void deleteServiceMedicine(ServiceMedicine* thisServiceMedicine) {
    deleteMyList(&thisServiceMedicine->thisList);
}

int addElementToServiceMedicine(ServiceMedicine* thisServiceMedicine, int uniqueCode, char* name, float concentration, int stock) {
    ElementType medicine = createMedicine(uniqueCode, name, concentration, stock);
    int errorCode = validateMedicine(&medicine);
    if (errorCode != 0)
    {
        deleteMedicine(&medicine);
        return errorCode;
    }
    errorCode = addToMyList(&thisServiceMedicine->thisList, &medicine);
    return errorCode;
}

int updateElementInServiceMedicine(ServiceMedicine* thisServiceMedicine, int uniqueCode, char* name, float concentration, int stock) {
    ElementType medicine = createMedicine(uniqueCode, name, concentration, stock);
    MyList copyList = copyOfMyList(&thisServiceMedicine->thisList);
    for (int i = 0; i < copyList.lenght; i++)
        if (strcmp(copyList.values[i].name, name) == 0)
        {
            int errorCode = validateMedicine(&medicine);
            if (errorCode != 0)
            {
                deleteMedicine(&medicine);
                deleteMyList(&copyList);
                return errorCode;
            }
            errorCode = updateInMyList(&thisServiceMedicine->thisList, &medicine, i);
            deleteMyList(&copyList);
            return errorCode;
        }
    deleteMedicine(&medicine);
    deleteMyList(&copyList);
    return 6;
}

int deleteElementFromServiceMedicine(ServiceMedicine* thisServiceMedicine, int uniqueCode) {
    int errorCode = deleteFromMyList(&thisServiceMedicine->thisList, uniqueCode);
    return errorCode;
}

MyList sortElementsInServiceMedicineByDirection(ServiceMedicine* thisServiceMedicine, int direction) {
    MyList copyThisList = copyOfMyList(&thisServiceMedicine->thisList);
    if (direction == 0)
        sortMyList(&copyThisList, (compareFunction)compareByNameAndStockAscending);
    else
        sortMyList(&copyThisList, (compareFunction)compareByNameAndStockDescending);
    return copyThisList;
}

MyList filterByCriteriaInServiceMedicine(ServiceMedicine* thisServiceMedicine, char* criteria)
{
    MyList copyThisList = copyOfMyList(&thisServiceMedicine->thisList);
    int criteriaByStock = isNumber(criteria);
    for (int i = copyThisList.lenght - 1; i >= 0; i--) {
        if (criteriaByStock == 1)
        {
            if (copyThisList.values[i].stock > strtol(criteria, NULL, 10))
            {
                deleteFromMyList(&copyThisList, copyThisList.values[i].uniqueCode);
            }
        }
        else
        {
            if (getElementFromMyList(&copyThisList, i)->name[0] != criteria[0])
            {
                deleteFromMyList(&copyThisList, copyThisList.values[i].uniqueCode);
            }
        }
    }
    return copyThisList;
}

int isNumber(const char* string)
{
    int i = 0;
    while (string[i] != '\0') {
        if (string[i] < '0' || string[i] > '9')
            return 0;
        i++;
    }
    return 1;
}

void testsServiceMedicine()
{
    ServiceMedicine thisServiceMedicine = createServiceMedicine();
    assert(thisServiceMedicine.thisList.lenght == 0);

    //Add
    assert(addElementToServiceMedicine(&thisServiceMedicine, 1, "Paracetamol", 1.0, 10) == 0);
    assert(addElementToServiceMedicine(&thisServiceMedicine, -1, "Paracetamol", 1.0, 10) == 1);
    assert(addElementToServiceMedicine(&thisServiceMedicine, 1, "", 1.0, 10) == 2);
    assert(addElementToServiceMedicine(&thisServiceMedicine, 1, "Paracetamol", 0, 10) == 3);
    assert(addElementToServiceMedicine(&thisServiceMedicine, 1, "Paracetamol", 1.0, -10) == 4);

    //Update
    assert(updateElementInServiceMedicine(&thisServiceMedicine, 1, "Paracetamol", 1.5, 10) == 0);
    assert(updateElementInServiceMedicine(&thisServiceMedicine, 2, "Insulin", 1.0, 10) == 6);
    assert(updateElementInServiceMedicine(&thisServiceMedicine, -1, "Paracetamol", 0, 10) == 1);
    assert(updateElementInServiceMedicine(&thisServiceMedicine, 1, "", 1.0, -10) == 6);
    assert(updateElementInServiceMedicine(&thisServiceMedicine, 1, "Paracetamol", -1.0, 10) == 3);
    assert(updateElementInServiceMedicine(&thisServiceMedicine, 1, "Paracetamol", 1.0, -10) == 4);

    addElementToServiceMedicine(&thisServiceMedicine, 2, "Insulin", 100, 10);
    assert(updateElementInServiceMedicine(&thisServiceMedicine, 2, "Insulin", 1.0, 10) == 0);
    addElementToServiceMedicine(&thisServiceMedicine, 3, "InsulinFast", 10, 110);

    //Sort
    MyList sortedList = sortElementsInServiceMedicineByDirection(&thisServiceMedicine, 0);
    assert(sortedList.lenght == 3);
    assert(sortedList.values[0].uniqueCode == 2);
    assert(sortedList.values[1].uniqueCode == 3);
    assert(sortedList.values[2].uniqueCode == 1);
    deleteMyList(&sortedList);
    sortedList = sortElementsInServiceMedicineByDirection(&thisServiceMedicine, 1);
    assert(sortedList.lenght == 3);
    assert(sortedList.values[0].uniqueCode == 1);
    assert(sortedList.values[1].uniqueCode == 3);
    assert(sortedList.values[2].uniqueCode == 2);
    deleteMyList(&sortedList);

    //Filter
    MyList filteredList = filterByCriteriaInServiceMedicine(&thisServiceMedicine, "50");
    assert(filteredList.lenght == 2);
    deleteMyList(&filteredList);
    filteredList = filterByCriteriaInServiceMedicine(&thisServiceMedicine, "I");
    assert(filteredList.lenght == 2);
    deleteMyList(&filteredList);

    //Is number
    assert(isNumber("123\n") == 0);
    assert(isNumber("123m") == 0);
    assert(isNumber("123") == 1);

    //Delete Element
    assert(deleteElementFromServiceMedicine(&thisServiceMedicine, 1) == 0);
    assert(deleteElementFromServiceMedicine(&thisServiceMedicine, 11) == 6);

    //Delete Service
    deleteServiceMedicine(&thisServiceMedicine);
    assert(thisServiceMedicine.thisList.lenght == 0);

}

