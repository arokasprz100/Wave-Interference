#ifndef MODEL_H
#define MODEL_H

#include "point.h"
#include "matrix.h"
#include <vector>
#include <QGraphicsScene>
#include "mainwindow.h"
#include "vector4.h"
#include <QPixmap>
#include <QTimer>

class QPainter;

using point_vector = std::vector<std::vector<Point>>;
using vector_vector = std::vector<std::vector<Vector4>>;

class Model : public QObject
{

    Q_OBJECT

public:
    Model(MainWindow& view, unsigned width = 200, unsigned height = 200);

    void repaint();

private:
    point_vector m_points;
    unsigned m_width_in_points, m_height_in_points;
    QSize m_draw_size;
    MainWindow& m_view;
    QPixmap m_bitmap;
    int& x_rotation;
    int& y_rotation;
    int& z_rotation;
    bool& is_animated;
    QPainter* m_painter;
    std::vector<std::pair<double, double> > m_ampfreq;
    void thread_sine_calc(unsigned w_from, unsigned w_to, unsigned h_from,unsigned h_to);
    void thread_repaint(unsigned w_from, unsigned w_to, unsigned h_from,unsigned h_to);
    std::vector<std::vector<QPoint>> m_points2D;

    Matrix m_transformations;

    QTimer* m_timer;
    QSize m_pixmap_size;
    double m_point_width_modifier;
    double m_point_height_modifier;
    int k;

public slots:
    void set_draw_size(QSize draw_size);
    void start_animation();
    void stop_animation();
    void next();
    void previous();
    void redraw();
    void sine_calc(int calc = 1);
    void source_added(int x_pos, int y_pos, double amplitude, double frequency);
    void sources_deleted();
    void model_clipboard();
    void model_save();
    void print_frame();
    void calculate_matrices();
};

#endif // MODEL_H
