#ifndef MATRIX_H
#define MATRIX_H

#include "vector4.h"

/*
 * Simple class representing 4x4 matrix used for
 * 3d graphics transformations.
 */
class Matrix
{
public:
    Matrix();

    /*
     * Simple method that prints matrix to std::cout
     */
    void print() const;

    /*
     * Overloaded * operator. Multiplies two matrices.
     */
    Matrix operator* (const Matrix& rhs) const;

    /*
     * Overloaded [] operator that allows access
     * to matrix elements
     */
    double* operator[] (unsigned index);

    Vector4 operator* (const Vector4& rhs) const;

private:
    double m_matrix_data[4][4];
};

#endif // MATRIX_H
