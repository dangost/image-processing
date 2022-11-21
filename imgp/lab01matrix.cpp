#include <math.h>
#include "lab01matrix.h"

Lab01Matrix::Lab01Matrix()
{

}

double Lab01Matrix::R_compare(double enegry1, double enegry2,
                 double entropy1, double entropy2,
                 double contrast1, double contrast2,
                 double homo1, double homo2)
{
    return std::sqrt(
                std::pow(enegry1-enegry2, 2) +
                std::pow(contrast1-contrast2, 2) +
                std::pow(entropy1-entropy2, 2) +
                std::pow(homo1-homo2, 2)
                );
}

double Lab01Matrix::enegry(double** matrix, int width, int height)
{
    double e = 0;

    for (int i = 0; i < width; i++)
        for(int j = 0; j < height; j++)
        {
            e += std::pow(matrix[i][j], 2);
        }
    return e;
}
double Lab01Matrix::entropy(double** matrix, int width, int height)
{
    double e = 0;
    for (int i = 0; i < width; i++)
        for(int j = 0; j < height; j++)
        {
            if (matrix[i][j] == 0.0)
            {
                continue;
            }
            e += (matrix[i][j] * std::log2(matrix[i][j]));
        }
    return e;
}
double Lab01Matrix::contrast(double** matrix, int width, int height)
{
    double e = 0;
    for (int i = 0; i < width; i++)
        for(int j = 0; j < height; j++)
        {
            e += std::pow(i-j, 2) * matrix[i][j];
        }
    return e;
}
double Lab01Matrix::homo(double** matrix, int width, int height)
{
    double e = 0;
    for (int i = 0; i < width; i++)
        for(int j = 0; j < height; j++)
        {
            e += matrix[i][j] /( 1 + std::abs(i-j));
        }
    return e;
}


double** Lab01Matrix::GetBaseMatrix(QImage image)
{
    const int w = image.width();
    const int h = image.height();

    double** matrix = new double*[w];

    for(int i = 0; i < w; i++)
        matrix[i] = new double[h];

    for(int x = 0; x < w; x++)
        for(int y = 0; y < h; y++)
        {
            matrix[x][y] = round(image.pixelColor(x,y).red() / 32);
        }
    return matrix;
}


double** Lab01Matrix::Smezhnost(double** matrix, int w, int h)
{
    int nmsize = 8;
    double** normalizedMatrix = new double*[nmsize];
    for(int i = 0; i < nmsize; i++)
        normalizedMatrix[i] = new double[nmsize];

    for(int x = 0; x < 8; x++)
        for(int y = 0; y < 8; y++)
            normalizedMatrix[x][y] = 0;


    for(int x = 1; x < w; x++)
        for(int y = 0; y < h; y++)
        {
            int current = (int)matrix[x][y];
            int left = (int)matrix[x-1][y];
            normalizedMatrix[current][left]++;
        }
    return normalizedMatrix;
}


double** Lab01Matrix::NormalizedMatrix(double** matrix)
{
    int size = 8;

    double** normalizedMatrix = new double*[size];
    for(int i = 0; i < size; i++)
        normalizedMatrix[i] = new double[size];

    int sum = 0;
    for(int x = 0; x < 8; x++)
        for(int y = 0; y < 8; y++)
            sum += matrix[x][y];

    for(int x = 0; x < size; x++)
    {
        for (int y = 0; y < size; y++)
        {
            if(matrix[x][y] == 0.0)
            {
                normalizedMatrix[x][y] = 0;
                continue;
            }
            normalizedMatrix[x][y] = matrix[x][y] / sum;
        }
    }

    return normalizedMatrix;
}


