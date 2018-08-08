#include "myclass.h"
#include <QtGui/QApplication>
#include <math.h>  
#include <QFile>


DataFun::DataFun(QWidget *parent) : QWidget(parent)
{ 
  n=1000;

  codec = QTextCodec::codecForName("Windows-1251"); 
  setWindowTitle(codec->toUnicode("Добавление"));
	
  frame = new QFrame(this);
  frame->setFrameShadow(QFrame::Raised);
  frame->setFrameShape(QFrame::Panel);
 
  inputLabel=new QLabel(codec->toUnicode("Ввод функции:                  "),this);  
  inputLDx =new QLabel(codec->toUnicode( "Ввод начало значения диапазона:"),this);
  inputLXe =new QLabel(codec->toUnicode( "Ввод начало конец диапазона:   "),this);
  inputLN  =new QLabel(codec->toUnicode( "Ввод шага:                     "),this);
  numP=new QLabel("",this);
  
  

 inputEdit = new QLineEdit("",this);
 inputDx   = new QLineEdit("",this);
 inputXe   = new QLineEdit("",this);
 inputN    = new QLineEdit("",this); 

 QRegExpValidator *exp= new QRegExpValidator(QRegExp("(\\d|[xy+-/()*^.]|[sin]|[cos]|[log]|[qrt]|[atan])+"),this);
     inputEdit->setValidator(exp);

   
  
  applyButton = new QPushButton(codec->toUnicode("принимать"),this);
     
   //компоновка приложений.
   
      
    
    QHBoxLayout *vLayout1 = new QHBoxLayout();
    vLayout1->addWidget(inputLabel);
	vLayout1->addWidget(inputEdit);
    vLayout1->addStretch();  
  
    QHBoxLayout *hLayDX = new QHBoxLayout();
    hLayDX->addWidget(inputLDx);
	hLayDX->addWidget(inputDx);
	hLayDX->addStretch();
    
	QHBoxLayout *hLayXE = new QHBoxLayout();
    hLayXE->addWidget(inputLXe);
	hLayXE->addWidget(inputXe);
	hLayXE->addStretch();

	QHBoxLayout *hLayN = new QHBoxLayout();
    hLayN->addWidget(inputLN);
	hLayN->addWidget(inputN);
	hLayN->addStretch();
	
		
    QVBoxLayout *vLayout5 = new QVBoxLayout(frame);
	vLayout5->addLayout(vLayout1);
	vLayout5->addLayout(hLayDX);
	vLayout5->addLayout(hLayXE);
	vLayout5->addLayout(hLayN);
	vLayout5->addWidget(numP);
	vLayout5->addStretch();

	QVBoxLayout *vLayout2 = new QVBoxLayout(this);
	vLayout2->addWidget(frame);
	vLayout2->addWidget(applyButton);
		
	connect(applyButton,SIGNAL(clicked(bool)),this,SLOT(begin()));	
     
}

void DataFun::Initialize(frecType &dr,int irow,dataFile &f) 
 {
	
	if ((dr.fun!="\0")&&(dr.dx!=0)&&(dr.xe!=0)&&(dr.n!=0)) 
 	{   myfile=&f;
		Irow=irow;

   inputEdit->setText(dr.fun);
   inputDx->setText(QString::number(dr.dx));   
   inputXe->setText(QString::number(dr.xe));  
   inputN->setText(QString::number(dr.n));  
	} 
	else
	{ 
   inputEdit->clear();
   inputDx->clear();  
   inputXe->clear();
   inputN->clear(); 
   Irow=irow;
	} 

 }

void DataFun::ChanceP()
{
	double Dx,Xe,N,K,Points;
	bool OkDx=true,OkXe=true,OkN=true;
	numP->clear();
	QString Str=inputEdit->text();
	QByteArray byteArray = Str.toUtf8();
	char* st = byteArray.data();
	
	QString strDx=inputDx->text();	
    Dx=strDx.toDouble(&OkDx);
   
	QString strXe=inputXe->text();
	Xe=strXe.toDouble(&OkXe); 

	QString strN=inputN->text();
	N=strN.toDouble(&OkN);
	
  

   if ((st[0]!='\0')&&(OkDx)&&(OkXe)&&(OkN)) //проверка пустая ли вводимая строка
	{
	 Points=((Xe-Dx)/N)*((Xe-Dx)/N);
	  QString  valueAsString = QString::number(Points);
	 if (valueAsString!="inf")
	 {
	  if (Points<=50000)
	  {
	   
	   applyButton->setEnabled(true);
	   QString valueAsString = QString::number(Points,'g',5);
	   numP->setText(codec->toUnicode("приблизительный кол-во  точек на  графике = ")+valueAsString+"<50000");
	   
	  }
	  else 
	  {
     
	   QString valueAsString1 = QString::number(Points,'g',6);
	   numP->setText(codec->toUnicode("превышен лимит точек = ")+valueAsString1);
       applyButton->setEnabled(false);
	  }

	 }
	 
   }
	
}

void DataFun::showEvent(QShowEvent *) 
 
{   
    
	myTimer=startTimer(n);      // включаем таймер
	
}

void DataFun::timerEvent(QTimerEvent *event) 
{ 
    if (event->timerId() == myTimer) // если наш таймер
    {
				
       ChanceP();        // обновить label
    }
    else 
       QWidget::timerEvent(event);  // иначе передать далее
};  

void DataFun::begin()
{  
    
	applyButton->setEnabled(true); 
	
	
	
	//______________________________________________________________________
	double Dx,Xe,N;
	 
	bool OkDx=true,OkXe=true,OkN=true;
	
	QString Str=inputEdit->text();
	QByteArray byteArray = Str.toUtf8();
	 
    QString strDx=inputDx->text();
    Dx=strDx.toDouble(&OkDx);

	QString strXe=inputXe->text();
	Xe=strXe.toDouble(&OkXe); 

	QString strN=inputN->text();
	N=strN.toDouble(&OkN);

	

	bool check = false;	
    char* st = byteArray.data();
    frecType Dr;
	    Dr.fun=st;
	    Dr.dx=Dx;
		Dr.n=N;
		Dr.xe=Xe;
		
       
if(myfile->bCorFitem(Dr,Irow))
{
   QMessageBox msgBox(QMessageBox::Information,
	codec->toUnicode("Информация"),
             codec->toUnicode("изменен"),
               QMessageBox::Ok);
			msgBox.exec();
}
else

{

  if (checkFun<20)
  {
	if ((st[0]!='\0')&&(OkDx)&&(OkXe)&&(OkN)) //проверка пустая ли вводимая строка
	{
		frecType r;
		r.fun=st;
		r.dx=Dx;
		r.xe=Xe;
		r.n=N;
		
        check = myfile2.addRec(r);    // добавления в файл

	}
	else
	{
         		QMessageBox msgBox(QMessageBox::Critical,
                codec->toUnicode("АГА ПОПАЛСЯ !!!"),
                codec->toUnicode("Введено неверное значение или не введено ничего."),
                QMessageBox::Ok);
				msgBox.exec();
	}
    if (check)
	{QMessageBox msgBox(QMessageBox::Information,
	codec->toUnicode("Информация"),
                codec->toUnicode("Добавлен"),
				QMessageBox::Ok);
				msgBox.exec();
	}
	
  }
  else
  {
	  QMessageBox msgBox(QMessageBox::Information,
			codec->toUnicode("Информация"),
                codec->toUnicode("Превышает кол-во допустимых функций"),
                QMessageBox::Ok);
				msgBox.exec();
  }

   
	checkFun++;
	
}
close();
}