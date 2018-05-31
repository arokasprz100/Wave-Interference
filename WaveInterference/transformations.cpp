#include "transformations.h"
#include <cmath>
#include <QGraphicsScene>

Matrix get_x_rotation_matrix()
{
    Matrix x_rotation_matrix;
    double angle = 0;
    x_rotation_matrix[0][0] = 1.0;
    x_rotation_matrix[1][1] = x_rotation_matrix[2][2] = cos(angle);
    x_rotation_matrix[1][2] = -sin(angle);
    x_rotation_matrix[2][1] = sin(angle);

    return x_rotation_matrix;
}

Matrix get_y_rotation_matrix()
{
    Matrix y_rotation_matrix;
    double angle = 45.0 * M_PI/180.0;
    y_rotation_matrix[1][1] = 1.0;
    y_rotation_matrix[0][0] = y_rotation_matrix[2][2] = cos(angle);
    y_rotation_matrix[2][0] = -sin(angle);
    y_rotation_matrix[0][2] = sin(angle);

    return y_rotation_matrix;
}

Matrix get_z_rotation_matrix()
{
    Matrix z_rotation_matrix;
    double angle = 45.0 * M_PI/180.0;
    z_rotation_matrix[2][2] = 1.0;
    z_rotation_matrix[0][0] = z_rotation_matrix[1][1] = cos(angle);
    z_rotation_matrix[0][1] = -sin(angle);
    z_rotation_matrix[1][0] = sin(angle);

    return z_rotation_matrix;
}

Matrix get_rotation_matrix()
{
    return get_x_rotation_matrix() * get_y_rotation_matrix() * get_z_rotation_matrix();
}


Matrix get_scaling_matrix()
{
    Matrix scaling_matrix;

    double scale = 0.1;

    scaling_matrix[0][0] = scale;
    scaling_matrix[1][1] = scale;
    scaling_matrix[2][2] = scale;

    return scaling_matrix;
}

Matrix get_perspective_matrix()
{
    Matrix perspective_cast_matrix;

    for (int i = 0; i < 3; ++i)
        perspective_cast_matrix[i][i] = 1.0;


    perspective_cast_matrix[3][2] = 1.0;//2.05;

    return perspective_cast_matrix;
}

Matrix get_centering_matrix(int width, int height)
{
    Matrix centering_matrix;

    centering_matrix[0][0] = width / 2.0;
    centering_matrix[1][1] = -height / 2.0;
    centering_matrix[0][3] = width / 2.0;
    centering_matrix[1][3] = height / 2.0;

    return centering_matrix;

}

Matrix Translate(int width, int height)
{
    Matrix translation;

    for (int i = 0; i < 4; ++i)
        translation[i][i] = 1.0;

    translation[0][3] = width/2.0;
    translation[1][3] = height/2.0;
    translation[2][3] = 0;

    return translation;

}
