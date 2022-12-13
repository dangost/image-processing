#include "grouppointset.h"

GroupPointSet::GroupPointSet()
{
    this->center = Point(-1, -1);
}

GroupPointSet::GroupPointSet(QList<Point> set1, QList<Point> set2, Point center)
{
    for (Point p : set1)
    {
        this->points.append(p);
    }
    for (Point p : set2)
    {
        this->points.append(p);
    }

    this->center = center;
}

void GroupPointSet::addPoint(Point point)
{
    this->points.append(point);
    Point new_center;
    if (this->center.x == -1)
    {
        new_center = point;
    }
    else
    {
         new_center = Point(
                    (this->center.x + point.x) / 2,
                    (this->center.y = point.y) / 2
                    );
    }
    this->center = new_center;

}
