// Created by amir eltaher elsayed , 20242055 //

#pragma once
#include "../Image_Class.h"

inline void rotateFilter(Image& _img, int _angle) {
    int _w = _img.width, _h = _img.height;
    if (_angle == 180) {
        Image _res(_w, _h);
        for (int _x = 0; _x < _w; _x++)
            for (int _y = 0; _y < _h; _y++)
                for (int c = 0; c < 3; c++)
                    _res(_w - 1 - _x, _h - 1 - _y, c) = _img(_x, _y, c);
        _img = _res;
    } else if (_angle == 90) {
        Image _res(_h, _w);
        for (int _x = 0; _x < _w; _x++)
            for (int _y = 0; _y < _h; _y++)
                for (int c = 0; c < 3; c++)
                    _res(_h - 1 - _y, _x, c) = _img(_x, _y, c);
        _img = _res;
    } else if (_angle == 270) {
        Image _res(_h, _w);
        for (int _x = 0; _x < _w; _x++)
            for (int _y = 0; _y < _h; _y++)
                for (int c = 0; c < 3; c++)
                    _res(_y, _w - 1 - _x, c) = _img(_x, _y, c);
        _img = _res;
    }
}
