#ifndef MATRIX_H
#define MATRIX_H

#include "vector4.h"

class Matrix
{
public:
    Matrix();

    void print() const;

    Matrix operator* (const Matrix& rhs) const;

    double* operator[] (unsigned index);

    Vector4 operator* (const Vector4& rhs) const;

private:
    double m_matrix_data[4][4];
};

#endif // MATRIX_H
