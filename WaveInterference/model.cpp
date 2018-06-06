#include "model.h"
#include "ui_mainwindow.h"
#include "matrix.h"
#include "transformations.h"
#include <iostream>
#include <QPainter>


Model::Model(MainWindow& view, unsigned width, unsigned height):
    m_width_in_points(width), m_height_in_points(height), m_view(view), x_rotation(view.get_x_rotation()), y_rotation(view.get_y_rotation()), z_rotation(view.get_z_rotation()), is_animated(view.get_is_animated())
{
    m_pixmap_size = QSize(1400,1400);
    m_bitmap = QPixmap(m_pixmap_size);
    m_point_width_modifier = (m_pixmap_size.width()-200) / static_cast<double>(m_width_in_points);
    m_point_height_modifier = (m_pixmap_size.height()-200) / static_cast<double>(m_height_in_points);
    for(unsigned i = 0; i < width; ++i){
        m_points.emplace_back();
        for(unsigned j = 0; j < height; ++j){
            m_points[i].push_back(Point(i*m_point_width_modifier ,j*m_point_height_modifier));
        }
    }
    m_painter = new QPainter(&m_bitmap);
    m_painter->setPen(QPen(Qt::black, 3));
    m_painter->translate(m_bitmap.rect().center());
    m_draw_size = (view.access_ui()).graphicsView->size();

    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(sine_calc()));
    repaint();
}


void Model::set_draw_size(QSize draw_size){
    m_draw_size = draw_size;
    m_draw_size.setHeight(m_draw_size.height());
    m_draw_size.setWidth(m_draw_size.width());
    m_view.access_ui().graphicsView->scene()->clear();
    repaint();
}

void Model::repaint()
{
    QGraphicsScene& draw_interface = *m_view.access_ui().graphicsView->scene();
    m_bitmap.fill();
    draw_interface.clear();
    double bitmap_width = m_bitmap.width();
    double bitmap_height = m_bitmap.height();
    vector_vector transformed_points;
    Matrix transformations = get_perspective_matrix()* get_scaling_matrix()* get_rotation_matrix(x_rotation, y_rotation, z_rotation)* Translate(-static_cast<double>(m_width_in_points*(m_point_width_modifier/2.)), -static_cast<double>(m_height_in_points*(m_point_height_modifier/2.)));

    for(unsigned i = 0; i< m_points.size(); ++i){
        transformed_points.emplace_back();
        for(unsigned j = 0; j < m_points[i].size(); ++j)
        {
            transformed_points[i].push_back(m_points[i][j].return_as_vector());
            transformed_points[i][j] = transformations * transformed_points[i][j];
            for (int k = 0; k < 3; ++k)
                transformed_points[i][j][k] /= transformed_points[i][j][3];
        }

    }
    for(unsigned i = 0; i< m_points.size() - 1; ++i)
    {

        for(unsigned j = 0; j < m_points.size() - 1; ++j)
        {
            QPoint line_start(transformed_points[i][j][0], transformed_points[i][j][1]);
            QPoint line_end1 (transformed_points[i+1][j][0], transformed_points[i+1][j][1]);
            QPoint line_end2 (transformed_points[i][j+1][0], transformed_points[i][j+1][1]);

            m_painter->drawLine(line_start, line_end1);
            m_painter->drawLine(line_start, line_end2);
        }
    }

    for (unsigned i = 0; i<m_points.size() - 1; ++i )
    {
        QPoint line_start(transformed_points[m_width_in_points - 1][i][0], transformed_points[m_width_in_points - 1][i][1]);
        QPoint line_end1 (transformed_points[m_width_in_points - 1][i+1][0], transformed_points[m_width_in_points - 1][i+1][1]);
        m_painter->drawLine(line_start, line_end1);

    }

    for (unsigned i = 0; i<m_points.size() - 1; ++i )
    {
        QPoint line_start(transformed_points[i][m_height_in_points-1][0], transformed_points[i][m_height_in_points-1][1]);
        QPoint line_end1 (transformed_points[i+1][m_height_in_points-1][0], transformed_points[i+1][m_height_in_points-1][1]);
        m_painter->drawLine(line_start, line_end1);

    }


    m_painter->drawLine(QPoint(bitmap_width,0), QPoint(bitmap_width, bitmap_height));
    draw_interface.setSceneRect(0,0,m_draw_size.width()-2,m_draw_size.height()-2);
    draw_interface.addPixmap(m_bitmap.scaled(m_draw_size));

}

void Model::start_animation(){

    m_timer->start(50);
}

void Model::stop_animation(){
    m_timer->stop();
}


void Model::redraw(){
    repaint();
}

void Model::sine_calc(int calc)
{
    static int k = 0;
    k+=calc;
    for (unsigned i = 0; i < m_points.size(); ++i)
        for (unsigned j = 0; j < m_points.size(); ++j){

            double distance_x = (m_points[i][j][0] - m_width_in_points*m_point_width_modifier/2.) * (m_points[i][j][0] - m_width_in_points*m_point_width_modifier/2.);
            double distance_y = (m_points[i][j][1] - m_height_in_points*m_point_height_modifier/2.) * (m_points[i][j][1] - m_height_in_points*m_point_height_modifier/2.);
            m_points[i][j][2] = 40 * sin(k - 0.05*sqrt(distance_x + distance_y));
         }
    redraw();
}

void Model::next(){
    sine_calc();
}

void Model::previous(){
    sine_calc(-1);
}
