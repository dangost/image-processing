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

    int count = this->E_class.count();
    for(Point point : this->E_class){
        sum_x += point.x;
        sum_x += point.y;
    }
    this->E_center = new Point(
                (float)(sum_x / count),
                (float)(sum_y / count));

    count = this->M_class.count();
    for(Point point : this->M_class){
        sum_x += point.x;
        sum_x += point.y;
    }
    this->M_center = new Point(
                (float)(sum_x / count),
                (float)(sum_y / count));

    count = this->W_class.count();
    for(Point point : this->W_class){
        sum_x += point.x;
        sum_x += point.y;
    }
    this->W_center = new Point(
                (float)(sum_x / count),
                (float)(sum_y / count));
}

QString LetterPointsDataset::findClass(Point new_point)
{
    QString result;

    float distance_E = std::sqrt((std::abs(this->E_center->x - new_point.x)) + std::abs(this->E_center->y - new_point.y));
    float distance_W = std::sqrt((std::abs(this->W_center->x - new_point.x)) + std::abs(this->W_center->y - new_point.y));
    float distance_M = std::sqrt((std::abs(this->M_center->x - new_point.x)) + std::abs(this->M_center->y - new_point.y));

    if (distance_E > distance_W)
    {
        if (distance_E > distance_M)
        {
            result = "E";
        }
        else {
            result = "М";
        }
    }
    else {
        if (distance_W > distance_M)
        {
            result = "W";
        }
        else {
            result = "M";
        }
    }

    return result;
}
