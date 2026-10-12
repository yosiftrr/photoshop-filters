// made by ali mohammed salah , 20242221 //

#pragma once
#include "../Image_Class.h"

inline void darkenFilter(Image& _img, int _percent) {
    double _f = 1.0 - _percent / 100.0;
    for (int _x = 0; _x < _img.width; _x++) {
        for (int _y = 0; _y < _img.height; _y++) {
            for (int c = 0; c < 3; c++) _img(_x, _y, c) = (unsigned char)(_img(_x, _y, c) * _f);
        }
    }
}
