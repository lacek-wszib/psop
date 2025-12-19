#include <stdio.h>
#include "vehicle_menu.h"
#include "input_utils.h"
#include "parking.h"

// rejestracja wjazdu samochodu
void handleParkingCheckIn();
// rejestracja wyjazdu samochodu
void handleParkingCheckOut();
// wypisanie listy samochodów na parking
void printVehicleList();
// wypisanie statystyk obłożenia
void printStatistics();


int main(void) {
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
        printf("| 5 => Baza samochodów                  |\n");
        printf("| 0 => Wyjście z programu               |\n");
        printf("+=======================================+\n");
        printf(">> ");

        // wczytanie opcji z klawiatury
        if (!readLineFromInput(userInput, stdin)
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
        }
    }
    return 0;
}

void handleParkingCheckIn() {
    char licencePlate[16];
    printf("Podaj numer rejestracyjny >>");
    if (!readLineFromInput(licencePlate, stdin)) {
        printf("Nieprawidłowy numer rejestracyjny\n");
    }
    // rejestacja wjazdu
    if (registerVehicleEntry(licencePlate)) {
        printf("Zarejestrowano wjazd pojazdu o numerze rejestracyjnym %s\n\n", licencePlate);
    } else {
        printf("Nie można zarejestrować wjazdu, brak miejsc na parkingu%s\n\n");
    }
}

void handleParkingCheckOut() {
    char licencePlate[16];
    printf("Podaj numer rejestracyjny >>");
    if (!readLineFromInput(licencePlate, stdin)) {
        printf("Nieprawidłowy numer rejestracyjny\n");
    }
    // rejestacja wyjazdu
    if (registerVehicleDeparture(licencePlate)) {
        printf("Zarejestrowano wyjazd pojazdu o numerze rejestracyjnym %s\n\n", licencePlate);
    } else {
        printf("Brak pojazdu o numerze rejestracyjnym %s na parkingu\n\n", licencePlate);
    }
}

void printVehicleList() {
    // pobranie listy zajętych miejsc
    ParkingDatabase parkedCars = getParkingDatabase();
    if (parkedCars.parkedCarCount == 0) {
        printf("Brak pojazdów na parkingu\n");
        return;
    }
    // wypisanie pojazdów
    printf("====================\nPojazdy na parkingu:\n====================\n");
    for (int i = 0; i < parkedCars.parkedCarCount; i++) {
        ParkingEntry *parkingEntry = &parkedCars.parkedCars[i];
        printf("%s\n", parkingEntry->licencePlate);
    }
}

void printStatistics() {
    ParkingStatistics parkingStatistics = getParkingStatistics();
    printf("Ilość zajętych miejsc parkingowych: %d\n", parkingStatistics.placesOccupied);
    printf("Ilość wolnych miejsc parkingowych: %d\n", parkingStatistics.placesFree);
    printf("Ilość wszystkich miejsc parkingowych: %d\n", parkingStatistics.placesTotal);
}
