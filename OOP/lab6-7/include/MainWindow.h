#pragma once
#include "produs_tip.h"
#include "TableWindow.h"
#include "qcombobox.h"
#include "service_produs.h"
#include <QWidget>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QComboBox>
#include <QLabel>

class MainWindow : public QWidget{
private:
    Q_OBJECT
    ServiceProdus& service;

    // Widgets kept as members so slots can access them
    QListWidget* item_list;
    QLineEdit* editName;
    QLineEdit* editProducator;
    QComboBox* editTip;
    QLineEdit* editPret;

    QPushButton* buttonRemove;
    QPushButton* buttonSortByName;
    QPushButton* buttonSortByPrice;
    QPushButton* buttonAdd;
    QPushButton* buttonUndo;
    QPushButton* buttonUpdate;
    QPushButton* buttonFilterByName;
    QPushButton* buttonFilterByPret;
    QPushButton* buttonFilterByProducator;
    QPushButton* buttonSortByNameType;

    QListWidget* cart_list;
    QPushButton* buttonEmptyCart;
    QPushButton* buttonAddToCart;
    QPushButton* buttonGenerateCart;
    QPushButton* buttonExportCsv;
    QPushButton* buttonExportHtml;
    QLabel* cart_total_label;

    QPushButton* buttonOpenTable;
    TableWindow* tableWindow;

    QHBoxLayout* horizontal_buttons_freq;
    std::vector<QPushButton> freq_tips;
    QString getTipName(const ProdusTip& tip) const;

    void set_up_ui();
    void refresh_list(const std::vector<Produs>& produse);
    void refresh_cart(const std::vector<Produs>& produse);
    void show_error(const std::string& msg);

private slots:
    void on_add();
    void on_update();
    void on_remove();
    void on_sort_name();
    void on_sort_price();
    void on_sort_name_type();
    void on_filter_name();
    void on_filter_pret();
    void on_filter_producator();
    void on_item_selected();
    void on_undo();
    void on_empty_cart();
    void on_add_to_cart();
    void on_generate_cart();
    void on_export_csv();
    void on_export_html();
    void on_open_table();

public:
    explicit MainWindow(ServiceProdus& service_produse, QWidget *parent = nullptr);
    ~MainWindow() = default;
};
