 #include "fFile.h"
dataFile::dataFile()
{	QTextCodec *codec = QTextCodec::codecForName("Windows-1251");
	f=new QFile("file.txt");
	if(!f->exists()) 
	{	QMessageBox msg(QMessageBox::Critical, 
                       codec->toUnicode("Файл не найден"), 
                       codec->toUnicode("Файл file.txt будет создан"),
                       QMessageBox::Ok,0);
	                   msg.exec();
	}
	f->close();
 }
dataFile::~dataFile()
{	
	f->close();	
    delete f; 
}


bool dataFile::addRec(frecType r)
{   	
	f->open(QFile::ReadWrite);
	f->seek(f->size());
	QDataStream out(f);
	rec.fun=r.fun;
	rec.dx = r.dx;
	rec.xe = r.xe;
	rec.n = r.n;
	rec.Time = QDateTime::currentDateTime();
	out<<rec.fun<<rec.dx<<rec.xe<<rec.n<<rec.Time;
    f->close();
	return true;
}
bool dataFile::readRec()
{   
	f->open(QFile::ReadWrite);
	QDataStream in(f);
	if (in.atEnd())return false;
	else 
	{
		in>>rec.fun>>rec.dx>>rec.xe>>rec.n>>rec.Time;
		return true;
	}
	
}

bool dataFile::bDelFitem(frecType &Dr)
{ 
  f1=new QFile("file1.txt");
  f1->close();
  f1->open(QFile::ReadWrite);
  QDataStream out(f1);
   f->open(QFile::ReadWrite);
   f->reset();
   
   while((readRec()))
	{
		bool k1=(!strcmp(Dr.fun,rec.fun));
		bool k2=(Dr.dx==rec.dx);
		bool k3=(Dr.xe==rec.xe);
		bool k4=(Dr.n==rec.n);
		if (!k1||!k2||!k3||!k4)
		{   
        	out<<rec.fun<<rec.dx<<rec.xe<<rec.n<<rec.Time;
		}
	}	   
	f->close();
	f->remove();
	f1->close();
	f1->rename("file.txt");
	delete f1;
	return true;
}


bool dataFile::bCorFitem(frecType &Dr,int irow)
{if(irow!=21)  
{
  
  f2=new QFile("file2.txt");
  f2->close();
  f2->open(QFile::ReadWrite);
  QDataStream out(f2);
   f->open(QFile::ReadWrite);
   f->reset();
   int i=0;
   while(readRec())
	{  if (irow!=i)
		{   
        	out<<rec.fun<<rec.dx<<rec.xe<<rec.n<<rec.Time;
		}
		else
		{
			out<<Dr.fun<<Dr.dx<<Dr.xe<<Dr.n<<Dr.Time;
		}
     i++;
	}	   
	f->close();
	f->remove();
	f2->close();
	f2->rename("file.txt");
	delete f2;
	return true;
}
else return false;

}