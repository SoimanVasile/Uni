#include "qapplication.h"
#include "repo_file.h"
#include "service_produs.h"
#include "MainWindow.h"
#include "validator.h"
#include <QApplication>

int main(int argc, char** argv){
    QApplication app(argc, argv);
    RepoFile repo("repo_produs.bak");
    Validator validator;
    ServiceProdus service(repo, validator);

    MainWindow window(service);
    window.show();

    return app.exec();
}
