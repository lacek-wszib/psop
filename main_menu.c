#include <stdio.h>
#include <string.h>

#include "input_utils.h"
#include "vehicle_menu.h"
#include "config_menu.h"
#include "parking.h"
#include "string_utils.h"

void handleParkingCheckIn();
void handleParkingCheckOut();
void printVehicleList();
void printStatistics();
void handleAddVehicle(LicencePlate licencePlate);

void displayMainMenu() {
    // wybór użytkownika
    char userInput[4];
    int mainMenuChoice = -1;

    // menu główne programu
    while (mainMenuChoice != 0) {
        printf("+=======================================+\n");
        printf("|            >>> P.S.O.P <<<            |\n");
        printf("|   PRZYJAZNY SYSTEM OBSŁUGI PARKINGU   |\n");
        printf("+=======================================+\n");
        printf("|              MENU GŁÓWNE              |\n");
        printf("+=======================================+\n");
        printf("| 1 => Rejestracja wjazdu na parking    |\n");
        printf("| 2 => Rejestracja wyjazdu z parkingu   |\n");
        printf("| 3 => Lista pojazdów na parkingu       |\n");
        printf("| 4 => Statystyki obłożenia parkingu    |\n");
        printf("| 5 => Baza pojazdów                    |\n");
        printf("| 6 => Konfiguracja                     |\n");
        printf("| 0 => Wyjście z programu               |\n");
        printf("+=======================================+\n");
        printf(">> ");

        // wczytanie opcji z klawiatury
        if (!readLineFromInput(userInput, sizeof userInput, stdin)
            || sscanf(userInput, "%d", &mainMenuChoice) != 1) {
            printf("Niepoprawna wartość, wybierz jedną z dostępnych opcji\n");
            continue;
        }

        // obsługa wybranej opcji
        switch (mainMenuChoice) {
            case 1:
                handleParkingCheckIn();
                break;
            case 2:
                handleParkingCheckOut();
                break;
            case 3:
                printVehicleList();
                break;
            case 4:
                printStatistics();
                break;
            case 5:
                displayVehicleManagmentMenu();
                break;
            case 6:
                displayConfigMenu();
                break;
        }
    }
}

/**
 * Rejestracja wjazdu samochodu
 */
void handleParkingCheckIn() {
    // sprawdzenie dostęności miejsc
    if (getParkingFreePlaces() == 0) {
        printf("Brak wolnych miejsc na parkingu, nie można zarejestrować wjazdu\n");
        return;
    }

    // wprowadzenie numeru rejestracyjnego
    LicencePlate licencePlate;
    printf("Podaj numer rejestracyjny >>");
    int inputStatus = 0;
    do {
        inputStatus = readLineFromInput(licencePlate, sizeof licencePlate, stdin);
        if (!inputStatus) {
            printf("Nieprawidłowy numer rejestracyjny\n");
        }
    } while (!inputStatus);
    toUpperCharArray(licencePlate, sizeof licencePlate);

    // sprawdzenie czy pojazdu nie ma na parkingu
    if (checkParkingVehicle(licencePlate)) {
        printf("Pojazd o numerze rejestracyjnym %s znajduje się już na parkingu\n", licencePlate);
        return;
    }

    // sprawdzenie czy pojazd jest w bazie
    if (!checkVehicle(licencePlate)) {
        printf("Nie znaleziono pojazdu w bazie, czy go dodać? (t/n) >>");
        char userInput[3];
        if (readLineFromInput(userInput, sizeof userInput, stdin)
            && (userInput[0] == 't' || userInput[0] == 'T')) {
            handleAddVehicle(licencePlate);
        } else {
            printf("Anulowano rejestrację wjazdu\n");
            return;
        }
    }

    // rejestacja wjazdu
    if (registerVehicleEntry(licencePlate)) {
        Vehicle *vehicle = findVehicle(licencePlate);
        printf("Zarejestrowano wjazd pojazdu %s %s o numerze rejestracyjnym %s\n", vehicle->brand, vehicle->model, licencePlate);
    } else {
        printf("Nie można zarejestrować wjazdu, brak miejsc na parkingu\n");
    }
}

/**
 * Rejestracja wyjazdu samochodu
 */
void handleParkingCheckOut() {
    // wprowadzenie numeru rejestracyjnego
    LicencePlate licencePlate;
    printf("Podaj numer rejestracyjny >>");
    int inputStatus = 0;
    do {
        inputStatus = readLineFromInput(licencePlate, sizeof licencePlate, stdin);
        if (!inputStatus) {
            printf("Nieprawidłowy numer rejestracyjny\n");
        }
    } while (!inputStatus);
    toUpperCharArray(licencePlate, sizeof licencePlate);

    // wyszukanie postoju w bazie
    ParkingEntry *parkingEntry = findParkingEntry(licencePlate);
    if (parkingEntry != NULL) {
        // wyliczenie czasu postoju
        const ParkingTime parkingTime = calculateParkingTime(parkingEntry);
        // rejestacja wyjazdu
        registerVehicleDeparture(licencePlate);
        // komunikat dla użytkownika
        printf("Zarejestrowano wyjazd pojazdu o numerze rejestracyjnym %s\n", licencePlate);
        printf("Czas postoju pojazdu wyniósł: %d:%02d\n", parkingTime.hours, parkingTime.minutes);
    } else {
        printf("Brak pojazdu o numerze rejestracyjnym %s na parkingu\n", licencePlate);
    }
}

/**
 * Wypisanie listy pojazdów na parkingu
 */
void printVehicleList() {
    // pobranie listy zajętych miejsc
    const ParkingDatabase parkedCars = getParkingDatabase();
    if (parkedCars.parkedCarCount == 0) {
        printf("Brak pojazdów na parkingu\n");
        return;
    }
    // wypisanie pojazdów
    printf("====================\nPojazdy na parkingu:\n====================\n");
    for (int i = 0; i < parkedCars.parkedCarCount; i++) {
        ParkingEntry *parkingEntry = &parkedCars.parkedCars[i];
        Vehicle *vehicle = findVehicle(parkingEntry->licencePlate);
        if (vehicle != NULL) {
            // konwersja czasu
            char timeBuf[17] = "brak czasu";
            struct tm *localDateTime = localtime(&parkingEntry->entryTime);
            if (localDateTime) {
                strftime(timeBuf, sizeof timeBuf, "%Y-%m-%d %H:%M", localDateTime);
            }
            // wyliczenie czasu postoju
            const ParkingTime parkingTime = calculateParkingTime(parkingEntry);
            // wyświetlenie informacji o parkowaniu
            printf("%s %s %s [%s] [%d:%02d]\n",
                   parkingEntry->licencePlate, vehicle->brand, vehicle->model, timeBuf, parkingTime.hours, parkingTime.minutes);
        } else {
            printf("%s (brak danych w bazie)\n", parkingEntry->licencePlate);
        }
    }
}

/**
 * Wypisanie statystyk parkingu
 */
void printStatistics() {
    const ParkingStatistics parkingStatistics = getParkingStatistics();
    printf("Ilość zajętych miejsc parkingowych: %d\n", parkingStatistics.placesOccupied);
    printf("Ilość wolnych miejsc parkingowych: %d\n", parkingStatistics.placesFree);
    printf("Ilość wszystkich miejsc parkingowych: %d\n", parkingStatistics.placesTotal);
}

void handleAddVehicle(LicencePlate licencePlate) {
    // sprawdzenie czy pojazd już jest w bazie
    if (checkVehicle(licencePlate)) {
        printf("Pojazd o numerze rejestracyjnym %s już znajduje się w bazie\n", licencePlate);
        return;
    }

    Vehicle newVehicle;
    strcpy(newVehicle.licencePlate, licencePlate);
    int inputStatus = 0;

    // marka pojazdu
    do {
        printf("Podaj marke pojazdu >>");
        inputStatus = readLineFromInput(newVehicle.brand, sizeof newVehicle.brand, stdin);
        if (!inputStatus) {
            printf("Nieprawidłowa marka pojadu\n");
        }
    } while (!inputStatus);
    // model pojazdu
    do {
        printf("Podaj model pojazdu >>");
        inputStatus = readLineFromInput(newVehicle.model, sizeof newVehicle.model, stdin);
        if (!inputStatus) {
            printf("Nieprawidłowy model pojadu\n");
        }
    } while (!inputStatus);

    // dodanie pojazdu do bazy
    addVehicleAndSave(&newVehicle);
}
