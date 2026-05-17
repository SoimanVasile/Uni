#pragma once
#include "service_produs.h"
#include <QWidget>
#include <QTableWidget>
#include <QPushButton>

class TableWindow : public QWidget {
    Q_OBJECT
private:
    ServiceProdus& service;
    QTableWidget* table;

    void set_up_ui();

public:
    explicit TableWindow(ServiceProdus& service_produse, QWidget *parent = nullptr);
    ~TableWindow() = default;

public slots:
    void refresh();
};
