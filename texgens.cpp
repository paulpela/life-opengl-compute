#include <stdlib.h>
#include "texgens.h"

// TODO implement options:
// step size/rows skipped
// modulo
// color
// alpha
void texgenRandomBarcode(float* data, size_t width, size_t height) {
    int ncomponents = 4;

    for(size_t i = 0; i < height; i += 4) {
        for(size_t j = 0; j < width; ) {
            for(size_t n = 0; n < ncomponents - n; n++) {
                data[i * width * ncomponents + j * ncomponents + n] = 1.0f;
            }
            data[i * width * ncomponents + j * ncomponents + ncomponents - 1] = 1.0f;
            j += rand() % 4;
        }
    }
}

void texgenFractal1(float* data, int width, int height) {
    for(size_t y = 0; y < width; y++) {
        for(size_t x = 0; x < height; x++) {
            data[(x * height + y) * 4 + 0] = (float) ((x & y) & 0xff) / 255.0f;
            data[(x * height + y) * 4 + 1] = (float) ((x | y) & 0xff) / 255.0f;
            data[(x * height + y) * 4 + 2] = (float) ((x ^ y) & 0xff) / 255.0f;
            data[(x * height + y) * 4 + 3] = 1.0f;
        }
    }
}

