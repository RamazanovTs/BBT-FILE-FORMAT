#include "bbtSrc.h"
#include "DynamicStringArray.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

void fillwidth(DynamicStringArray *Canvas, uint32_t width, uint32_t height);
Pixel* createPixels(DynamicStringArray *Canvas, uint32_t *outPixelCount);
void trimNewline(char *str);

int main() {
    printf("--- BBT monochrome image creator ---\n");
    printf("Black=>1\nWhite=>0\n");
    printf("type \"exit\" on new line to exit\n");
    printf("max width is 255\n");

    DynamicStringArray *Canvas = CreateStringArray();
    
    char buffer[256];
    fgets(buffer, 255, stdin);
    
    while (strcmp(buffer, "exit\n") != 0) {
        buffer[strcspn(buffer, "\n")] = 0;
        addString(Canvas, buffer);
        fgets(buffer, 255, stdin);
    }

    uint32_t height = getStringCount(Canvas);
    uint32_t width = 0;
    uint32_t counter = 0;

    for (size_t i = 0; i < height; i++) {
        counter = strlen(getString(Canvas, i));
        if (counter > width) {
            width = counter;
        }
    }

    printf("Canvas height: %d\n", height);
    printf("Canvas width: %d\n", width);

    fillwidth(Canvas, width, height);

    uint32_t pixelCount;
    Pixel *pixels = createPixels(Canvas, &pixelCount);
    if (pixels == NULL) {
        printf("Failed to create pixels.\n");
        return 1;
    }

    bbt_creator(width, height, 24, pixels);
    free(pixels);

    return 0;
}

void fillwidth(DynamicStringArray *Canvas, uint32_t width, uint32_t height) {
    for (size_t i = 0; i < height; i++) {
        char *original = (char*)getString(Canvas, i);
        uint32_t originalLength = strlen(original);

        if (original[originalLength - 1] == '\n') {
            originalLength--;
        }

        uint32_t gap = width - originalLength;
        if (gap > 0) {
            for (size_t j = originalLength; j < width; j++) {
                original[j] = '1';
            }
        }
        original[width] = '\0';
    }
}


Pixel* createPixels(DynamicStringArray *Canvas, uint32_t *outPixelCount) {
    uint32_t height = getStringCount(Canvas);
    uint32_t width = strlen(getString(Canvas, 0));
    *outPixelCount = width * height;

    Pixel *pixels = (Pixel *)malloc(*outPixelCount * sizeof(Pixel));
    if (!pixels) {
        perror("Memory allocation failed in createPixels");
        return NULL;
    }

    uint32_t pixelIndex = 0;
    for (size_t i = 0; i < height; i++) {
        const char *row = getString(Canvas, i);
        
        for (size_t j = 0; j < width; j++) {
            Pixel pixel;
            if (row[j] == '1') {
                pixel.r = 0;
                pixel.g = 0;
                pixel.b = 0;
            } else {
                pixel.r = 255;
                pixel.g = 255;
                pixel.b = 255;
            }

            pixels[pixelIndex++] = pixel;
        }
    }

    return pixels;
}

void trimNewline(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}
