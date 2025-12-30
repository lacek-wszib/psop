#ifndef STRING_UTILS_H
#define STRING_UTILS_H

/**
 * Konwersja wszystkich liter w tablicy znaków na wielkie litery
 * @param s - tablica znaków do konwersji
 */
void toUpperCharArray(char string[], size_t size);

/**
 * Kopiowanie ciągów znaków pomiędzy tablicami o różnych rozmiarach
 * @param destination docelowy ciąg znaków
 * @param source źródłowy ciąg znaków
 */
void stringCopy(char *destination, size_t dstSize, char *source);

#endif