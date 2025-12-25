#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vehicle.h"

// początkowy rozmiar bazy pojazdów
const int INITIAL_DATABASE_SIZE = 2;

// baza pojazdów
Vehicle *vehicles = NULL;
int vehicleCapacity = 0;
int vehicleCount = 0;

void initVehicleDatabase() {
    vehicles = malloc(INITIAL_DATABASE_SIZE * sizeof(Vehicle));
    if (!vehicles) {
        fprintf(stderr, "Błąd alokacji pamięci dla bazy pojazdów\n");
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
    // dodanie pojazdu do bazy
    vehicleCount++;
    vehicles[vehicleCount - 1] = *newVehicle;
    printf("Dodano do bazy pojazd o numerze rejestracyjnym %s\n", newVehicle->licencePlate);
}

int removeVehicle(char *licencePlate) {
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

int checkVehicle(char *licencePlate) {
    for (int i = 0; i < vehicleCount; i++) {
        if (strcmp(vehicles[i].licencePlate, licencePlate) == 0) {
            return 1; // pojazd znaleziony
        }
    }
    return 0; // pojazd nie znajduje się w bazie
}

VehicleDatabase getVehicleDatabase() {
    // utworzenie struktury bazy pojazdów
    VehicleDatabase vehicleDatabase;
    vehicleDatabase.vehicles = vehicles;
    vehicleDatabase.vehicleCount = vehicleCount;

    return vehicleDatabase;
}
