#include <QApplication>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
   QApplication a (argc, argv);
   MainWindow w;
   w.show();
   w.setAttribute (Qt::WA_QuitOnClose);
   a.connect( &a, SIGNAL( lastWindowClosed() ), &a, SLOT( quit() ) );
    
   return a.exec();
}
