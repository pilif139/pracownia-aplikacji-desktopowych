#include "PBMImage.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

PBMImage::PBMImage() : Image() {}

PBMImage::PBMImage(int w, int h) : Image(w, h) {
    data = new ColorValue*[height];
    for (unsigned int i = 0; i < height; ++i) {
        data[i] = new ColorValue[width](); // 1 byte per pixel (0 or 255)
    }
}

PBMImage::~PBMImage() {
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

bool PBMImage::load(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) return false;

    std::string line;
    std::getline(file, line);
    if (line != "P4") return false;

    int newWidth = 0, newHeight = 0;

    // Read width and height (skip comments)
    do {
        if (!std::getline(file, line)) return false;
    } while (isCommentOrEmpty(line));

    std::istringstream iss(line);
    if (!(iss >> newWidth >> newHeight)) {
        if (!(file >> newWidth >> newHeight)) return false;
    }

    file.get(); // Skip single whitespace

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

    // Allocate new data
    data = new ColorValue*[height];
    for (unsigned int i = 0; i < height; ++i) {
        data[i] = new ColorValue[width];
    }

    // Read packed bit data
    // Each row is packed into bytes (8 pixels per byte)
    unsigned int bytesPerRow = (width + 7) / 8;
    std::vector<unsigned char> rowBuffer(bytesPerRow);

    for (unsigned int r = 0; r < height; ++r) {
        file.read(reinterpret_cast<char*>(rowBuffer.data()), bytesPerRow);
        if (!file && !file.eof()) {
            for (unsigned int k = 0; k < height; ++k) delete[] data[k];
            delete[] data;
            data = nullptr;
            width = height = 0;
            return false;
        }

        // Unpack bits to pixels (0 = white = 255, 1 = black = 0)
        for (unsigned int c = 0; c < width; ++c) {
            unsigned int byteIdx = c / 8;
            unsigned int bitIdx = 7 - (c % 8);
            bool bit = (rowBuffer[byteIdx] >> bitIdx) & 1;
            data[r][c] = bit ? 0 : 255; // 1=black=0, 0=white=255
        }
    }

    return true;
}

bool PBMImage::save(const std::string& filename) const {
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open() || !data) return false;

    file << "P4\n";
    file << width << " " << height << "\n";

    // Write packed bit data
    unsigned int bytesPerRow = (width + 7) / 8;
    std::vector<unsigned char> rowBuffer(bytesPerRow);

    for (unsigned int i = 0; i < height; ++i) {
        // Clear buffer
        std::fill(rowBuffer.begin(), rowBuffer.end(), 0);

        // Pack pixels into bits (threshold at 128)
        for (unsigned int j = 0; j < width; ++j) {
            unsigned int byteIdx = j / 8;
            unsigned int bitIdx = 7 - (j % 8);
            // If pixel < 128, it's black (bit = 1), else white (bit = 0)
            if (data[i][j] < 128) {
                rowBuffer[byteIdx] |= (1 << bitIdx);
            }
        }

        file.write(reinterpret_cast<const char*>(rowBuffer.data()), bytesPerRow);
    }

    return true;
}