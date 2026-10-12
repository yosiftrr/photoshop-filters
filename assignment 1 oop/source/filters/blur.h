#pragma once

#include "Image_Class.h"

// Blur filter: averages the pixels in a square neighborhood around each pixel.
// Keep this filter in its own file: filters/blur.h
inline void blurFilter(Image& img, int radius = 2) {
    if (radius < 1 || img.width <= 0 || img.height <= 0 || img.channels <= 0) {
        return;
    }

    Image original = img;

    for (int y = 0; y < img.height; ++y) {
        for (int x = 0; x < img.width; ++x) {
            for (int c = 0; c < img.channels; ++c) {
                long long sum = 0;
                int count = 0;

                for (int dy = -radius; dy <= radius; ++dy) {
                    for (int dx = -radius; dx <= radius; ++dx) {
                        const int nx = x + dx;
                        const int ny = y + dy;

                        if (nx >= 0 && nx < original.width &&
                            ny >= 0 && ny < original.height) {
                            sum += original.getPixel(nx, ny, c);
                            ++count;
                        }
                    }
                }

                if (count > 0) {
                    img.setPixel(x, y, c,
                                 static_cast<unsigned char>(sum / count));
                }
            }
        }
    }
}
