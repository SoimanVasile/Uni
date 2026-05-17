#include <iostream>
#include <QApplication>
#include "MainWindow.h"

int main(int argc, char** argv){
    QApplication app(argc, argv);
    Repo repo("repo.txt");
    Service service(repo);
    MainWindow window(service);

    window.show();

    return app.exec();
}
