//
// Created by Filip on 18/11/2025.
//

#include "ContrastTools.h"
#include <cmath>
#include <algorithm>
#include <QColor>

int getLinearContrast(int colorValue , double factor) {
    return qBound(0, static_cast<int>(std::round(factor * (colorValue - 128) + 128)), 255);
}

void ContrastTools::applyLinear(QImage& image, double contrast) {
    if (image.isNull()) return;
    contrast = std::clamp(contrast, -1.0, 1.0);

    // Standard contrast formula: f(x) = factor * (x - 128) + 128
    double c255 = contrast * 255.0;
    double factor = (259.0 * (c255 + 255.0)) / (255.0 * (259.0 - c255));

    std::array<int, 256> lookupTable = {};

    for (int y = 0; y < image.height(); ++y) {
        for (int x = 0; x < image.width(); ++x) {
            QColor color = image.pixelColor(x, y);
            int nr;
            int ng;
            int nb;

            if (lookupTable[color.red()] != 0) {
                nr = lookupTable[color.red()];
            } else {
                nr = getLinearContrast(color.red(), factor);
                lookupTable[color.red()] = nr;
            }
            if (lookupTable[color.green()] != 0) {
                ng = lookupTable[color.green()];
            } else {
                ng = getLinearContrast(color.green(), factor);
                lookupTable[color.green()] = ng;
            }
            if (lookupTable[color.blue()] != 0) {
                nb = lookupTable[color.blue()];
            } else {
                nb = getLinearContrast(color.blue(), factor);
                lookupTable[color.blue()] = nb;
            }

            image.setPixelColor(x, y, QColor(nr, ng, nb));
        }
    }
}

void ContrastTools::applyLogarithmic(QImage& image, double k) {
    if (image.isNull() || k <= 0.0) return;

    double denom = std::log1p(k); // log(1 + k)

    for (int y = 0; y < image.height(); ++y) {
        for (int x = 0; x < image.width(); ++x) {
            QColor color = image.pixelColor(x, y);

            double r = color.red() / 255.0;
            double g = color.green() / 255.0;
            double b = color.blue() / 255.0;

            int nr = qBound(0, static_cast<int>(std::round(std::log1p(k * r) / denom * 255.0)), 255);
            int ng = qBound(0, static_cast<int>(std::round(std::log1p(k * g) / denom * 255.0)), 255);
            int nb = qBound(0, static_cast<int>(std::round(std::log1p(k * b) / denom * 255.0)), 255);

            image.setPixelColor(x, y, QColor(nr, ng, nb));
        }
    }
}

void ContrastTools::applyExponential(QImage& image, double k) {
    if (image.isNull() || k <= 1e-12) return;

    double expk = std::exp(k);
    double denom = expk - 1.0;

    for (int y = 0; y < image.height(); ++y) {
        for (int x = 0; x < image.width(); ++x) {
            QColor color = image.pixelColor(x, y);

            double r = color.red() / 255.0;
            double g = color.green() / 255.0;
            double b = color.blue() / 255.0;

            int nr = qBound(0, static_cast<int>(std::round((std::exp(k * r) - 1.0) / denom * 255.0)), 255);
            int ng = qBound(0, static_cast<int>(std::round((std::exp(k * g) - 1.0) / denom * 255.0)), 255);
            int nb = qBound(0, static_cast<int>(std::round((std::exp(k * b) - 1.0) / denom * 255.0)), 255);

            image.setPixelColor(x, y, QColor(nr, ng, nb));
        }
    }
}

