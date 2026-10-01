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
    cout << "10. Save the image\n";
    cout << "11. Exit\n";
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
            saveImageFile(_img, _currentName);
        } else if (_choice == 11) {
            if (askSave()) saveImageFile(_img, _currentName);
            break;
        } else {
            cout << "Invalid choice.\n";
        }
    }
    return 0;
}
