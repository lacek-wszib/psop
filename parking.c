#include <time.h>
#include <inttypes.h>
#include <dirent.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "parking.h"
#include "vehicle.h"
#include "config.h"
#include "string_utils.h"

ParkingEntry *parkedCars = NULL;
int parkedCarsCapacity = 0;
int parkedCarsCount = 0;

void getParkingEntryFileName(char *fileName, size_t size, LicencePlate licencePlate);
void saveParkingEntry(ParkingEntry *parkingEntry);

void initParkingDatabase(int databaseCapacity) {
    parkedCars = malloc(databaseCapacity * sizeof(ParkingEntry));
    if (!parkedCars) {
        printf("Błąd alokacji pamięci dla bazy parkingu\n");
        exit(EXIT_FAILURE);
    }
    parkedCarsCapacity = databaseCapacity;
}

int changeParkingDatabaseCapacity(int newCapacity) {
    if (newCapacity >= parkedCarsCount) {
        ParkingEntry *tmp = realloc(parkedCars, newCapacity * sizeof(ParkingEntry));
        if (!tmp) {
            printf("Błąd alokacji pamięci dla bazy parkingu\n");
            exit(EXIT_FAILURE);
        }
        parkedCars = tmp;
        parkedCarsCapacity = newCapacity;
        return 1;
    } else {
        printf("Nowa pojemność bazy parkingu jest mniejsza niż aktualna liczba pojazdów na parkingu\n");
        return 0;
    }
}

void freeParkingDatabase() {
    free(parkedCars);
    parkedCars = NULL;
    parkedCarsCapacity = 0;
    parkedCarsCount = 0;
}

/**
 * Dodanie pojazdu do bazy zaparkowanych pojazdów
 * @param parkingEntry - wskaźnik na strukturę pojazdu do dodania
 * @return 1 jeśli dodano, 0 jeśli brak miejsc
 */
int addParkingEntry(ParkingEntry *parkingEntry) {
    if (parkedCarsCount < parkedCarsCapacity) {
        // znalezienie miejsca wstawienia (alfabetycznie)
        int pos = 0;
        while (pos < parkedCarsCount
               && strcmp(parkedCars[pos].licencePlate, parkingEntry->licencePlate) < 0) {
            pos++;
        }
        // przesunięcie elementów w prawo
        for (int j = parkedCarsCount; j > pos; j--) {
            parkedCars[j] = parkedCars[j - 1];
        }
        // dodanie pojazdu do tablicy
        parkedCars[pos] = *parkingEntry;
        parkedCarsCount++;
        // sukces
        return 1;
    }
    return 0;
}

int registerVehicleEntry(LicencePlate licencePlate) {
    // informacje o wjeździe na parking
    ParkingEntry parkingEntry;
    strncpy(parkingEntry.licencePlate, licencePlate, sizeof(parkingEntry.licencePlate) - 1);
    parkingEntry.entryTime = time(NULL);
    // dodanie do bazy zaparkowanych pojazdów
    if (addParkingEntry(&parkingEntry)) {
        // zapisanie na dysku
        saveParkingEntry(&parkingEntry);
        // sukces
        return 1;
    }
    return 0; // brak miejsc
}

/**
 * Zapisanie pojazdu do pliku
 * @param vehicle - wskaźnik na strukturę pojazdu do zapisania
 */
void saveParkingEntry(ParkingEntry *parkingEntry) {
    // ściezka do pliku
    char fileName[256];
    getParkingEntryFileName(fileName, sizeof fileName, parkingEntry->licencePlate);
    // otwarcie pliku do zapisu
    FILE *vehicleFile = fopen(fileName, "w");
    // zapisanie danych do pliku
    fprintf(vehicleFile, "%" PRIdMAX "\n", (intmax_t) parkingEntry->entryTime);
    // zamknięcie pliku
    fclose(vehicleFile);
}

int loadParkingEntries() {
    // otwarcie katalogu z danymi postojów
    DIR *dir = opendir(PARKING_DATA_DIR_NAME);
    struct dirent *entry;
    // wczytanie plików z danymi postojów
    int loaded = 0;
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") != 0
            && strcmp(entry->d_name, "..") != 0) {
            // pełna ścieżka pliku
            LicencePlate licencePlate;
            stringCopy(licencePlate, sizeof licencePlate, entry->d_name);
            char parkingPath[256];
            getParkingEntryFileName(parkingPath, sizeof parkingPath, licencePlate);

            // otwarcie pliku z danymi postoju
            FILE *parkingFile = fopen(parkingPath, "r");
            if (!parkingFile) {
                printf("Nie udało się otworzyć pliku z danymi postoju %s\n", parkingPath);
                exit(EXIT_FAILURE);
            }

            // utworzenie struktury pojazdu
            ParkingEntry parkingEntry;
            strcpy(parkingEntry.licencePlate, licencePlate);

            // wczytanie danych pojazdu z pliku
            int checkInTime;
            if (fscanf(parkingFile, "%d\n", &checkInTime) != 1) {
                printf("Niepoprawne dane postoju w pliku %s\n", parkingPath);
                exit(EXIT_FAILURE);
            }
            fclose(parkingFile);

            parkingEntry.entryTime = (time_t) checkInTime;

            // dodanie pojadu do bazy
            if (addParkingEntry(&parkingEntry)) {
                loaded++;
            } else {
                printf("Błąd odtworzenia bazy miejsc postojowych: nie można dodać pojazdu %s, brak miejsc na parkingu.\n", licencePlate);
                exit(EXIT_FAILURE);
            }
        }
    }

    closedir(dir);
    return loaded; // liczba wczytanych postojów
}

/**
 * Pobranie nazwy pliku pojazdu na podstawie numeru rejestracyjnego
 * @param fileName - bufor na nazwę pliku
 * @param size - rozmiar bufora
 * @param licencePlate - numer rejestracyjny pojazdu
 */
void getParkingEntryFileName(char *fileName, size_t size, LicencePlate licencePlate) {
    snprintf(fileName, size, "%s%s", PARKING_DATA_DIR_NAME, licencePlate);
}

int registerVehicleDeparture(LicencePlate licencePlate) {
    for (int i = 0; i < parkedCarsCount; i++) {
        if (strcmp(parkedCars[i].licencePlate, licencePlate) == 0) {
            // przesunięcie kolejnych rekordów
            for (int j = i; j < parkedCarsCount; j++) {
                parkedCars[j] = parkedCars[j + 1];
            }
            // zmniejszenie liczby pojazdów na parkingu
            parkedCarsCount--;
            // usunięcie pliku z danymi postoju
            char fileName[256];
            getParkingEntryFileName(fileName, sizeof fileName, licencePlate);
            if (remove(fileName) != 0) {
                printf("Nie udało się usunąć pliku z danymi postoju %s\n", fileName);
            }
            // sukces
            return 1;
        }
    }
    return 0; // pojazd nie znaleziony
}

int checkParkingVehicle(LicencePlate licencePlate) {
    for (int i = 0; i < parkedCarsCount; i++) {
        if (strcmp(parkedCars[i].licencePlate, licencePlate) == 0) {
            return 1;
        }
    }
    return 0; // pojazd nie znaleziony
}

ParkingStatistics getParkingStatistics() {
    ParkingStatistics parkingStatistics;
    parkingStatistics.placesOccupied = parkedCarsCount;
    parkingStatistics.placesTotal = getParkingCapacity();
    parkingStatistics.placesFree = getParkingCapacity() - parkedCarsCount;
    return parkingStatistics;
}

int getParkingFreePlaces() {
    return getParkingCapacity() - parkedCarsCount;
}

ParkingDatabase getParkingDatabase() {
    ParkingDatabase parkingDatabase;
    parkingDatabase.parkedCars = parkedCars;
    parkingDatabase.parkedCarCount = parkedCarsCount;
    return parkingDatabase;
}
