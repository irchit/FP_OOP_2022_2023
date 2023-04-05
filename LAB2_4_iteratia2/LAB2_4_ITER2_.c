#include "console.h"
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h> 
#include <crtdbg.h>

void runApp()
{
    Console console = createConsole(1);
    runConsole(&console);
    printf("Aplicatia s-a inchis cu succes!\n");
    destroyConsole(&console);
    printf("Aplicatia a fost stearsa cu succes!\n");
}

void runTests()
{
    testsMedicine();
    testsMyList();
    testSort();
    testsServiceMedicine();
}

int main() {
    runTests();
    runApp();
    _CrtDumpMemoryLeaks();
    return 0;
}
