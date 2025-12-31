#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "vehicle.h"
#include "config.h"
#include "string_utils.h"


// początkowy rozmiar bazy pojazdów
const int INITIAL_DATABASE_SIZE = 2;

char *getVehicleFileName(LicencePlate licencePlate);
void saveVehicle(Vehicle *vehicle);

// baza pojazdów
Vehicle *vehicles = NULL;
int vehicleCapacity = 0;
int vehicleCount = 0;

void initVehicleDatabase() {
    vehicles = malloc(INITIAL_DATABASE_SIZE * sizeof(Vehicle));
    if (!vehicles) {
        printf("Błąd alokacji pamięci dla bazy pojazdów\n");
        exit(EXIT_FAILURE);
    }
    vehicleCapacity = INITIAL_DATABASE_SIZE;
}

void freeVehicleDatabase() {
    free(vehicles);
    vehicles = NULL;
    vehicleCapacity = 0;
    vehicleCount = 0;
}

/**
 * Sprawdzenie czy baza pojazdów ma wystarczającą pojemność.
 * W razie potrzeby następuje alokacja potrzebnej pamięci i zwiększenie pojemności bazy.
 * @param newVehicleCount - nowa ilość pojazdów po dodaniu
 */
void checkDatabaseCapacity(int newVehicleCount) {
    if (newVehicleCount > vehicleCapacity) {
        int newCapacity = vehicleCapacity * 2;
        Vehicle *tmp = realloc(vehicles, newCapacity * sizeof(Vehicle));
        if (!tmp) {
            printf("Błąd alokacji pamięci dla bazy pojazdów\n");
            exit(EXIT_FAILURE);
        }
        vehicles = tmp;
        vehicleCapacity = newCapacity;
    }
}

void addVehicle(Vehicle *newVehicle) {
    // sprawdzenie pojemności bazy
    checkDatabaseCapacity(vehicleCount + 1);
    // znalezienie miejsca wstawienia (alfabetycznie wg numeru rejestracyjnego)
    int pos = 0;
    while (pos < vehicleCount && strcmp(vehicles[pos].licencePlate, newVehicle->licencePlate) < 0) {
        pos++;
    }
    // przesunięcie elementów w prawo
    for (int j = vehicleCount; j > pos; j--) {
        vehicles[j] = vehicles[j - 1];
    }
    // dodanie pojazdu do bazy
    vehicles[pos] = *newVehicle;
    vehicleCount++;
}

void addVehicleAndSave(Vehicle *newVehicle) {
    // dodanie pojazdu
    addVehicle(newVehicle);
    printf("Dodano do bazy pojazd %s %s o numerze rejestracyjnym %s\n", newVehicle->brand, newVehicle->model, newVehicle->licencePlate);
    // zapisanie pojazdu
    saveVehicle(newVehicle);
}

/**
 * Zapisanie pojazdu do pliku
 * @param vehicle - wskaźnik na strukturę pojazdu do zapisania
 */
void saveVehicle(Vehicle *vehicle) {
    FILE *vehicleFile;
    // otwarcie pliku do zapisu
    char *fileName = getVehicleFileName(vehicle->licencePlate);
    vehicleFile = fopen(fileName, "w");
    // zapisanie tekstu do pliku
    fprintf(vehicleFile, "%s\n%s", vehicle->brand, vehicle->model);
    // zamknięcie pliku
    fclose(vehicleFile);
    free(fileName);
}

/**
 * Pobranie nazwy pliku pojazdu na podstawie numeru rejestracyjnego
 * @param licencePlate - numer rejestracyjny pojazdu
 * @return ścieżka do pliku z danymi pojazdu (należy zwolnić pamięć po użyciu)
 */
char *getVehicleFileName(LicencePlate licencePlate) {
    size_t len = strlen(VEHICLES_DATA_DIR_NAME) + strlen(licencePlate) + 1;
    char *fileName = malloc(len);
    snprintf(fileName, len, "%s%s", VEHICLES_DATA_DIR_NAME, licencePlate);
    return fileName;
}

int loadVehicles() {
    // otwarcie katalogu z danymi pojazdów
    DIR *dir = opendir(VEHICLES_DATA_DIR_NAME);
    struct dirent *entry;
    // wczytanie plików z danymi pojazdów
    int loaded = 0;
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") != 0
            && strcmp(entry->d_name, "..") != 0) {
            // pełna ścieżka pliku
            size_t vehiclePathLen = strlen(VEHICLES_DATA_DIR_NAME) + strlen(entry->d_name) + 1;
            char *vehiclePath = malloc(vehiclePathLen);
            snprintf(vehiclePath, vehiclePathLen, "%s%s", VEHICLES_DATA_DIR_NAME, entry->d_name);

            // otwarcie pliku z danymi pojazdu
            FILE *vehicleFile = fopen(vehiclePath, "r");
            if (!vehicleFile) {
                printf("Nie udało się otworzyć pliku z danymi pojazdu %s\n", vehiclePath);
                free(vehiclePath);
                exit(EXIT_FAILURE);
            }

            // utworzenie struktury pojazdu
            Vehicle vehicle;
            stringCopy(vehicle.licencePlate, sizeof vehicle.licencePlate, entry->d_name);

            // wczytanie danych pojazdu z pliku
            if (fscanf(vehicleFile, "%s\n%s", vehicle.brand, vehicle.model) != 2) {
                printf("Niepoprawne dane pojazdu w pliku %s\n", vehiclePath);
                free(vehiclePath);
                exit(EXIT_FAILURE);
            }
            free(vehiclePath);
            fclose(vehicleFile);

            // dodanie pojadu do bazy
            addVehicle(&vehicle);
            loaded++;
        }
    }

    closedir(dir);
    return loaded; // liczba wczytanych pojazdów
}

int removeVehicle(LicencePlate licencePlate) {
    // wyszukanie pojazdu do usunięcia
    for (int i = 0; i < vehicleCount; i++) {
        if (strcmp(vehicles[i].licencePlate, licencePlate) == 0) {
            // przesunięcie kolejnych rekordów
            for (int j = i; j < vehicleCount; j++) {
                vehicles[j] = vehicles[j + 1];
            }
            // zmniejszenie liczby pojazdów w bazie
            vehicleCount--;
            // zwrócenie sukcesu
            return 1;
        }
    }
    return 0;
}

int checkVehicle(LicencePlate licencePlate) {
    for (int i = 0; i < vehicleCount; i++) {
        if (strcmp(vehicles[i].licencePlate, licencePlate) == 0) {
            return 1; // pojazd znaleziony
        }
    }
    return 0; // pojazd nie znajduje się w bazie
}

Vehicle *findVehicle(LicencePlate licencePlate) {
    for (int i = 0; i < vehicleCount; i++) {
        if (strcmp(vehicles[i].licencePlate, licencePlate) == 0) {
            return &vehicles[i];
        }
    }
    return NULL; // brak pojazdu
}

VehicleDatabase getVehicleDatabase() {
    // utworzenie struktury bazy pojazdów
    VehicleDatabase vehicleDatabase;
    vehicleDatabase.vehicles = vehicles;
    vehicleDatabase.vehicleCount = vehicleCount;

    return vehicleDatabase;
}
