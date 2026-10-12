#pragma once
#include "../Image_Class.h"

class MergeFilter {
public:
    // Returns false if the images can't be merged
    bool apply(Image& first_img, const Image& second_img, float ratio) {
        if (first_img.imageData == nullptr || second_img.imageData == nullptr) return false;
        if (ratio < 0.0f || ratio > 1.0f) return false;
        if (first_img.width != second_img.width ||
            first_img.height != second_img.height ||
            first_img.channels != second_img.channels) {
            return false;
        }

        const size_t total = static_cast<size_t>(first_img.width) * first_img.height * first_img.channels;

        for (size_t k = 0; k < total; k++) {
            float blended = first_img.imageData[k] * ratio +
                            second_img.imageData[k] * (1.0f - ratio);
            if (blended > 255.0f) blended = 255.0f;
            if (blended < 0.0f) blended = 0.0f;

            first_img.imageData[k] = static_cast<unsigned char>(blended);
        }
        return true;
    }
};
