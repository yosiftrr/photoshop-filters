#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include "Image_Class.h"
#include "filters/grayscale.h"
#include "filters/blackwhite.h"
#include "filters/invert.h"
#include "filters/flip.h"
#include "filters/rotate.h"
#include "filters/darken.h"
#include "filters/lighten.h"
#include "filters/crop.h"
#include "filters/blur.h"
#include "filters/OilPaintingFilter.h"
#include "filters/infrared.h"
#include "filters/merge.h"

using namespace std;

bool validExtension(const string& _name) {
    size_t _p = _name.find_last_of('.');
    if (_p == string::npos) return false;
    string _e = _name.substr(_p);
    transform(_e.begin(), _e.end(), _e.begin(), ::tolower);
    return _e == ".jpg" || _e == ".jpeg" || _e == ".png" || _e == ".bmp";
}

bool fileExists(const string& _name) {
    ifstream _f(_name);
    return _f.good();
}

bool loadImageFile(Image& _img, string& _currentName) {
    string _name;
    cout << "Enter image file name: ";
    cin >> _name;
    if (!validExtension(_name)) {
        cout << "Invalid extension. Use .jpg, .jpeg, .png or .bmp\n";
        return false;
    }
    if (!fileExists(_name)) {
        cout << "File not found.\n";
        return false;
    }
    try {
        _img.loadNewImage(_name);
    } catch (...) {
        cout << "Could not load the image.\n";
        return false;
    }
    _currentName = _name;
    cout << "Image loaded.\n";
    return true;
}

void saveImageFile(Image& _img, const string& _currentName) {
    string _name = _currentName;
    char _c;
    cout << "Save on the same file? (y/n): ";
    cin >> _c;
    if (_c == 'n' || _c == 'N') {
        while (true) {
            cout << "Enter new file name: ";
            cin >> _name;
            if (validExtension(_name)) break;
            cout << "Invalid extension. Use .jpg, .jpeg, .png or .bmp\n";
        }
    }
    _img.saveImage(_name);
    cout << "Image saved as " << _name << "\n";
}

bool askSave() {
    char _c;
    cout << "Do you want to save the current image first? (y/n): ";
    cin >> _c;
    return _c == 'y' || _c == 'Y';
}

void showMenu() {
    cout << "\n===== Baby Photoshop =====\n";
    cout << "1. Load a new image\n";
    cout << "2. Grayscale\n";
    cout << "3. Black and White\n";
    cout << "4. Invert\n";
    cout << "5. Flip\n";
    cout << "6. Rotate\n";
    cout << "7. Darken\n";
    cout << "8. Lighten\n";
    cout << "9. Crop\n";
    cout << "10. Blur\n";
    cout << "11. Oil Painting\n";
    cout << "12. Infrared\n";
    cout << "13. Merge with another image\n";
    cout << "14. Save the image\n";
    cout << "15. Exit\n";
    cout << "Choice: ";
}

int main() {
    Image _img;
    string _currentName;

    while (!loadImageFile(_img, _currentName)) {}

    while (true) {
        showMenu();
        int _choice;
        if (!(cin >> _choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input.\n";
            continue;
        }

        if (_choice == 1) {
            if (askSave()) saveImageFile(_img, _currentName);
            loadImageFile(_img, _currentName);
        } else if (_choice == 2) {
            grayscaleFilter(_img);
        } else if (_choice == 3) {
            blackWhiteFilter(_img);
        } else if (_choice == 4) {
            invertFilter(_img);
        } else if (_choice == 5) {
            char _d;
            cout << "Flip horizontally (h) or vertically (v): ";
            cin >> _d;
            if (_d == 'h' || _d == 'H') flipFilter(_img, 'h');
            else if (_d == 'v' || _d == 'V') flipFilter(_img, 'v');
            else cout << "Invalid option.\n";
        } else if (_choice == 6) {
            int _a;
            cout << "Angle (90 / 180 / 270): ";
            cin >> _a;
            if (_a == 90 || _a == 180 || _a == 270) rotateFilter(_img, _a);
            else cout << "Invalid angle.\n";
        } else if (_choice == 7) {
            int _p;
            cout << "Darken percentage (0-100): ";
            cin >> _p;
            if (_p >= 0 && _p <= 100) darkenFilter(_img, _p);
            else cout << "Invalid percentage.\n";
        } else if (_choice == 8) {
            int _p;
            cout << "Lighten percentage (0-100): ";
            cin >> _p;
            if (_p >= 0 && _p <= 100) lightenFilter(_img, _p);
            else cout << "Invalid percentage.\n";
        } else if (_choice == 9) {
            int _x, _y, _w, _h;
            cout << "Start point x y: ";
            cin >> _x >> _y;
            cout << "Width and height: ";
            cin >> _w >> _h;
            if (!cropFilter(_img, _x, _y, _w, _h)) cout << "Invalid crop dimensions.\n";
        } else if (_choice == 10) {
            int radius;
            cout << "Blur radius (1-10): ";
            cin >> radius;
            if (radius >= 1 && radius <= 10) blurFilter(_img, radius);
            else cout << "Invalid radius.\n";
        } else if (_choice == 11) {
            int radius, levels;
            cout << "Oil painting radius (1-10): ";
            cin >> radius;
            cout << "Intensity levels (2-64): ";
            cin >> levels;
            if (radius >= 1 && radius <= 10 && levels >= 2 && levels <= 64) {
                OilPaintingFilter oilFilter(radius, levels);
                oilFilter.apply(_img);
                cout << "Oil painting filter applied.\n";
            } else {
                cout << "Invalid radius or levels.\n";
            }
        } else if (_choice == 12) {
            InfraredFilter infraredFilter;
            infraredFilter.apply(_img);
            cout << "Infrared filter applied.\n";
        } else if (_choice == 13) {
            string secondName;
            cout << "Enter second image file name: ";
            cin >> secondName;
            if (!validExtension(secondName) || !fileExists(secondName)) {
                cout << "Invalid image file name or file not found.\n";
                continue;
            }
            Image second;
            try {
                second.loadNewImage(secondName);
            } catch (...) {
                cout << "Could not load the second image.\n";
                continue;
            }
            float ratio;
            cout << "Blend ratio for current image (0.0-1.0): ";
            cin >> ratio;
            MergeFilter mergeFilter;
            if (!mergeFilter.apply(_img, second, ratio))
                cout << "Merge failed: images must have the same dimensions/channels and ratio must be 0-1.\n";
            else
                cout << "Images merged. Save to keep the result.\n";
        } else if (_choice == 14) {
            saveImageFile(_img, _currentName);
        } else if (_choice == 15) {
            if (askSave()) saveImageFile(_img, _currentName);
            break;
        } else {
            cout << "Invalid choice.\n";
        }
    }
    return 0;
}
