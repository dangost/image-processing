#ifndef POINT_H
#define POINT_H


#include "letterdata.h"
class Point
{
public:
    Point(float x, float y);
    Point(int id, float x, float y);
    Point(LetterData item);
    Point();
    float x;
    float y;
    int id;
};

#endif // POINT_H
