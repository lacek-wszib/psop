#ifndef PARKING_H
#define PARKING_H
#include <time.h>
#include "vehicle.h"
#include <stdbool.h>

/**
 * Inicjalizacja bazy zajętych miejsc parkingowych
 * @param databaseCapacity
 */
void initParkingDatabase(int databaseCapacity);

/**
 * Zmiana pojemności bazy zajętych miejsc parkingowych
 * @param newCapacity - nowa pojemność bazy
 * @return true jeśli zmieniono, false jeśli nowa pojemność jest mniejsza niż aktualna liczba pojazdów na parkingu
 */
bool changeParkingDatabaseCapacity(int newCapacity);

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
 * Struktura reprezentująca czas postoju na parkingu
 */
typedef struct parkingTime {
    int hours;
    int minutes;
} ParkingTime;

/**
 * Rejestracja wjazdu pojazdu na parking
 * @param licencePlate - numer rejestracyjny pojazdu
 * @return true jeśli zarejestrowano wjazd, false jeśli brak miejsc
 */
bool registerVehicleEntry(LicencePlate licencePlate);

/**
 * Rejestracja wyjazdu pojazdu z parkingu
 * @param licencePlate - numer rejestracyjny pojazdu
 * @return true jeśli zarejestrowano wyjazd, false jeśli pojazd nie był na parkingu
 */
bool registerVehicleDeparture(LicencePlate licencePlate);

/**
 * Wyszukanie wpisu parkingowego na podstawie numeru rejestracyjnego pojazdu
 * @param licencePlate  - numer rejestracyjny pojazdu
 * @return wskaźnik na strukturę wpisu parkingowego jeśli znaleziono, NULL jeśli nie znaleziono
 */
ParkingEntry *findParkingEntry(LicencePlate licencePlate);

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
 * @return true jeśli pojazd jest na parkingu, false jeśli nie
 */
bool checkParkingVehicle(LicencePlate licencePlate);

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

/**
 * Wyliczenie czasu postoju pojazu
 * @param parkingEntry dane postoju pojazdu
 * @return czas postoju pojazdu
 */
ParkingTime calculateParkingTime(ParkingEntry *parkingEntry);

#endif
