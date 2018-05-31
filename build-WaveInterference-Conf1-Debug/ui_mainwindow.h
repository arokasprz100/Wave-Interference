/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_2;
    QGraphicsView *graphicsView;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_3;
    QVBoxLayout *verticalLayout_2;
    QPushButton *m_animation;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *m_previous;
    QPushButton *m_next;
    QSpacerItem *verticalSpacer;
    QVBoxLayout *verticalLayout_3;
    QPushButton *m_save;
    QPushButton *m_clipboard;
    QSpacerItem *verticalSpacer_4;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_2;
    QScrollBar *x_bar;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_3;
    QScrollBar *y_bar;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label;
    QScrollBar *z_bar;
    QSpacerItem *verticalSpacer_5;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1066, 672);
        MainWindow->setMouseTracking(false);
        MainWindow->setWindowOpacity(2);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));

        horizontalLayout_2->addWidget(graphicsView);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, -1, -1, -1);
        verticalSpacer_3 = new QSpacerItem(5, 10, QSizePolicy::Minimum, QSizePolicy::MinimumExpanding);

        verticalLayout->addItem(verticalSpacer_3);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        m_animation = new QPushButton(centralWidget);
        m_animation->setObjectName(QStringLiteral("m_animation"));
        m_animation->setMinimumSize(QSize(70, 40));

        verticalLayout_2->addWidget(m_animation);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        m_previous = new QPushButton(centralWidget);
        m_previous->setObjectName(QStringLiteral("m_previous"));

        horizontalLayout_3->addWidget(m_previous);

        m_next = new QPushButton(centralWidget);
        m_next->setObjectName(QStringLiteral("m_next"));

        horizontalLayout_3->addWidget(m_next);


        verticalLayout_2->addLayout(horizontalLayout_3);


        verticalLayout->addLayout(verticalLayout_2);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        m_save = new QPushButton(centralWidget);
        m_save->setObjectName(QStringLiteral("m_save"));

        verticalLayout_3->addWidget(m_save);

        m_clipboard = new QPushButton(centralWidget);
        m_clipboard->setObjectName(QStringLiteral("m_clipboard"));

        verticalLayout_3->addWidget(m_clipboard);


        verticalLayout->addLayout(verticalLayout_3);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_4);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setMaximumSize(QSize(10, 16777215));

        horizontalLayout_6->addWidget(label_2);

        x_bar = new QScrollBar(centralWidget);
        x_bar->setObjectName(QStringLiteral("x_bar"));
        x_bar->setStyleSheet(QStringLiteral("z_bar->setStyleSheet(\"background-color: yellow\");"));
        x_bar->setMaximum(359);
        x_bar->setOrientation(Qt::Horizontal);

        horizontalLayout_6->addWidget(x_bar);


        verticalLayout_4->addLayout(horizontalLayout_6);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setMaximumSize(QSize(10, 16777215));

        horizontalLayout_5->addWidget(label_3);

        y_bar = new QScrollBar(centralWidget);
        y_bar->setObjectName(QStringLiteral("y_bar"));
        y_bar->setMaximum(359);
        y_bar->setOrientation(Qt::Horizontal);

        horizontalLayout_5->addWidget(y_bar);


        verticalLayout_4->addLayout(horizontalLayout_5);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setMaximumSize(QSize(10, 16777215));
        label->setLayoutDirection(Qt::RightToLeft);

        horizontalLayout_4->addWidget(label);

        z_bar = new QScrollBar(centralWidget);
        z_bar->setObjectName(QStringLiteral("z_bar"));
        z_bar->setStyleSheet(QStringLiteral(""));
        z_bar->setMaximum(359);
        z_bar->setOrientation(Qt::Horizontal);

        horizontalLayout_4->addWidget(z_bar);


        verticalLayout_4->addLayout(horizontalLayout_4);


        verticalLayout->addLayout(verticalLayout_4);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_5);


        horizontalLayout_2->addLayout(verticalLayout);


        gridLayout->addLayout(horizontalLayout_2, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1066, 20));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);
        QObject::connect(m_animation, SIGNAL(clicked(bool)), MainWindow, SLOT(start_clicked()));
        QObject::connect(x_bar, SIGNAL(valueChanged(int)), MainWindow, SLOT(x_rotated(int)));
        QObject::connect(y_bar, SIGNAL(valueChanged(int)), MainWindow, SLOT(y_rotated(int)));
        QObject::connect(z_bar, SIGNAL(valueChanged(int)), MainWindow, SLOT(z_rotated(int)));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Wave Interference", nullptr));
        m_animation->setText(QApplication::translate("MainWindow", "Start", nullptr));
        m_previous->setText(QApplication::translate("MainWindow", "<-", nullptr));
        m_next->setText(QApplication::translate("MainWindow", "->", nullptr));
        m_save->setText(QApplication::translate("MainWindow", "Save to file", nullptr));
        m_clipboard->setText(QApplication::translate("MainWindow", "Copy to clipboard", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "X:", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "Y:", nullptr));
        label->setText(QApplication::translate("MainWindow", "Z:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
