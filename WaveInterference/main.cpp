#include "mainwindow.h"
#include <QApplication>
#include "model.h"
#include "ui_mainwindow.h"
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
    model.print_lines();
    w.print_receivers();
    return a.exec();
}
