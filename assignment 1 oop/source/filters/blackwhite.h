// made by youssef tamer , 20242405 //

#pragma once
#include "../Image_Class.h"

inline void blackWhiteFilter(Image& _img) {
    for (int _x = 0; _x < _img.width; _x++) {
        for (int _y = 0; _y < _img.height; _y++) {
            int _sum = 0;
            for (int c = 0; c < 3; c++) _sum += _img(_x, _y, c);
            unsigned char _v = (_sum / 3 >= 128) ? 255 : 0;
            for (int c = 0; c < 3; c++) _img(_x, _y, c) = _v;
        }
    }
}
