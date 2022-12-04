#ifndef LAB02CORE_H
#define LAB02CORE_H

#include <QPixmap>


class Lab02Core
{
public:
    Lab02Core();

    int** ZongSune(int** image, int width, int height);
    int** GetBaseMatrix(QImage image);

    int** FromZerosToRGB(int** image, int width, int height);

    int** CNMatrix(int** thin, int w, int h);

private:
    int cn(int** matrix3x3); // b8-a8
    int** firstStepZonge(int** image, int width, int height);
    int** secondtepZonge(int** image, int width, int height);
};

#endif // LAB02CORE_H
