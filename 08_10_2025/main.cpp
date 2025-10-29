#include <iostream>

#include "PBMImage.h"
#include "PPMImage.h"

int main()
{
    PPMImage img(200, 200);
    unsigned char *data = img.getData();
    for (int y = 0; y < img.getHeight(); ++y)
    {
        for (int x = 0; x < img.getWidth(); ++x)
        {
            int idx = (y * img.getWidth() + x) * 3;
            data[idx] = x * 255 / img.getWidth();      // R: gradient poziomy
            data[idx + 1] = y * 255 / img.getHeight(); // G: gradient pionowy
            data[idx + 2] = 128;                       // B: stała wartość
        }
    }
    if (img.savePPM("test_ascii.ppm"))
    {
        std::cout << "Zapisano test_ascii.ppm (P3)" << std::endl;
    }

    if (img.savePPMBinary("test_bin.ppm"))
    {
        std::cout << "Zapisano test_bin.ppm (P6)" << std::endl;
    }

    PPMImage img2;
    if (img2.loadPPMBinary("test_bin.ppm"))
    {
        img2.savePPM("test_ascii_from_bin.ppm");
        std::cout << "Wczytano test_bin.ppm i zapisano jako test_ascii_from_bin.ppm" << std::endl;
    }
    else
    {
        std::cout << "Błąd wczytywania test_bin.ppm" << std::endl;
    }

    PBMImage pbm(100,100);
    bool** pbmData = pbm.getData();
    for (int y = 0; y < pbm.getHeight(); ++y) {
        for (int x=0; x < pbm.getWidth(); ++x) {
            pbmData[y][x] = ((x/3 + y/3) % 2 == 0);
        }
    }
    if (pbm.savePBM("test.pbm")) {
        std::cout << "Zapisano test.pbm" << std::endl;
    }else {
        std::cout<<"Błąd zapisywania test.pbm"<<std::endl;
    }
    if (pbm.loadPBM("test.pbm")) {
        std::cout<<"Pomyślnie wczytano test.pbm"<<std::endl;
    } else {
        std::cout<<"Błąd wczytywania test.pbm"<<std::endl;
    }
    return 0;
}
