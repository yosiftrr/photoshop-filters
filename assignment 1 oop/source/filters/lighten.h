// Created by amir eltaher elsayed , 20242055 //

#pragma once
#include "../Image_Class.h"

inline void lightenFilter(Image& _img, int _percent) {
    double _f = 1.0 + _percent / 100.0;
    for (int _x = 0; _x < _img.width; _x++) {
        for (int _y = 0; _y < _img.height; _y++) {
            for (int c = 0; c < 3; c++) {
                int _v = (int)(_img(_x, _y, c) * _f);
                _img(_x, _y, c) = (_v > 255) ? 255 : _v;
            }
        }
    }
}
