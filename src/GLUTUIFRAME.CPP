#include <gl/glut.h>
#include <cstdio>
#include <ctime>
#include <vector>
using namespace std;

#include "glutuiframe.h"
#include "Line.h"
#include "Triangle.h"
#include "Rectangle.h"
#include "Pen.h"
#include "Quads.h"
#include "Circle.h"

int g_width, g_height;	// 紀錄視窗長寬
int draw_mode = 6;		// 預設是畫筆
int count = 0;			// 紀錄目前的點
GLfloat size = 3.0;		// 紀錄pixel大小
bool FILL = false;		// 設定是否要填滿圖形
bool BLEND = false;		// 設定是否要啟用透明色
int pos[3][2];			// 紀錄"點"位址
GLfloat color[4]={0.0, 0.0, 0.0, 0.5};	// 預設顏色是黑色

vector<PaintObject *> obj;	// 紀錄所有繪圖物件

void SetupCallback(void)
{
	glutReshapeFunc(OnSize);
    glutDisplayFunc(OnPaint);
    glutKeyboardFunc(OnKeyIn);
	glutSpecialFunc(OnKeySPIn);
	glutKeyboardUpFunc(OnKeyUp);
    glutMouseFunc(OnMouseDown);
    glutMotionFunc(OnMouseMove);
	//glutPassiveMotionFunc(OnMouseMove);
	glutIdleFunc(OnIdle);
}

void CreateWindow(char *title, int ox, int oy, int width, int height)
{
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutInitWindowPosition(ox, oy);
    glutInitWindowSize(width, height);
    glutCreateWindow(title);
}

void InitOpenGL(int width,int height)
{
	g_width = width;
	g_height = height;

	glViewport(0.0, 0.0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity(); 
	gluOrtho2D(0.0, (GLdouble)width, (GLdouble)height, 0.0);
	glMatrixMode(GL_MODELVIEW);
	
	// 背景設成灰色
	glClearColor(0.8, 0.8, 0.8, 1.0);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// 設定右鍵menu
	int f_menu = glutCreateMenu(fill_menu);
    glutAddMenuEntry("打開填滿", 1);
    glutAddMenuEntry("關掉填滿", 2);
	glutAddMenuEntry("打開透明", 3);
	glutAddMenuEntry("關掉透明", 4);

	int c_menu = glutCreateMenu(color_menu);
    glutAddMenuEntry("紅",1);
    glutAddMenuEntry("綠",2);
    glutAddMenuEntry("藍",3);
    glutAddMenuEntry("青綠",4);
    glutAddMenuEntry("洋紅",5);
    glutAddMenuEntry("黃",6);
    glutAddMenuEntry("白",7);
    glutAddMenuEntry("黑",8);
	glutAddMenuEntry("隨機",9);

	int o_menu = glutCreateMenu(object_menu);
	glutAddMenuEntry("線",1);
	glutAddMenuEntry("三角形",2);
	glutAddMenuEntry("矩形",3);
	//glutAddMenuEntry("圓形",4);
	glutAddMenuEntry("橡擦",5);
	glutAddMenuEntry("畫筆",6);

	int p_menu = glutCreateMenu(pixel_menu);
    glutAddMenuEntry("增加像素大小", 1);
    glutAddMenuEntry("減少像素大小", 2);
	glutAddMenuEntry("預設像素大小", 3);

	int e_menu = glutCreateMenu(effect_menu);
    glutAddMenuEntry("隨機顏色", 1);
	glutAddMenuEntry("反轉顏色", 5);
    glutAddMenuEntry("填滿反轉", 2);
	glutAddMenuEntry("透明反轉", 4);
	glutAddMenuEntry("隨機大小", 3);

	glutCreateMenu(right_menu);
	glutAddSubMenu("繪圖物件", o_menu);
	glutAddSubMenu("顏色選項", c_menu);
	glutAddSubMenu("像素大小", p_menu);
	glutAddSubMenu("開關選項", f_menu);
	glutAddSubMenu("特別選項", e_menu);
	glutAddMenuEntry("清除",7);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	srand( (unsigned) time(NULL) );
}

void OnSize(int width, int height)
{
	g_width = width;
	g_height = height;

	glViewport(0.0, 0.0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity(); 
	gluOrtho2D(0.0, (GLdouble)width, (GLdouble)height, 0.0);
	glMatrixMode(GL_MODELVIEW);
}

void OnPaint(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
		
	for (int i=0; i<obj.size(); ++i)
		obj[i]->doDraw();

	glFlush();
	glutSwapBuffers();
}

void OnKeyIn(unsigned char key, int x, int y)
{
	if (key == 'a') {	// 按"a"可random設定顏色
		color[0] = (rand()%255)/255.0;
		color[1] = (rand()%255)/255.0; 
		color[2] = (rand()%255)/255.0; 
		color[3] = (rand()%255)/255.0;
	}
}

void OnKeySPIn(int key, int x, int y)
{
	switch(key) {
	case GLUT_KEY_PAGE_UP:
		size += 1.0;
		break;
	case GLUT_KEY_PAGE_DOWN:
		size -= 1.0;
		if (size < 1.0)
			size = 1.0;
		break;
	case GLUT_KEY_HOME:
		size = 3.0;
		break;
	case GLUT_KEY_F1:	// 填滿反轉
		ReverseFill();
		glutPostRedisplay();
		break;
	case GLUT_KEY_F2:	// 反轉顏色
		ReverseColor();
		glutPostRedisplay();
		break;
	case GLUT_KEY_F3:	// 隨機像素大小
		RandomSize();
		glutPostRedisplay();
		break;
	case GLUT_KEY_F4:	// 隨機像素大小
		ReverseBlend();
		glutPostRedisplay();
		break;
	case GLUT_KEY_F5:	// 隨機顏色
		RandomColor();
		glutPostRedisplay();
		break;
	}
}

void OnKeyUp(unsigned char key, int x, int y)
{
}

void OnMouseDown(int button, int state, int x, int y)
{
	if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN) {
		switch (draw_mode) {
		case 1:	// 線
			if(count==0) {
				count++;
				pos[0][0] = x;
				pos[0][1] = y;
			} else {
				pos[1][0] = x;
				pos[1][1] = y;
				obj.push_back( new Line(pos[0], pos[1], color, size, BLEND) );
				count=0;
			}
			break;
		case 2:	// 三角形
			if(count==0) {
				count++;
				pos[0][0] = x;
				pos[0][1] = y;
			} else if (count == 1) {
				count++;
				pos[1][0] = x;
				pos[1][1] = y;
			} else {
				pos[2][0] = x;
				pos[2][1] = y;
				obj.push_back( new Triangle(pos[0], pos[1], pos[2], color, FILL, size, BLEND) );
				count = 0;
			}
			break;
		case 3:	// 矩形
			if(count==0) {
				count++;
				pos[0][0] = x;
				pos[0][1] = y;
			} else {
				pos[1][0] = x;
				pos[1][1] = y;
				obj.push_back( new Rectangle(pos[0], pos[1], color, FILL, size, BLEND) );
				count = 0;
			}
			break;
		case 4:	// 圓形
			if(count==0) {
				count++;
				pos[0][0] = x;
				pos[0][1] = y;
			} else {
				pos[1][0] = x;
				pos[1][1] = y;
				obj.push_back( new Circle(pos[0], pos[1], color, FILL, size, BLEND) );
				count = 0;
			}
			break;
		case 5:	// 橡擦
			pos[0][0] = x;
			pos[0][1] = y;
			obj.push_back( new Quads(pos[0], size) );
			break;
		case 6:	// 畫筆
			pos[0][0] = x;
			pos[0][1] = y;
			obj.push_back( new Pen(pos[0], color, size, BLEND) );
			break;
		case 7: // 清除全部的繪圖物件
			obj.clear();
			draw_mode = 6;
			break;
		default:
			break;
		}
	}
	glutPostRedisplay();
}

void OnMouseMove(int x, int y)
{
	if (draw_mode == 5) {
		pos[0][0] = x;
		pos[0][1] = y;
		obj.push_back( new Quads(pos[0], size) );
		glutPostRedisplay();
	} else if (draw_mode == 6) {
		pos[0][0] = x;
		pos[0][1] = y;
		obj.push_back( new Pen(pos[0], color, size, BLEND) );
		glutPostRedisplay();
	}
}


void OnIdle(void)
{
}

///////////////////////////////////////////////////////////////////////////////
// menu function
///////////////////////////////////////////////////////////////////////////////

void right_menu(int id)
{
   draw_mode = id;
   count = 0;
}

void object_menu(int id)
{
   draw_mode = id;
   count = 0;
}

void fill_menu(int id)
{
	switch(id) {
	case 1:
		FILL = true;
		break;
	case 2:
		FILL = false;
		break;
	case 3:
		BLEND = true;
		break;
	case 4:
		BLEND = false;
		break;
	}
}

void pixel_menu(int id)
{
   if (id == 1) size *= 2.0;
   else if (size > 1) size /= 2.0;
   if (id == 3) size = 3.0;
}

void color_menu(int id)
{
   if(id == 1) {color[0] = 1.0; color[1] = 0.0; color[2] = 0.0; color[3] = 0.5;}
   else if(id == 2) {color[0] = 0.0; color[1] = 1.0; color[2] = 0.0; color[3] = 0.5;}
   else if(id == 3) {color[0] = 0.0; color[1] = 0.0; color[2] = 1.0; color[3] = 0.5;}
   else if(id == 4) {color[0] = 0.0; color[1] = 1.0; color[2] = 1.0; color[3] = 0.5;}
   else if(id == 5) {color[0] = 1.0; color[1] = 0.0; color[2] = 1.0; color[3] = 0.5;}
   else if(id == 6) {color[0] = 1.0; color[1] = 1.0; color[2] = 0.0; color[3] = 0.5;}
   else if(id == 7) {color[0] = 1.0; color[1] = 1.0; color[2] = 1.0; color[3] = 0.5;}
   else if(id == 8) {color[0] = 0.0; color[1] = 0.0; color[2] = 0.0; color[3] = 0.5;}
   else if(id == 9) {	
		color[0] = (rand()%255)/255.0; 
		color[1] = (rand()%255)/255.0; 
		color[2] = (rand()%255)/255.0; 
		color[3] = (rand()%255)/255.0;
   }
}

void effect_menu(int id)
{
	switch(id) {
	case 1:
		RandomColor();
		break;
	case 2:
		ReverseFill();
		break;
	case 3:
		RandomSize();
		break;
	case 4:
		ReverseBlend();
		break;
	case 5:
		ReverseColor();
		break;
	default:
		break;
	}
}
///////////////////////////////////////////////////////////////////////////////
// Special effect function
///////////////////////////////////////////////////////////////////////////////

void RandomColor()
{
	int obj_count = obj.size();
	for (int i=0; i<obj_count; ++i)
		obj[i]->setColor(	(GLfloat)(rand()%255)/255.0,
							(GLfloat)(rand()%255)/255.0,
							(GLfloat)(rand()%255)/255.0,
							(GLfloat)(rand()%255)/255.0);
}

void ReverseFill()
{
	int obj_count = obj.size();
	for (int i=0; i<obj_count; ++i)
		obj[i]->reverseFill();
}

void ReverseBlend()
{
	int obj_count = obj.size();
	for (int i=0; i<obj_count; ++i)
		obj[i]->reverseBlend();
}

void ReverseColor()
{
	int obj_count = obj.size();
	for (int i=0; i<obj_count; ++i)
		obj[i]->reverseColor();
}

void RandomSize()
{
	int obj_count = obj.size();
	for (int i=0; i<obj_count; ++i)
		obj[i]->randomSize();
}