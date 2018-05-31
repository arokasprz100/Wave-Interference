#include "point.h"
#include <stdexcept>

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
