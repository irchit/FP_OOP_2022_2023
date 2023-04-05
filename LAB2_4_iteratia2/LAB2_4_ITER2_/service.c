//
// Created by irchit on 3/29/2023.
//
#include "service.h"

int isNumber(const char* string);

ServiceMedicine createServiceMedicine() {
    ServiceMedicine newServiceMedicine;
    newServiceMedicine.thisList = createMyList();
    newServiceMedicine.undoList = malloc(sizeof(char*) * UNDO_LENGHT);
    newServiceMedicine.undoLenght = 0;
    for (int i = 0; i < UNDO_LENGHT; i++)
        newServiceMedicine.undoList[i] = malloc(sizeof(char) * 250);
    return newServiceMedicine;
}

void deleteServiceMedicine(ServiceMedicine* thisServiceMedicine) {
    deleteMyList(&thisServiceMedicine->thisList);
    for (int i = 0; i < UNDO_LENGHT; i++)
        free(thisServiceMedicine->undoList[i]);
    free(thisServiceMedicine->undoList);
    thisServiceMedicine->undoLenght = 0;
}

int addElementToServiceMedicine(ServiceMedicine* thisServiceMedicine, int uniqueCode, char* name, float concentration, int stock, int undo) {
    ElementType medicine = createMedicine(uniqueCode, name, concentration, stock);
    int errorCode = validateMedicine(&medicine);
    if (errorCode != 0)
    {
        deleteMedicine(&medicine);
        return errorCode;
    }
    errorCode = addToMyList(&thisServiceMedicine->thisList, &medicine);
    if (errorCode == 0 && undo == 0)
    {
        char* stringOfContent = malloc(sizeof(char) * 250);
        sprintf_s(stringOfContent, 250, "del|%d|%s|%f|%d", uniqueCode, name, concentration, stock);
        strcpy_s(thisServiceMedicine->undoList[thisServiceMedicine->undoLenght], 250, stringOfContent);
        thisServiceMedicine->undoLenght++;
        free(stringOfContent);
    }
    return errorCode;
}

int updateElementInServiceMedicine(ServiceMedicine* thisServiceMedicine, int uniqueCode, char* name, float concentration, int stock, int undo) {
    ElementType medicine = createMedicine(uniqueCode, name, concentration, stock);
    MyList copyList = copyOfMyList(&thisServiceMedicine->thisList);
    for (int i = 0; i < copyList.lenght; i++)
        if (strcmp(copyList.values[i].name, name) == 0)
        {
            int uniqueCodeOld = copyList.values[i].uniqueCode;
            int stockOld = copyList.values[i].stock;
            float concentrationOld = copyList.values[i].concentration;
            int errorCode = validateMedicine(&medicine);
            if (errorCode != 0)
            {
                deleteMedicine(&medicine);
                deleteMyList(&copyList);
                return errorCode;
            }
            errorCode = updateInMyList(&thisServiceMedicine->thisList, &medicine, i);
            deleteMyList(&copyList);
            if (errorCode == 0 && undo == 0)
            {
                char* stringOfContent = malloc(sizeof(char) * 250);
                sprintf_s(stringOfContent, 250, "mod|%d|%s|%f|%d", uniqueCodeOld, name, concentrationOld, stockOld);
                strcpy_s(thisServiceMedicine->undoList[thisServiceMedicine->undoLenght], 250, stringOfContent);
                thisServiceMedicine->undoLenght++;
                free(stringOfContent);
            }
            return errorCode;
        }
    deleteMedicine(&medicine);
    deleteMyList(&copyList);
    return 6;
}

int deleteElementFromServiceMedicine(ServiceMedicine* thisServiceMedicine, int uniqueCode, int undo) {
    MyList copyList = copyOfMyList(&thisServiceMedicine->thisList);
    char* name = malloc(30 * sizeof(char));
    float concentration;
    int stock;
    for (int i = 0; i < copyList.lenght; i ++)
        if (uniqueCode == copyList.values[i].uniqueCode)
        {
            strcpy_s(name, 30, copyList.values[i].name);
            stock = copyList.values[i].stock;
            concentration = copyList.values[i].concentration;
        }
    int errorCode = deleteFromMyList(&thisServiceMedicine->thisList, uniqueCode);
    if (errorCode == 0 && undo == 0)
    {
        char* stringOfContent = malloc(sizeof(char) * 250);
        sprintf_s(stringOfContent, 250, "add|%d|%s|%f|%d", uniqueCode, name, concentration, stock);
        strcpy_s(thisServiceMedicine->undoList[thisServiceMedicine->undoLenght], 250, stringOfContent);
        thisServiceMedicine->undoLenght++;
        free(stringOfContent);
    }
    free(name);
    deleteMyList(&copyList);
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

int undoLastCommand(ServiceMedicine* thisServiceMedicine) {
    if (thisServiceMedicine->undoLenght == 0)
        return 1;
    char* command = malloc(sizeof(char) * 250);
    strcpy_s(command, 250, thisServiceMedicine->undoList[thisServiceMedicine->undoLenght - 1]);
    thisServiceMedicine->undoLenght--;
    char* pointerToSection;
    char* next_pointer;
    next_pointer = NULL;
    pointerToSection = strtok_s(command, "|", &next_pointer);
    char* method = malloc(4 * sizeof(char));
    strcpy_s(method, 4, pointerToSection);
    pointerToSection = strtok_s(NULL, "|", &next_pointer);
    int uniqueCode = atoi(pointerToSection);
    pointerToSection = strtok_s(NULL, "|", &next_pointer);
    char* name = malloc(30 * sizeof(char));
    strcpy_s(name, 30, pointerToSection);
    pointerToSection = strtok_s(NULL, "|", &next_pointer);
    float concentration = atof(pointerToSection);
    pointerToSection = strtok_s(NULL, "|", &next_pointer);
    int stock = atoi(pointerToSection);
    if (strcmp(method, "add") == 0)
        addElementToServiceMedicine(thisServiceMedicine, uniqueCode, name, concentration, stock, 1);
    else if (strcmp(method, "mod") == 0)
        updateElementInServiceMedicine(thisServiceMedicine, uniqueCode, name, concentration, stock, 1);
    else
        deleteElementFromServiceMedicine(thisServiceMedicine, uniqueCode, 1);
    next_pointer = NULL;
    free(name);
    free(command);
    free(method);
    return 0;
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
    assert(addElementToServiceMedicine(&thisServiceMedicine, 1, "Paracetamol", 1.0, 10, 0) == 0);
    assert(undoLastCommand(&thisServiceMedicine) == 0);
    assert(undoLastCommand(&thisServiceMedicine) == 1);
    assert(addElementToServiceMedicine(&thisServiceMedicine, 1, "Paracetamol", 1.0, 10, 0) == 0);
    assert(addElementToServiceMedicine(&thisServiceMedicine, -1, "Paracetamol", 1.0, 10, 0) == 1);
    assert(addElementToServiceMedicine(&thisServiceMedicine, 1, "", 1.0, 10, 0) == 2);
    assert(addElementToServiceMedicine(&thisServiceMedicine, 1, "Paracetamol", 0, 10, 0) == 3);
    assert(addElementToServiceMedicine(&thisServiceMedicine, 1, "Paracetamol", 1.0, -10, 0) == 4);

    //Update
    assert(updateElementInServiceMedicine(&thisServiceMedicine, 1, "Paracetamol", 1.5, 10, 0) == 0);
    assert(undoLastCommand(&thisServiceMedicine) == 0);
    assert(updateElementInServiceMedicine(&thisServiceMedicine, 1, "Paracetamol", 1.5, 10, 0) == 0);
    assert(updateElementInServiceMedicine(&thisServiceMedicine, 2, "Insulin", 1.0, 10, 0) == 6);
    assert(updateElementInServiceMedicine(&thisServiceMedicine, -1, "Paracetamol", 0, 10, 0) == 1);
    assert(updateElementInServiceMedicine(&thisServiceMedicine, 1, "", 1.0, -10, 0) == 6);
    assert(updateElementInServiceMedicine(&thisServiceMedicine, 1, "Paracetamol", -1.0, 10, 0) == 3);
    assert(updateElementInServiceMedicine(&thisServiceMedicine, 1, "Paracetamol", 1.0, -10, 0) == 4);

    addElementToServiceMedicine(&thisServiceMedicine, 2, "Insulin", 100, 10, 0);
    assert(updateElementInServiceMedicine(&thisServiceMedicine, 2, "Insulin", 1.0, 10, 0) == 0);
    addElementToServiceMedicine(&thisServiceMedicine, 3, "InsulinFast", 10, 110, 0);

    //Sort
    for (int i = 0; i < thisServiceMedicine.thisList.lenght; i++)
    {
        printf("%d %s %f %d\n", thisServiceMedicine.thisList.values[i].uniqueCode
            , thisServiceMedicine.thisList.values[i].name
            , thisServiceMedicine.thisList.values[i].concentration
            , thisServiceMedicine.thisList.values[i].stock);
    }
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
    assert(deleteElementFromServiceMedicine(&thisServiceMedicine, 1, 0) == 0);
    assert(undoLastCommand(&thisServiceMedicine) == 0);
    assert(deleteElementFromServiceMedicine(&thisServiceMedicine, 1, 0) == 0);
    assert(deleteElementFromServiceMedicine(&thisServiceMedicine, 11, 0) == 6);

    //Delete Service
    deleteServiceMedicine(&thisServiceMedicine);
    assert(thisServiceMedicine.thisList.lenght == 0);

}

