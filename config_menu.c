#include <stdio.h>
#include "input_utils.h"
#include "config.h"
#include "parking.h"

void handleParkingSizeChange();
void printConfig();


void displayConfigMenu() {

    char userInput[3];
    int configMenuChoice = -1;
    int configChanged = 0;

    while (configMenuChoice != 0) {
        printf("+=======================================+\n");
        printf("|            >>> P.S.O.P <<<            |\n");
        printf("|   PRZYJAZNY SYSTEM OBSŁUGI PARKINGU   |\n");
        printf("+=======================================+\n");
        printf("|             KONFIGURACJA              |\n");
        printf("+=======================================+\n");
        printf("| 1 => Wyświetl konfigurację            |\n");
        printf("| 2 => Ustaw ilość miejsc parkingowych  |\n");
        printf("| 0 => Powrót do głównego menu          |\n");
        printf("+=======================================+\n");
        printf(">> ");

        // wczytanie opcji z klawiatury
        if (!readLineFromInput(userInput, sizeof userInput, stdin)
            || sscanf(userInput, "%d", &configMenuChoice) != 1) {
            printf("Niepoprawna wartość, wybierz jedną z dostępnych opcji\n");
            continue;
        }

        switch (configMenuChoice) {
            case 1:
                printConfig();
                break;
            case 2:
                handleParkingSizeChange();
                configChanged = 1;
                break;
            case 0:
                if (configChanged && saveConfig()) {
                    printf("Zapisano konfigurację\n");
                }
                break;
        }
    }
}

void handleParkingSizeChange() {
    // aktualna ilość miejsc parkingowych
    printf("Aktualna ilość miejsc parkingowych: %d\n", getParkingCapacity());
    // nowa ilośc miejsc
    char userInput[10];
    int inputStatus = 0;
    int newParkingSize = 0;
    do {
        printf("Podaj nową ilość miejsc parkingowych >>");
        if (readLineFromInput(userInput, sizeof userInput, stdin)
            && sscanf(userInput, "%d", &newParkingSize)) {
            inputStatus = 1;
        } else {
            printf("Podaj poprawną ilość miejsc parkingowych\n");
        }
    } while (!inputStatus);

    // zmiana ilości miejsc parkingowych
    if (changeParkingDatabaseCapacity(newParkingSize)) {
        printf("Zmieniono ilość miejsc parkingowych na %d\n", newParkingSize);
        setParkingCapacity(newParkingSize);
    }
}

void printConfig() {
    // ilość miejsc parkingowych
    printf("Ilość miejsc parkingowych: %d\n", getParkingCapacity());
}
