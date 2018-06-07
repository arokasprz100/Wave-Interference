#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsScene>
#include <QMouseEvent>
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QGraphicsScene* scene = new QGraphicsScene(this);
    ui->setupUi(this);
    ui->graphicsView->setScene(scene);
    x_rotation = y_rotation = z_rotation = 0;
    is_animated = false;
    ui->graphicsView->setHorizontalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setAcceptDrops(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
   QMainWindow::resizeEvent(event);
   emit window_resized(this->ui->graphicsView->size());
}

void MainWindow::print_receivers(){
    std::cout<<receivers(SIGNAL(window_resized(QSize)));
}

void MainWindow::z_rotated(int rcv){
    z_rotation = rcv;
    emit redraw();
}

void MainWindow::y_rotated(int rcv){
    y_rotation = rcv;
    emit redraw();
}

void MainWindow::x_rotated(int rcv){
    x_rotation = rcv;
    emit redraw();
}

void MainWindow::start_clicked(){
    if(!is_animated){
       ui->m_clipboard->setDisabled(true);
       ui->m_save->setDisabled(true);
       ui->m_next->setDisabled(true);
       ui->m_previous->setDisabled(true);
       ui->x_bar->setDisabled(true);
       ui->y_bar->setDisabled(true);
       ui->z_bar->setDisabled(true);
       ui->m_animation->setText("Stop");
       is_animated=true;
       emit start_animation();
    }else if(is_animated){
        ui->m_clipboard->setDisabled(false);
        ui->m_save->setDisabled(false);
        ui->m_next->setDisabled(false);
        ui->m_previous->setDisabled(false);
        ui->x_bar->setDisabled(false);
        ui->y_bar->setDisabled(false);
        ui->z_bar->setDisabled(false);
        ui->m_animation->setText("Start");
        is_animated=false;
        emit stop_animation();
    }
}

void MainWindow::next_clicked(){
    emit next();
}

void MainWindow::previous_clicked(){
    emit previous();
}

void MainWindow::add_clicked(){
    dialog.show();
    if(dialog.exec()){
        int x_pos, y_pos;
        double amplitude, frequency;
        x_pos = dialog.get_x();
        y_pos = dialog.get_y();
        amplitude = dialog.get_amplitude();
        frequency = dialog.get_frequency();
        if((amplitude>0) && frequency>0 && x_pos>0 && y_pos>0){
            emit source_added(x_pos,y_pos,amplitude,frequency);
        }
    }
}

void MainWindow::delete_clicked(){
    emit sources_deleted();
}

void MainWindow::copy_clicked(){
    emit model_clipboard();
}

void MainWindow::save_clicked(){
    emit model_save();
}

void MainWindow::print_clicked(){
    emit print_frame();
}
