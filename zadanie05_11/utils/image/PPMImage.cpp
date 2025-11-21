#include "PPMImage.h"
#include <fstream>
#include <sstream>

PPMImage::PPMImage() : Image(), maxColorValue(255) {}

PPMImage::PPMImage(int w, int h, int maxVal) : Image(w, h), maxColorValue(maxVal) {
    data = new ColorValue*[height];
    for (unsigned int i = 0; i < height; ++i) {
        data[i] = new ColorValue[width * 3]();
    }
}

PPMImage::~PPMImage() {
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

bool PPMImage::load(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) return false;
    std::string line;
    std::getline(file, line);
    if (line != "P6") return false;

    int newWidth = 0, newHeight = 0, newMax = 255;

    do {
        if (!std::getline(file, line)) return false;
    } while (isCommentOrEmpty(line));
    std::istringstream iss(line);
    if (!(iss >> newWidth >> newHeight)) {
        if (!(file >> newWidth >> newHeight)) return false;
    }
    if (!(file >> newMax)) return false;
    file.get();

    // cleanup image loaded before
    ColorValue **oldData = data;
    unsigned int oldHeight = height;
    if (oldData) {
        for (unsigned int r = 0; r < oldHeight; ++r) delete[] oldData[r];
        delete[] oldData;
        data = nullptr;
    }

    width = newWidth;
    height = newHeight;
    maxColorValue = newMax;

    data = new ColorValue*[height];
    for (unsigned int i = 0; i < height; ++i) {
        data[i] = new ColorValue[width * 3];
    }

    for (unsigned int r = 0; r < height; ++r) {
        file.read(reinterpret_cast<char*>(data[r]), width * 3);
        if (!file) {
            for (unsigned int k = 0; k < height; ++k) delete[] data[k];
            delete[] data;
            data = nullptr;
            width = height = 0;
            return false;
        }
    }
    return true;
}

bool PPMImage::save(const std::string& filename) const {
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open() || !data) return false;
    file << "P6\n";
    file << width << " " << height << "\n";
    file << maxColorValue << "\n";
    for (unsigned int i = 0; i < height; ++i) {
        file.write(reinterpret_cast<const char*>(data[i]), width * 3);
    }
    return true;
}


