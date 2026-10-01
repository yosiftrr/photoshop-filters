// hussien ezzat hussien , 20242106 //

#pragma once
#include "../Image_Class.h"

inline void invertFilter(Image& _img) {
    for (int _x = 0; _x < _img.width; _x++) {
        for (int _y = 0; _y < _img.height; _y++) {
            for (int c = 0; c < 3; c++) _img(_x, _y, c) = 255 - _img(_x, _y, c);
        }
    }
}
