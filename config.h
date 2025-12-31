#ifndef CONFIG_H
#define CONFIG_H
#include <sys/stat.h>
#include <stdbool.h>

extern const char *VEHICLES_DATA_DIR_NAME;
extern const char *PARKING_DATA_DIR_NAME;
extern const mode_t DATA_DIR_MODE;

/**
 * Pobranie ilości miejsc parkingowych
 * @return ilość miejsc parkingowych
 */
int getParkingCapacity();

/**
 * Ustawienie ilości miejsc parkingowych
 * @param newParkingCapacity - nowa ilość miejsc parkingowych
 */
void setParkingCapacity(int newParkingCapacity);

/**
 * Wczytanie konfiguracji
 * @return true jeśli wczytano, false jeśli wystąpił błąd
 */
bool loadConfig();

/**
 * Zapisanie konfiguracji
 * @return true jeśli zapisano, false jeśli wystąpił błąd
 */
bool saveConfig();

/**
 * Utworzenie katalogów potrzebnych do działania programu
 */
void createDirectories();

#endif