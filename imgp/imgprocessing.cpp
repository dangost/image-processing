#include "imgprocessing.h"

#include <iostream>

ImageProcessingCore::ImageProcessingCore()
{}

double** ImageProcessingCore::RgbToGray(QImage &image)
{
    const int w = image.width();
    const int h = image.height();

    double **matrix = new double*[w];

    for(int i = 0; i < image.width(); i++)
        matrix[i] = new double[h];


    for(int x = 0; x < image.width(); x++)
    {
        for(int y = 0; y < image.height(); y++)
        {
            QColor rgb = image.pixelColor(x, y);
            int gray = (rgb.red() + rgb.blue() + rgb.green()) / 3;

            matrix[x][y] = gray;

            image.setPixel(x, y, QColor(gray, gray, gray).rgb());
        }
    }

    return matrix;
}

double** ImageProcessingCore::RgbToBinary(QImage &image)
{
    const int w = image.width();
    const int h = image.height();

    double **matrix = new double*[w];

    for(int i = 0; i < w; i++)
        matrix[i] = new double[h];

    for(int x = 0; x < w; x++)
    {
        for(int y = 0; y < h; y++)
        {
            QColor rgb = image.pixelColor(x, y);
            int gray = (rgb.red() + rgb.blue() + rgb.green()) / 3;

            int color = gray > 128 ? 255 : 0;

            matrix[x][y] = color == 0 ? 0 : 1;

            image.setPixel(x, y, QColor(color, color, color).rgb());
        }
    }

    return matrix;
}

double** ImageProcessingCore::RgbViaWaves(QImage &image)
{
    const int w = image.width();
    const int h = image.height();

    double **matrix = new double*[w];

    for(int i = 0; i < image.width(); i++)
        matrix[i] = new double[h];

    for(int i = 0; i < w; i++)
        for(int j = 0; j < h; j++)
        {
            QColor rgb = image.pixelColor(i, j);
            int gray = (rgb.red() + rgb.blue() + rgb.green()) / 3;
            matrix[i][j] = gray > 128 ? 0 : 1;
        }

    double min = 0;
    double max = 1;
    this->calculateWaves(matrix, w , h, max, min);

    double relativeValue = max - min;
    for(int i = 0; i < w; i++)
    {
        for(int j = 0; j < h; j++)
        {
            double temp = matrix[i][j];
            int color = 255 - (int)((temp * 255) / relativeValue);
            image.setPixel(i, j, QColor(color, color, color).rgb());
        }
    }

    return matrix;
}

void ImageProcessingCore::calculateWaves(double **&matrix, int w, int h, double &max, double &min)
{
    for (int i = 0; i < w; i++)
    {
        for (int j = 0; j < h; j++)
        {
            if (matrix[i][j] == 1)
            {
                for (int x = -3; x <= 3; x++)
                {
                    for (int y = -2; y <= 3; y++)
                    {
                        double increment;
                        if (!(x > -3 && x < 3 && y > -3 && y < 3))
                        {
                            increment = 0.1;
                        }
                        else if (!(x > -2 && x < 2 && y > -2 && y < 2))
                        {
                            increment = 0.3;
                        }
                        else if (!(x > -1 && x < 1 && y > -1 && y < 1))
                        {
                            increment = 0.6;
                        }
                        else
                            continue;

                        if ((i+x >=0 && i+x < w) && (j+y >= 0 && j+y < h))
                        {
                            matrix[i+x][j+y] += increment;

                            double value = matrix[i+x][j+y];


                            if (value > max)
                                max = value;
                            else if (value < min)
                                min = value;
                        }
                    }
                }
            }

        }
    }
}
