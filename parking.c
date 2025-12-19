#include <time.h>
#include <string.h>
#include "parking.h"
#include "vehicle.h"

ParkingEntry parkedCars[100];
int parkedCarCount = 0;

int registerVehicleEntry(LicencePlate licencePlate) {
    if (parkedCarCount < 100) {
        parkedCarCount++;
        // informacje o pojeździe na parkingu
        ParkingEntry parkingEntry;
        strncpy(parkingEntry.licencePlate, licencePlate, sizeof(parkingEntry.licencePlate) - 1);
        parkingEntry.entryTime = time(NULL);
        // dodanie pojazdu do tablicy
        parkedCars[parkedCarCount - 1] = parkingEntry;
        // sukces
        return 1;
    }
    return 0; // brak miejsc
}

int registerVehicleDeparture(LicencePlate licencePlate) {
    for (int i = 0; i < parkedCarCount; i++) {
        if (strcmp(parkedCars[i].licencePlate, licencePlate) == 0) {
            // przesunięcie kolejnych rekordów
            for (int j = i; j < parkedCarCount; j++) {
                parkedCars[j] = parkedCars[j + 1];
            }
            // zmniejszenie liczby pojazdów na parkingu
            parkedCarCount--;
            // sukces
            return 1;
        }
    }
    return 0; // pojazd nie znaleziony
}

ParkingStatistics getParkingStatistics() {
    ParkingStatistics parkingStatistics;
    parkingStatistics.placesOccupied = parkedCarCount;
    parkingStatistics.placesTotal = 100;
    parkingStatistics.placesFree = 100 - parkedCarCount;
    return parkingStatistics;
}

ParkingDatabase getParkingDatabase() {
    ParkingDatabase parkingDatabase;
    parkingDatabase.parkedCars = parkedCars;
    parkingDatabase.parkedCarCount = parkedCarCount;
    return parkingDatabase;
}
