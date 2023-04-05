//
// Created by irchit on 3/29/2023.
//

#ifndef LAB2_4_ITER2_CONSOLE_H
#define LAB2_4_ITER2_CONSOLE_H

#include "service.h"
#include <stdio.h>

typedef struct {
    int idConsole;
    int currentCommand;
    char** commands;
    ServiceMedicine serviceMedicine;
}Console;

Console createConsole(int idConsole);
void runConsole(Console* thisConsole);
void destroyConsole(Console* console);

#endif //LAB2_4_ITER2_CONSOLE_H
