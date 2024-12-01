#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct
{
    uint32_t signature;
    uint32_t width;
    uint32_t height;
    uint32_t depth;
} Header;

typedef struct
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
} Pixel;

void bbt_creator(uint32_t width, uint32_t height, uint32_t depth, Pixel *pixels) {
    if (depth != 24) {
        printf("Only 24-bit (RGB) model is supported.\n");
        return;
    }

    FILE *file = fopen("image.bbt", "wb");
    if (!file) {
        perror("Failed to create file");
        return;
    }

    Header header = {0x42425400, width, height, depth};
    fwrite(&header, sizeof(Header), 1, file);

    if (!pixels) {
        perror("Memory allocation failed");
        fclose(file);
        return;
    }

    fwrite(pixels, sizeof(Pixel), width * height, file);
    free(pixels);
    fclose(file);
}
