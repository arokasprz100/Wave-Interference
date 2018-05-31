#include "model.h"
#include "ui_mainwindow.h"
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
            QPoint line_start(m_points[i][j][1], m_points[i][j][2]);
            QPoint line_end1 (m_points[i+1][j][1], m_points[i+1][j][2]);
            QPoint line_end2 (m_points[i][j+1][1], m_points[i][j+1][2]);
            draw_interface.addLine(QLine(line_start, line_end1), QPen(Qt::black));
            draw_interface.addLine(QLine(line_start, line_end2), QPen(Qt::black));
        }
    }

    for (unsigned i = 0; i<m_points.size() - 1; ++i )
    {
        QPoint line_start(m_points[m_width_in_points - 1][i][1], m_points[m_width_in_points - 1][i][2]);
        QPoint line_end1 (m_points[m_width_in_points - 1][i+1][1], m_points[m_width_in_points - 1][i+1][2]);
        draw_interface.addLine(QLine(line_start, line_end1), QPen(Qt::black));

    }

    for (unsigned i = 0; i<m_points.size() - 1; ++i )
    {
        QPoint line_start(m_points[i][m_height_in_points-1][1], m_points[i][m_height_in_points-1][2]);
        QPoint line_end1 (m_points[i+1][m_height_in_points-1][1], m_points[i+1][m_height_in_points-1][2]);
        draw_interface.addLine(QLine(line_start, line_end1), QPen(Qt::black));

    }
}

void Model::set_draw_size(QSize draw_size){
    m_draw_size = draw_size;
    m_view.access_ui().graphicsView->scene()->clear();
    print_lines();
}

void Model::start_animation(){
    std::cout<<"started animation"<<std::endl;
}
