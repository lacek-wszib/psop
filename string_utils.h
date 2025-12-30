#ifndef STRING_UTILS_H
#define STRING_UTILS_H

/**
 * Konwersja wszystkich liter w tablicy znaków na wielkie litery
 * @param s - tablica znaków do konwersji
 */
void toUpperCharArray(char s[]);

/**
 * Kopiowanie ciągów znaków pomiędzy tablicami o różnych rozmiarach
 * @param destination docelowy ciąg znaków
 * @param source źródłowy ciąg znaków
 */
void stringCopy(char *destination, char *source);

#endif