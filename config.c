#include "config.h"

#include <stdio.h>
#include <stdlib.h>

// nazwa pliku z konfiguracją
const char *CONFIG_FILE_NAME = "data/config";

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
    configFile = fopen(CONFIG_FILE_NAME, "r");
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
    configFile = fopen(CONFIG_FILE_NAME, "w");
    // zapisanie tekstu do pliku
    fprintf(configFile, "%d", parkingCapacity);
    // zamknięcie pliku
    fclose(configFile);
    return 1;
}