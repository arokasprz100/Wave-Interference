#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();

    Ui::MainWindow& access_ui()
    {
        return *ui;
    }

    void print_receivers();
private:
    Ui::MainWindow *ui;
    void resizeEvent(QResizeEvent* event);

signals:
    void window_resized(QSize new_size);

};

#endif // MAINWINDOW_H
