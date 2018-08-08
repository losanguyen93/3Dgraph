#include "myclass.h"
#include <locale.h>
#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <stdlib.h>
#include <string>
#include <atlstr.h>
#include <QtGui>
#include <QFile>
#include <QtGui/QApplication>


using namespace std;

 createpoints::createpoints(char* st, double dx,double xe,double n)
 {
	
 pTop Root;
 bool key;
 double x,y,z;
 
	QFile * f;
	
	codec = QTextCodec::codecForName("UTF-8"); 
	f=new QFile("file.dat");// создаем объект-файл
	f->remove("file.dat");
	f->open(QFile::WriteOnly); // открываем файл для ввода-вывода
	QDataStream out(f); // связываем с файлом поток ввода
	
	
countP = new double; 

Root=new Top;
*countP=0;


Const_Tree(Root,st); //построение дерево
       
for(y=dx; y<=xe;y+=n){
    for(x=dx; x<=xe;x+=n){
       key = true;
       
	   z=Count(Root,x,y,key); //подсчет функции
	   if (key) {	   
		              		        
          /*x*/ out<<x;            
		  /*y*/	out<<y;            
		  /*z*/ out<<z; 
		  *countP+=1;  
		                                    
		        }
	   else
	   {   y=xe;
		   x=xe; 
		   break;
	   }
	   

                          }

                             }

	f->close();
	
 }

bool createpoints::check(char sim,str5 SetOp1) //проверка вхождения строк
{  
  for (int i=0;i<strlen(SetOp1);i++){
     if (sim==SetOp1[i]) return true;
                                  }
  return false;
}

int createpoints::PosOP(str80 st, str5 SetOp)//проверка опреции для построения корни
 { 
   int i,j,k,p;
   j=0; k=0; p=0; i=0;
   while ((i<=strlen(st))&&(p==0)){
      if (st[i]=='(') j++;
    else if (st[i]==')') k++;
         else if ((j==k) && (check(st[i],SetOp))) p=i;
   i++;
               
                                    }
   return p;
 }
 
 
void createpoints::Const_Tree(pTop r, str80 st)
{
  pTop next;  str5 setChar; int po, code, c;
  str80 stl,stri;

if (st[0]=='-')
 {
    r->operatop[0]='-';
    r->operatop[1]='\0';
	strncpy(stl, st+1,strlen(st)-1);
	stl[strlen(st)-1]='\0';
    r->left=new Top;
	Const_Tree(r->left,stl);
	r->right=NULL;

 }  
else
{
  
  po=PosOP(st,"+-");

  if (po==0) po=PosOP(st,"*/");

  if (po==0) po=PosOP(st,"^");
  
  if (po!=0){
           
         r->operatop[0]=st[po];
		  r->operatop[1]='\0';
         strncpy(stl, st,po);
         stl[po]='\0';

         if ((stl[0]=='(') && ((PosOP(stl,"*/+-^")==0))){
                                    strncpy(stl, st+1,strlen(stl)-1);
                                    stl[strlen(stl)-2]='\0';                            
                                                       }
         strncpy(stri, st+po+1,strlen(st)-po);
           stri[strlen(st)-po]='\0';

         if ((stri[0]=='(') && ((PosOP(stri,"*/+-^")==0))){
                                    strncpy(stri, stri+1,strlen(stri)-2);
                                stri[strlen(stri)-2]='\0';                            
                                                       }
          r->left=new Top;
          Const_Tree(r->left,stl);
        

          r->right=new Top;
          Const_Tree(r->right,stri);  
            }
     else{
      if ((st[0]=='x')&&(st[1]!='x')){
            r->operatop[0]='x';
			r->operatop[1]='\0';
            r->left=NULL;
            r->right=NULL;
                     }
     else{
           if (st[0]=='y'&&(st[1]!='y')){
             r->operatop[0]='y';
			 r->operatop[1]='\0';
             r->left=NULL;
             r->right=NULL;
                           }
            else{
                             char* end_ptr;
                             double val = strtod(st, &end_ptr);
                             if (!*end_ptr)
                              {
                                 r->operatop[0]='o';
								 r->operatop[1]='\0';
                                 r->left=NULL;
                                 r->right=NULL;
                                 r->value=val;
                              }
                           
                             else 
							 if (check(st[0],"+-*/^"))
							 {   
								 r->operatop[0]='\0';
			                     r->operatop[1]='\0';
                                 r->left=NULL;
                                 r->right=NULL;
								 						
							 }
							 else
                             {
							  if ((st[1]!='x')&&(st[1]!='y'))
							  {
						      char *ptr;
                              int  p;
							  if (ptr=strstr(st,"("))
							  {
                              p=ptr-st;                            
                              strncpy(r->operatop , st,p);
                              r->operatop[p]='\0'; 
                              r->right=NULL;
                              strncpy(stl,st+p+1,strlen(st));
                              stl[strlen(st)-p-2]='\0';  
                              r->left = new Top;
                              Const_Tree(r->left,stl);
							  }
							  else
							  {
							     r->operatop[0]='\0';
			                     r->operatop[1]='\0';
                                 r->left=NULL;
                                 r->right=NULL;
							  }
							  {
							  }
							  }
							  
							 
                            }
                           
                }
                   
     }
}
   } 

                                    
                                     }
double createpoints::Count(pTop r, double x, double y,  bool &key)
{ double s, s1;
  if (!key) 
  {
    return 0;
    exit;
  }
  if (r->operatop[0]=='o') return r->value;
  else 
       {

        if (r->operatop[0]=='x') return x;
        else
         {
           if (r->operatop[0]=='y') return y;
           else			
             switch (r->operatop[0])
             {
				 
				             
                 case '+': return (Count(r->left,x,y,key)+Count(r->right,x,y,key)); break;
				 case '-': {
					       if((r->right!=NULL)&&(r->operatop[0]=='-'))
					                               return (Count(r->left,x,y,key)-Count(r->right,x,y,key)); 
						   else	                   
							                       return (-Count(r->left,x,y,key));
		 				   break;
						   }
				 case '*': return (Count(r->left,x,y,key)*Count(r->right,x,y,key)); break;
				 case '/':{
                            s=Count(r->right,x,y,key);
                            if (abs(s)<1e-10)
                            {
                              return 0;
                              key=false;
                            }
                            else return Count(r->left,x,y,key)/s;
                            break;
                           };
                case '^':{
                            s=Count(r->left,x,y,key);
                            s1=Count(r->right,x,y,key);
							
					
							double k=pow(s,s1); 
                            QString  valueAsString = QString::number(k);
							if ((s!=0)&&(valueAsString!="nan")) 
								return k; 
                            else
                                {
                                if (s1=0) return 1;
								else {return 0; key=false;}
                                }
                            break;
                         };    
                  case 'c': return cos(Count(r->left,x,y,key)); break;
				  case 'e': return exp(Count(r->left,x,y,key));
		   }
				  if (strcmp(r->operatop,"log10")== 0)  
					  return log10(Count(r->left,x,y,key));
				 
				  if (strcmp(r->operatop,"ln")== 0)  
					  return log(Count(r->left,x,y,key));
				 
				  if (strcmp(r->operatop,"sin")== 0)  
					  return sin(Count(r->left,x,y,key));
				 
				  if (strcmp(r->operatop,"sqrt")== 0)  
					  return pow(Count(r->left,x,y,key),0.5);

				  if (strcmp(r->operatop,"atan")== 0)  
					  return atan(Count(r->left,x,y,key));
				  
             
             if ((r->operatop!="x")&&(r->operatop!="y")&&(r->operatop!="z")&&(r->operatop!="o")&&(strcmp(r->operatop,"log10")!= 0)&&(strcmp(r->operatop,"ln")!= 0)&&(strcmp(r->operatop,"sin")!= 0)&&(strcmp(r->operatop,"sqrt")!= 0))
             { 
				 QMessageBox msgBox(QMessageBox::Critical,
                                    codec->toUnicode("АГА ПОПАЛСЯ !!!"),
                                    codec->toUnicode("Введено неверная функция"),
                                    QMessageBox::Ok);
				                    msgBox.exec();			   
				 
			   key=false;
               return 0;
               
             }

		}
  }
		    	
            
}
                                         
        
 
