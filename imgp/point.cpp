#include "point.h"

Point::Point(float x, float y)
{
    this->x = x;
    this->y = y;
}

Point::Point() {}

Point::Point(LetterData item)
{
    this->x = item.ends;
    this->y = item.knotes;
}
