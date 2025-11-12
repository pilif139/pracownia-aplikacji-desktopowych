#include "PPMImage.h"
#include <fstream>
#include <sstream>

PPMImage::PPMImage() : width(0), height(0), maxColorValue(255), data(nullptr) {}

PPMImage::PPMImage(int w, int h, int maxVal) : width(w), height(h), maxColorValue(maxVal) {
    data = new unsigned char*[height];
    for (int i = 0; i < height; ++i) {
        data[i] = new unsigned char[width * 3]();
    }
}

PPMImage::~PPMImage() {
    if (data) {
        for (int i = 0; i < height; ++i) {
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

bool PPMImage::loadPPM(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) return false;
    std::string line;

    std::getline(file, line);
    if (line != "P3") return false;

    int newWidth = 0, newHeight = 0, newMax = 255;
    do {
        if (!std::getline(file, line)) return false;
    } while (isCommentOrEmpty(line));
    std::istringstream iss(line);
    if (!(iss >> newWidth >> newHeight)) {
        std::string rest;
        while (iss >> rest) {
        }
        if (!(file >> newWidth >> newHeight)) return false;
    }
    if (!(file >> newMax)) return false;
    file.get();

    // cleanup image loaded before
    unsigned char **oldData = data;
    int oldHeight = height;
    if (oldData) {
        for (int r = 0; r < oldHeight; ++r) delete[] oldData[r];
        delete[] oldData;
        data = nullptr;
    }

    width = newWidth;
    height = newHeight;
    maxColorValue = newMax;

    data = new unsigned char*[height];
    for (int i = 0; i < height; ++i) {
        data[i] = new unsigned char[width * 3];
    }

    int val;
    int idx = 0;
    const int expected = width * height * 3;
    while (idx < expected && (file >> val)) {
        int row = idx / (width * 3);
        int col = idx % (width * 3);
        data[row][col] = static_cast<unsigned char>(val);
        ++idx;
    }
    return (idx == expected);
}

bool PPMImage::savePPM(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open() || !data) return false;
    file << "P3\n";
    file << width << " " << height << "\n";
    file << maxColorValue << "\n";
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width * 3; ++j) {
            file << static_cast<int>(data[i][j]) << (((j + 1) % (width * 3) == 0) ? "\n" : " ");
        }
    }
    return true;
}

bool PPMImage::loadPPMBinary(const std::string& filename) {
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

    unsigned char **oldData = data;
    int oldHeight = height;
    if (oldData) {
        for (int r = 0; r < oldHeight; ++r) delete[] oldData[r];
        delete[] oldData;
        data = nullptr;
    }

    width = newWidth;
    height = newHeight;
    maxColorValue = newMax;

    data = new unsigned char*[height];
    for (int i = 0; i < height; ++i) {
        data[i] = new unsigned char[width * 3];
    }

    for (int r = 0; r < height; ++r) {
        file.read(reinterpret_cast<char*>(data[r]), width * 3);
        if (!file) {
            for (int k = 0; k < height; ++k) delete[] data[k];
            delete[] data;
            data = nullptr;
            width = height = 0;
            return false;
        }
    }
    return true;
}

bool PPMImage::savePPMBinary(const std::string& filename) const {
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open() || !data) return false;
    file << "P6\n";
    file << width << " " << height << "\n";
    file << maxColorValue << "\n";
    for (int i = 0; i < height; ++i) {
        file.write(reinterpret_cast<const char*>(data[i]), width * 3);
    }
    return true;
}
