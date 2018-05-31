#ifndef POINT_H
#define POINT_H

#include "vector4.h"

class Point
{
public:
    Point(double x = 0.0, double y = 0.0, double z = 0.0):
        m_x(x), m_y(y), m_z(z) {}

    double& operator[](int index);

    Vector4 return_as_vector() const;

private:
    double m_x, m_y, m_z;
};

#endif // POINT_H
