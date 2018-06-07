#include "model.h"
#include "ui_mainwindow.h"
#include "matrix.h"
#include "transformations.h"
#include <iostream>
#include <QPainter>
#include <QClipboard>
#include <QFileDialog>
#include <QVector>

Model::Model(MainWindow& view, unsigned width, unsigned height):
    m_width_in_points(width), m_height_in_points(height), m_view(view), x_rotation(view.get_x_rotation()), y_rotation(view.get_y_rotation()), z_rotation(view.get_z_rotation()), is_animated(view.get_is_animated())
{
    m_pixmap_size = QSize(1400,1400);
    m_bitmap = QPixmap(m_pixmap_size);
    m_point_width_modifier = (m_pixmap_size.width()-200) / static_cast<double>(m_width_in_points);
    m_point_height_modifier = (m_pixmap_size.height()-200) / static_cast<double>(m_height_in_points);
    for(unsigned i = 0; i < width; ++i){
        m_points.emplace_back();
        m_points2D.emplace_back();
        for(unsigned j = 0; j < height; ++j){
            m_points[i].push_back(Point(i*m_point_width_modifier ,j*m_point_height_modifier));
            m_points2D[i].push_back(QPoint(0,0));
        }
    }

    m_transformations = get_perspective_matrix()* get_scaling_matrix()* get_rotation_matrix(x_rotation, y_rotation, z_rotation)* Translate(-static_cast<double>(m_width_in_points*(m_point_width_modifier/2.)), -static_cast<double>(m_height_in_points*(m_point_height_modifier/2.)));

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
    vector_vector transformed_points;

    for(unsigned i = 0; i< m_points.size(); ++i){
        transformed_points.emplace_back();
        for(unsigned j = 0; j < m_points[i].size(); ++j)
        {
            transformed_points[i].push_back(m_points[i][j].return_as_vector());
            transformed_points[i][j] = m_transformations * transformed_points[i][j];
            for (int k = 0; k < 3; ++k)
                transformed_points[i][j][k] /= transformed_points[i][j][3];

            m_points2D[i][j].rx() = transformed_points[i][j][0];
            m_points2D[i][j].ry() = transformed_points[i][j][1];
        }

    }
    QVector<QPoint> lines_to_draw;
    for(unsigned i = 0; i< m_points.size() - 1; ++i)
    {
        for(unsigned j = 0; j < m_points.size() - 1; ++j)
        {
            lines_to_draw.push_back(m_points2D[i][j]);
            lines_to_draw.push_back(m_points2D[i+1][j]);
            lines_to_draw.push_back(m_points2D[i][j]);
            lines_to_draw.push_back(m_points2D[i][j+1]);
        }

        lines_to_draw.push_back(m_points2D[m_width_in_points - 1][i]);
        lines_to_draw.push_back(m_points2D[m_width_in_points - 1][i+1]);
        lines_to_draw.push_back(m_points2D[i][m_height_in_points-1]);
        lines_to_draw.push_back(m_points2D[i+1][m_height_in_points-1]);
    }

//    for (unsigned i = 0; i<m_points.size() - 1; ++i )
//    {
//        lines_to_draw.push_back(m_points2D[m_width_in_points - 1][i]);
//        lines_to_draw.push_back(m_points2D[m_width_in_points - 1][i+1]);
//        lines_to_draw.push_back(m_points2D[i][m_height_in_points-1]);
//        lines_to_draw.push_back(m_points2D[i+1][m_height_in_points-1]);

//    }
    m_painter->drawLines(lines_to_draw);
    draw_interface.setSceneRect(0,0,m_draw_size.width()-2,m_draw_size.height()-2);
    draw_interface.addPixmap(m_bitmap.scaled(m_draw_size));

}

void Model::start_animation(){

    m_transformations = get_perspective_matrix()* get_scaling_matrix()* get_rotation_matrix(x_rotation, y_rotation, z_rotation)* Translate(-static_cast<double>(m_width_in_points*(m_point_width_modifier/2.)), -static_cast<double>(m_height_in_points*(m_point_height_modifier/2.)));

    m_timer->start(25);
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
    k= (calc + k) % 314;
    for (unsigned i = 0; i < m_points.size(); ++i)
        for (unsigned j = 0; j < m_points.size(); ++j){
            m_points[i][j][2]=0;
            for(unsigned l = 0; l < m_points[i][j].distance.size(); ++l){
                m_points[i][j][2]+=m_ampfreq[l].first*sin(k - m_ampfreq[l].second*0.05*m_points[i][j].distance[l]);
            }
         }
    redraw();
}

void Model::next(){
    sine_calc();
}

void Model::previous(){
    sine_calc(-1);
}

void Model::source_added(int x_pos, int y_pos, double amplitude, double frequency){
    for(unsigned i = 0 ; i < m_points.size(); ++i){
        for(unsigned j = 0; j < m_points.size(); ++j){
            m_points[i][j].add_source_dist(x_pos-100, y_pos-100);
        }
    }
    std::cout<<amplitude<<" "<<frequency<<std::endl;
    m_ampfreq.push_back(std::pair<double, double>(amplitude,frequency));
}

void Model::sources_deleted(){
    for(unsigned i = 0 ; i < m_points.size(); ++i){
        for(unsigned j = 0; j < m_points.size(); ++j){
            m_points[i][j].clear_sources();
        }
    }
    m_ampfreq.clear();
}

void Model::model_clipboard(){
    QClipboard* clipboard = QApplication::clipboard();
    clipboard->setPixmap(m_bitmap);
}

void Model::model_save(){
    QString filename = QFileDialog::getSaveFileName();
    m_bitmap.save(filename);
}

void Model::calculate_matrices()
{
    m_transformations = get_perspective_matrix()* get_scaling_matrix()* get_rotation_matrix(x_rotation, y_rotation, z_rotation)* Translate(-static_cast<double>(m_width_in_points*(m_point_width_modifier/2.)), -static_cast<double>(m_height_in_points*(m_point_height_modifier/2.)));
    redraw();
}
