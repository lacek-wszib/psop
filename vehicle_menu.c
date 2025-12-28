#include <stdio.h>
#include "input_utils.h"
#include "vehicle.h"

void printAllVehicleList();
void handleVehicleAdd();
void handleVehicleRemove();


void displayVehicleManagmentMenu() {

    char userInput[3];
    int vehicleMenuChoice = -1;

    while (vehicleMenuChoice != 0) {
        printf("+=======================================+\n");
        printf("|            >>> P.S.O.P <<<            |\n");
        printf("|   PRZYJAZNY SYSTEM OBSŁUGI PARKINGU   |\n");
        printf("+=======================================+\n");
        printf("|             BAZA POJAZDÓW             |\n");
        printf("+=======================================+\n");
        printf("| Dostępne opcje:                       |\n");
        printf("| 1 => Wyświetlenie listy pojazdów      |\n");
        printf("| 2 => Dodanie pojazdu do bazy          |\n");
        printf("| 3 => Usunięcie pojazdu z bazy         |\n");
        printf("| 0 => Powrót do głównego menu          |\n");
        printf("+=======================================+\n");
        printf(">> ");

        // wczytanie opcji z klawiatury
        if (!readLineFromInput(userInput, stdin)
            || sscanf(userInput, "%d", &vehicleMenuChoice) != 1) {
            printf("Niepoprawna wartość, wybierz jedną z dostępnych opcji\n");
            continue;
        }

        switch (vehicleMenuChoice) {
            case (1):
                printAllVehicleList();
                break;
            case (2):
                handleVehicleAdd();
                break;
            case (3):
                handleVehicleRemove();
                break;
        }
    }
}

void printAllVehicleList() {
    // pobranie listy pojazdów
    VehicleDatabase vehicleDatabase = getVehicleDatabase();
    if (vehicleDatabase.vehicleCount == 0) {
        printf("Brak pojazdów w bazie\n");
        return;
    }
    // wypisanie pojazdów
    printf("===============\nLista pojazdów:\n===============\n");
    for (int i = 0; i < vehicleDatabase.vehicleCount; i++) {
        Vehicle *vehicle = &vehicleDatabase.vehicles[i];
        printf("Nr rejestracyjny: %s\nMarka pojazdu: %s\nModel pojazdu: %s\nKolor pojazdu: %s\n===\n",
               vehicle->licencePlate, vehicle->brand, vehicle->model, vehicle->colour);
    }
}

void handleVehicleAdd() {
    Vehicle newVehicle;
    int inputStatus = 0;

    printf("Dodanie pojazdu: \n");
    // numer rejstracyjny
    do {
        printf("Podaj numer rejestracyjny >>");
        inputStatus = readLineFromInput(newVehicle.licencePlate, stdin);
        if (!inputStatus) {
            printf("Nieprawidłowy numer rejestracyjny\n");
        }
    } while (!inputStatus);
    // marka pojazdu
    do {
        printf("Podaj marke pojazdu >>");
        inputStatus = readLineFromInput(newVehicle.brand, stdin);
        if (!inputStatus) {
            printf("Nieprawidłowa marka pojadu\n");
        }
    } while (!inputStatus);
    // model pojazdu
    do {
        printf("Podaj model pojazdu >>");
        inputStatus = readLineFromInput(newVehicle.model, stdin);
        if (!inputStatus) {
            printf("Nieprawidłowy model pojadu\n");
        }
    } while (!inputStatus);
    // kolor pojazdu
    do {
        printf("Podaj kolor pojazdu >>");
        inputStatus = readLineFromInput(newVehicle.colour, stdin);
        if (!inputStatus) {
            printf("Nieprawidłowy kolor pojadu\n");
        }
    } while (!inputStatus);

    // dodanie pojazdu do bazy
    addVehicle(&newVehicle);
}

void handleVehicleRemove() {
    LicencePlate licencePlate;
    int inputStatus = 0;
    // numer rejstracyjny
    do {
        printf("Podaj numer rejestracyjny pojazdu do usunięcia>>");
        inputStatus = readLineFromInput(licencePlate, stdin);
        if (!inputStatus) {
            printf("Nieprawidłowy numer rejestracyjny\n");
        }
    } while (!inputStatus);

    // usunięcie pojazdu z bazy
    if (!removeVehicle(licencePlate)) {
        printf("Usunięto pojazdu o numerze rejestracyjnym %s\n", licencePlate);
    } else {
        printf("Nie znaleziono pojazdu o numerze rejestracyjnym %s\n", licencePlate);
    }
}
