#include "console.h"

void runApp()
{
    Console console = createConsole(1);
    runConsole(&console);
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
    return 0;
}
