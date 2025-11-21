#include "PGMImage.h"
#include <fstream>
#include <sstream>

PGMImage::PGMImage() : Image(), maxGrayValue(255) {}

PGMImage::PGMImage(int w, int h, int maxVal) : Image(w, h), maxGrayValue(maxVal) {
    data = new ColorValue*[height];
    for (unsigned int i = 0; i < height; ++i) {
        data[i] = new ColorValue[width](); // Only 1 byte per pixel for grayscale
    }
}

PGMImage::~PGMImage() {
    if (data) {
        for (unsigned int i = 0; i < height; ++i) {
            delete[] data[i];
        }
        delete[] data;
        data = nullptr;
    }
}

static bool isCommentOrEmpty(const std::string &line) {
    for (char c : line) {
        if (c == '#') return true;
        if (!isspace(static_cast<unsigned char>(c))) return false;
    }
    return true;
}

bool PGMImage::load(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) return false;

    std::string line;
    std::getline(file, line);
    if (line != "P5") return false;

    int newWidth = 0, newHeight = 0, newMax = 255;

    // Read width and height (skip comments)
    do {
        if (!std::getline(file, line)) return false;
    } while (isCommentOrEmpty(line));

    std::istringstream iss(line);
    if (!(iss >> newWidth >> newHeight)) {
        if (!(file >> newWidth >> newHeight)) return false;
    }

    // Read max gray value
    if (!(file >> newMax)) return false;
    if (newMax <= 0 || newMax >= 65536) return false;
    file.get(); // Skip single whitespace after maxval

    // Cleanup old image data
    ColorValue **oldData = data;
    unsigned int oldHeight = height;
    if (oldData) {
        for (unsigned int r = 0; r < oldHeight; ++r) delete[] oldData[r];
        delete[] oldData;
        data = nullptr;
    }

    width = newWidth;
    height = newHeight;
    maxGrayValue = newMax;

    // Allocate new data (1 byte per pixel for grayscale)
    data = new ColorValue*[height];
    for (unsigned int i = 0; i < height; ++i) {
        data[i] = new ColorValue[width];
    }

    // Read pixel data
    // If maxval < 256, each pixel is 1 byte, otherwise 2 bytes
    if (maxGrayValue < 256) {
        // 1 byte per pixel
        for (unsigned int r = 0; r < height; ++r) {
            file.read(reinterpret_cast<char*>(data[r]), width);
            if (!file) {
                for (unsigned int k = 0; k < height; ++k) delete[] data[k];
                delete[] data;
                data = nullptr;
                width = height = 0;
                return false;
            }
        }
    } else {
        // 2 bytes per pixel (most significant byte first)
        for (unsigned int r = 0; r < height; ++r) {
            for (unsigned int c = 0; c < width; ++c) {
                unsigned char byte1, byte2;
                file.read(reinterpret_cast<char*>(&byte1), 1);
                file.read(reinterpret_cast<char*>(&byte2), 1);
                if (!file) {
                    for (unsigned int k = 0; k < height; ++k) delete[] data[k];
                    delete[] data;
                    data = nullptr;
                    width = height = 0;
                    return false;
                }
                // Combine two bytes (MSB first) and scale to 8-bit
                unsigned int value = (byte1 << 8) | byte2;
                data[r][c] = static_cast<ColorValue>((value * 255) / maxGrayValue);
            }
        }
    }

    return true;
}

bool PGMImage::save(const std::string& filename) const {
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open() || !data) return false;

    file << "P5\n";
    file << width << " " << height << "\n";
    file << maxGrayValue << "\n";

    // Write pixel data
    // If maxval < 256, each pixel is 1 byte, otherwise 2 bytes
    if (maxGrayValue < 256) {
        // 1 byte per pixel
        for (unsigned int i = 0; i < height; ++i) {
            file.write(reinterpret_cast<const char*>(data[i]), width);
        }
    } else {
        // 2 bytes per pixel (most significant byte first)
        for (unsigned int i = 0; i < height; ++i) {
            for (unsigned int j = 0; j < width; ++j) {
                // Scale 8-bit value to maxGrayValue range and write as 2 bytes
                unsigned int value = (data[i][j] * maxGrayValue) / 255;
                unsigned char byte1 = (value >> 8) & 0xFF; // MSB
                unsigned char byte2 = value & 0xFF;        // LSB
                file.write(reinterpret_cast<const char*>(&byte1), 1);
                file.write(reinterpret_cast<const char*>(&byte2), 1);
            }
        }
    }

    return true;
}
