#pragma once
//
// Created by irchit on 3/29/2023.
//

#ifndef LAB2_4_ITER2_MEDICINE_H
#define LAB2_4_ITER2_MEDICINE_H

#include <string.h>
#include <assert.h>
#include <stdlib.h>

typedef struct {
    int uniqueCode;
    char* name;
    float concentration;
    int stock;
} Medicine;

Medicine createMedicine(int uniqueCode, char* name, float concentration, int stock);
void deleteMedicine(Medicine* medicine);
int validateMedicine(Medicine* medicine);
Medicine copyMedicine(Medicine* medicine);
void testsMedicine();

#endif //LAB2_4_ITER2_MEDICINE_H
