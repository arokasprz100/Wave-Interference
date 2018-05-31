#include "mainwindow.h"
#include <QApplication>
#include <QTimer>
#include "model.h"
#include "ui_mainwindow.h"
#include "matrix.h"
#include "transformations.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    Model model(w);
    //model.print_points(*w.access_ui().graphicsView->scene());
    QObject::connect(&w, SIGNAL(window_resized(QSize)),
                     &model, SLOT(set_draw_size(QSize)));
    QObject::connect(&w, SIGNAL(start_animation()),
                     &model, SLOT(start_animation()));
    QObject::connect(&w, SIGNAL(redraw()),
                     &model, SLOT(redraw()));
    model.repaint();
    w.print_receivers();

    return a.exec();
}
