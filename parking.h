#ifndef PARKING_H
#define PARKING_H
#include <time.h>
#include "vehicle.h"

/**
 * Informacje o pojaździe znajdującym się na parkingu
 */
typedef struct parkingEntry {
    LicencePlate licencePlate;
    time_t entryTime;
} ParkingEntry;

/**
 * Struktura reprezentująca statystyki parkingu
 */
typedef struct parkingStatistics {
    int placesTotal;
    int placesOccupied;
    int placesFree;
} ParkingStatistics;

/**
 * Struktura reprezentująca bazę zajętych miejsc parkingowych
 */
typedef struct parkingDatabase {
    ParkingEntry *parkedCars;
    int parkedCarCount;
} ParkingDatabase;

/**
 * Rejestracja wjazdu pojazdu na parking
 * @param licencePlate - numer rejestracyjny pojazdu
 * @return 1 jeśli zarejestrowano wjazd, 0 jeśli brak miejsc
 */
int registerVehicleEntry(LicencePlate licencePlate);

/**
 * Rejestracja wyjazdu pojazdu z parkingu
 * @param licencePlate - numer rejestracyjny pojazdu
 * @return 1 jeśli zarejestrowano wyjazd, 0 jeśli pojazdu nie znaleziono
 */
int registerVehicleDeparture(LicencePlate licencePlate);

/**
 * Pobranie statystyk parkingu
 * @return struktura zawierająca statystyki parkingu
 */
ParkingStatistics getParkingStatistics();

/**
 * Pobranie bazy zajętych miejsc parkingowych
 * @return struktura zawierająca dane bazy parkingu
 */
ParkingDatabase getParkingDatabase();

#endif