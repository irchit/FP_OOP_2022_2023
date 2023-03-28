//
// Created by irchit on 3/28/2023.
//

#ifndef LAB2_4_ITER1_CONSOLE_H
#define LAB2_4_ITER1_CONSOLE_H
#include "service.h"
#include <stdio.h>

typedef struct{
    int idConsole;
    int currentCommand;
    char commands[6][50];
    ServiceMedicine serviceMedicine;
}Console;

Console createConsole(int idConsole);
void runConsole(Console* thisConsole);

#endif
