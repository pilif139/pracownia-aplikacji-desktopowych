#include <iostream>
#include "Image.h"

int main() {
    Image img(200, 200);
    unsigned char* data = img.getData();
    for (int y = 0; y < img.getHeight(); ++y) {
        for (int x = 0; x < img.getWidth(); ++x) {
            int idx = (y * img.getWidth() + x) * 3;
            data[idx] = x * 255 / img.getWidth();      // R: gradient poziomy
            data[idx + 1] = y * 255 / img.getHeight(); // G: gradient pionowy
            data[idx + 2] = 128;                       // B: stała wartość
        }
    }
    if (img.savePPM("test_ascii.ppm")) {
        std::cout << "Zapisano test_ascii.ppm (P3)" << std::endl;
    }

    if (img.savePPMBinary("test_bin.ppm")) {
        std::cout << "Zapisano test_bin.ppm (P6)" << std::endl;
    }

    Image img2;
    if (img2.loadPPMBinary("test_bin.ppm")) {
        img2.savePPM("test_ascii_from_bin.ppm");
        std::cout << "Wczytano test_bin.ppm i zapisano jako test_ascii_from_bin.ppm" << std::endl;
    } else {
        std::cout << "Błąd wczytywania test_bin.ppm" << std::endl;
    }
    return 0;
}
