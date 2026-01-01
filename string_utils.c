#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

void toUpperCharArray(char string[], size_t size) {
    // walidacja parametrów wejściowych
    if (string == NULL) return;
    // zmiana wielkości znaku
    for (size_t i = 0; i < size && string[i] != '\0'; ++i) {
        string[i] = (char) toupper((unsigned char) string[i]);
    }
}

void stringCopy(char *destination, size_t dstSize, char *source) {
    // walidacja parametrów wejściowych
    if (destination == NULL || source == NULL || dstSize == 0) return;
    // kopiujemy maksymalnie długość ciągu docelowego
    strncpy(destination, source, dstSize - 1);
    // zakończenie znakiem \0, jeżeli źródło było dłuższe niż cel
    if (strlen(source) >= dstSize) {
        destination[dstSize - 1] = '\0';
    }
}

bool isAlphanumericOnly(const char *string) {
    // walidacja wejścia
    if (string == NULL) return 0;
    // sprawdzenie znaków w stringu
    for (size_t i = 0; string[i] != '\0'; i++) {
        if (!isalnum((unsigned char)string[i])) {
            return false; // string zawiera niedozwolone znaki
        }
    }
    return true;
}
