#ifndef TRANSFORMATIONS_H
#define TRANSFORMATIONS_H

#include "matrix.h"

Matrix get_x_rotation_matrix(double angle);

Matrix get_y_rotation_matrix(double angle);

Matrix get_z_rotation_matrix(double angle);

Matrix get_rotation_matrix(double angle_x, double angle_y, double angle_z);

Matrix get_scaling_matrix();

Matrix get_perspective_matrix();

Matrix get_centering_matrix(int width, int height);

Matrix Translate(double width, double height);

#endif // TRANSFORMATIONS_H
