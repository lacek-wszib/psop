#ifndef VEHICLE_H
#define VEHICLE_H

/**
 * Typ definiujący numer rejestracyjny pojazdu
 */
typedef char LicencePlate[16];

/**
 * Struktura reprezentująca pojazd
 */
typedef struct vehicle {
    LicencePlate licencePlate;  // nr rejestracyjny
    char brand[64];             // marka
    char model[64];             // model
    char colour[64];            // kolor
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
 * Pobranie bazy pojazdów
 * @return struktura zawierająca dane bazy pojazdów
 */
VehicleDatabase getVehicleDatabase();

#endif