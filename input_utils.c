#include <stdio.h>
#include <string.h>

int readLineFromInput(char *buffor, size_t bufsize, FILE *stream) {
    // walidacja parametrów wejściowych
    if (buffor == NULL || bufsize == 0 || stream == NULL) return 0;
    // wczytanie danych do bufora
    if (fgets(buffor, bufsize, stream)) {
        if (strchr(buffor, '\n') == NULL) {
            // dane nie zmieściły się w buforze
            int c;
            while ((c = fgetc(stream)) != EOF && c != '\n'); // opróżnienie strumienia
        } else {
            // usunięcie znaku nowej linii
            buffor[strcspn(buffor, "\n")] = '\0';
        }
        return 1;
    }
    return 0;
}
