// made by ali mohammed salah , 20242221 //

#pragma once
#include "Image_Class.h"
#include <utility>

inline void flipFilter(Image& _img, char _dir) {
    if (_dir == 'h') {
        for (int _x = 0; _x < _img.width / 2; _x++) {
            for (int _y = 0; _y < _img.height; _y++) {
                for (int c = 0; c < 3; c++)
                    std::swap(_img(_x, _y, c), _img(_img.width - 1 - _x, _y, c));
            }
        }
    } else {
        for (int _x = 0; _x < _img.width; _x++) {
            for (int _y = 0; _y < _img.height / 2; _y++) {
                for (int c = 0; c < 3; c++)
                    std::swap(_img(_x, _y, c), _img(_x, _img.height - 1 - _y, c));
            }
        }
    }
}
