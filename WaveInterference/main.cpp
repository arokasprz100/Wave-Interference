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
    QObject::connect(&w, SIGNAL(window_resized(QSize)),
                     &model, SLOT(set_draw_size(QSize)));
    QObject::connect(&w, SIGNAL(start_animation()),
                     &model, SLOT(start_animation()));
    QObject::connect(&w, SIGNAL(redraw()),
                     &model, SLOT(redraw()));
    QObject::connect(&w, SIGNAL(calculate_matrices()),
                     &model, SLOT(calculate_matrices()));
    QObject::connect(&w, SIGNAL(stop_animation()),
                     &model, SLOT(stop_animation()));
    QObject::connect(&w, SIGNAL(previous()),
                     &model, SLOT(previous()));
    QObject::connect(&w, SIGNAL(next()),
                     &model, SLOT(next()));
    QObject::connect(&w, SIGNAL(source_added(int,int,double,double)),
                     &model, SLOT(source_added(int, int, double, double)));
    QObject::connect(&w, SIGNAL(sources_deleted()),
                     &model, SLOT(sources_deleted()));
    QObject::connect(&w, SIGNAL(model_clipboard()),
                     &model, SLOT(model_clipboard()));
    QObject::connect(&w, SIGNAL(model_save()),
                     &model, SLOT(model_save()));

    return a.exec();
}
