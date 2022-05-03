#ifndef IMAGEPROCESSINGCORE_H
#define IMAGEPROCESSINGCORE_H

#include <QImage>

class ImageProcessingCore
{
public:
    ImageProcessingCore();

    double** RgbToGray(QImage &);

    double** RgbToBinary(QImage &);

    double** RgbViaWaves(QImage &);

    double** S8Binarisation(QImage &);

    double** GlobalBinarisation(QImage &, int);

    double** RedMatrix(QImage &);
    double** GreenMatrix(QImage &);
    double** BlueMatrix(QImage &);

    double** MinMaxGrayImage(QImage &);


private:
    void calculateWaves(double **&, int, int, double&, double&);
};

#endif // IMAGEPROCESSINGCORE_H
