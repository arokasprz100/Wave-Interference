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
    is_source_triggered = false;
    ui->graphicsView->setHorizontalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
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

void MainWindow::source_trigger(int val){
    is_source_triggered = val;
}

void MainWindow::add_clicked(){

}

void MainWindow::delete_clicked(){

}
