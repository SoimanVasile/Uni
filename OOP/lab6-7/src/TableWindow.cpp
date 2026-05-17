#include "TableWindow.h"
#include "produs_tip.h"

#include <QVBoxLayout>
#include <QHeaderView>

static QString tip_to_qstring(ProdusTip tip) {
    switch (tip) {
        case LACTATE:   return "LACTATE";
        case CARNE:     return "CARNE";
        case DULCIURI:  return "DULCIURI";
        case CURATENIE: return "CURATENIE";
    }
    return "???";
}

TableWindow::TableWindow(ServiceProdus& service_produse, QWidget *parent)
    : QWidget(parent), service(service_produse)
{
    this->setWindowTitle("Produse - Vizualizare Tabelara");
    this->resize(700, 450);
    set_up_ui();
    refresh();
}

void TableWindow::set_up_ui() {
    QVBoxLayout* layout = new QVBoxLayout(this);

    this->setStyleSheet(
        "QWidget { font-family: 'Segoe UI', Arial, sans-serif; font-size: 10pt; }"
        "QTableWidget { border: 1px solid #CCC; border-radius: 4px; gridline-color: #E0E0E0; }"
        "QHeaderView::section { background-color: #0078D7; color: white; padding: 6px; "
        "    font-weight: bold; border: none; }"
        "QTableWidget::item { padding: 4px; }"
        "QTableWidget::item:selected { background-color: #CCE5FF; color: black; }"
    );

    table = new QTableWidget();
    table->setColumnCount(4);
    table->setHorizontalHeaderLabels({"Nume", "Producator", "Tip", "Pret"});
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setAlternatingRowColors(true);
    table->horizontalHeader()->setStretchLastSection(true);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->verticalHeader()->setVisible(false);

    layout->addWidget(table);
}

void TableWindow::refresh() {
    const auto& produse = service.get_all();
    table->setRowCount(static_cast<int>(produse.size()));

    for (int i = 0; i < static_cast<int>(produse.size()); ++i) {
        const auto& p = produse[static_cast<size_t>(i)];
        table->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(p.get_nume())));
        table->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(p.get_producator())));
        table->setItem(i, 2, new QTableWidgetItem(tip_to_qstring(p.get_tip())));
        table->setItem(i, 3, new QTableWidgetItem(QString::number(p.get_pret(), 'f', 2)));
    }
}
