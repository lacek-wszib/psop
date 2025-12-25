#include <stdio.h>
#include "input_utils.h"
#include "config.h"
#include "parking.h"

void handleParkingSizeChange();


void displayConfigMenu() {
    char userInput[3];
    int configMenuChoice = -1;

    while (configMenuChoice != 0) {
        printf("+=======================================+\n");
        printf("|            >>> P.S.O.P <<<            |\n");
        printf("|   PRZYJAZNY SYSTEM OBSŁUGI PARKINGU   |\n");
        printf("+=======================================+\n");
        printf("|             KONFIGURACJA              |\n");
        printf("+=======================================+\n");
        printf("| 1 => Ilość miejsc parkingowych        |\n");
        printf("| 0 => Powrót do głównego menu          |\n");
        printf("+=======================================+\n");
        printf(">> ");

        // wczytanie opcji z klawiatury
        if (!readLineFromInput(userInput, stdin)
            || sscanf(userInput, "%d", &configMenuChoice) != 1) {
            printf("Niepoprawna wartość, wybierz jedną z dostępnych opcji\n");
            continue;
        }

        switch (configMenuChoice) {
            case (1):
                handleParkingSizeChange();
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
        if (readLineFromInput(userInput, stdin)
            && sscanf(userInput, "%d", &newParkingSize)) {
            inputStatus = 1;
        } else {
            printf("Podaj poprawną ilość miejsc parkingowych\n");
        }
    } while (!inputStatus);

    // zmiana ilości miejsc parkingowych
    if  (changeParkingDatabaseCapacity(newParkingSize)) {
        printf("Zmieniono ilość miejsc parkingowych na %d\n", newParkingSize);
        setParkingCapacity(newParkingSize);
    }
}
