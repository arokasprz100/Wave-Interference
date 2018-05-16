#ifndef POINT_H
#define POINT_H

#include <QPoint>

class Point
{
public:
    Point(double x = 0.0, double y = 0.0):
        m_x(x), m_y(y) {}

    double& operator[](int index);

private:
    double m_x, m_y, m_z;
};

#endif // POINT_H
