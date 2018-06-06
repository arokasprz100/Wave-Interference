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
    int& get_x_rotation(){return x_rotation;}
    int& get_y_rotation(){return y_rotation;}
    int& get_z_rotation(){return z_rotation;}
    bool& get_is_animated(){return is_animated;}

private:
    Ui::MainWindow *ui;
    void resizeEvent(QResizeEvent* event);
    int x_rotation, y_rotation, z_rotation;
    bool is_animated;
    bool is_source_triggered;

signals:
    void window_resized(QSize new_size);
    void next();
    void previous();
    void start_animation();
    void stop_animation();
    void redraw();

public slots:
    void z_rotated(int rcv);
    void y_rotated(int rcv);
    void x_rotated(int rcv);
    void start_clicked();
    void next_clicked();
    void previous_clicked();
    void add_clicked();
    void delete_clicked();
};

#endif // MAINWINDOW_H
