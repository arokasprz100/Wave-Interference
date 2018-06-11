#include "customdialog.h"
#include <QIntValidator>
#include <QDoubleValidator>


CustomDialog::CustomDialog()
{
    grid = new QGridLayout;
    x_label = new QLabel("X position(0-1000)");
    y_label = new QLabel("Y position(0-1000)");
    frequency_label = new QLabel("Frequency(0.0-9.9)");
    amplitude_label = new QLabel("Amplitude(0.0-9.9)");

    x_edit = new QLineEdit();
    x_edit->setValidator(new QIntValidator(0,1000,x_edit));

    y_edit = new QLineEdit();
    y_edit->setValidator(new QIntValidator(0,1000,y_edit));

    frequency_edit = new QLineEdit();
    QDoubleValidator *dbval = new QDoubleValidator(0.0, 9.9, 1, frequency_edit);
    dbval->setNotation(QDoubleValidator::StandardNotation);
    frequency_edit->setValidator(dbval);

    amplitude_edit = new QLineEdit();
    QDoubleValidator *dbval2 = new QDoubleValidator(0.0, 9.9, 1, amplitude_edit);
    dbval2->setNotation(QDoubleValidator::StandardNotation);
    amplitude_edit->setValidator(dbval2);

    grid->addWidget(x_label, 0, 0);
    grid->addWidget(x_edit, 0, 1);
    grid->addWidget(y_label, 1, 0);
    grid->addWidget(y_edit, 1, 1);
    grid->addWidget(frequency_label, 2, 0);
    grid->addWidget(frequency_edit, 2, 1);
    grid->addWidget(amplitude_label, 3, 0);
    grid->addWidget(amplitude_edit, 3, 1);

    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    grid->addWidget(buttonBox,4,0,1,2);
    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    setLayout(grid);

}

int CustomDialog::get_x(){
    return x_edit->text().toInt();
}

int CustomDialog::get_y(){
    return y_edit->text().toInt();
}

double CustomDialog::get_frequency(){
    return frequency_edit->text().replace(",", ".").toDouble();
}

double CustomDialog::get_amplitude(){
    return amplitude_edit->text().replace(",", ".").toDouble();
}
