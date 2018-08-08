#ifndef LR10_H
#define LR10_H
#include <QtGui>
#include <QGLWidget> // подключаем класс QGLWidget
#include "fFile.h"//класс для работы с файлами
#include <GL/glut.h>
 

class createpoints //класс создание точек
{protected:
  double *countP;
  QTextCodec *codec;
  typedef  char str5[5];
  typedef  char str80[80];
  struct Top;
  typedef  struct Top *pTop;
  struct Top {  
     str5 operatop; 
     double value; 
     pTop left,right;   
              };  
  
 bool check(char sim,str5 SetOp1);  //проверяет вхождения сторок
 int PosOP(str80 st, str5 SetOp);   //поиск корки дерева
 void Const_Tree(pTop r, str80 st); //построение дерево
 double Count(pTop r, double x, double y, bool &key);//Считает дерево 

 public:
     double *getP(){return  countP;}  //получения информации о кол-во точек на графике 
	 createpoints(char* st, double dx,double xe,double n);//полученя точек
    ~createpoints(){}
};



class Scene3D :public QGLWidget //Рисование 3D Объект
{
   private:
	  double *countP;
	 
	  createpoints *creater;
      GLfloat xRot; // переменная хранит угол поворота вокруг оси X
      GLfloat yRot; // переменная хранит угол поворота вокруг оси Y   
      GLfloat zRot; // переменная хранит угол поворота вокруг оси Z 
      GLfloat nSca; // переменная хранит угол поворота вокруг оси Z 
      QPoint ptrMousePosition; // переменная хранит координату указателя мыши в момент нажатия 
 
      void scale_plus();     // приблизить сцену
      void scale_minus();    // удалиться от сцены  
      void rotate_up();      // повернуть сцену вверх
      void rotate_down();    // повернуть сцену вниз
      void rotate_left();    // повернуть сцену влево
      void rotate_right();   // повернуть сцену вправо
      void translate_down(); // транслировать сцену вниз
      void translate_up();   // транслировать сцену вверх      
      void defaultScene();   // наблюдение сцены по умолчанию      
      void drawAxis();       // построить оси координат
      void getVertexArray(); // определить массив вершин  
      void drawFigure();     // построить фигуру
 
   protected:
      void wheelEvent(QWheelEvent* pe);
      void resizeGL(int nWidth, int nHeight);  // метод вызывается при изменении размеров окна виджета
      void paintGL();                          // метод, чтобы заново перерисовать содержимое виджета  
      void mousePressEvent(QMouseEvent* pe);   // методы обработки события мыши при нажатии клавиши мыши
      void mouseMoveEvent(QMouseEvent* pe);    // методы обработки события мыши при перемещении мыши
   public:
	  
      void initialize(char* st,double dx,double xe,double n); // метод для проведения инициализаций, связанных с OpenGL 
	  double *getP(){return  countP;}
	 
	   Scene3D(QWidget* parent = 0);
	   ~Scene3D(){}
    
      
}; 
class DataFun: public QWidget //класс добавления данных
{
	 Q_OBJECT
 int myTimer; // идентификатор таймера
 int n;//милисек
 int Irow;

   protected:   
      
      dataFile  *myfile,myfile2;
	  QTextCodec *codec;
	  QFrame *frame;
	  
	  QLabel *inputLabel;
	  QLabel *inputLN;
	  QLabel *inputLXe;
	  QLabel *inputLDx; 
	  QLabel *numP; 
	  	  
      QLineEdit *inputEdit;
	  QLineEdit *inputN;
	  QLineEdit *inputXe;
	  QLineEdit *inputDx;
	  QPushButton *applyButton;
	  
private:
	void ChanceP();
	void timerEvent(QTimerEvent *event);
    void showEvent(QShowEvent *event);
public:
	 int checkFun; //проверяеь кол-во функций вводимый
	 void Initialize(frecType &dr,int irow,dataFile &f);// для коррекция поля функции 
	 DataFun(QWidget *parent = 0);
	 
	
	
public slots:
	 void begin(); //принимает строку

};



class Win:public QWidget // класс Scene3D наследует встроенный класс QGLWidget
{
   Q_OBJECT
	

	
	
protected:
	int myTimer; // идентификатор таймера
    int n;       // милисекунд
	int irow;    // строка после нажатия на таблице
	bool Rcheck; // контроль покраски
    double Dx,Xe,N; //для таблиц
	char *st, *t;
	

	
	dataFile myFile;
	QTableWidgetItem *item;
	QTextCodec *codec;
	DataFun *datafun;
	
	QLabel  *infoText1;
	QLabel  *listgrLabel;
	QMenuBar *menuBar;
	QPushButton  *OpenButton;
	QPushButton  *buildButton;
	QPushButton  *DelButton;
	QPushButton  *exitButton;
	QTableWidget *listgrTable;
	Scene3D *scene3D;

private:
	
	void showRow(int i,frecType r);//показ строки таблиц
	void timerEvent(QTimerEvent *event);
    void showEvent(QShowEvent *event);
	void mouseReleaseEvent(QMouseEvent *e);
	bool takeparam();

public:
	Win(QWidget *parent = 0);
	void showTable();
	~Win(){}
	
public slots:
	 void Build();
	 void Delete();
	 void refresh();//Обновление таблиц;
	 void makepoint(int row, int column);//вызов функции отрисовки изображения
	 void open(); //открывает ввод строк
	 void PrintAScreen();
	 void ShotAScreen();
	 void closeD();
signals:
  void clicked();
};

#endif // LR10_H
