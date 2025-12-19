#ifndef INPUT_UTILS_H
#define INPUT_UTILS_H

/**
 * Zczytanie linii tekstu ze strumienia wejściowego
 *
 * @param buf - wskaźnik na bufor do przechowywania wczytanej linii
 * @param stream - strumień wejściowy
 * @return 1 jeśli wczytano linię, 0 w przeciwnym wypadku
 */
int readLineFromInput(char *buf, FILE *stream);

#endif
