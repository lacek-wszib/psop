#ifndef PARKING_H
#define PARKING_H
#include <time.h>
#include "vehicle.h"

/**
 * Inicjalizacja bazy zajętych miejsc parkingowych
 * @param databaseCapacity
 */
void initParkingDatabase(int databaseCapacity);

/**
 * Zmiana pojemności bazy zajętych miejsc parkingowych
 * @param newCapacity - nowa pojemność bazy
 * @return 1 jeśli zmieniono, 0 jeśli nie udało się zmienić
 */
int changeParkingDatabaseCapacity(int newCapacity);

/**
 * Zwolnienie pamięci zaalokowanej dla bazy zajętych miejsc parkingowych
 */
void freeParkingDatabase();

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

/**
 * Sprawdzenie czy pojazd znajduje się na parkingu
 * @param licencePlate - numer rejestracyjny pojazdu
 * @return 1 jeśli pojazd znajduje się na parkingu, 0 jeśli nie
 */
int checkParkingVehicle(LicencePlate licencePlate);

/**
 * Pobranie ilości wolnych miejsc parkingowych
 * @return ilość wolnych miejsc parkingowych
 */
int getParkingFreePlaces();

/**
 * Wczytanie pojazdów z plików do bazy pojazdów
 * @return liczba wczytanych pojazdów
 */
int loadParkingEntries();

#endif