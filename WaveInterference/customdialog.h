#ifndef CUSTOMDIALOG_H
#define CUSTOMDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include <QDialogButtonBox>

class CustomDialog : public QDialog
{
Q_OBJECT

public:
    CustomDialog();
    int get_x();
    int get_y();
    double get_frequency();
    double get_amplitude();
private:
    QLabel* x_label;
    QLabel* y_label;
    QLabel* frequency_label;
    QLabel* amplitude_label;
    QLineEdit* x_edit;
    QLineEdit* y_edit;
    QLineEdit* frequency_edit;
    QLineEdit* amplitude_edit;
    QGridLayout* grid;
    QDialogButtonBox* buttonBox;

};

#endif // CUSTOMDIALOG_H
