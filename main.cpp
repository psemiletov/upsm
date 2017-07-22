#include <QApplication>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
   QApplication a (argc, argv);
   MainWindow w;
   w.show();
   w.setAttribute (Qt::WA_QuitOnClose);
   w.hide();
    
   return a.exec();
}
