#include <stdio.h>
#include "main_menu.h"
#include "vehicle.h"
#include "parking.h"
#include "config.h"

const char PROGRAM_NAME[] = "P.S.O.P - Przyjazny System Obsługi Parkingu";
const char PROGRAM_VERSION[] = "0.5.0";
const char PROGRAM_AUTHOR[] = "Aleksander Łacek";
const char TITLE_SEPARATOR[] = "===========================================";

int main(void) {
    printf("%s\n%s\n%s\n", TITLE_SEPARATOR, PROGRAM_NAME, TITLE_SEPARATOR);
    printf("Wersja: %s\nAutor: %s\n", PROGRAM_VERSION, PROGRAM_AUTHOR);
    printf("%s\n", TITLE_SEPARATOR);

    printf("Wczytanie konfiguracji...\n");
    // utworzenie katalogów
    createDirectories();
    // wczytanie konfiguracji
    loadConfig();
    // inicjalizacja pamięci
    initVehicleDatabase();
    initParkingDatabase(getParkingCapacity());
    // wczytanie danych
    printf("Wczytanie danych...\n");
    const int vehiclesCount = loadVehicles();
    printf("Wczytano %d pojazdów\n", vehiclesCount);
    const int parkingEntryCount = loadParkingEntries();
    printf("Wczytano %d postojów\n", parkingEntryCount);

    // wyświetlenie menu głównego
    displayMainMenu();

    // zwolnienie pamięci
    freeParkingDatabase();
    freeVehicleDatabase();

    return 0;
}
