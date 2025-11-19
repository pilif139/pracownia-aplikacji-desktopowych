//
// Created by Filip on 18/11/2025.
//

#ifndef ZADANIE05_11_CONTRASTTOOLS_H
#define ZADANIE05_11_CONTRASTTOOLS_H

#include <vector>

class ContrastTools {
public:
    // Linear contrast adjustment
    // contrast: value in range [-1.0, 1.0], where 0 = no change
    static void applyLinear(uint8_t** data, int width, int height, double contrast);

    // Logarithmic contrast adjustment
    // k: parameter > 0, larger k = stronger brightening of dark areas
    // Formula: out = log(1 + k*v) / log(1 + k), where v is normalized to [0,1]
    static void applyLogarithmic(uint8_t** data, int width, int height, double k);

    // Exponential contrast adjustment
    // k: parameter > 0, larger k = stronger emphasis on bright areas
    // Formula: out = (exp(k*v) - 1) / (exp(k) - 1), where v is normalized to [0,1]
    static void applyExponential(uint8_t** data, int width, int height, double k);
};

#endif //ZADANIE05_11_CONTRASTTOOLS_H

