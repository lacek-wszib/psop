#ifndef VEHICLE_H
#define VEHICLE_H

/**
 * Typy definiujące dane pojazdu
 */
typedef char LicencePlate[16];
typedef char Brand[64];
typedef char Model[64];

/**
 * Struktura reprezentująca pojazd
 */
typedef struct vehicle {
    LicencePlate licencePlate;  // nr rejestracyjny
    Brand brand;                // marka
    Model model;                // model
} Vehicle;

/**
 * Struktura reprezentująca bazę pojazdów
 */
typedef struct vehicleDatabase {
    Vehicle *vehicles;
    int vehicleCount;
} VehicleDatabase;

/**
 * Inicjalizacja bazy pojazdów
 */
void initVehicleDatabase();

/**
 * Zwolnienie pamięci zaalokowanej dla bazy pojazdów
 */
void freeVehicleDatabase();

/**
 * Dodanie pojazdu do bazy
 * @param newVehicle - wskaźnik na strukturę pojazdu do dodania
 */
void addVehicle(Vehicle *newVehicle);

/**
 * Dodanie pojazdu do bazy i zapisanie go do pliku
 * @param newVehicle - wskaźnik na strukturę pojazdu do dodania
 */
void addVehicleAndSave(Vehicle *newVehicle);

/**
 * Usunięcie pojazdu z bazy
 * @param licencePlate - numer rejestracyjny pojazdu do usunięcia
 * @return 1 jeśli usunięto, 0 jeśli nie znaleziono pojazdu
 */
int removeVehicle(LicencePlate licencePlate);

/**
 * Sprawdzenie czy pojazd znajduje się w bazie
 * @param licencePlate - numer rejestracyjny pojazdu do sprawdzenia
 * @return 1 jeśli pojazd jest w bazie, 0 jeśli nie
 */
int checkVehicle(LicencePlate licencePlate);

/**
 * Wyszukanie pojazdu w bazie
 * @param licencePlate - numer rejestracyjny pojazdu do wyszukania
 * @return wskaźnik na strukturę pojazdu jeśli znaleziono, NULL jeśli nie znaleziono
 */
Vehicle *findVehicle(LicencePlate licencePlate);

/**
 * Pobranie bazy pojazdów
 * @return struktura zawierająca dane bazy pojazdów
 */
VehicleDatabase getVehicleDatabase();

/**
 * Wczytanie pojazdów z katalogu danych
 * @return liczba wczytanych pojazdów
 */
int loadVehicles();

#endif