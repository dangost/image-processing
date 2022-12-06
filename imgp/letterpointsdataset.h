#include "point.h"
#include <QList>

#ifndef LETTERPOINTSDATASET_H
#define LETTERPOINTSDATASET_H


class LetterPointsDataset
{
public:
    LetterPointsDataset();
    QList<Point> E_class;
    QList<Point> W_class;
    QList<Point> M_class;

    Point *E_center;
    Point *W_center;
    Point *M_center;

    void add_E(Point);
    void add_W(Point);
    void add_M(Point);

    void init_centers();

    QString findClass(Point new_point);
};

#endif // LETTERPOINTSDATASET_H
