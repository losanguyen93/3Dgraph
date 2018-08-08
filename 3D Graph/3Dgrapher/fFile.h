#ifndef fFile_h
#define fFile_h
#include <QtGui>
#include <QFile>
#include <QTime>




typedef struct  //данные необходимые для отрисовки
 { 
	 char *fun;
	 double dx;
	 double n;
	 double xe;
	 QDateTime Time;
	 
	 
}frecType;

class dataFile  // класс работа с Файлом
{	
	
public:
	QFile *f;
	QFile *f1; 
	QFile *f2; 

	frecType rec;
	dataFile();
	~dataFile();                
	bool addRec(frecType r);      //добавление в файле
	bool readRec();	              //прочтение файла	
	bool bDelFitem(frecType &Dr);  //удаление элемент Dr из файла
	bool bCorFitem(frecType &Dr,int irow);//замена элемента
	void beginf(){f->reset();}    //переустановка указатели файла
	
};
#endif
