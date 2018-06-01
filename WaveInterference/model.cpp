#include "model.h"
#include "ui_mainwindow.h"
#include "matrix.h"
#include "transformations.h"
#include <iostream>
#include <QPainter>
#include <QTimer>

Model::Model(MainWindow& view, unsigned width, unsigned height):
    m_width_in_points(width), m_height_in_points(height), m_view(view), x_rotation(view.get_x_rotation()), y_rotation(view.get_y_rotation()), z_rotation(view.get_z_rotation()), is_animated(view.get_is_animated())
{
    m_bitmap = QPixmap(1000,1000);
    for(unsigned i = 0; i < width; ++i){
        m_points.emplace_back();
        for(unsigned j = 0; j < height; ++j){
            m_points[i].push_back(Point(i*20,j*20));
        }
    }
    m_painter = new QPainter(&m_bitmap);
    m_painter->setPen(QPen(Qt::black, 2));
    m_draw_size = (view.access_ui()).graphicsView->size();
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
    Matrix transformations = get_perspective_matrix()* get_scaling_matrix()*Translate(-(-bitmap_width/2.0), -(-bitmap_height/2.0))* get_rotation_matrix(x_rotation, y_rotation, z_rotation)* Translate(-static_cast<double>(m_width_in_points*10.0 - 10), -static_cast<double>(m_height_in_points*10.0 - 10));
    for(unsigned i = 0; i< m_points.size(); ++i){
        transformed_points.emplace_back();
        for(unsigned j = 0; j < m_points[i].size(); ++j)
        {
            transformed_points[i].push_back(m_points[i][j].return_as_vector());
            transformed_points[i][j] = transformations * transformed_points[i][j];
            for (int k = 0; k < 3; ++k)
                transformed_points[i][j][k] /= transformed_points[i][j][3];
            transformed_points[i][j].print();
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
    std::cout<<"started animation"<<std::endl;
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(sine_calc()));
    timer->start(100);
}

void Model::redraw(){
    repaint();
}

void Model::sine_calc()
{
    static int k = 0;
    k++;
    for (unsigned i = 0; i < m_points.size(); ++i)
        for (unsigned j = 0; j < m_points.size(); ++j)
            m_points[i][j][2] = 10 * sin(k + sqrt(m_points[i][j][0] * m_points[i][j][0] + m_points[i][j][1]*m_points[i][j][1]));
    redraw();

}
