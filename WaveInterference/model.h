#ifndef MODEL_H
#define MODEL_H

#include "point.h"
#include <vector>
#include <QGraphicsScene>
#include "mainwindow.h"

using point_vector = std::vector<std::vector<Point>>;

class Model : public QObject
{

    Q_OBJECT

public:
    Model(MainWindow& view, unsigned width = 30, unsigned height = 30);

    void print_lines();

private:
    point_vector m_points;
    unsigned m_width_in_points, m_height_in_points;
    QSize m_draw_size;
    MainWindow& m_view;

public slots:
    void set_draw_size(QSize draw_size);
};

#endif // MODEL_H
