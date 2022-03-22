#ifndef IMAGEPROCESSINGCORE_H
#define IMAGEPROCESSINGCORE_H

#include <QImage>


class ImageProcessingCore
{
public:
    ImageProcessingCore();

    void RgbToGray(QImage &);

    void RgbToBinary(QImage &);

    void RgbViaWaves(QImage &);

private:
    void calculateWaves(double **&, int, int, double&, double&);
};

#endif // IMAGEPROCESSINGCORE_H
