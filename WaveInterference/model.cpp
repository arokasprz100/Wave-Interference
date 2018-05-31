#include "model.h"
#include "ui_mainwindow.h"
#include "matrix.h"
#include "transformations.h"
#include <iostream>

Model::Model(MainWindow& view, unsigned width, unsigned height):
    m_width_in_points(width), m_height_in_points(height), m_view(view), x_rotation(view.get_x_rotation()), y_rotation(view.get_y_rotation()), z_rotation(view.get_z_rotation()), is_animated(view.get_is_animated())
{

    for(unsigned i = 0; i < width; ++i){
        m_points.emplace_back();
        for(unsigned j = 0; j < height; ++j){
            m_points[i].emplace_back(i*20,j*20);
        }
    }
}


void Model::print_lines()
{
    QGraphicsScene& draw_interface = *m_view.access_ui().graphicsView->scene();
    for(unsigned i = 0; i< m_points.size() - 1; ++i){
        for(unsigned j = 0; j < m_points[i].size() - 1; ++j){
            QPoint line_start(m_points[i][j][0], m_points[i][j][1]);
            QPoint line_end1 (m_points[i+1][j][0], m_points[i+1][j][1]);
            QPoint line_end2 (m_points[i][j+1][0], m_points[i][j+1][1]);
            draw_interface.addLine(QLine(line_start, line_end1), QPen(Qt::black));
            draw_interface.addLine(QLine(line_start, line_end2), QPen(Qt::black));
        }
    }

    for (unsigned i = 0; i<m_points.size() - 1; ++i )
    {
        QPoint line_start(m_points[m_width_in_points - 1][i][0], m_points[m_width_in_points - 1][i][1]);
        QPoint line_end1 (m_points[m_width_in_points - 1][i+1][0], m_points[m_width_in_points - 1][i+1][1]);
        draw_interface.addLine(QLine(line_start, line_end1), QPen(Qt::black));

    }

    for (unsigned i = 0; i<m_points.size() - 1; ++i )
    {
        QPoint line_start(m_points[i][m_height_in_points-1][0], m_points[i][m_height_in_points-1][1]);
        QPoint line_end1 (m_points[i+1][m_height_in_points-1][0], m_points[i+1][m_height_in_points-1][1]);
        draw_interface.addLine(QLine(line_start, line_end1), QPen(Qt::black));

    }
}

void Model::set_draw_size(QSize draw_size){
    m_draw_size = draw_size;
    m_view.access_ui().graphicsView->scene()->clear();
    repaint();
}

void Model::repaint()
{
    QGraphicsScene& draw_interface = *m_view.access_ui().graphicsView->scene();
    vector_vector transformed_points;
    Matrix transformations = get_scaling_matrix()*get_rotation_matrix(x_rotation, y_rotation, z_rotation)* get_centering_matrix(m_width_in_points*20, m_height_in_points*20);
    for(unsigned i = 0; i< m_points.size(); ++i){
        transformed_points.emplace_back();
        for(unsigned j = 0; j < m_points[i].size(); ++j)
        {
            transformed_points[i].push_back(m_points[i][j].return_as_vector());
            transformed_points[i][j] = transformations * transformed_points[i][j];
            for (int k = 0; k < 3; ++k)
                transformed_points[i][j][k] /= transformed_points[i][j][3];
            //transformed_points[i][j].print();
            transformations.print();
        }
    }

    for(unsigned i = 0; i< transformed_points.size() - 1; ++i)
    {

        for(unsigned j = 0; j < transformed_points.size() - 1; ++j)
        {
            QPoint line_start(transformed_points[i][j][0], transformed_points[i][j][1]);
            QPoint line_end1 (transformed_points[i+1][j][0], transformed_points[i+1][j][1]);
            QPoint line_end2 (transformed_points[i][j+1][0], transformed_points[i][j+1][1]);
            draw_interface.addLine(QLine(line_start, line_end1), QPen(Qt::black));
            draw_interface.addLine(QLine(line_start, line_end2), QPen(Qt::black));
        }
    }
}

void Model::start_animation(){
    std::cout<<"started animation"<<std::endl;
}
