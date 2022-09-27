#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

const uint8_t data[] =
        { 0x48, 0x65, 0x6C, 0x6C, 0x6F, 0x2C, 0x20, 0x57, 0x6F, 0x72, 0x6C, 0x64, 0x21 };

const char* filename = "binary-in-c.txt";

int main(void) {
    printf("Starting binary file write...\n");

    FILE* output_file = fopen(filename, "wb+");
    if (!output_file) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    fwrite(data, 1, sizeof data, output_file);
    printf("Done Writing!\n");
    fclose(output_file);

    FILE* in_file = fopen(filename, "rb");
    if (!in_file) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    struct stat sb;
    if (stat(filename, &sb) == -1) {
        perror("stat");
        exit(EXIT_FAILURE);
    }

    char* file_contents = malloc(sb.st_size);
    fread(file_contents, sb.st_size, 1, in_file);

    printf("read data in binary file: %s\n", file_contents);
    fclose(in_file);

    free(file_contents);
    exit(EXIT_SUCCESS);
}