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

private:
    void calculateWaves(double **&, int, int, double&, double&);
};

#endif // IMAGEPROCESSINGCORE_H
