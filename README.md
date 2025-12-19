# System parkingowy

Prosty system parkingowy umożliwiający obsługę rejestracji wjazdów i wyjazdów oraz innych podstawowych funkcji potrzebnych do obsługi parkingu.  

## 1. Funkcje 

* Rejestracja wjazdu na parking
* Rejestracja wyjazdu 
* Wyświetlenie listy samochodów na parkingu
* Zliczenie ilości wolnych/zajętych miejsc
* Możliwość definiowania i usuwania z bazy danych samochodu
* Zapis danych w plikach tekstowych
* Wczytanie stanu po ponownym uruchomieniu programu

## 2. Technologie

* język C
  
W programie wykorzystam tablice, struktury, wskaźniki i operacja na plikach.

## 3. Wymagania

* system operacyjny Linux

## 4. Kompilacja

Do kompilacji pod systemem Linux jest potrzebny zainstalowany kompilator C (np. GCC) oraz narzędziem CMake.<br>
Aby skompilować program przy użyciu polecenia `cmake` należy wykonac plecenia:
```
mkdir -p build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . -- -j$(nproc)
```
Czyszczenie plików build:
```
cmake --build . --target clean
```