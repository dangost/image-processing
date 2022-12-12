#include <math.h>
#include "letterpointsdataset.h"

LetterPointsDataset::LetterPointsDataset()
{

}

void LetterPointsDataset::add_E(Point point)
{
    this->E_class.append(point);
}
void LetterPointsDataset::add_W(Point point)
{
    this->W_class.append(point);
}
void LetterPointsDataset::add_M(Point point)
{
    this->M_class.append(point);
}

void LetterPointsDataset::init_centers()
{
    float sum_x = 0.0f;
    float sum_y = 0.0f;
    float x = 0.0f;
    float y = 0.0f;

    int count = this->E_class.count();
    for(Point point : this->E_class){
        sum_x += point.x;
        sum_y += point.y;
    }
    x = sum_x / count;
    y = sum_y / count;

    this->E_center = new Point(x, y);

    sum_x = 0.0f;
    sum_y = 0.0f;
    count = this->M_class.count();
    for(Point point : this->M_class){
        sum_x += point.x;
        sum_y += point.y;
    }
    this->M_center = new Point(
                (float)(sum_x / count),
                (float)(sum_y / count));

    sum_x = 0.0f;
    sum_y = 0.0f;
    count = this->W_class.count();
    for(Point point : this->W_class){
        sum_x += point.x;
        sum_y += point.y;
    }
    this->W_center = new Point(
                (float)(sum_x / count),
                (float)(sum_y / count));
    return;
}

QString LetterPointsDataset::findClass(Point new_point, QString &dist)
{
    QString result;

    float distance_E = std::sqrt(
                (
                    std::pow(
                        std::abs(this->E_center->x - new_point.x), 2
                        )
                    )
                + std::pow(std::abs(this->E_center->y - new_point.y), 2));


    float distance_W = std::sqrt((std::pow(std::abs(this->W_center->x - new_point.x), 2))+ std::pow(std::abs(this->W_center->y - new_point.y), 2));
    float distance_M = std::sqrt((std::pow(std::abs(this->M_center->x - new_point.x), 2))+ std::pow(std::abs(this->M_center->y - new_point.y), 2));

    dist = "E " + QString::number(distance_E) + " Щ " + QString::number(distance_W) + " М " + QString::number(distance_M);

    // find minimal!!!!@!@#!@#123hjlk
    if (!(distance_E > distance_W))
    {
        if (!(distance_E > distance_M))
        {
            result = "Е";
        }
        else {
            result = "М";
        }
    }
    else {
        if (!(distance_W > distance_M))
        {
            result = "Щ";
        }
        else {
            result = "М";
        }
    }

    return result;
}
