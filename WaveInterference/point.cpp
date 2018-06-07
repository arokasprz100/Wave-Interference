#include "point.h"
#include <stdexcept>
#include <cmath>

double& Point::operator[](int index){
    if(index==0)return m_x;
    else if(index==1)return m_y;
    else if(index==2)return m_z;
    else throw std::out_of_range("out of range");
}

Vector4 Point::return_as_vector() const
{
    Vector4 result;
    result[0] = m_x;
    result[1] = m_y;
    result[2] = m_z;

    return result;
}

void Point::add_source_dist(double x, double y){
    double new_dist = sqrt( pow(m_x-x,2) + pow(m_y-y,2) );
    distance.push_back(new_dist);
}

void Point::clear_sources(){
    distance.clear();
}
