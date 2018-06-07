#ifndef POINT_H
#define POINT_H

#include "vector4.h"
#include <vector>

class Point
{
public:
    Point(double x = 0.0, double y = 0.0, double z = 0.0):
        m_x(x), m_y(y), m_z(z) {}

    double& operator[](int index);

    void add_source_dist(double x, double y);
    void clear_sources();

    Vector4 return_as_vector() const;

    std::vector<double> distance;
private:
    double m_x, m_y, m_z;
};

#endif // POINT_H
