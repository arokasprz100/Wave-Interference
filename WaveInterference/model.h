#ifndef MODEL_H
#define MODEL_H

#include "point.h"
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
    Model(MainWindow& view, unsigned width = 70, unsigned height = 70);

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

    QTimer* m_timer;
    QSize m_pixmap_size;
    double m_point_width_modifier;
    double m_point_height_modifier;

public slots:
    void set_draw_size(QSize draw_size);
    void start_animation();
    void stop_animation();
    void next();
    void previous();
    void redraw();
    void sine_calc(int calc = 1);
};

#endif // MODEL_H
