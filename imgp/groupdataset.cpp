#include "groupdataset.h"

GroupDataset::GroupDataset()
{

}

void GroupDataset::addPoint(Point point)
{
    this->m_points.append(point);
}

Point GroupDataset::findPoint(int id)
{
    for (Point p : this->m_points)
    {
        if (p.id == id)
        {
            return p;
        }
    }
    return this->m_points[id];
}

QString GroupDataset::ouput()
{
    QString result = QString("");

    for (GroupPointSet set : this->sets)
    {
        result.append("[");
        for (Point p : set.points)
        {
            result.append(QString::number(p.id));
            result.append(", ");
        }
        result.append("] ");
    }

    return result;
}

void GroupDataset::unitSets(int id1, int id2, Point &a, Point &b)
{
    auto set1 = this->sets[id1];
    auto set2 = this->sets[id2];

    a = set1.center;
    b = set2.center;

    Point center = Point(
                (set1.center.x + set2.center.x) / 2,
                (set1.center.y + set2.center.y) / 2
                );

    if (id1 > id2)
    {
        this->sets.remove(id1);
        this->sets.remove(id2);
    }
    else
    {
        this->sets.remove(id2);
        this->sets.remove(id1);
    }

    GroupPointSet set = GroupPointSet(set1.points, set2.points, center);
    this->sets.append(set);

}

void GroupDataset::pointsToSet()
{
    for (Point point : this->m_points)
    {
        auto set = GroupPointSet();
        set.addPoint(point);
        this->sets.append(set);
    }
}

float** GroupDataset::findSetsDistances()
{
    int count = this->sets.length();

    this->m_distances = new float*[count];
    for (int i = 0; i < count; i++)
        this->m_distances[i] = new float[count];


    for (int x = 0; x < count; x++)
    {
        for (int y = 0; y < count; y++)
        {
            Point a = this->sets[x].center;
            Point b = this->sets[y].center;

            float distance;
            if (!(x == y))
                distance = std::sqrt((std::pow(std::abs(a.x - b.x), 2))+ std::pow(std::abs(a.y - b.y), 2));
            else
                distance = 0.0f;

            this->m_distances[x][y] = distance;
        }
    }

    return this->m_distances;
}

float** GroupDataset::findDistances(int& count)
{
    count = this->m_points.length();

    this->m_distances = new float*[count];
    for (int i = 0; i < count; i++)
        this->m_distances[i] = new float[count];


    for (int x = 0; x < count; x++)
    {
        for (int y = 0; y < count; y++)
        {
            Point a = this->m_points[x];
            Point b = this->m_points[y];

            float distance;
            if (!(x == y))
                distance = std::sqrt((std::pow(std::abs(a.x - b.x), 2))+ std::pow(std::abs(a.y - b.y), 2));
            else
                distance = 0.0f;

            this->m_distances[x][y] = distance;
        }
    }

    return this->m_distances;
}

QList<QList<int>> GroupDataset::group()
{

}
