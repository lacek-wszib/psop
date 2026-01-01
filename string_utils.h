#ifndef STRING_UTILS_H
#define STRING_UTILS_H

/**
 * Konwersja wszystkich liter w tablicy znaków na wielkie litery
 * @param string - tablica znaków do konwersji
 * @param size - rozmiar tablicy znaków
 */
void toUpperCharArray(char string[], size_t size);

/**
 * Bezpieczne kopiowanie ciągów znaków pomiędzy tablicami o różnych rozmiarach
 * @param destination docelowy ciąg znaków
 * @param dstSize rozmiar docelowego ciągu znaków
 * @param source źródłowy ciąg znaków
 */
void stringCopy(char *destination, size_t dstSize, char *source);

/**
 * Sprawdzenie czy ciąg znaków zawiera tylko znaki alfanumeryczne
 * @param string  - ciąg znaków do sprawdzenia
 * @return true jeśli ciąg zawiera tylko znaki alfanumeryczne, false w przeciwnym wypadku
 */
bool isAlphanumericOnly(const char *string);

#endif
