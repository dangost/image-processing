#ifndef GROUPPOINTSET_H
#define GROUPPOINTSET_H


#include "point.h"
#include "qlist.h"

class GroupPointSet
{
public:
    GroupPointSet();

    GroupPointSet(QList<Point> set1, QList<Point> set2, Point center);

    QList<Point> points;

    Point center;

    void addPoint(Point point);

};

#endif // GROUPPOINTSET_H
