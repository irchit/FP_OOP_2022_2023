//
// Created by irchit on 3/28/2023.
//
#include "console.h"

void printMenu(Console* thisConsole);

void getCommand(Console *console);

void closeConsole(Console *console);

void addMedicineConsole(Console *console);

void updateMedicineConsole(Console *console);

void deleteStockOfMedicineConsole(Console *console);

void sortMedicineConsole(Console *console);

void filterMedicineConsole(Console *console);

Console createConsole(int idConsole)
{
    Console newConsole;
    newConsole.idConsole = idConsole;
    newConsole.currentCommand = -1;
    strcpy(newConsole.commands[0], "Adauga medicament");
    strcpy(newConsole.commands[1], "Modifica medicament");
    strcpy(newConsole.commands[2], "Sterge stoc medicament");
    strcpy(newConsole.commands[3], "Sortare cresc/descresc");
    strcpy(newConsole.commands[4], "Filtrare dupa criteriu");
    strcpy(newConsole.commands[5], "Inchideti");
    newConsole.serviceMedicine = createServiceMedicine();
    return newConsole;
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
                closeConsole(thisConsole);
                return;
            default:
                printf("Comanda Invalida\n");
                break;
        }
    }
}

void filterMedicineConsole(Console *console) {
    char criteria[50];
    printf("Un criteriu (prima litera/stoc maxim): ");
    scanf_s("%s", criteria, 50);
    MyList result = filterByCriteriaInServiceMedicine(&console->serviceMedicine, criteria);
    printf("|%8s|%30s|%10s|%9s|\n", "Cod Unic", "Nume", "Concentratie", "Stoc");
    for (int i = 0; i < getLenghtOfMyList(&result); i++)
        printf("|%8d|%30s|%10.4f|%9d|\n", result.values[i].uniqueCode, result.values[i].name, result.values[i].concentration, result.values[i].stock);
    printf("\n");
}

void sortMedicineConsole(Console *console) {
    int directie;
    printf("Directie (0 - crescator, 1 - descrescator): ");
    scanf_s("%d", &directie);
    MyList result = sortElementsInServiceMedicineByDirection(&console->serviceMedicine, directie);
    printf("|%8s|%30s|%10s|%9s|\n", "Cod Unic", "Nume", "Concentratie", "Stoc");
    for (int i = 0; i < getLenghtOfMyList(&result); i++)
        printf("|%8d|%30s|%10.4f|%9d|\n", result.values[i].uniqueCode, result.values[i].name, result.values[i].concentration, result.values[i].stock);
    printf("\n");
}

void deleteStockOfMedicineConsole(Console *console) {
    int uniqueCode;
    printf("Cod Unic: ");
    scanf_s("%d", &uniqueCode);
    int result = deleteElementFromServiceMedicine(&console->serviceMedicine, uniqueCode);
    switch(result)
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

void updateMedicineConsole(Console *console) {
    int uniqueCode;
    char name[30];
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
    int result = updateElementInServiceMedicine(&console->serviceMedicine, uniqueCode, name, concentration, stock);
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
}

void addMedicineConsole(Console *console) {
    int uniqueCode;
    char name[30];
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
    int result = addElementToServiceMedicine(&console->serviceMedicine, uniqueCode, name, concentration, stock);
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
}

void closeConsole(Console *console) {
    console->currentCommand = -1;
    console->idConsole = -1;
    deleteServiceMedicine(&console->serviceMedicine);
}

void getCommand(Console *console) {
    printf("Comanda: ");
    scanf_s("%d", &console->currentCommand);
}

void printMenu(Console* thisConsole) {
    for (int i = 0; i < 6; i ++) {
        printf("%d. %s\n", i + 1, thisConsole->commands[i]);
    }
}
