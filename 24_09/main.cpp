#include <iostream>
#include <stdlib.h>

void zadanie1() {
    int x = 500;
    int y = 400;
    int z = 270;
    int krok = 10;
    int ***tab = new int **[x/krok];

    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    for (int i = 0; i < x/krok; i++) {
        tab[i] = new int*[y/krok];
        for (int j = 0; j < y/krok; j++) {
            tab[i][j] = new int[z/krok];
            for (int k = 0; k < z/krok; k++) {
                tab[i][j][k] = 18 + std::rand() % 8;
            }
        }
    }

    double maxAvg = 0;
    for (int i=0; i < x/krok; i++) {
        for (int j=0; j < y/krok; j++) {
            double sum = 0;
            for (int k=0; k < z/krok; k++) {
                sum += tab[i][j][k];
            }
            double avg = sum/(static_cast<double>(z)/krok);
            if (avg > maxAvg) {
                maxAvg = avg;
            }
        }
    }
    std::cout << "Max avg: " << maxAvg << std::endl;

    for (int i = 0; i < x/krok; i++) {
        for (int j = 0; j < y/krok; j++) {
            delete[] tab[i][j];
        }
        delete[] tab[i];
    }
    delete[] tab;
}

void zadanie2() {
    int x = 5000;
    int y = 4000;
    int** tab = new int *[x];

    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    for (int i = 0; i < x; ++i) {
        tab[i] = new int[y];
        for (int j = 0; j < y; ++j) {
            tab[i][j] = 1200 + std::rand() % 2300;
        }
    }

    long int area = 0;
    for (int i = 0; i < x - 1; i++) {
        for (int j = 0; j < y - 1; j++) {
            int h1 = tab[i][j];
            int h2 = tab[i+1][j];
            int h3 = tab[i][j+1];
            int h4 = tab[i+1][j+1];
        }
    }
    std::cout<<"Pole wynosi: "<<area/1000<<" kilometrów kwadratowych."<<std::endl;

    for (int i = 0; i < x; i++) {
        delete[] tab[i];
    }
    delete[] tab;
}

struct Punkt {
    int x,y;
};

void zadanie3_1() {
    int x = 5000, y = 4000;
    int** tab = new int*[x];
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    for (int i = 0; i < x; ++i) {
        tab[i] = new int[y];
        for (int j = 0; j < y; ++j)
            tab[i][j] = 1200 + std::rand() % 2300;
    }
    Punkt start, end;
    // random points from tab array
    start.x = std::rand() % x;
    start.y = std::rand() % y;
    end.x = std::rand() % x;
    end.y = std::rand() % y;




}

int main() {
    // int** tab = new int *[2];
    // for (int i = 0; i < 2; ++i) {
    //     tab[i] = new int[6];
    // }
    // for (int i = 0; i < 2; ++i) {
    //     for (int j = 0; j < 6; ++j) {
    //         tab[i][j] = i * 6 + j + 1; // Fill with values from 1 to 12
    //     }
    // }
    //
    // std::cout<<*(*tab+0)+0<<std::endl;

    // https://fraktal.faculty.wmi.amu.edu.pl/aplikacje_desktopowe/lab2.html
    std::cout<<"Zadanie 1:"<<std::endl;
    zadanie1();

    std::cout<<"Zadanie 2:"<<std::endl;
    zadanie2();
    return 0;
}