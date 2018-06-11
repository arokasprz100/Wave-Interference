#include "model.h"
#include "ui_mainwindow.h"
#include "matrix.h"
#include "transformations.h"
#include <iostream>
#include <QPainter>
#include <QClipboard>
#include <QThread>
#include <QFileDialog>
#include <QtPrintSupport/QPrintDialog>
#include <QtPrintSupport/QPrinter>
#include <QVector>

Model::Model(MainWindow& view, unsigned width, unsigned height):
    m_width_in_points(width), m_height_in_points(height), m_view(view), x_rotation(view.get_x_rotation()), y_rotation(view.get_y_rotation()), z_rotation(view.get_z_rotation()), is_animated(view.get_is_animated())
{
    k=0;
    m_pixmap_size = QSize(1000,1000);
    m_bitmap = QPixmap(m_pixmap_size);
    m_point_width_modifier = (m_pixmap_size.width()-200)/ static_cast<double>(m_width_in_points);
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
    if(m_bitmaps.size()<63){
        QThread *thread1 = QThread::create([this]{thread_repaint(0,m_width_in_points/2,0,m_height_in_points/2.0);});
        QThread *thread2 = QThread::create([this]{thread_repaint(m_width_in_points/2.0,m_width_in_points,0,m_height_in_points/2.0);});
        QThread *thread3 = QThread::create([this]{thread_repaint(0,m_width_in_points/2.0,m_height_in_points/2.0,m_height_in_points);});
        QThread *thread4 = QThread::create([this]{thread_repaint(m_width_in_points/2.0,m_width_in_points,m_height_in_points/2.0,m_height_in_points);});
        thread1->start();
        thread2->start();
        thread3->start();
        thread4->start();
        thread1->wait();
        thread2->wait();
        thread3->wait();
        thread4->wait();
        connect_layers();
        if(m_view.get_is_animated())m_bitmaps.push_back(m_bitmap);
        draw_interface.setSceneRect(0,0,m_draw_size.width(),m_draw_size.height());
        draw_interface.addPixmap(m_bitmap.scaled(m_draw_size));
    }else{
        draw_interface.setSceneRect(0,0,m_draw_size.width(),m_draw_size.height());
        draw_interface.addPixmap(m_bitmaps[k%63].scaled(m_draw_size));
    }
}

void Model::thread_repaint(unsigned w_from, unsigned w_to, unsigned h_from,unsigned h_to){
    vector_vector transformed_points;
    unsigned how_much = w_to - w_from;
    for(unsigned i = 0; i< how_much; ++i){
        transformed_points.emplace_back();
        for(unsigned j = 0; j < how_much; ++j)
        {
            transformed_points[i].push_back(m_points[i+w_from][j+h_from].return_as_vector());
            transformed_points[i][j] = m_transformations * transformed_points[i][j];
            for (int k = 0; k < 3; ++k)
                transformed_points[i][j][k] /= transformed_points[i][j][3];

            m_points2D[i+w_from][j+h_from].rx() = transformed_points[i][j][0];
            m_points2D[i+w_from][j+h_from].ry() = transformed_points[i][j][1];
        }

    }
    QVector<QPoint> lines_to_draw;
    for(unsigned i = 0; i< how_much-1; ++i)
    {
        for(unsigned j = 0; j < how_much-1; ++j)
        {
            lines_to_draw.push_back(m_points2D[i+w_from][j+h_from]);
            lines_to_draw.push_back(m_points2D[i+w_from+1][j+h_from]);
            lines_to_draw.push_back(m_points2D[i+w_from][j+h_from]);
            lines_to_draw.push_back(m_points2D[i+w_from][j+1+h_from]);
        }
    }
    for(unsigned j = 0; j < how_much - 1; ++j){
        lines_to_draw.push_back(m_points2D[w_to-1][j+h_from]);
        lines_to_draw.push_back(m_points2D[w_to-1][j+1+h_from]);
        lines_to_draw.push_back(m_points2D[j+w_from][h_to-1]);
        lines_to_draw.push_back(m_points2D[j+1+w_from][h_to-1]);
    }
    m_painter->drawLines(lines_to_draw);
    return;
}

void Model::start_animation(){
    k=0;
    m_transformations = get_perspective_matrix()* get_scaling_matrix()* get_rotation_matrix(x_rotation, y_rotation, z_rotation)* Translate(-static_cast<double>(m_width_in_points*(m_point_width_modifier/2.)), -static_cast<double>(m_height_in_points*(m_point_height_modifier/2.)));
    m_timer->start(50);
}

void Model::stop_animation(){
    m_timer->stop();
    m_bitmaps.clear();    
}


void Model::redraw(){
    repaint();
}

void Model::thread_sine_calc(unsigned w_from, unsigned w_to, unsigned h_from,unsigned h_to){
    for (unsigned i = w_from; i < w_to; ++i)
        for (unsigned j = h_from; j < h_to; ++j){
            m_points[i][j][2]=0;
            for(unsigned l = 0; l < m_points[i][j].distance.size(); ++l){
                m_points[i][j][2]+=m_ampfreq[l].first*10*sin(k - m_ampfreq[l].second*0.01*m_points[i][j].distance[l]);
            }
         }
}

void Model::connect_layers(){
    QVector<QPoint> lines_to_draw;
    for(unsigned i =0 ; i<m_width_in_points; ++i){
        lines_to_draw.push_back(m_points2D[m_width_in_points/2-1][i]);
        lines_to_draw.push_back(m_points2D[m_width_in_points/2][i]);
        lines_to_draw.push_back(m_points2D[i][m_width_in_points/2-1]);
        lines_to_draw.push_back(m_points2D[i][m_width_in_points/2]);
    }

    m_painter->drawLines(lines_to_draw);
    return;
}

void Model::sine_calc(int calc)
{
    k+=calc;
    QThread *thread1 = QThread::create([this]{thread_sine_calc(0,m_width_in_points/2,0,m_height_in_points/2);});
    QThread *thread2 = QThread::create([this]{thread_sine_calc(m_width_in_points/2,m_width_in_points,0,m_height_in_points/2);});
    QThread *thread3 = QThread::create([this]{thread_sine_calc(0,m_width_in_points/2,m_height_in_points/2,m_height_in_points);});
    QThread *thread4 = QThread::create([this]{thread_sine_calc(m_width_in_points/2,m_width_in_points,m_height_in_points/2,m_height_in_points);});
    thread1->start();
    thread2->start();
    thread3->start();
    thread4->start();
    thread1->wait();
    thread2->wait();
    thread3->wait();
    thread4->wait();
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

void Model::print_frame(){
    QPrinter printer;
    if (QPrintDialog(&printer).exec() == QDialog::Accepted) {
        QPainter painter(&printer);
        painter.setRenderHint(QPainter::Antialiasing);
        m_view.access_ui().graphicsView->scene()->render(&painter);
    }
     return;
}

void Model::calculate_matrices()
{
    m_transformations = get_perspective_matrix()* get_scaling_matrix()* get_rotation_matrix(x_rotation, y_rotation, z_rotation)* Translate(-static_cast<double>(m_width_in_points*(m_point_width_modifier/2.)), -static_cast<double>(m_height_in_points*(m_point_height_modifier/2.)));
    redraw();
}
