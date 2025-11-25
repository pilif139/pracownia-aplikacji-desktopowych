#include "PBMImage.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

PBMImage::PBMImage() : Image() {}

PBMImage::PBMImage(int w, int h) : Image(w, h) {
    data = new ColorValue*[height];
    for (unsigned int i = 0; i < height; ++i) {
        data[i] = new ColorValue[width]();
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

bool PBMImage::loadBinary(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) return false;

    std::string line;
    std::getline(file, line);
    if (line != "P4") return false;

    int newWidth = 0, newHeight = 0;

    do {
        if (!std::getline(file, line)) return false;
    } while (isCommentOrEmpty(line));

    std::istringstream iss(line);
    if (!(iss >> newWidth >> newHeight)) {
        if (!(file >> newWidth >> newHeight)) return false;
    }

    file.get();

    ColorValue **oldData = data;
    unsigned int oldHeight = height;
    if (oldData) {
        for (unsigned int r = 0; r < oldHeight; ++r) delete[] oldData[r];
        delete[] oldData;
        data = nullptr;
    }

    width = newWidth;
    height = newHeight;

    data = new ColorValue*[height];
    for (unsigned int i = 0; i < height; ++i) {
        data[i] = new ColorValue[width];
    }

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

        for (unsigned int c = 0; c < width; ++c) {
            unsigned int byteIdx = c / 8;
            unsigned int bitIdx = 7 - (c % 8);
            bool bit = (rowBuffer[byteIdx] >> bitIdx) & 1;
            data[r][c] = bit ? 0 : 255; // 1=black=0, 0=white=255
        }
    }

    return true;
}

bool PBMImage::saveBinary(const std::string& filename) const {
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open() || !data) return false;

    file << "P4\n";
    file << width << " " << height << "\n";

    unsigned int bytesPerRow = (width + 7) / 8;
    std::vector<unsigned char> rowBuffer(bytesPerRow);

    for (unsigned int i = 0; i < height; ++i) {
        std::fill(rowBuffer.begin(), rowBuffer.end(), 0);

        for (unsigned int j = 0; j < width; ++j) {
            unsigned int byteIdx = j / 8;
            unsigned int bitIdx = 7 - (j % 8);
            if (data[i][j] < 128) {
                rowBuffer[byteIdx] |= (1 << bitIdx);
            }
        }

        file.write(reinterpret_cast<const char*>(rowBuffer.data()), bytesPerRow);
    }

    return true;
}

bool PBMImage::loadAscii(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) return false;

    std::string line;
    std::getline(file, line);
    if (line != "P1") return false;

    int newWidth = 0, newHeight = 0;

    do {
        if (!std::getline(file, line)) return false;
    } while (isCommentOrEmpty(line));

    std::istringstream iss(line);
    if (!(iss >> newWidth >> newHeight)) {
        if (!(file >> newWidth >> newHeight)) return false;
    }

    ColorValue **oldData = data;
    unsigned int oldHeight = height;
    if (oldData) {
        for (unsigned int r = 0; r < oldHeight; ++r) delete[] oldData[r];
        delete[] oldData;
        data = nullptr;
    }

    width = newWidth;
    height = newHeight;

    data = new ColorValue*[height];
    for (unsigned int i = 0; i < height; ++i) {
        data[i] = new ColorValue[width];
    }

    int bit;
    for (unsigned int r = 0; r < height; ++r) {
        for (unsigned int c = 0; c < width; ++c) {
            if (!(file >> bit)) {
                for (unsigned int k = 0; k < height; ++k) delete[] data[k];
                delete[] data;
                data = nullptr;
                width = height = 0;
                return false;
            }
            data[r][c] = (bit == 1) ? 0 : 255;
        }
    }

    return true;
}

bool PBMImage::saveAscii(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open() || !data) return false;

    file << "P1\n";
    file << width << " " << height << "\n";

    for (unsigned int i = 0; i < height; ++i) {
        for (unsigned int j = 0; j < width; ++j) {
            int bit = (data[i][j] < 128) ? 1 : 0;
            file << bit;
            if (j < width - 1) {
                file << " ";
            }
        }
        file << "\n";
    }

    return true;
}
