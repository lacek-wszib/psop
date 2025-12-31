#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "config.h"

// katalog z konfiguracją
const char *CONFIG_DIR_NAME = "config/";
// konfiguracja pojemności parkingu
const char *CAPACITY_CONFIG_FILE_PATH = "config/capacity";
// katalog na dane
const char *DATA_DIR_NAME = "data";
// katalog z danymi pojazdów
const char *VEHICLES_DATA_DIR_NAME = "data/vehicles/";
// katalog z danymi postojów
const char *PARKING_DATA_DIR_NAME = "data/parking/";
// uprawnienia do tworzonych katalogów
const mode_t DATA_DIR_MODE = 0755;

int parkingCapacity = 0;

int getParkingCapacity() {
    return parkingCapacity;
}

void setParkingCapacity(int newParkingCapacity) {
    parkingCapacity = newParkingCapacity;
}

int loadConfig() {
    FILE *configFile;
    // otwarcie pliku do odczytu
    configFile = fopen(CAPACITY_CONFIG_FILE_PATH, "r");
    if (configFile == NULL) {
        printf("Nie można otworzyć pliku konfiguracyjnego\n");
        return 0;
    }
    // odczyt zawartości
    char configData[10];
    fgets(configData, 10, configFile);
    if (sscanf(configData, "%d", &parkingCapacity) != 1) {
        printf("Błędny plik konfiguracyjny\n");
        // zamknięcie pliku
        fclose(configFile);
        return 0;
    }
    // zamknięcie pliku
    fclose(configFile);
    return 1;
}

int saveConfig() {
    FILE *configFile;
    // otwarcie pliku do zapisu
    configFile = fopen(CAPACITY_CONFIG_FILE_PATH, "w");
    // zapisanie tekstu do pliku
    fprintf(configFile, "%d", parkingCapacity);
    // zamknięcie pliku
    fclose(configFile);
    return 1;
}

void createDirectories() {
    // utworzenie katalogu na konfigurację
    mkdir(CONFIG_DIR_NAME, DATA_DIR_MODE);
    // utworzenie katalogu na dane
    mkdir(DATA_DIR_NAME, DATA_DIR_MODE);
    // utworzenie katalogu na dane pojazdów
    mkdir(VEHICLES_DATA_DIR_NAME, DATA_DIR_MODE);
    // utworzenie katalogu na dane postojów
    mkdir(PARKING_DATA_DIR_NAME, DATA_DIR_MODE);
}