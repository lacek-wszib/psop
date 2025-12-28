#include <ctype.h>
#include <stddef.h>

void toUpperCharArray(char s[]) {
    size_t size = sizeof s;
    for (size_t i = 0; i < size && s[i] != '\0'; ++i) {
        s[i] = (char) toupper((unsigned char) s[i]);
    }
}
