#include <stdio.h>
#include "main_menu.h"
#include "vehicle.h"
#include "parking.h"
#include "config.h"

const char PROGRAM_NAME[] = "P.S.O.P - Przyjazny System Obsługi Parkingu";
const char PROGRAM_VERSION[] = "0.1.0";
const char PROGRAM_AUTHOR[] = "Aleksander Łacek";
const char TITLE_SEPARATOR[] = "===========================================";

int main(void) {

    printf("%s\n%s\n%s\n", TITLE_SEPARATOR, PROGRAM_NAME, TITLE_SEPARATOR);
    printf("Wersja: %s\nAutor: %s\n", PROGRAM_VERSION, PROGRAM_AUTHOR);
    printf("%s\n", TITLE_SEPARATOR);

    // inicjalizacja pamięci
    printf("Inicjalizacja pamięci...");
    initVehicleDatabase();
    initParkingDatabase(getParkingCapacity());
    printf("OK\n");

    // wyświetlenie menu głównego
    displayMainMenu();

    return 0;
}