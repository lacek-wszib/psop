# Przyjazny System Obsługi Parkingu (PSOP)

Projekt zaliczeniowy z Podstaw Informatyki - I semestr Informatyki.

## 1. Funkcje 

* Rejestracja wjazdu na parking
* Rejestracja wyjazdu i zliczenie czasu postoju
* Wyświetlenie listy samochodów na parkingu
* Zliczenie ilości wolnych i zajętych miejsc
* Możliwość definiowania i usuwania pojazdów w bazie pojazdów
* Zapis bazy danych pojazdów i zajętych miejsc w plikach tekstowych
* Wczytanie bazy pojazdów i zajętości parkingu przy uruchomieniu programu
* Zapis i odczyt konfiguracji

## 2. Technologie

* język C

W programie wykorzystane są tablice, struktury, wskaźniki, dynamiczna alokacja pamięci, operacje na plikach, podstawowe operacje na łańcuchach znaków oraz obsługa błędów.

## 3. Wymagania

* system operacyjny: `Linux`
* kompilator C (zalecany `gcc`)
* narzędzia budowania: `CMake` 4+ oraz `make` lub `ninja`

## 4. Struktura plików źródłowych

### Pliki główne
* `main.c` - punkt wejścia programu, wczytanie konfiguracji i danych oraz wywołanie głównego menu
* `main_menu.c` - obsługa menu głównego aplikacji i główna pętla programu

### Moduły funkcjonalne
* `parking.c` - logika zarządzania parkingiem (wjazd/wyjazd pojazdów, zliczanie wolnych miejsc)
* `vehicle.c` - operacje na bazie pojazdów (dodawanie, usuwanie, wyszukiwanie, zapis/odczyt)
* `config.c` - zarządzanie konfiguracją systemu (zmiana ustawień, zapis/odczyt)

### Moduły menu
* `vehicle_menu.c` - menu zarządzania bazą pojazdów
* `config_menu.c` - menu konfiguracji programu

### Moduły pomocnicze
* `input_utils.c` - funkcje do bezpiecznego wczytywania danych od użytkownika
* `string_utils.c` - funkcje pomocnicze do operacji na ciągach znaków

### Pliki budowania
* `CMakeLists.txt` - konfiguracja CMake do kompilacji projektu

## 5. Kompilacja

### 5.1. Kompilacja przy użyciu `cmake`

Do kompilacji pod systemem Linux jest potrzebny zainstalowany kompilator C (np. GCC) oraz narzędziem CMake.<br>
Aby skompilować program przy użyciu polecenia `cmake`, należy wykonać polecenia:
```bash
mkdir -p build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . -- -j$(nproc)
```
Czyszczenie plików build:
```bash
cmake --build . --target clean
```

### 5.2. Kompilacja przy użyciu `gcc`

Aby skompilować aplikacje przy użyciu `gcc` należy użyć standardu `gnu99` z uwagi na użyte funkcje z rozszerzenia GNU/POSIX.<br> 
```bash
gcc -std=gnu99 -Wall -Wextra -O2 \
    main.c main_menu.c parking.c vehicle.c config.c \
    vehicle_menu.c config_menu.c input_utils.c string_utils.c \
    -o psop
```

## 6. Uruchomienie
```bash
./psop
```

## 7. Użycie

Po programie porusza się za pomocą menu tekstowego. Wybór opcji odbywa się poprzez wpisanie odpowiedniej liczby i naciśnięcie klawisza Enter.<br>
Aby dokonać rejestracji wjazdu na parking należy najpierw w konfiguracji ustawić ilość dostępnych miejsca parkingowych.<br>
W programie dostępne są trzy menu:
* menu główne
* menu bazy pojazdów
* menu konfiguracji

## 8. Struktura katalogów

Przy pierwszym uruchomieniu programu zostaną utworzone katalogi w których są przechowywane dane programu w postaci plików tekstowych.

* config/ - katalog z plikami konfiguracyjnymi
* data/ - katalog z plikami z danymi
* data/vehicles/ - katalog z bazą pojazdów
* data/parking/ - katalog z zajętością parkingu