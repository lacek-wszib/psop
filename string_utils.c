#include <ctype.h>
#include <stddef.h>
#include <string.h>

void toUpperCharArray(char s[]) {
    size_t size = sizeof s;
    for (size_t i = 0; i < size && s[i] != '\0'; ++i) {
        s[i] = (char) toupper((unsigned char) s[i]);
    }
}

void stringCopy(char *destination, char *source) {
    // kopiujemy maksymalnie długość ciągu docelowego
    strncpy(destination, source, sizeof(destination) - 1);
    // zakończenie znakiem \0 , jeżeli źródło było dłuższe niż cel
    if (strlen(source) >= sizeof(destination)) {
        destination[sizeof(destination) - 1] = '\0';
    }
}
