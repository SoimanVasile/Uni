#include "MainWindow.h"
#include "qboxlayout.h"
#include "qpushbutton.h"
#include <QTableWidget>

#include <QHBoxLayout>
#include <QVBoxLayout>

void MainWindow::set_up(){
    QHBoxLayout* main_H_layout = new QHBoxLayout;

    QVBoxLayout* left_side_layout = new QVBoxLayout;
    QVBoxLayout* right_side_layout = new QVBoxLayout;

    table = new QTableWidget;

    buttonExit = new QPushButton;

    right_side_layout->addWidget(buttonExit);
    left_side_layout->addWidget(table);

    main_H_layout->addLayout(left_side_layout);
    main_H_layout->addLayout(right_side_layout);

    connect(buttonExit, &QPushButton::clicked, this, &MainWindow::close);
}
