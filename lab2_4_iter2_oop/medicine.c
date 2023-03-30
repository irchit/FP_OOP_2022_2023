#pragma once
//
// Created by irchit on 3/29/2023.
//
#include "medicine.h"

Medicine createMedicine(int uniqueCode, char* name, float concentration, int stock)
{
    Medicine newMedicine;
    newMedicine.uniqueCode = uniqueCode;
    newMedicine.name = (char*)malloc(sizeof(char) * 30);
    strcpy_s(newMedicine.name, 30, name);
    newMedicine.concentration = concentration;
    newMedicine.stock = stock;
    return newMedicine;
}

Medicine copyMedicine(Medicine* medicine)
{
    Medicine newMedicine = createMedicine(medicine->uniqueCode, medicine->name, medicine->concentration, medicine->stock);
    return newMedicine;
}

void deleteMedicine(Medicine* medicine)
{
    medicine->uniqueCode = -1;
    free(medicine->name);
    medicine->concentration = 0;
    medicine->stock = 0;
}

int validateMedicine(Medicine* medicine)
{
    int uniqueCode = medicine->uniqueCode;
    char* name = (char*)malloc(sizeof(char) * 30);
    strcpy_s(name, 30, medicine->name);
    float concentration = medicine->concentration;
    int stock = medicine->stock;
    if (uniqueCode < 0)
    {
        free(name);
        return 1;
    }
    if (strlen(name) == 0)
    {
        free(name);
        return 2;
    }
    if (concentration <= 0)
    {
        free(name);
        return 3;
    }
    if (stock < 0)
    {
        free(name);
        return 4;
    }
    free(name);
    return 0;
}

void testsMedicine() {
    //Create tests
    int uniqueCode1 = 1;
    char* name1 = "Aspirin";
    float concentration1 = 150;
    int stock1 = 1000;
    Medicine medicine1 = createMedicine(uniqueCode1, name1, concentration1, stock1);
    assert(medicine1.uniqueCode == uniqueCode1);
    assert(medicine1.concentration == concentration1);
    assert(medicine1.stock == stock1);
    assert(strcmp(medicine1.name, name1) == 0);

    //Validate tests
    assert(validateMedicine(&medicine1) == 0);
    int uniqueCode2 = -10;
    char* name2 = "";
    float concentration2 = 0;
    int stock2 = -2000;
    Medicine medicine2 = createMedicine(uniqueCode2, name2, concentration2, stock2);
    assert(validateMedicine(&medicine2) == 1);
    medicine2.uniqueCode = uniqueCode1;
    assert(validateMedicine(&medicine2) == 2);
    strcpy_s(medicine2.name, 30, name1);
    assert(validateMedicine(&medicine2) == 3);
    medicine2.concentration = concentration1;
    assert(validateMedicine(&medicine2) == 4);

    //Copy tests
    Medicine medicine3 = copyMedicine(&medicine1);
    assert(medicine1.uniqueCode == medicine3.uniqueCode);
    assert(medicine1.concentration == medicine3.concentration);
    assert(medicine1.stock == medicine3.stock);
    assert(strcmp(medicine1.name, medicine3.name) == 0);

    //Delete tests
    deleteMedicine(&medicine1);
    deleteMedicine(&medicine2);
    deleteMedicine(&medicine3);
    assert(medicine1.uniqueCode == -1);
    assert(medicine1.concentration == 0);
    assert(medicine1.stock == 0);
    assert(medicine2.uniqueCode == -1);
    assert(medicine2.concentration == 0);
    assert(medicine2.stock == 0);
    assert(medicine3.uniqueCode == -1);
    assert(medicine3.concentration == 0);
    assert(medicine3.stock == 0);
}
