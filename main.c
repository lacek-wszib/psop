#include <stdio.h>
#include <sys/stat.h>
#include "main_menu.h"
#include "vehicle.h"
#include "parking.h"
#include "config.h"

const char PROGRAM_NAME[] = "P.S.O.P - Przyjazny System Obsługi Parkingu";
const char PROGRAM_VERSION[] = "0.2.0";
const char PROGRAM_AUTHOR[] = "Aleksander Łacek";
const char TITLE_SEPARATOR[] = "===========================================";
// katalog na dane
const char *DATA_DIR = "data";
const mode_t DATA_DIR_MODE = 0755;

int main(void) {
    printf("%s\n%s\n%s\n", TITLE_SEPARATOR, PROGRAM_NAME, TITLE_SEPARATOR);
    printf("Wersja: %s\nAutor: %s\n", PROGRAM_VERSION, PROGRAM_AUTHOR);
    printf("%s\n", TITLE_SEPARATOR);

    printf("Wczytanie danych...\n");
    // utworzenie katalogu na dane
    mkdir(DATA_DIR, DATA_DIR_MODE);
    // wczytanie danych
    if (loadConfig()) {
        printf("Wczytano konfigurację\n");
    }
    // inicjalizacja pamięci
    initVehicleDatabase();
    initParkingDatabase(getParkingCapacity());

    // wyświetlenie menu głównego
    displayMainMenu();

    // zwolnienie pamięci
    freeParkingDatabase();
    freeVehicleDatabase();

    return 0;
}
