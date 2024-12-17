#include <stdio.h>
#include <stdlib.h>

int read_file(const char *filename, char **buffer)
{
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("fopen");
        return 1;
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    *buffer = malloc(length + 1);
    if (*buffer == NULL) {
        fclose(file);
        return 1;
    }

    fread(*buffer, 1, length, file);
    fclose(file);
    (*buffer)[length] = '\0';

    return 0;
}