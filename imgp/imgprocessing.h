#ifndef IMAGEPROCESSINGCORE_H
#define IMAGEPROCESSINGCORE_H

#include <QImage>
#include <QVector2D>
#include <QTableWidget>

class ImageProcessingCore
{
public:
    ImageProcessingCore();

    double** MatrixOfSimilarity(QImage &);

    double** RgbToGray(QImage &);

    double** RgbToBinary(QImage &);

    double** RgbViaWaves(QImage &);

    double** S8Binarisation(QImage &);

    double** GlobalBinarisation(QImage &, int);

    double** RedMatrix(QImage &);
    double** GreenMatrix(QImage &);
    double** BlueMatrix(QImage &);

    double** MinMaxGrayImage(QImage &);

    double** Filter(QImage &);

    double** Unlocking(QImage &, int[]);

    double** Erosion(QImage &, int[]);
    double** Extenstion(QImage &, int[], double **&);



private:
    void calculateWaves(double **&, int, int, double&, double&);


    int* bubbleSort(int* &, int);
};

#endif // IMAGEPROCESSINGCORE_H
