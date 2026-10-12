#pragma once
#include "../Image_Class.h"

class InfraredFilter {
public:
    void apply(Image& img) {
        if (img.imageData == nullptr ||
            img.width <= 0 ||
            img.height <= 0 ||
            img.channels < 3) {
            return;
        }

        const size_t total = static_cast<size_t>(img.width) * img.height * img.channels;

        for (size_t index = 0; index + 2 < total; index += img.channels) {
            unsigned char red_val   = img.imageData[index];
            unsigned char green_val = img.imageData[index + 1];
            unsigned char blue_val  = img.imageData[index + 2];

            int calc_r = static_cast<int>(green_val * 1.5 + red_val * 0.5);
            if (calc_r > 255) calc_r = 255;

            int calc_g = 255 - static_cast<int>(red_val);
            if (calc_g < 0) calc_g = 0;

            int calc_b = 255 - static_cast<int>(blue_val);
            if (calc_b < 0) calc_b = 0;

            img.imageData[index]     = static_cast<unsigned char>(calc_r);
            img.imageData[index + 1] = static_cast<unsigned char>(calc_g);
            img.imageData[index + 2] = static_cast<unsigned char>(calc_b);
        }
    }
};
