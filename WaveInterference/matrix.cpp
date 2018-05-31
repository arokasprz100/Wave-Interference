#include "matrix.h"
#include <iostream>

Matrix::Matrix()
{
    for (int i = 0; i< 4; ++i)
        for (int j = 0; j < 4; ++j)
            m_matrix_data[i][j] = 0.0;
    m_matrix_data[3][3] = 1.0;
}

void Matrix::print() const
{
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
            std::cout << m_matrix_data[i][j] << " ";
        std::cout << std::endl;
    }
}

Matrix Matrix::operator* (const Matrix& rhs) const
{
    Matrix result;
    for (int i = 0; i < 4; ++i){
        for (int j = 0; j < 4; ++j){
            result[i][j] = 0.0;
            for (int k = 0; k < 4; ++k)
                result[i][j] += m_matrix_data[i][k] * rhs.m_matrix_data[k][j];
        }
    }
    return result;
}

double* Matrix::operator[] (unsigned index)
{
    return m_matrix_data[index];
}

Vector4 Matrix::operator* (const Vector4& rhs) const
{
    Vector4 result;
    for (int i = 0; i < 4; ++i){
        result[i] = 0.0;
        for (int j = 0; j < 4; ++j)
            result[i] += m_matrix_data[i][j]*rhs[j];
    }
    return result;
}
