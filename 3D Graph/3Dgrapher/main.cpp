#include "myclass.h"
#include <QtGui/QApplication>

int main(int argc, char** argv) 
{ 
   QApplication app(argc, argv); // создаём приложение, инициализация оконной системы
 
   Win win(0); // создаём виджет класса Scene3D
   win.setFixedSize(QSize(720,970));
   win.show(); // изобразить виджет
    
   return app.exec();
}