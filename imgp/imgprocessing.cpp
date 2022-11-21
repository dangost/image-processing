#include "imgprocessing.h"

ImageProcessingCore::ImageProcessingCore()
{}

double** ImageProcessingCore::MatrixOfSimilarity(QImage &image)
{
    const int w = image.width();
    const int h = image.height();

    double** matrix = new double*[w];

    for(int i = 0; i < image.width(); i++)
        matrix[i] = new double[h];

    for(int x = 0; x < w; x++)
    {
        for(int y = 0; y < h; y++)
        {
            QColor rgb = image.pixelColor(x, y);
            int gray = (rgb.red() + rgb.blue() + rgb.green()) / 3;
            image.setPixel(x, y, QColor(gray, gray, gray).rgb());
        }
    }

    for (int x = 0; x < w; x++)
    {
        for(int y = 0; y < h; y ++)
        {

        }
    }
}

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

double** ImageProcessingCore::Filter(QImage &image)
{
    double **matrix = this->RgbToGray(image);

    const int w = image.width();
    const int h = image.height();
    const int arrayLen = 9;

    for (int x = 0; x < w; x++)
    {
        for(int y = 0; y < h; y++)
        {
            if ((x - 1 >= 0 && x + 1 < w) && ( y - 1 >= 0 && y + 1 < h ))
            {
                int* array = new int[arrayLen];

                array[0] = matrix[x-1][y-1];
                array[1] = matrix[ x ][y-1];
                array[2] = matrix[x+1][y-1];

                array[3] = matrix[x-1][ y ];
                array[4] = matrix[ x ][ y ];
                array[5] = matrix[x+1][ y ];

                array[6] = matrix[x-1][y+1];
                array[7] = matrix[ x ][y+1];
                array[8] = matrix[x+1][y+1];

                int sum = 0;
                for (int q = 0; q < arrayLen; q++)
                    sum += array[q];

                int average = sum / arrayLen;
                array[4] = average;

                // sort, then array[4] = sorted[4]
                int* sorted = this->bubbleSort(array, arrayLen);

                matrix[x][y] = sorted[4];

                delete[] array;
                delete[] sorted;
            }
        }
    }

    for (int i = 0; i < w; i++)
        for (int j = 0; j < h; j++)
            image.setPixel(i, j, qRgb(matrix[i][j], matrix[i][j], matrix[i][j]));


    return matrix;
}

double** ImageProcessingCore::Erosion(QImage &image, int mask[])
{
    double** matrix = this->RgbToBinary(image);



    const int w = image.width();
    const int h = image.height();
    const int arrayLen = 8;

    double **matrixCopy = new double*[w];

    for(int i = 0; i < w; i++)
        matrixCopy[i] = new double[h];

    for (int i = 0; i < w; i++)
        for (int j = 0; j < h; j++)
            matrixCopy[i][j] = matrix[i][j];

    for (int x = 0; x < w; x++)
    {
        for (int y = 0; y < h; y++)
        {
            if ((x - 1 >= 0 && x + 1 < w) && ( y - 1 >= 0 && y + 1 < h ))
            {
                int array[arrayLen];

                array[0] = matrix[x-1][y-1] * mask[0];
                array[1] = matrix[ x ][y-1] * mask[1];
                array[2] = matrix[x+1][y-1] * mask[2];

                array[3] = matrix[x-1][ y ] * mask[3];
                array[4] = matrix[x+1][ y ] * mask[4];

                array[5] = matrix[x-1][y+1] * mask[5];
                array[6] = matrix[ x ][y+1] * mask[6];
                array[7] = matrix[x+1][y+1] * mask[7];

                matrixCopy[x][y] = 1;
                for (int q = 0; q < arrayLen; q++)
                {
                    if (array[q] == 0 && mask[q] == 1)
                    {
                        matrixCopy[x][y] = 0;
                        break;
                    }
                }

                int color = matrixCopy[x][y] == 1 ? 255 : 0;
                image.setPixel(x, y, QColor(color, color, color).rgb());
            }
        }
    }

    return matrixCopy;
}

double** ImageProcessingCore::Extenstion(QImage & image, int mask[], double**&matrix)
{
    const int w = image.width();
    const int h = image.height();
    const int arrayLen = 8;

    double **matrixCopy = new double*[w];

    for(int i = 0; i < w; i++)
        matrixCopy[i] = new double[h];

    for (int i = 0; i < w; i++)
        for (int j = 0; j < h; j++)
            matrixCopy[i][j] = matrix[i][j];

    for (int x = 0; x < w; x++)
    {
        for (int y = 0; y < h; y++)
        {
            if ((x - 1 >= 0 && x + 1 < w) && ( y - 1 >= 0 && y + 1 < h ))
            {
                int array[arrayLen];

                array[0] = matrix[x-1][y-1] * mask[0];
                array[1] = matrix[ x ][y-1] * mask[1];
                array[2] = matrix[x+1][y-1] * mask[2];

                array[3] = matrix[x-1][ y ] * mask[3];
                array[4] = matrix[x+1][ y ] * mask[4];

                array[5] = matrix[x-1][y+1] * mask[5];
                array[6] = matrix[ x ][y+1] * mask[6];
                array[7] = matrix[x+1][y+1] * mask[7];

                matrixCopy[x][y] = 0;
                for (int q = 0; q < arrayLen; q++)
                {
                    if (array[q] == 1 && mask[q] == 1)
                    {
                        matrixCopy[x][y] = 1;
                        break;
                    }
                }

                int color = matrixCopy[x][y] == 1 ? 255 : 0;
                image.setPixel(x, y, QColor(color, color, color).rgb());
            }
        }
    }

    return matrixCopy;
}

double** ImageProcessingCore::Unlocking(QImage &image, int mask[])
{
    double ** erosion = this->Erosion(image, mask);
    double ** result = this->Extenstion(image, mask, erosion);

    return result;
}

int* ImageProcessingCore::bubbleSort(int* &array, int size)
{
    int* sorted = new int[size];

    for (int i = 0; i < size; i++)
        sorted[i] = array[i];

    int counter;

    while(true)
    {
        counter = 0;
        for (int i = 0; i < size - 1; i++)
        {
            if (sorted[i] > sorted[i+1])
            {
                int q = sorted[i];
                sorted[i] = sorted[i+1];
                sorted[i+1] = q;

                counter++;
            }
        }
        if (counter == 0)
            break;
    }

    return sorted;

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

double** ImageProcessingCore::S8Binarisation(QImage &image)
{
    const int w = image.width();
    const int h = image.height();

    double **matrix = new double*[w];
    for (int i = 0; i < w; i++)
        matrix[i] = new double[h];

    for (int i = 0; i < w; i++)
    {
        for (int j = 0; j < h; j++)
        {
            QColor color = image.pixelColor(i, j);
            int coreGray = (color.red() + color.green() + color.blue()) / 3;
            int coreColor = 0;
            int sumOfA8 = 0;
            int countOfA8Elements = 0;
            for (int x = - 1; x <= 1; x++)
            {
                for (int y = -1; y <= 1; y++)
                {
                    if (x == i && y == j)
                        continue;
                    if ((i+x < 0 || i+x >= w) || (j+y < 0 || j+y >= h))
                        continue;
                    QColor temporaryColor = image.pixelColor(i+x, j+y);
                    int gray = (temporaryColor.green() +
                                temporaryColor.red() + temporaryColor.blue()) / 3;
                    sumOfA8 += gray;
                    countOfA8Elements++;
                }
            }

            if((sumOfA8 / countOfA8Elements) > coreGray)
                coreColor = 1;
            matrix[i][j] = coreColor;
        }
    }

    for (int i = 0; i < w; i++)
    {
        for (int j = 0; j < h; j++)
        {
            QRgb color = matrix[i][j] == 1 ? qRgb(0, 0, 0) : qRgb(255, 255, 255);
            image.setPixel(i, j, color);
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


double** ImageProcessingCore::GlobalBinarisation(QImage &image, int trashold)
{
    const int w = image.width();
    const int h = image.height();
    double** matrix = new double*[w];
    for (int i = 0; i < w; i++)
        matrix[i] = new double[h];

    for(int i = 0; i < w; i++)
    {
        for (int j = 0; j < h; j++)
        {
            QColor color = image.pixelColor(i, j);
            int gray = ((color.green() + color.blue() +color.red()) / 3);

            int binColor = gray < trashold ? 1 : 0;

            matrix[i][j] = binColor;

            QColor newColor = binColor == 1 ? qRgb(0, 0, 0) : qRgb(255, 255, 255);

            image.setPixelColor(i, j, newColor);

        }
    }

    return matrix;
}


double** ImageProcessingCore::RedMatrix(QImage &image)
{
    const int w = image.width();
    const int h = image.height();
    double** matrix = new double*[w];
    for (int i = 0; i < w; i++)
        matrix[i] = new double[h];

    for (int i = 0; i < w; i++)
    {
        for(int j = 0; j < h; j++)
        {
            matrix[i][j] = image.pixelColor(i, j).red();
        }
    }

    return matrix;
}


double** ImageProcessingCore::GreenMatrix(QImage &image)
{
    const int w = image.width();
    const int h = image.height();
    double** matrix = new double*[w];
    for (int i = 0; i < w; i++)
        matrix[i] = new double[h];

    for (int i = 0; i < w; i++)
    {
        for(int j = 0; j < h; j++)
        {
            matrix[i][j] = image.pixelColor(i, j).green();
        }
    }

    return matrix;
}
double** ImageProcessingCore::BlueMatrix(QImage &image)
{
    const int w = image.width();
    const int h = image.height();
    double** matrix = new double*[w];
    for (int i = 0; i < w; i++)
        matrix[i] = new double[h];

    for (int i = 0; i < w; i++)
    {
        for(int j = 0; j < h; j++)
        {
            matrix[i][j] = image.pixelColor(i, j).blue();
        }
    }

    return matrix;
}

double** ImageProcessingCore::MinMaxGrayImage(QImage &image)
{
    const int w = image.width();
    const int h = image.height();
    double** matrix = new double*[w];
    for (int i = 0; i < w; i++)
        matrix[i] = new double[h];

    for (int i = 0; i < w; i++)
    {
        for(int j = 0; j < h; j++)
        {
            int red = image.pixelColor(i, j).red();
            int green = image.pixelColor(i, j).green();
            int blue = image.pixelColor(i, j).blue();

            int max = red;
            int min = red;

            if (green > max)
                max = green;
            else if (min > green)
                min = green;

            if (blue > max)
                max = blue;
            else if (min > blue)
                min = blue;

            int gray = round((min + max) / 2);
            if (gray < 0)
                gray = 0;
            if (gray > 255)
                gray = 255;
            image.setPixel(i, j, qRgb(gray, gray, gray));
            matrix[i][j] = gray;
        }
    }

    return matrix;
}
