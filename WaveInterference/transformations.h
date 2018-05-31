#ifndef TRANSFORMATIONS_H
#define TRANSFORMATIONS_H

#include "matrix.h"

Matrix get_x_rotation_matrix();

Matrix get_y_rotation_matrix();

Matrix get_z_rotation_matrix();

Matrix get_rotation_matrix();

Matrix get_scaling_matrix();

Matrix get_perspective_matrix();

Matrix get_centering_matrix(int width, int height);

Matrix Translate(int width, int height);

#endif // TRANSFORMATIONS_H
