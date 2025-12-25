#include <time.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "parking.h"
#include "vehicle.h"

ParkingEntry *parkedCars = NULL;
int parkedCarsCapacity = 0;
int parkedCarsCount = 0;

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

int registerVehicleEntry(LicencePlate licencePlate) {
    if (parkedCarsCount < 100) {
        parkedCarsCount++;
        // informacje o pojeździe na parkingu
        ParkingEntry parkingEntry;
        strncpy(parkingEntry.licencePlate, licencePlate, sizeof(parkingEntry.licencePlate) - 1);
        parkingEntry.entryTime = time(NULL);
        // dodanie pojazdu do tablicy
        parkedCars[parkedCarsCount - 1] = parkingEntry;
        // sukces
        return 1;
    }
    return 0; // brak miejsc
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
            // sukces
            return 1;
        }
    }
    return 0; // pojazd nie znaleziony
}

ParkingStatistics getParkingStatistics() {
    ParkingStatistics parkingStatistics;
    parkingStatistics.placesOccupied = parkedCarsCount;
    parkingStatistics.placesTotal = 100;
    parkingStatistics.placesFree = 100 - parkedCarsCount;
    return parkingStatistics;
}

ParkingDatabase getParkingDatabase() {
    ParkingDatabase parkingDatabase;
    parkingDatabase.parkedCars = parkedCars;
    parkingDatabase.parkedCarCount = parkedCarsCount;
    return parkingDatabase;
}
