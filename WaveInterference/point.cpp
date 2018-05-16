#include "point.h"
#include <stdexcept>

double& Point::operator[](int index){
    if(index==1)return m_x;
    else if(index==2)return m_y;
    else if(index==3)return m_z;
    else{
        throw std::out_of_range("kurwa");
    }
}
