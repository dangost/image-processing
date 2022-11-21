#ifndef LAB01MATRIX_H
#define LAB01MATRIX_H

#include <QImage>



class Lab01Matrix
{
public:
    Lab01Matrix();
    double** GetBaseMatrix(QImage image);
    double** Smezhnost(double** matrix, int w, int h);
    double** NormalizedMatrix(double** matrix);

    double enegry(double** matrix, int width, int height);
    double entropy(double** matrix, int width, int height);
    double contrast(double** matrix, int width, int height);
    double homo(double** matrix, int width, int height);

    double R_compare(double enegry1, double enegry2,
                     double entropy1, double entropy2,
                     double contrast1, double contrast2,
                     double homo1, double homo2);
};

#endif // LAB01MATRIX_H
