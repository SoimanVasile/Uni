#pragma once

#include "qboxlayout.h"
#include "qdebug.h"
#include "qformlayout.h"
#include "qpushbutton.h"
#include "service.h"
#include <QWidget>
#include <QListWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QComboBox>
#include <QFormLayout>
#include <QVariant>
#include <QString>
#include <QDebug>

class MainWindow : public QWidget{
    private:

        Service& service;

        QListWidget* list = new QListWidget;
        QLineEdit* edit_cod = new QLineEdit;
        QLineEdit* edit_denumire = new QLineEdit;
        QLineEdit* edit_pret = new QLineEdit;
        QComboBox* edit_marime = new QComboBox;
        QComboBox* edit_available = new QComboBox;
        QPushButton* buttonInchiriere = new QPushButton("Inchiriere Rochie");


        void on_item_selected(){
            auto items = list->selectedItems();
            if (items.empty()) return;

            QString cod = items[0]->data(Qt::UserRole).toString();

            int cod_bun = cod.toInt();

            auto all = service.get_all();

            auto it = std::find_if(all.begin(), all.end(), [&](const Fusta& p) {
                    return p.get_cod() == cod_bun;
                    });

            if (it == all.end()) return;
            
            const Fusta& f = *it;
            edit_cod->setText(QString::number(f.get_cod()));
            edit_denumire->setText(QString::fromStdString(f.get_denumire()));
            edit_pret->setText(QString::number(f.get_pret()));
            edit_marime->setCurrentIndex(edit_marime->findData(QVariant::fromValue(f.get_marime())));
            edit_available->setCurrentIndex(edit_available->findData(f.get_disponibilitate() ? 1 : 0));
        }

        void inchiriere_fusta(){
            int cod = edit_cod->text().toInt();
            service.inchiriere(cod);
            refresh(service.get_all());
         }

        void set_up(){
            auto* main_layout = new QHBoxLayout;
            QVBoxLayout* right_side = new QVBoxLayout;


            QFormLayout* form = new QFormLayout;

            edit_marime->addItem("XS", QVariant::fromValue(Marime::XS));
            edit_marime->addItem("S", QVariant::fromValue(Marime::S));
            edit_marime->addItem("M", QVariant::fromValue(Marime::M));
            edit_marime->addItem("L", QVariant::fromValue(Marime::L));
            edit_marime->addItem("XL", QVariant::fromValue(Marime::XL));

            edit_available->addItem("True", QVariant::fromValue(1));
            edit_available->addItem("Flase", QVariant::fromValue(0));

            form->addRow("Cod", edit_cod);
            form->addRow("Denumire", edit_denumire);
            form->addRow("Pret", edit_pret);
            form->addRow("Marime", edit_marime);
            form->addRow("Valabil", edit_available);

            right_side->addLayout(form);
            right_side->addWidget(buttonInchiriere);

            refresh(service.get_all());

            main_layout->addWidget(list);
            main_layout->addLayout(right_side);

            setLayout(main_layout);

            connect(list, &QListWidget::itemSelectionChanged, this, &MainWindow::on_item_selected);
            connect(buttonInchiriere, &QPushButton::clicked, this, &MainWindow::inchiriere_fusta);
        }

        void refresh(std::vector<Fusta> items){
            list->clear();
            for (const auto& item : items){
                auto* listItem = new QListWidgetItem(QString::fromStdString(
                    std::to_string(item.get_cod())+" ; "+item.get_denumire()+" ; "+
                    marime_to_string(item.get_marime())+" ; "+std::to_string(item.get_pret())));
                listItem->setData(Qt::UserRole, item.get_cod());
                if (item.get_disponibilitate())
                    listItem->setBackground(QBrush(QColor(144, 238, 144))); // light green
                else
                    listItem->setBackground(QBrush(QColor(255, 102, 102))); // light red
                list->addItem(listItem);
            }

        }

    public:
        MainWindow(Service& s): service(s){set_up();};

};
