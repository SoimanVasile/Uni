#include "MainWindow.h"
#include "TableWindow.h"
#include "attribute_produs.h"
#include "produs_tip.h"
#include "qboxlayout.h"
#include "qobject.h"
#include "qpushbutton.h"
#include "repo_produs.h"
#include "validator.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QPushButton>
#include <QListWidget>
#include <QLineEdit>
#include <QMessageBox>
#include <QInputDialog>
#include <QGroupBox>
#include <QLabel>
#include <exception>
#include <sstream>
#include <string>
#include <algorithm>

MainWindow::MainWindow(ServiceProdus& service_produse, QWidget *parent)
    : QWidget(parent), service(service_produse)
{
    this->setWindowTitle("OOP cel mai smecher gui!");
    this->resize(900, 600);
    set_up_ui();
    refresh_list(service.get_all());
    refresh_cart(service.cos_get_all());
}


void MainWindow::set_up_ui(){
    QVBoxLayout* outerLayout = new QVBoxLayout(this);
    QHBoxLayout* mainLayout = new QHBoxLayout;

    // Styling
    this->setStyleSheet(
        "QWidget { font-family: 'Segoe UI', Arial, sans-serif; font-size: 10pt; }"
        "QPushButton { background-color: #0078D7; color: white; border-radius: 4px; padding: 6px; min-width: 80px; }"
        "QPushButton:hover { background-color: #005A9E; }"
        "QGroupBox { font-weight: bold; border: 1px solid #CCC; border-radius: 5px; margin-top: 10px; }"
        "QGroupBox::title { subcontrol-origin: margin; subcontrol-position: top left; padding: 0 3px; }"
        "QListWidget { border: 1px solid #CCC; border-radius: 4px; padding: 2px; }"
        "QLineEdit, QComboBox { border: 1px solid #CCC; border-radius: 3px; padding: 4px; }"
    );

    // --- Left Panel: Products ---
    QGroupBox* groupProducts = new QGroupBox("Produse");
    QVBoxLayout* layoutProducts = new QVBoxLayout;
    
    item_list = new QListWidget();
    layoutProducts->addWidget(item_list);
    
    // Sorting Buttons
    QHBoxLayout* layoutSort = new QHBoxLayout;
    buttonSortByName = new QPushButton("Sort Nume");
    buttonSortByPrice = new QPushButton("Sort Pret");
    buttonSortByNameType = new QPushButton("Sort Nume+Tip");
    layoutSort->addWidget(buttonSortByName);
    layoutSort->addWidget(buttonSortByPrice);
    layoutSort->addWidget(buttonSortByNameType);
    layoutProducts->addLayout(layoutSort);
    
    // Filtering Buttons
    QHBoxLayout* layoutFilter = new QHBoxLayout;
    buttonFilterByName = new QPushButton("Filtru Nume");
    buttonFilterByPret = new QPushButton("Filtru Pret");
    buttonFilterByProducator = new QPushButton("Filtru Prod.");
    layoutFilter->addWidget(buttonFilterByName);
    layoutFilter->addWidget(buttonFilterByPret);
    layoutFilter->addWidget(buttonFilterByProducator);
    layoutProducts->addLayout(layoutFilter);
    
    // Freq Buttons (dynamic)
    horizontal_buttons_freq = new QHBoxLayout;
    layoutProducts->addLayout(horizontal_buttons_freq);
    
    groupProducts->setLayout(layoutProducts);
    
    // --- Middle Panel: Form ---
    QGroupBox* groupForm = new QGroupBox("Detalii Produs");
    QVBoxLayout* layoutFormBox = new QVBoxLayout;
    
    QFormLayout *formLayout = new QFormLayout();
    editName = new QLineEdit;
    editProducator = new QLineEdit;
    editTip = new QComboBox();
    
    editTip->addItem(getTipName(ProdusTip::CARNE), QVariant::fromValue(ProdusTip::CARNE));
    editTip->addItem(getTipName(ProdusTip::LACTATE), QVariant::fromValue(ProdusTip::LACTATE));
    editTip->addItem(getTipName(ProdusTip::CURATENIE), QVariant::fromValue(ProdusTip::CURATENIE));
    editTip->addItem(getTipName(ProdusTip::DULCIURI), QVariant::fromValue(ProdusTip::DULCIURI));
    
    editPret = new QLineEdit;
    formLayout->addRow("Nume:", editName);
    formLayout->addRow("Producator:", editProducator);
    formLayout->addRow("Tip:", editTip);
    formLayout->addRow("Pret:", editPret);
    layoutFormBox->addLayout(formLayout);
    
    // Action Buttons
    QHBoxLayout* layoutActions1 = new QHBoxLayout;
    buttonAdd = new QPushButton("Adauga");
    buttonUpdate = new QPushButton("Modifica");
    buttonRemove = new QPushButton("Sterge");
    layoutActions1->addWidget(buttonAdd);
    layoutActions1->addWidget(buttonUpdate);
    layoutActions1->addWidget(buttonRemove);
    layoutFormBox->addLayout(layoutActions1);
    
    buttonUndo = new QPushButton("Undo");
    layoutFormBox->addWidget(buttonUndo);
    
    layoutFormBox->addStretch();
    groupForm->setLayout(layoutFormBox);
    
    // --- Right Panel: Cart ---
    QGroupBox* groupCart = new QGroupBox("Cos Cumparaturi");
    QVBoxLayout* layoutCart = new QVBoxLayout;
    
    cart_list = new QListWidget();
    layoutCart->addWidget(cart_list);
    
    cart_total_label = new QLabel("Total: 0.00 lei");
    cart_total_label->setStyleSheet("font-weight: bold; font-size: 12pt; color: #D83B01;");
    layoutCart->addWidget(cart_total_label);
    
    QHBoxLayout* layoutCartActions1 = new QHBoxLayout;
    buttonAddToCart = new QPushButton("Adauga in Cos");
    buttonEmptyCart = new QPushButton("Goleste Cos");
    layoutCartActions1->addWidget(buttonAddToCart);
    layoutCartActions1->addWidget(buttonEmptyCart);
    layoutCart->addLayout(layoutCartActions1);
    
    QHBoxLayout* layoutCartActions2 = new QHBoxLayout;
    buttonGenerateCart = new QPushButton("Genereaza Random");
    layoutCartActions2->addWidget(buttonGenerateCart);
    layoutCart->addLayout(layoutCartActions2);
    
    QHBoxLayout* layoutCartActions3 = new QHBoxLayout;
    buttonExportCsv = new QPushButton("Export CSV");
    buttonExportHtml = new QPushButton("Export HTML");
    layoutCartActions3->addWidget(buttonExportCsv);
    layoutCartActions3->addWidget(buttonExportHtml);
    layoutCart->addLayout(layoutCartActions3);
    
    groupCart->setLayout(layoutCart);

    // --- Open Table View Button ---
    buttonOpenTable = new QPushButton("Vizualizare Tabelara");
    buttonOpenTable->setStyleSheet("background-color: #6A0DAD; padding: 8px; font-weight: bold;");
    tableWindow = nullptr;
    
    // --- Assemble Main Layout ---
    mainLayout->addWidget(groupProducts, 2);
    mainLayout->addWidget(groupForm, 1);
    mainLayout->addWidget(groupCart, 2);

    outerLayout->addLayout(mainLayout);
    outerLayout->addWidget(buttonOpenTable);

    // --- Connections ---
    connect(buttonAdd, &QPushButton::clicked, this, &MainWindow::on_add);
    connect(buttonUpdate, &QPushButton::clicked, this, &MainWindow::on_update);
    connect(buttonRemove, &QPushButton::clicked, this, &MainWindow::on_remove);
    connect(buttonSortByName, &QPushButton::clicked, this, &MainWindow::on_sort_name);
    connect(buttonSortByPrice, &QPushButton::clicked, this, &MainWindow::on_sort_price);
    connect(buttonSortByNameType, &QPushButton::clicked, this, &MainWindow::on_sort_name_type);
    connect(buttonFilterByName, &QPushButton::clicked, this, &MainWindow::on_filter_name);
    connect(buttonFilterByPret, &QPushButton::clicked, this, &MainWindow::on_filter_pret);
    connect(buttonFilterByProducator, &QPushButton::clicked, this, &MainWindow::on_filter_producator);
    connect(item_list, &QListWidget::itemSelectionChanged, this, &MainWindow::on_item_selected);
    connect(buttonUndo, &QPushButton::clicked, this, &MainWindow::on_undo);
    
    connect(buttonAddToCart, &QPushButton::clicked, this, &MainWindow::on_add_to_cart);
    connect(buttonEmptyCart, &QPushButton::clicked, this, &MainWindow::on_empty_cart);
    connect(buttonGenerateCart, &QPushButton::clicked, this, &MainWindow::on_generate_cart);
    connect(buttonExportCsv, &QPushButton::clicked, this, &MainWindow::on_export_csv);
    connect(buttonExportHtml, &QPushButton::clicked, this, &MainWindow::on_export_html);
    connect(buttonOpenTable, &QPushButton::clicked, this, &MainWindow::on_open_table);
}

// ===================== Helpers =====================

static std::string produs_tip_to_string(ProdusTip tip) {
    switch (tip) {
        case LACTATE: return "LACTATE";
        case CARNE: return "CARNE";
        case DULCIURI: return "DULCIURI";
        case CURATENIE: return "CURATENIE";
    }
    return "???";
}

void MainWindow::refresh_list(const std::vector<Produs>& produse) {
    item_list->clear();
    for (const auto& p : produse) {
        std::ostringstream oss;
        oss << p.get_nume() << " | " << p.get_producator()
            << " | " << produs_tip_to_string(p.get_tip())
            << " | " << p.get_pret() << " lei";
        QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(oss.str()));
        item->setData(Qt::UserRole, QString::fromStdString(p.get_nume()));
        item->setData(Qt::UserRole + 1, QString::fromStdString(p.get_producator()));
        item_list->addItem(item);
    }
    while (auto item = horizontal_buttons_freq->takeAt(0)) {
        delete item->widget();
        delete item;
    }
    auto freq = service.freq_tip();
    for(auto item : freq){
        QPushButton* button = new QPushButton(QString("%1 (%2)").arg(getTipName(item.first)).arg(item.second));
        button->setStyleSheet("background-color: #4CAF50; padding: 4px; min-width: 50px;");
        connect(button, &QPushButton::clicked, this, [this, item]() {
            QMessageBox::information(this, "Frecventa", QString("Sunt %1 produse de tip %2").arg(item.second).arg(getTipName(item.first)));
        });
        horizontal_buttons_freq->addWidget(button);
    }
    horizontal_buttons_freq->parentWidget()->update();
}

void MainWindow::refresh_cart(const std::vector<Produs>& produse) {
    cart_list->clear();
    for (const auto& p : produse) {
        std::ostringstream oss;
        oss << p.get_nume() << " | " << p.get_producator() << " | " << p.get_pret() << " lei";
        cart_list->addItem(QString::fromStdString(oss.str()));
    }
    cart_total_label->setText(QString("Total: %1 lei").arg(service.cos_total()));
}

void MainWindow::show_error(const std::string& msg) {
    QMessageBox::warning(this, "Eroare", QString::fromStdString(msg));
}

QString MainWindow::getTipName(const ProdusTip& tip) const{
    switch (tip) {
        case ProdusTip::LACTATE: return "LACTATE";
        case ProdusTip::CARNE: return "CARNE";
        case ProdusTip::DULCIURI: return "DULCIURI";
        case ProdusTip::CURATENIE: return "CURATENIE";
        default: return "UNKNOWN";
    }
}

// ===================== Slots =====================

void MainWindow::on_item_selected() {
    auto items = item_list->selectedItems();
    if (items.empty()) return;

    QString nume = items[0]->data(Qt::UserRole).toString();
    QString producator = items[0]->data(Qt::UserRole + 1).toString();

    auto all = service.get_all();
    auto it = std::find_if(all.begin(), all.end(), [&](const Produs& p) {
        return p.get_nume() == nume.toStdString() && p.get_producator() == producator.toStdString();
    });
    if (it == all.end()) return;

    const Produs& p = *it;
    editName->setText(QString::fromStdString(p.get_nume()));
    editProducator->setText(QString::fromStdString(p.get_producator()));
    int index = editTip->findData(QVariant::fromValue(p.get_tip()));
    if (index != -1){
        editTip->setCurrentIndex(index);
    }
    editPret->setText(QString::number(p.get_pret()));
}

void MainWindow::on_add() {
    std::string name = editName->text().toStdString();
    std::string producator = editProducator->text().toStdString();
    QVariant data = editTip->currentData();
    std::string pret_str = editPret->text().toStdString();

    try {
        float pret = std::stof(pret_str);
        ProdusTip tip = data.value<ProdusTip>();
        AttributeProdus attrib(name, producator);
        service.add_produs(attrib, tip, pret);
        refresh_list(service.get_all());
    } catch (const ValidatorException& e) {
        show_error(e.get_mesaj());
    } catch (const RepoException& e) {
        show_error(e.get_mesaj());
    } catch (const ProdusTipExpection& e) {
        show_error(e.mesaj());
    } catch (const std::exception& e) {
        show_error(std::string("Eroare: ") + e.what());
    }
}

void MainWindow::on_update() {
    std::string name = editName->text().toStdString();
    std::string producator = editProducator->text().toStdString();
    QVariant data = editTip->currentData();
    std::string pret_str = editPret->text().toStdString();

    try {
        float pret = std::stof(pret_str);
        ProdusTip tip = data.value<ProdusTip>();
        AttributeProdus attrib(name, producator);
        service.modifica_produs(attrib, tip, pret);
        refresh_list(service.get_all());
        refresh_cart(service.cos_get_all()); // cart might contain updated product
    } catch (const ValidatorException& e) {
        show_error(e.get_mesaj());
    } catch (const RepoException& e) {
        show_error(e.get_mesaj());
    } catch (const ProdusTipExpection& e) {
        show_error(e.mesaj());
    } catch (const std::exception& e) {
        show_error(std::string("Eroare: ") + e.what());
    }
}

void MainWindow::on_remove() {
    auto items = item_list->selectedItems();
    if (items.empty()) {
        show_error("Selectati un produs din lista!");
        return;
    }

    QString nume = items[0]->data(Qt::UserRole).toString();
    QString producator = items[0]->data(Qt::UserRole + 1).toString();

    try {
        service.sterge_produs(nume.toStdString(), producator.toStdString());
        refresh_list(service.get_all());
        refresh_cart(service.cos_get_all()); // in case deleted product was in cart
    } catch (const RepoException& e) {
        show_error(e.get_mesaj());
    } catch (const ValidatorException& e) {
        show_error(e.get_mesaj());
    }
}

void MainWindow::on_sort_name() {
    refresh_list(service.sortare_dupa_nume());
}

void MainWindow::on_sort_price() {
    refresh_list(service.sortare_dupa_pret());
}

void MainWindow::on_sort_name_type() {
    refresh_list(service.sortare_dupa_nume_si_tip());
}

void MainWindow::on_filter_name() {
    bool ok;
    QString text = QInputDialog::getText(this, "Filtrare dupa Nume",
        "Introduceti numele:", QLineEdit::Normal, "", &ok);
    if (ok && !text.isEmpty()) {
        refresh_list(service.filtrare_dupa_nume(text.toStdString()));
    }
}

void MainWindow::on_filter_pret() {
    bool ok;
    QString text = QInputDialog::getText(this, "Filtrare dupa Pret",
        "Introduceti pretul maxim:", QLineEdit::Normal, "", &ok);
    if (ok && !text.isEmpty()) {
        try {
            float pret = std::stof(text.toStdString());
            refresh_list(service.filtrare_dupa_pret(pret));
        } catch (const std::exception&) {
            show_error("Introduceti un pret valid!");
        }
    }
}

void MainWindow::on_filter_producator() {
    bool ok;
    QString text = QInputDialog::getText(this, "Filtrare dupa Producator",
        "Introduceti producatorul:", QLineEdit::Normal, "", &ok);
    if (ok && !text.isEmpty()) {
        refresh_list(service.filtrare_dupa_producator(text.toStdString()));
    }
}

void MainWindow::on_undo() {
    try {
        service.undo();
        refresh_list(service.get_all());
        refresh_cart(service.cos_get_all());
    }
    catch(ValidatorException& e){
        (void)e;
        QMessageBox::warning(this, "Eroare", "Nu ai mai facut actiuni sa dai undo!");
    }
}

void MainWindow::on_empty_cart() {
    service.cos_goleste();
    refresh_cart(service.cos_get_all());
}

void MainWindow::on_add_to_cart() {
    auto items = item_list->selectedItems();
    if (items.empty()) {
        show_error("Selectati un produs din lista pentru a-l adauga in cos!");
        return;
    }
    QString nume = items[0]->data(Qt::UserRole).toString();
    try {
        service.cos_adauga(nume.toStdString());
        refresh_cart(service.cos_get_all());
    } catch (const std::exception& e) {
        show_error(e.what());
    }
}

void MainWindow::on_generate_cart() {
    bool ok;
    int numar = QInputDialog::getInt(this, "Generare Cos",
        "Introduceti numarul de produse:", 1, 1, 1000, 1, &ok);
    if (ok) {
        try {
            service.cos_genereaza(numar);
            refresh_cart(service.cos_get_all());
        } catch (const std::exception& e) {
            show_error(e.what());
        }
    }
}

void MainWindow::on_export_csv() {
    bool ok;
    QString text = QInputDialog::getText(this, "Export CSV",
        "Introduceti numele fisierului (.csv):", QLineEdit::Normal, "cos.csv", &ok);
    if (ok && !text.isEmpty()) {
        try {
            service.cos_export_csv(text.toStdString());
            QMessageBox::information(this, "Success", "Cos exportat cu succes in " + text);
        } catch (const std::exception& e) {
            show_error(e.what());
        }
    }
}

void MainWindow::on_export_html() {
    bool ok;
    QString text = QInputDialog::getText(this, "Export HTML",
        "Introduceti numele fisierului (.html):", QLineEdit::Normal, "cos.html", &ok);
    if (ok && !text.isEmpty()) {
        try {
            service.cos_export_html(text.toStdString());
            QMessageBox::information(this, "Success", "Cos exportat cu succes in " + text);
        } catch (const std::exception& e) {
            show_error(e.what());
        }
    }
}

void MainWindow::on_open_table() {
    if (!tableWindow) {
        tableWindow = new TableWindow(service, nullptr);
    }
    tableWindow->refresh();
    tableWindow->show();
    tableWindow->raise();
    tableWindow->activateWindow();
}
