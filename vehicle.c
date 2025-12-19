#include <stdio.h>
#include "vehicle.h"
#include <string.h>

Vehicle vehicles[100];
int vehicleCount = 0;

void addVehicle(Vehicle *newVehicle) {
    if (vehicleCount < 100) {
        vehicleCount++;
        vehicles[vehicleCount - 1] = *newVehicle;
        printf("Dodano do bazy pojazd o numerze rejestracyjnym %s\n", newVehicle->licencePlate);
    } else {
        printf("Baza pojazdów jest pełna, nie można dodać nowego pojazdu\n");
    }
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
