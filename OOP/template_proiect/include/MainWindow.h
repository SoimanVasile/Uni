#pragma once
#include "service.h"

#include <stdio.h>
#include <QWidget>
#include <QPushButton>
#include <QTableWidget>

class MainWindow : public QWidget{
    private:
        Q_OBJECT
        Service* service;
        
        QPushButton* buttonExit;
        QTableWidget* table;

        void set_up();
        void refresh();
        
    private slots:
        void exit();

    public:
        MainWindow(Service* s) : service(s){};
};
