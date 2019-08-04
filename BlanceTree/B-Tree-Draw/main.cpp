#include "mainwindow.h"
#include <QApplication>

int Node_num=0;
Node*Root_Node;
int xx=0;
int yy=0;
bool insert_fail=false;
bool del_fail=false;
int search_fail=0;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
