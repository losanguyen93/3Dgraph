#include "myclass.h"
#include <QtGui/QApplication>

int main(int argc, char** argv) 
{ 
   QApplication app(argc, argv); // ������ ����������, ������������� ������� �������
 
   Win win(0); // ������ ������ ������ Scene3D
   win.setFixedSize(QSize(720,970));
   win.show(); // ���������� ������
    
   return app.exec();
}