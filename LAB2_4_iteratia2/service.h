#pragma once
//
// Created by irchit on 3/29/2023.
//

#ifndef LAB2_4_ITER2_SERVICE_H
#define LAB2_4_ITER2_SERVICE_H

#include "myList.h"
#include "sortMyList.h"

typedef struct {
    MyList thisList;
}ServiceMedicine;

ServiceMedicine createServiceMedicine();
void deleteServiceMedicine(ServiceMedicine* thisServiceMedicine);

int addElementToServiceMedicine(ServiceMedicine* thisServiceMedicine, int uniqueCode, char* name, float concentration, int stock);
int updateElementInServiceMedicine(ServiceMedicine* thisServiceMedicine, int uniqueCode, char* name, float concentration, int stock);
int deleteElementFromServiceMedicine(ServiceMedicine* thisServiceMedicine, int uniqueCode);
MyList sortElementsInServiceMedicineByDirection(ServiceMedicine* thisServiceMedicine, int direction);
MyList filterByCriteriaInServiceMedicine(ServiceMedicine* thisServiceMedicine, char* criteria);
void testsServiceMedicine();

#endif //LAB2_4_ITER2_SERVICE_H
