#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsScene>
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QGraphicsScene* scene = new QGraphicsScene(this);
    ui->setupUi(this);
    ui->graphicsView->setScene(scene);
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
