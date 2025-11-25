#include "PGMImage.h"
#include <fstream>
#include <sstream>

PGMImage::PGMImage() : Image(), maxGrayValue(255) {}

PGMImage::PGMImage(int w, int h, int maxVal) : Image(w, h), maxGrayValue(maxVal) {
    data = new ColorValue*[height];
    for (unsigned int i = 0; i < height; ++i) {
        data[i] = new ColorValue[width]();
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

bool PGMImage::loadBinary(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) return false;

    std::string line;
    std::getline(file, line);
    if (line != "P5") return false;

    int newWidth = 0, newHeight = 0, newMax = 255;

    do {
        if (!std::getline(file, line)) return false;
    } while (isCommentOrEmpty(line));

    std::istringstream iss(line);
    if (!(iss >> newWidth >> newHeight)) {
        if (!(file >> newWidth >> newHeight)) return false;
    }

    if (!(file >> newMax)) return false;
    if (newMax <= 0 || newMax >= 65536) return false;
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
    maxGrayValue = newMax;

    data = new ColorValue*[height];
    for (unsigned int i = 0; i < height; ++i) {
        data[i] = new ColorValue[width];
    }

    if (maxGrayValue < 256) {
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
                unsigned int value = (byte1 << 8) | byte2;
                data[r][c] = static_cast<ColorValue>((value * 255) / maxGrayValue);
            }
        }
    }

    return true;
}

bool PGMImage::saveBinary(const std::string& filename) const {
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open() || !data) return false;

    file << "P5\n";
    file << width << " " << height << "\n";
    file << maxGrayValue << "\n";

    if (maxGrayValue < 256) {
        for (unsigned int i = 0; i < height; ++i) {
            file.write(reinterpret_cast<const char*>(data[i]), width);
        }
    } else {
        for (unsigned int i = 0; i < height; ++i) {
            for (unsigned int j = 0; j < width; ++j) {
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

bool PGMImage::loadAscii(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) return false;

    std::string line;
    std::getline(file, line);
    if (line != "P2") return false;

    int newWidth = 0, newHeight = 0, newMax = 255;

    do {
        if (!std::getline(file, line)) return false;
    } while (isCommentOrEmpty(line));

    std::istringstream iss(line);
    if (!(iss >> newWidth >> newHeight)) {
        if (!(file >> newWidth >> newHeight)) return false;
    }

    if (!(file >> newMax)) return false;
    if (newMax <= 0 || newMax >= 65536) return false;

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

    data = new ColorValue*[height];
    for (unsigned int i = 0; i < height; ++i) {
        data[i] = new ColorValue[width];
    }

    int val;
    for (unsigned int r = 0; r < height; ++r) {
        for (unsigned int c = 0; c < width; ++c) {
            if (!(file >> val)) {
                for (unsigned int k = 0; k < height; ++k) delete[] data[k];
                delete[] data;
                data = nullptr;
                width = height = 0;
                return false;
            }
            if (maxGrayValue == 255) {
                data[r][c] = static_cast<ColorValue>(val);
            } else {
                data[r][c] = static_cast<ColorValue>((val * 255) / maxGrayValue);
            }
        }
    }

    return true;
}

bool PGMImage::saveAscii(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open() || !data) return false;

    file << "P2\n";
    file << width << " " << height << "\n";
    file << maxGrayValue << "\n";

    for (unsigned int i = 0; i < height; ++i) {
        for (unsigned int j = 0; j < width; ++j) {
            int val;
            if (maxGrayValue == 255) {
                val = static_cast<int>(data[i][j]);
            } else {
                val = (static_cast<int>(data[i][j]) * maxGrayValue) / 255;
            }
            file << val;
            if (j < width - 1) {
                file << " ";
            }
        }
        file << "\n";
    }

    return true;
}
