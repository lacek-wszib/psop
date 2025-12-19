#include <stdio.h>
#include <string.h>

int readLineFromInput(char *buffor, FILE *stream) {
    // wczytanie danych do bufora
    if (fgets(buffor, sizeof buffor, stdin)) {
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
