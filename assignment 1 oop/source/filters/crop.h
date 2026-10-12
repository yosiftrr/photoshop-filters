// made by youssef tamer , 20242405 //

#pragma once
#include "../Image_Class.h"

inline bool cropFilter(Image& _img, int _x0, int _y0, int _w, int _h) {
    if (_x0 < 0 || _y0 < 0 || _w <= 0 || _h <= 0) return false;
    if (_x0 + _w > _img.width || _y0 + _h > _img.height) return false;
    Image _res(_w, _h);
    for (int _x = 0; _x < _w; _x++)
        for (int _y = 0; _y < _h; _y++)
            for (int c = 0; c < 3; c++)
                _res(_x, _y, c) = _img(_x0 + _x, _y0 + _y, c);
    _img = _res;
    return true;
}
