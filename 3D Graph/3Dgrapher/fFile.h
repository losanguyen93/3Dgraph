#ifndef fFile_h
#define fFile_h
#include <QtGui>
#include <QFile>
#include <QTime>




typedef struct  //������ ����������� ��� ���������
 { 
	 char *fun;
	 double dx;
	 double n;
	 double xe;
	 QDateTime Time;
	 
	 
}frecType;

class dataFile  // ����� ������ � ������
{	
	
public:
	QFile *f;
	QFile *f1; 
	QFile *f2; 

	frecType rec;
	dataFile();
	~dataFile();                
	bool addRec(frecType r);      //���������� � �����
	bool readRec();	              //��������� �����	
	bool bDelFitem(frecType &Dr);  //�������� ������� Dr �� �����
	bool bCorFitem(frecType &Dr,int irow);//������ ��������
	void beginf(){f->reset();}    //������������� ��������� �����
	
};
#endif
