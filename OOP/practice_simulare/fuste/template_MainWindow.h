#pragma once
#include <QWidget>
#include <QString>
#include <vector>

class MainWindow : public QWidget{

    private:
        Q_OBJECT
        Service& service;

        void set_up(){

        }
        // Pt QListWidget
        void on_item_selectedL(){
            auto items = list->selectedItems();
            if (items.empty()) return;

            QString cod = items[0]->data(Qt::UserRole).toString();

            int cod_bun = cod.toInt();

            auto all = service.get_all();

            auto it = std::find_if(all.begin(), all.end(), [&](const DOMAIN& i){
                    return i.get_cod() == cod_bun;
                    });

            if (it == all.end()) return;
            const DOMAIN& i = *it;
            //Modificam edit lineurile
        }

        // PT QListWidget
        void refresh(std::vector<DOMAIN> items){
            list->clear();
            for (const auto& item : items){
                //Din fieldurile clasei, le transformam in String
                auto* listItem = new QListWidgetItem();

                //Pt UserRole
                listItem->setData(Qt::UserRole, item.get_cod());

                // Am putea schimba backgroundul

                list->addItem(listItem);
            }
        }

    public:
        MainWindow(Service& s):service(s){set_up();}

};
