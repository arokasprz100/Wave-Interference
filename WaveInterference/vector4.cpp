#include "vector4.h"
#include <iostream>

Vector4::Vector4()
{
    for (int i = 0; i < 3; ++i)
        m_vector_data[i] = 0.0;
    m_vector_data[3] = 1.0;
}

void Vector4::print() const
{
    for (int i = 0; i< 4; ++i)
        std::cout << m_vector_data[i] <<std::endl;
}

void Vector4::set(double x, double y, double z)
{
    m_vector_data[0] = x;
    m_vector_data[1] = y;
    m_vector_data[2] = z;
}

double& Vector4::operator[] (unsigned index)
{
    return m_vector_data[index];
}

const double& Vector4::operator[] (unsigned index) const
{
    return m_vector_data[index];
}

Vector4 Vector4::operator+ (const Vector4& rhs) const
{
    Vector4 result;
    for (int i = 0; i < 4; ++i)
        result[i] += m_vector_data[i] + rhs.m_vector_data[i];
    return result;
}

Vector4 Vector4::operator- (const Vector4& rhs) const
{
    Vector4 result;
    for (int i = 0; i < 4; ++i)
        result[i] += m_vector_data[i] - rhs.m_vector_data[i];
    return result;
}
