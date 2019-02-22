#ifndef VECTOR4_H
#define VECTOR4_H


class Vector4
{
public:
    Vector4();

    void print() const;

    void set(double x, double y, double z);

    double& operator[] (unsigned index);

    const double& operator[] (unsigned index) const;

    Vector4 operator+ (const Vector4& rhs) const;

    Vector4 operator- (const Vector4& rhs) const;


private:
    double m_vector_data[4];
};



#endif // VECTOR4_H
