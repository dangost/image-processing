#ifndef GROUPDATASET_H
#define GROUPDATASET_H

#include "grouppointset.h"
#include "point.h"
#include "qlist.h"
#include "QVector"

class GroupDataset
{
private:


public:
    GroupDataset();

    QList<Point> m_points;

    QList<GroupPointSet> sets;

    QString ouput();

    void unitSets(int id1, int id2, Point &a, Point &b);

    Point findPoint(int id);

    void addPoint(Point point);

    float** findDistances(int& count);

    void pointsToSet();
    float** findSetsDistances();

    QList<QList<int>> group();

    float** m_distances;


};

#endif // GROUPDATASET_H
