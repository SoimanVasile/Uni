#pragma once
#include "service_produs.h"
#include <QWidget>

class MainWindow : public QWidget{
private:
    Q_OBJECT
    ServiceProdus& service;
public:
    explicit MainWindow(ServiceProdus& service_produse, QWidget *parent = nullptr): QWidget(parent), service(service_produse){
        this->setWindowTitle("OOP cel mai smecher gui!");
        this->resize(600, 600);

        set_up_ui();
    }

    void set_up_ui();
    
    ~MainWindow() = default;
};
