#include "myclass.h"
#include <QtGui/QApplication>
#include <GL/glut.h>    /*Для Linux и Windows*/
#include <math.h>  
#include <QFile>
#define ZZ 2

const static float pi=3.141593, k=pi/180;
GLfloat pVerts[ZZ*75000];



Scene3D::Scene3D(QWidget* parent) : QGLWidget(parent)
{ 
   // начальные значения
   xRot=-90; yRot=0; zRot=0; nSca=1;
   setFixedSize(QSize(700,650));
   
} 


void Scene3D::initialize(char* st,double dx,double xe,double n) // инициализация
{  
   creater=new createpoints(st,dx,xe,n);
   countP=creater->getP();

   qglClearColor(Qt::white); // цвет для очистки буфера изображения - здесь просто фон окна
   glEnable(GL_DEPTH_TEST);  // устанавливает режим проверки глубины пикселей
   glShadeModel(GL_FLAT);    // отключает режим сглаживания цветов 
   glEnable(GL_CULL_FACE);   // устанавливается режим, когда строятся только внешние поверхности 
 
   getVertexArray(); // определить массив вершин 
   glEnableClientState(GL_VERTEX_ARRAY); // активизация массива вершин
  }
 
/*virtual*/void Scene3D::resizeGL(int nWidth, int nHeight) // окно виджета
{ 
   glMatrixMode(GL_PROJECTION); // устанавливает текущей проекционную матрицу
   glLoadIdentity();            // присваивает проекционной матрице единичную матрицу
 
   GLfloat ratio=(GLfloat)nHeight/(GLfloat)nWidth; // отношение высоты окна виджета к его ширине
 
   // мировое окно
   if (nWidth>=nHeight)
      glOrtho(-1.0/ratio, 1.0/ratio, -1.0, 1.0, -10.0, 1.0); // параметры видимости ортогональной проекции
   else
    glOrtho(-1.0, 1.0, -1.0*ratio, 1.0*ratio, -10.0, 1.0); // параметры видимости ортогональной проекции        

   glViewport(0, 0, (GLint)nWidth, (GLint)nHeight);
}
 
/*virtual*/ void Scene3D::paintGL() // рисование
{  glClearColor(1.0,1.0,1.0,1.0);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // очистка буфера изображения и глубины
   glMatrixMode(GL_MODELVIEW); // устанавливает положение и ориентацию матрице моделирования
   glLoadIdentity();           // загружает единичную матрицу моделирования
 
   glScalef(nSca, nSca, nSca);        // масштабирование   
   glRotatef(xRot, 1.0f, 0.0f, 0.0f); // поворот вокруг оси X         
   glRotatef(yRot, 0.0f, 1.0f, 0.0f); // поворот вокруг оси Y
   glRotatef(zRot, 0.0f, 0.0f, 1.0f); // поворот вокруг оси Z

   drawAxis();   // рисование осей координат

   drawFigure(); // нарисовать фигуру
}  
 
void Scene3D::mousePressEvent(QMouseEvent* pe) // нажатие клавиши мыши
{
   ptrMousePosition = pe->pos();                          
} 
 
void Scene3D::mouseMoveEvent(QMouseEvent* pe) // изменение положения стрелки мыши
{   
   xRot += 180/nSca*(GLfloat)(pe->y()-ptrMousePosition.y())/height(); // вычисление углов поворота
   zRot += 180/nSca*(GLfloat)(pe->x()-ptrMousePosition.x())/width(); 
   ptrMousePosition = pe->pos();
   updateGL(); // обновление изображения
}
void Scene3D::wheelEvent(QWheelEvent* pe) // вращение колёсика мыши
{ 
   if ((pe->delta())>0) nSca = nSca*1.1; else if ((pe->delta())<0) nSca = nSca/1.1;  
 
   updateGL(); // обновление изображения          
}
 
void Scene3D::drawAxis() // построить оси координат
{  

	glColor4f(1.00f, 0.00f, 0.00f, 1.0f); // устанавливается цвет последующих примитивов
   // ось x красного цвета
   glBegin(GL_LINES); // построение линии
      glVertex3f( 30.0f,  0.0f,  0.0f); // первая точка
      glVertex3f(-30.0f,  0.0f,  0.0f); // вторая точка
   glEnd();  
 
   QColor halfGreen(0, 128, 0, 255);
   qglColor(halfGreen);
   glBegin(GL_LINES);
      // ось y зеленого цвета
      glVertex3f( 0.0f,  30.0f,  0.0f);
      glVertex3f( 0.0f, -30.0f,  0.0f);
 
      glColor4f(0.00f, 0.00f, 1.00f, 1.0f);
      // ось z синего цвета
      glVertex3f( 0.0f,  0.0f,  30.0f);
      glVertex3f( 0.0f,  0.0f, -30.0f);
   glEnd();
}
long count=0;
void Scene3D::getVertexArray() // определить массив вершин
{
	QFile * f;
	double x,y,z;
	count=0;	
	f=new QFile("file.dat");// создаем объект-файл
	f->open(QFile::ReadWrite); // открываем файл для ввода-вывода
	QDataStream in(f); // связываем с файлом поток ввода
	long k=0;
	while(!in.atEnd()){
		in>>x>>y>>z;
		pVerts[k++]=float(x)/2; // x
		pVerts[k++]=float(y)/2; // y
		pVerts[k++]=float(z)/2; // z
		count++;
	}
	f->close();
	f->remove();
}
 
void Scene3D::drawFigure() // построить фигуру
{
   //glTexCoordPointer(3,GL_FLOAT,0,pVerts);

   glColor3ub(255,0,0);
   int k=0;
   glBegin(GL_POINTS);
		for(int i=0;i<count;i++)
		{
		glVertex3f( pVerts[k],  pVerts[k+1], pVerts[k+2]);
		k+=3;
		}
	glEnd();
}
