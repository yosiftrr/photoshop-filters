#include <algorithm>
#include <vector>
#include "Image_Class.h"

class OilPaintingFilter {
private:
    int rad;
    int lvl_count;

public:
    OilPaintingFilter(int r = 3, int levels = 20)
        : rad(std::max(0, r)),
          lvl_count(std::max(1, std::min(256, levels))) {}

    void apply(Image& img) {
        if (img.imageData == nullptr ||
            img.width <= 0 ||
            img.height <= 0 ||
            img.channels < 3) {
            return;
        }

        // Keep an unchanged copy as the source for every neighborhood.
        Image backup = img;

        const int width = img.width;
        const int height = img.height;

        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                std::vector<int> count_arr(lvl_count, 0);
                std::vector<int> r_sum(lvl_count, 0);
                std::vector<int> g_sum(lvl_count, 0);
                std::vector<int> b_sum(lvl_count, 0);

                for (int dy = -rad; dy <= rad; ++dy) {
                    for (int dx = -rad; dx <= rad; ++dx) {
                        const int curr_x = x + dx;
                        const int curr_y = y + dy;

                        if (curr_x < 0 || curr_x >= width ||
                            curr_y < 0 || curr_y >= height) {
                            continue;
                        }

                        const int red   = backup.getPixel(curr_x, curr_y, 0);
                        const int green = backup.getPixel(curr_x, curr_y, 1);
                        const int blue  = backup.getPixel(curr_x, curr_y, 2);

                        int intensity = ((red + green + blue) / 3) * lvl_count / 256;
                        intensity = std::min(intensity, lvl_count - 1);

                        ++count_arr[intensity];
                        r_sum[intensity] += red;
                        g_sum[intensity] += green;
                        b_sum[intensity] += blue;
                    }
                }

                int chosen_lvl = 0;
                int max_freq = 0;

                for (int i = 0; i < lvl_count; ++i) {
                    if (count_arr[i] > max_freq) {
                        max_freq = count_arr[i];
                        chosen_lvl = i;
                    }
                }

                if (max_freq > 0) {
                    img.setPixel(x, y, 0,
                        static_cast<unsigned char>(r_sum[chosen_lvl] / max_freq));
                    img.setPixel(x, y, 1,
                        static_cast<unsigned char>(g_sum[chosen_lvl] / max_freq));
                    img.setPixel(x, y, 2,
                        static_cast<unsigned char>(b_sum[chosen_lvl] / max_freq));
                }
            }
        }
    }
};
