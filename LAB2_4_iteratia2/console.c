//
// Created by irchit on 3/29/2023.
//
#include "console.h"
#define MAX_COMMANDS_LENGHT 10

void printMenu(Console* thisConsole);

void getCommand(Console* console);

void addMedicineConsole(Console* console);

void updateMedicineConsole(Console* console);

void deleteStockOfMedicineConsole(Console* console);

void sortMedicineConsole(Console* console);

void filterMedicineConsole(Console* console);

void undoLastCommandConsole(thisConsole);

Console createConsole(int idConsole)
{
    Console newConsole;
    newConsole.idConsole = idConsole;
    newConsole.currentCommand = -1;
    newConsole.commands = (char**)malloc(MAX_COMMANDS_LENGHT * sizeof(char*));
    for (int i = 0; i < MAX_COMMANDS_LENGHT; i++)
        newConsole.commands[i] = (char*)malloc(30 * sizeof(char));
    strcpy_s(newConsole.commands[0], 30, "Adauga medicament");
    strcpy_s(newConsole.commands[1], 30, "Modifica medicament");
    strcpy_s(newConsole.commands[2], 30, "Sterge stoc medicament");
    strcpy_s(newConsole.commands[3], 30, "Sortare cresc/descresc");
    strcpy_s(newConsole.commands[4], 30, "Filtrare dupa criteriu");
    strcpy_s(newConsole.commands[5], 30, "Inchideti");
    strcpy_s(newConsole.commands[6], 30, "Undo");
    newConsole.serviceMedicine = createServiceMedicine();
    return newConsole;
}

void destroyConsole(Console* thisConsole)
{
    thisConsole->idConsole = -1;
    thisConsole->currentCommand = -1;
    for (int i = 0; i < MAX_COMMANDS_LENGHT; i++)
        free(thisConsole->commands[i]);
    free(thisConsole->commands);
    deleteServiceMedicine(&thisConsole->serviceMedicine);
}

void runConsole(Console* thisConsole)
{
    while (1) {
        if (thisConsole->idConsole == -1)
            return;
        printMenu(thisConsole);
        getCommand(thisConsole);
        switch (thisConsole->currentCommand) {
        case 1:
            addMedicineConsole(thisConsole);
            break;
        case 2:
            updateMedicineConsole(thisConsole);
            break;
        case 3:
            deleteStockOfMedicineConsole(thisConsole);
            break;
        case 4:
            sortMedicineConsole(thisConsole);
            break;
        case 5:
            filterMedicineConsole(thisConsole);
            break;
        case 6:
            return;
        case 7:
            undoLastCommandConsole(thisConsole);
            break;
        default:
            printf("Comanda Invalida\n");
            break;
        }
    }
}

void undoLastCommandConsole(Console* console) {
    int errorCode = undoLastCommand(&console->serviceMedicine);
    if (errorCode == 1)
        printf("-- UNDO STACK EMPTY --\n");
    else
        printf("UNDO realizat cu succes!\n");
}

void filterMedicineConsole(Console* console) {
    char* criteria = (char*)malloc(50 * sizeof(char));
    printf("Un criteriu (prima litera/stoc maxim): ");
    scanf_s("%s", criteria, 50);
    MyList result = filterByCriteriaInServiceMedicine(&console->serviceMedicine, criteria);
    printf("|%8s|%30s|%12s|%9s|\n", "Cod Unic", "Nume", "Concentratie", "Stoc");
    for (int i = 0; i < getLenghtOfMyList(&result); i++)
        printf(" |%8d|%30s|%12.4f|%9d|\n", result.values[i].uniqueCode, result.values[i].name, result.values[i].concentration, result.values[i].stock);
    printf("\n");
    free(criteria);
    deleteMyList(&result);
}

void sortMedicineConsole(Console* console) {
    int directie;
    printf("Directie (0 - crescator, 1 - descrescator): ");
    scanf_s("%d", &directie);
    MyList result = sortElementsInServiceMedicineByDirection(&console->serviceMedicine, directie);
    printf("|%8s|%30s|%12s|%9s|\n", "Cod Unic", "Nume", "Concentratie", "Stoc");
    for (int i = 0; i < getLenghtOfMyList(&result); i++)
        printf(" |%8d|%30s|%12.4f|%9d|\n", result.values[i].uniqueCode, result.values[i].name, result.values[i].concentration, result.values[i].stock);
    printf("\n");
    deleteMyList(&result);
}

void deleteStockOfMedicineConsole(Console* console) {
    int uniqueCode;
    printf("Cod Unic: ");
    scanf_s("%d", &uniqueCode);
    int result = deleteElementFromServiceMedicine(&console->serviceMedicine, uniqueCode, 0);
    switch (result)
    {
    case 0:
        printf("Medicamentul a fost sters!\n");
        break;
    case 1:
        printf("Cod Unic invalid!\n");
        break;
    default:
        printf("Medicamentul nu exista!\n");
        break;
    }
}

void updateMedicineConsole(Console* console) {
    int uniqueCode;
    char* name = (char*)malloc(30 * sizeof(char));
    float concentration;
    int stock;
    printf("Cod Unic: ");
    scanf_s("%d", &uniqueCode);
    printf("Nume: ");
    scanf_s("%s", name, 30);
    printf("Concentratie: ");
    scanf_s("%f", &concentration);
    printf("Stoc: ");
    scanf_s("%d", &stock);
    int result = updateElementInServiceMedicine(&console->serviceMedicine, uniqueCode, name, concentration, stock, 0);
    switch (result)
    {
    case 0:
        printf("Medicamentul a fost adaugat!\n");
        break;
    case 1:
        printf("Cod Unic invalid!\n");
        break;
    case 2:
        printf("Nume invalid!\n");
        break;
    case 3:
        printf("Concentratie invalida!\n");
        break;
    case 4:
        printf("Stoc invalid!\n");
        break;
    case 5:
        printf("Medicamentul exista deja!\n");
        break;
    case 6:
        printf("Medicamentul nu a putut fi adaugat!\n");
        break;
    default:
        break;
    }
    free(name);
}

void addMedicineConsole(Console* console) {
    int uniqueCode;
    char* name = (char*)malloc(30 * sizeof(char));
    float concentration;
    int stock;
    printf("Cod Unic: ");
    scanf_s("%d", &uniqueCode);
    printf("Nume: ");
    scanf_s("%s", name, 30);
    printf("Concentratie: ");
    scanf_s("%f", &concentration);
    printf("Stoc: ");
    scanf_s("%d", &stock);
    int result = addElementToServiceMedicine(&console->serviceMedicine, uniqueCode, name, concentration, stock, 0);
    switch (result)
    {
    case 0:
        printf("Medicamentul a fost adaugat!\n");
        break;
    case 1:
        printf("Cod Unic invalid!\n");
        break;
    case 2:
        printf("Nume invalid!\n");
        break;
    case 3:
        printf("Concentratie invalida!\n");
        break;
    case 4:
        printf("Stoc invalid!\n");
        break;
    case 5:
        printf("Medicamentul exista deja!\n");
        break;
    case 6:
        printf("Medicamentul nu a putut fi adaugat!\n");
        break;
    default:
        break;
    }
    free(name);
}

void getCommand(Console* console) {
    printf("Comanda: ");
    scanf_s("%d", &console->currentCommand);
}

void printMenu(Console* thisConsole) {
    for (int i = 0; i < 7; i++) {
        printf("%d. %s\n", i + 1, thisConsole->commands[i]);
    }
}

