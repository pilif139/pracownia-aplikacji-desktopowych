//
// Created by Filip on 18/11/2025.
//

#include "ContrastTools.h"
#include <cmath>
#include <algorithm>

void ContrastTools::applyLinear(uint8_t** data, int width, int height, double contrast) {
    if (!data || width <= 0 || height <= 0) return;
    contrast = std::clamp(contrast, -1.0, 1.0); // std::clamp zwraca wartość lub najbliższą wartość w zakresie

    // Standard contrast formula: f(x) = factor * (x - 128) + 128
    // factor = (259 * (contrast*255 + 255)) / (255 * (259 - contrast*255))
    double c255 = contrast * 255.0;
    double factor = (259.0 * (c255 + 255.0)) / (255.0 * (259.0 - c255));

    int rowSize = width * 3;
    for (int r = 0; r < height; ++r) {
        uint8_t* row = data[r];
        for (int c = 0; c < rowSize; ++c) {
            int v = row[c];
            int out = static_cast<int>(std::round(factor * (v - 128) + 128));
            row[c] = static_cast<uint8_t>(std::clamp(out, 0, 255));
        }
    }
}

void ContrastTools::applyLogarithmic(uint8_t** data, int width, int height, double k) {
    if (!data || width <= 0 || height <= 0 || k <= 0.0) return;

    double denom = std::log1p(k); // log(1 + k)
    int rowSize = width * 3;

    for (int r = 0; r < height; ++r) {
        uint8_t* row = data[r];
        for (int c = 0; c < rowSize; ++c) {
            double v = static_cast<double>(row[c]) / 255.0; // normalize to [0,1]
            double mapped = std::log1p(k * v) / denom; // log mapping
            int out = static_cast<int>(std::round(mapped * 255.0));
            row[c] = static_cast<uint8_t>(std::clamp(out, 0, 255));
        }
    }
}

void ContrastTools::applyExponential(uint8_t** data, int width, int height, double k) {
    if (!data || width <= 0 || height <= 0 || k <= 1e-12) return;

    double expk = std::exp(k);
    double denom = expk - 1.0;
    int rowSize = width * 3;

    for (int r = 0; r < height; ++r) {
        uint8_t* row = data[r];
        for (int c = 0; c < rowSize; ++c) {
            double v = static_cast<double>(row[c]) / 255.0; // normalize to [0,1]
            double mapped = (std::exp(k * v) - 1.0) / denom; // exponential mapping
            int out = static_cast<int>(std::round(mapped * 255.0));
            row[c] = static_cast<uint8_t>(std::clamp(out, 0, 255));
        }
    }
}

