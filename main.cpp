#include "view.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    gameModel gameModel;
    MainWindow w(&gameModel);
    w.show();
    return a.exec();
}
