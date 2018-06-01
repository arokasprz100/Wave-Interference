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
    QObject::connect(&w, SIGNAL(stop_animation()),
                     &model, SLOT(stop_animation()));
    QObject::connect(&w, SIGNAL(previous()),
                     &model, SLOT(previous()));
    QObject::connect(&w, SIGNAL(next()),
                     &model, SLOT(next()));

    return a.exec();
}
