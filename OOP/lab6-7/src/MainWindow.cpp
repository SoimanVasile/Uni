#include "MainWindow.h"
#include "qabstractspinbox.h"
#include "qboxlayout.h"
#include "qpushbutton.h"
#include <QHBoxLayout>
#include <QPushButton>
#include <QListWidget>
#include <QFormLayout>
#include <QLineEdit>

void MainWindow::set_up_ui(){
    QHBoxLayout* layout = new QHBoxLayout(this);

    QVBoxLayout* box1=new QVBoxLayout(this);
    QVBoxLayout* box2=new QVBoxLayout(this);


    auto item_list = new QListWidget();

    QPushButton* buttonV1 = new QPushButton("Remove");
    QPushButton* buttonV2 = new QPushButton("SortByName");
    QPushButton* buttonV3 = new QPushButton("SortByPrice");

    QHBoxLayout* small_buttons = new QHBoxLayout(this);

    small_buttons->addWidget(buttonV1);
    small_buttons->addWidget(buttonV2);
    small_buttons->addWidget(buttonV3);

    QPushButton* button12 = new QPushButton("Add");
    QPushButton* button22 = new QPushButton("Update");

    QFormLayout *formLayout = new QFormLayout();

    QLineEdit* editName = new QLineEdit;
    QLineEdit* editProducator = new QLineEdit;
    QLineEdit* editTip = new QLineEdit;
    QLineEdit* editPret = new QLineEdit;
    formLayout->addRow("Nume", editName);
    formLayout->addRow("Producator", editProducator);
    formLayout->addRow("Tip", editTip);
    formLayout->addRow("Pret", editPret);

    QHBoxLayout* small_buttons1 = new QHBoxLayout(this);
    QHBoxLayout* small_buttons2 = new QHBoxLayout(this);

    small_buttons1->addWidget(button12);
    small_buttons1->addWidget(button22);

    QPushButton* button123 = new QPushButton("FilterByName");
    QPushButton* button223 = new QPushButton("FilterByPret");
    QPushButton* button323 = new QPushButton("FilterByProducator");

    small_buttons2->addWidget(button123);
    small_buttons2->addWidget(button223);
    small_buttons2->addWidget(button323);

    QVBoxLayout* small_box2=new QVBoxLayout(this);
    small_box2->addLayout(formLayout);
    small_box2->addLayout(small_buttons1);
    small_box2->addLayout(small_buttons2);

    box1->addWidget(item_list);
    box1->addLayout(small_buttons);
    box2->addLayout(small_box2);

    layout->addLayout(box1);
    layout->addLayout(box2);

    this->show();
}
