#include "lab02core.h"
#include <algorithm>

Lab02Core::Lab02Core()
{
}

int** Lab02Core::ZongSune(int** image, int w, int h)
{
    while(true)
    {
        auto firstStep = this->firstStepZonge(image, w, h);
        auto secondStep = this->secondtepZonge(firstStep, w, h);
        for (int i = 0 ; i< h; i++)
            for(int j = 0; j < w; j++)
            {
                image[i][j] = secondStep[i][j];
            }

        bool equal = true;
        for (int i = 0; i < w; i++)
        {
            for (int j = 0; j < h; j++)
            {
                if (!(firstStep[i][j] == secondStep[i][j]))
                {
                    equal = false;
                    break;
                }
            }
        }
        if (equal)
        {
            break;
        }
    }
    return image;
}

int** Lab02Core::CNMatrix(QPixmap image)
{

}

int Lab02Core::cn(int** matrix3x3) // b8-a8
{

}

int** Lab02Core::GetBaseMatrix(QImage image)
{
    const int w = image.width();
    const int h = image.height();

    int** matrix = new int*[w];

    for(int i = 0; i < w; i++)
        matrix[i] = new int[h];

    for(int x = 0; x < w; x++)
        for(int y = 0; y < h; y++)
        {
            int color = image.pixelColor(x,y).red();
            matrix[x][y] = color == 0 ? 1 : 0;

        }
    return matrix;
}

int** Lab02Core::FromZerosToRGB(int** image, int w, int h)
{
    for (int i = 0; i < w; i++)
    {
        for (int j = 0; j < h; j++)
        {
            image[i][j] = image[i][j] == 0 ? 255 : 0;
        }
    }

    return image;
}


// TODO FORMAT BLACK MATRIX TO 0-1 !~``````````````````asdc/.gmnasdk.fnasdm,fnasd,m.fasl.kjf
int** Lab02Core::firstStepZonge(int** image, int w, int h)
{
    int** result = new int*[w];
    for (int i = 0; i < h; i++)
    {
        result[i] = new int[h];
        for (int j = 0; j < w; j++)
        {
            if (i == 0 || j == 0)
            {
                result[i][j] = 0;
            }
            else
            {result[i][j] = image[i][j];}
        }
    }

    for(int x = 1; x < w - 1; x++)
    {
        for (int y = 1; y < h - 1; y++)
        { //border-color: red}
            if ((int)image[x][y] == 0)
                continue;

            std::vector<int> vector3x3 = {
                (int)image[x][y], (int)image[x][y-1], (int)image[x+1][y-1],
                (int)image[x+1][y], (int)image[x+1][y+1], (int)image[x][y+1],
                (int)image[x-1][y+1], (int)image[x-1][y], (int)image[x-1][y-1]};

            // First step
            int b1 = 0;
            for (int q = 1; q < 8; q++)
            {
                if (vector3x3[q] == 0 && vector3x3[q+1] == 1)
                {
                    b1++;
                }
            }

            if (!(b1 >= 2 && b1 <= 6))
            {
                continue;
            }

            int A = 0;
            for (int i = 1; i < 8; i++)
            {
                A += vector3x3[i];
            }
            if (!(A > 1))
                continue;

            int P1 = vector3x3[1] * vector3x3[3] * vector3x3[5];
            int P2 = vector3x3[3] * vector3x3[5] * vector3x3[7];

            if (!(P1 > 0))
                continue;
            if (!(P2 > 0))
                continue;

            result[x][y] = 0;

        }
    }

    return result;
}


int** Lab02Core::secondtepZonge(int** image, int w, int h)
{
    int** result = new int*[w];
    for (int i = 0; i < h; i++)
    {
        result[i] = new int[h];
        for (int j = 0; j < w; j++)
        {
            if (i == 0 || j == 0)
            {
                result[i][j] = 0;
            }
            else
            {result[i][j] = image[i][j];}
        }
    }

    for(int x = 1; x < w - 1; x++)
    {
        for (int y = 1; y < h - 1; y++)
        {
            if ((int)image[x][y] == 0)
                continue;

            std::vector<int> vector3x3 = {
                (int)image[x][y], (int)image[x][y-1], (int)image[x+1][y-1],
                (int)image[x+1][y], (int)image[x+1][y+1], (int)image[x][y+1],
                (int)image[x-1][y+1], (int)image[x-1][y], (int)image[x-1][y-1]};


            int A = 0;
            for (int i = 1; i < 8; i++)
            {
                A += vector3x3[i];
            }
            if (!(A > 1))
                continue;

            int P1 = vector3x3[1] * vector3x3[3] * vector3x3[7];
            int P2 = vector3x3[1] * vector3x3[5] * vector3x3[7];

            if (!(P1 > 0))
                continue;
            if (!(P2 > 0))
                continue;

            result[x][y] = 0;

        }
    }

    return result;
}
