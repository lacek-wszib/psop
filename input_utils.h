#ifndef INPUT_UTILS_H
#define INPUT_UTILS_H
#include <stdbool.h>

/**
 * Zczytanie linii tekstu ze strumienia wejściowego
 * @param buffor - wskaźnik na bufor do przechowywania wczytanej linii
 * @param bufsize - rozmiar bufora
 * @param stream - strumień wejściowy
 * @return true jeśli wczytano linię, false jeśli błąd
 */
bool readLineFromInput(char *buffor, size_t bufsize, FILE *stream);

#endif
