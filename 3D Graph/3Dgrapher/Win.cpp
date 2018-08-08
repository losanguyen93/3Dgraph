#include "myclass.h"
#include <QtGui/QApplication>
#include <math.h>


Win::Win(QWidget *parent) : QWidget(parent) //������� ���� 
{
  n=500;
  irow = 21;
  Rcheck=false;
  
  codec = QTextCodec::codecForName("Windows-1251"); //������� �����
  setWindowTitle("3D Grapher");


    QAction *menuAction;
    QActionGroup *menuActionGroup = new QActionGroup(this);
    menuBar = new QMenuBar(this);
 
    QMenu *menu = menuBar->addMenu(codec->toUnicode("����� ������"));
    menuAction = menu->addAction(codec->toUnicode("������"));
    connect(menuAction, SIGNAL(triggered()), this, SLOT(PrintAScreen()));
    menuAction = menu->addAction(codec->toUnicode("����� � Jpeg"));
    connect(menuAction, SIGNAL(triggered()), this, SLOT(ShotAScreen())); 
 
 

 //�������� ����� �������� ���� 
  datafun = new DataFun; // ���� ���������� �������
  scene3D = new Scene3D(this); //����� ��� ���������
  
  //___________________________________
  infoText1=new QLabel("",this);
  listgrLabel = new QLabel(codec->toUnicode("������ �������:"), this);
 //___________________________________
  OpenButton = new QPushButton(codec->toUnicode("��������������� � ����������"),this); 
  exitButton = new QPushButton(codec->toUnicode("�����"),this);
  buildButton = new QPushButton(codec->toUnicode("���������"),this);
  DelButton  = new QPushButton(codec->toUnicode("�������"),this); 
  // �������� ������� ,��������� � ���-�� ������� 
  QStringList strlist;
    strlist <<codec->toUnicode("������")<< codec->toUnicode("������ �������")<< codec->toUnicode("����� �������")<< codec->toUnicode("���");
    listgrTable = new QTableWidget(20,4,this);
    listgrTable->setHorizontalHeaderLabels(strlist);
	listgrTable->horizontalHeader()->setResizeMode(0,QHeaderView::Stretch);
	listgrTable->horizontalHeader()->setResizeMode(1,QHeaderView::Stretch);
	listgrTable->horizontalHeader()->setResizeMode(2,QHeaderView::Stretch);
	listgrTable->horizontalHeader()->setResizeMode(3,QHeaderView::Stretch);
  
   //���������� ����������.
 
	
 QHBoxLayout *hLayInfoB = new QHBoxLayout();
	hLayInfoB->addWidget(buildButton);
	hLayInfoB->addWidget(DelButton); 
 QHBoxLayout *hLayInfoA = new QHBoxLayout();
    hLayInfoA->addWidget(menuBar);
	

 
 QVBoxLayout *vLayout2 = new QVBoxLayout(this);
	vLayout2->addLayout(hLayInfoA);
    vLayout2->addWidget(scene3D);
	vLayout2->addWidget( listgrLabel);
	vLayout2->addWidget(  listgrTable);
	vLayout2->addWidget(infoText1);
	vLayout2->addLayout(hLayInfoB);
	vLayout2->addWidget(OpenButton);
	vLayout2->addWidget(exitButton);
    vLayout2-> addStretch();
	showTable();// ����������� �������.
    infoText1->setVisible(false);
	

	connect(exitButton,SIGNAL(clicked(bool)),this,SLOT(close()));
    connect(OpenButton,SIGNAL(clicked(bool)),this,SLOT(open()));	//������� ���� ���������� 
	connect(exitButton,SIGNAL(clicked(bool)),this,SLOT(closeD()));	//������� ���� ���������� 
	connect(listgrTable,SIGNAL(cellClicked (int ,int )),this,SLOT(makepoint(int ,int ))); //���������� �� ������ ������
	connect(buildButton,SIGNAL(clicked(bool)),this,SLOT(Build()));//��������
	connect(DelButton,SIGNAL(clicked(bool)),this,SLOT(Delete()));//�������
	
	buildButton->setVisible(false);
    DelButton->setVisible(false);
	
   
}
void Win::closeD()
{
 datafun->close(); 
}
void Win::mouseReleaseEvent(QMouseEvent *e) //��� ����������
{	
		if(e->button() == Qt::LeftButton)
		{
			emit clicked();
			Rcheck = false;
			irow = 21;
			buildButton->setVisible(false);
            DelButton->setVisible(false);
			infoText1->setVisible(false);
		}	
}
void Win::showEvent(QShowEvent *) 
 
{       
	myTimer=startTimer(n);      // �������� ������	
}

void Win::timerEvent(QTimerEvent *event) 
{ 
    if (event->timerId() == myTimer) // ���� ��� ������
    {
				
       refresh();        // �������� ������� ���
    }
    else 
       QWidget::timerEvent(event);  // ����� �������� �����
};  

void Win::refresh()//���������� �������
{
    myFile.beginf(); //��������� ��������� ����� ������ � ������ �����
	showTable();   // ����������� �������.
}

bool Win::takeparam()
{if (irow!=21)
{
    bool OkDx=true,OkXe=true,OkN=true;
	QString Str = listgrTable->item(irow,0)->text();  
	QByteArray byteArray = Str.toUtf8();
     st = byteArray.data();	
	 strcpy(t,st);
	 
	 
	
	QString strDx=listgrTable->item( irow,1)->text();
	Dx = strDx.toDouble(&OkDx);

	QString strXe=listgrTable->item( irow,2)->text();
	Xe=strXe.toDouble(&OkXe); 

	QString strN=listgrTable->item( irow,3)->text();
	N=strN.toDouble(&OkN);

	if ((st[0]!='\0')&&(OkDx)&&(OkXe)&&(OkN))	
      return true;
	else return false;
}
else return false;

}


void Win::open() //����� �������� ���� ����������
{  
     OpenButton->setEnabled(false); 
  	OpenButton->setDefault(false);
	
   frecType Dr1;
   
 
	if (takeparam())
	{
	    
		Dr1.dx=Dx;
		Dr1.n=N;
		Dr1.xe=Xe;
		Dr1.fun=t;
	    datafun->Initialize(Dr1,irow,myFile);
	}
	else
    {   Dr1.dx=0;
		Dr1.n=0;
		Dr1.xe=0;
		Dr1.fun="/0";
	  datafun->Initialize(Dr1,21,myFile); 
	}

	datafun->setFixedSize(QSize(500,200));
	datafun->show(); 
   	OpenButton->setEnabled(true);
    OpenButton->setDefault(true);
    } 



void Win::showTable() // ����������� �������.
{
	
	int i=0;
	while (myFile.readRec())
	{
		showRow(i,myFile.rec);
	    i++;
	}
	 listgrTable->setRowCount(i);
	 datafun->checkFun=listgrTable->rowCount();

	  
	
}

void Win::showRow(int i,frecType r)//����� ������
{
	QString str;    
	     
        if((i==irow)&&(Rcheck)) 
		{
	     item = new QTableWidgetItem();
	     item->setFlags(Qt::NoItemFlags);
		 item->setText(r.fun);
		 item->setBackground(QColor(204,204,204));
		 listgrTable->setItem(i,0,item);

		 item = new QTableWidgetItem();
	     item->setFlags(Qt::NoItemFlags);
		 QString valueAsString = QString::number(r.dx);
		 item->setText(valueAsString);
		 item->setBackground(QColor(204,204,204));
		 listgrTable->setItem(i,1,item);

		 item = new QTableWidgetItem();
	     item->setFlags(Qt::NoItemFlags);
		 valueAsString = QString::number(r.xe);
		 item->setText(valueAsString);
		 item->setBackground(QColor(204,204,204));
		 listgrTable->setItem(i,2,item);

		 item = new QTableWidgetItem();
	     item->setFlags(Qt::NoItemFlags);
		 valueAsString = QString::number(r.n);
		 item->setText(valueAsString);
		 item->setBackground(QColor(204,204,204));
		 listgrTable->setItem(i,3,item);
		}
		else
		{
		 item = new QTableWidgetItem();
	     item->setFlags(Qt::NoItemFlags);
		 item->setText(r.fun);
		 listgrTable->setItem(i,0,item);

		 item = new QTableWidgetItem();
	     item->setFlags(Qt::NoItemFlags);
		 QString valueAsString = QString::number(r.dx);
		 item->setText(valueAsString);
		 listgrTable->setItem(i,1,item);

		 item = new QTableWidgetItem();
	     item->setFlags(Qt::NoItemFlags);
		 valueAsString = QString::number(r.xe);
		 item->setText(valueAsString);
		 listgrTable->setItem(i,2,item);

		 item = new QTableWidgetItem();
	     item->setFlags(Qt::NoItemFlags);
		 valueAsString = QString::number(r.n);
		 item->setText(valueAsString);
		 listgrTable->setItem(i,3,item);
		}
}

void Win::makepoint(int row, int column) //�������� ������� �� ��������� 
{
     
   	
	irow = row;
	Rcheck=true;
	buildButton->setVisible(true);
	DelButton->setVisible(true);
	
}

void Win::Build()
{
 
	
 
	if (takeparam())
	{		
		scene3D->initialize(t,Dx,Xe,N);
		double *countP=scene3D->getP();		
        scene3D->updateGL(); // ���������� ����������� 			
		infoText1->setVisible(true);
	    infoText1->setText(codec->toUnicode("��������� ����� �� ������� (<50000 �����) = ")+QString::number(*countP)+"  Points");    
	}	
	buildButton->setVisible(false);
	DelButton->setVisible(false);
	
}

void Win::Delete()
{
 frecType Dr1;

 
	if (takeparam())
	{
		Dr1.fun=t;
		Dr1.dx=Dx;
        Dr1.xe=Xe;
		Dr1.n=N;
	    if(myFile.bDelFitem(Dr1))
		{
			QMessageBox msgBox(QMessageBox::Information,
			codec->toUnicode("����������"),
                codec->toUnicode("������"),
                QMessageBox::Ok);
				msgBox.exec();
		}
			
	}
	
	DelButton->setVisible(false);
	buildButton->setVisible(false);
	irow = 21;
	
}
void Win::ShotAScreen()
	{
		scene3D->renderPixmap(1000,1000,false).save("screenshot.jpg", "JPG");
	    QMessageBox msgBox(QMessageBox::Information,
			codec->toUnicode("����������"),
                codec->toUnicode("������ �������� � ����� ���������"),
                QMessageBox::Ok);
				msgBox.exec();
  	
	}
void Win::PrintAScreen()
{
 	
	QPrinter printer;
	printer.setOrientation(QPrinter::Portrait);
	printer.setPaperSize(QPrinter::A4);
	QPrintDialog *dialog = new QPrintDialog(&printer);
    dialog->setWindowTitle("Print Document");
 
    if(dialog->exec() == QDialog::Accepted)//���� �������� ��, �� ��������
	{
		scene3D->render(&printer);
	}
	      
}
	 

