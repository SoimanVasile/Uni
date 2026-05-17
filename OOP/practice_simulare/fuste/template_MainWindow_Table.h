#pragma once
#include <QWidget>
#include <QString>
#include <QTableWidget>
#include <QHeaderView>
#include <vector>

class MainWindow : public QWidget{

    private:
        Q_OBJECT
        Service& service;

        QTableWidget* table = new QTableWidget;

        void set_up(){
            // Setam nr de coloane si headerele
            table->setColumnCount(4); // cate coloane avem
            table->setHorizontalHeaderLabels({"Cod", "Denumire", "Camp3", "Camp4"});

            // Optional: coloanele sa ocupe tot spatiul
            table->horizontalHeader()->setStretchLastSection(true);
            // table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

            // Optional: selectam rand intreg, nu celula
            table->setSelectionBehavior(QAbstractItemView::SelectRows);

            // Optional: un singur rand selectat o data
            table->setSelectionMode(QAbstractItemView::SingleSelection);

            // Optional: nu putem edita direct in tabel
            table->setEditTriggers(QAbstractItemView::NoEditTriggers);

            // Conectam semnalul de selectie
            connect(table, &QTableWidget::itemSelectionChanged, this, &MainWindow::on_item_selectedT);
        }

        // Pt QTableWidget
        void on_item_selectedT(){
            auto items = table->selectedItems();
            if (items.empty()) return;

            // Luam randul selectat
            int row = table->currentRow();

            // Citim din coloana 0 (unde am pus cod-ul)
            // Varianta 1: din text
            QString cod = table->item(row, 0)->text();
            int cod_bun = cod.toInt();

            // Varianta 2: din UserRole (daca am setat data pe item)
            // int cod_bun = table->item(row, 0)->data(Qt::UserRole).toInt();

            auto all = service.get_all();

            auto it = std::find_if(all.begin(), all.end(), [&](const DOMAIN& i){
                    return i.get_cod() == cod_bun;
                    });

            if (it == all.end()) return;
            const DOMAIN& i = *it;
            //Modificam edit lineurile
        }

        // PT QTableWidget
        void refresh(std::vector<DOMAIN> items){
            table->setRowCount(0); // stergem toate randurile

            for (const auto& item : items){
                int row = table->rowCount();
                table->insertRow(row);

                // Coloana 0: Cod
                auto* item_cod = new QTableWidgetItem(QString::number(item.get_cod()));
                // Optional: punem cod-ul si in UserRole
                item_cod->setData(Qt::UserRole, item.get_cod());
                table->setItem(row, 0, item_cod);

                // Coloana 1: Denumire
                table->setItem(row, 1, new QTableWidgetItem(
                    QString::fromStdString(item.get_denumire())));

                // Coloana 2: alt camp
                // table->setItem(row, 2, new QTableWidgetItem(...));

                // Coloana 3: alt camp
                // table->setItem(row, 3, new QTableWidgetItem(...));

                // Optional: coloram randul
                // for (int col = 0; col < table->columnCount(); col++){
                //     if (item.get_disponibilitate())
                //         table->item(row, col)->setBackground(QBrush(QColor(144, 238, 144)));
                //     else
                //         table->item(row, col)->setBackground(QBrush(QColor(255, 102, 102)));
                // }
            }
        }

    public:
        MainWindow(Service& s):service(s){set_up();}

};
