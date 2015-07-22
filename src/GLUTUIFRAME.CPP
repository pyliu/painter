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

int g_width, g_height;	// �����������e
int draw_mode = 6;		// �w�]�O�e��
int count = 0;			// �����ثe���I
GLfloat size = 3.0;		// ����pixel�j�p
bool FILL = false;		// �]�w�O�_�n�񺡹ϧ�
bool BLEND = false;		// �]�w�O�_�n�ҥγz����
int pos[3][2];			// ����"�I"��}
GLfloat color[4]={0.0, 0.0, 0.0, 0.5};	// �w�]�C��O�¦�

vector<PaintObject *> obj;	// �����Ҧ�ø�Ϫ���

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
	
	// �I���]���Ǧ�
	glClearColor(0.8, 0.8, 0.8, 1.0);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// �]�w�k��menu
	int f_menu = glutCreateMenu(fill_menu);
    glutAddMenuEntry("���}��", 1);
    glutAddMenuEntry("������", 2);
	glutAddMenuEntry("���}�z��", 3);
	glutAddMenuEntry("�����z��", 4);

	int c_menu = glutCreateMenu(color_menu);
    glutAddMenuEntry("��",1);
    glutAddMenuEntry("��",2);
    glutAddMenuEntry("��",3);
    glutAddMenuEntry("�C��",4);
    glutAddMenuEntry("�v��",5);
    glutAddMenuEntry("��",6);
    glutAddMenuEntry("��",7);
    glutAddMenuEntry("��",8);
	glutAddMenuEntry("�H��",9);

	int o_menu = glutCreateMenu(object_menu);
	glutAddMenuEntry("�u",1);
	glutAddMenuEntry("�T����",2);
	glutAddMenuEntry("�x��",3);
	//glutAddMenuEntry("���",4);
	glutAddMenuEntry("����",5);
	glutAddMenuEntry("�e��",6);

	int p_menu = glutCreateMenu(pixel_menu);
    glutAddMenuEntry("�W�[�����j�p", 1);
    glutAddMenuEntry("��ֹ����j�p", 2);
	glutAddMenuEntry("�w�]�����j�p", 3);

	int e_menu = glutCreateMenu(effect_menu);
    glutAddMenuEntry("�H���C��", 1);
	glutAddMenuEntry("�����C��", 5);
    glutAddMenuEntry("�񺡤���", 2);
	glutAddMenuEntry("�z������", 4);
	glutAddMenuEntry("�H���j�p", 3);

	glutCreateMenu(right_menu);
	glutAddSubMenu("ø�Ϫ���", o_menu);
	glutAddSubMenu("�C��ﶵ", c_menu);
	glutAddSubMenu("�����j�p", p_menu);
	glutAddSubMenu("�}���ﶵ", f_menu);
	glutAddSubMenu("�S�O�ﶵ", e_menu);
	glutAddMenuEntry("�M��",7);
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
	if (key == 'a') {	// ��"a"�irandom�]�w�C��
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
	case GLUT_KEY_F1:	// �񺡤���
		ReverseFill();
		glutPostRedisplay();
		break;
	case GLUT_KEY_F2:	// �����C��
		ReverseColor();
		glutPostRedisplay();
		break;
	case GLUT_KEY_F3:	// �H�������j�p
		RandomSize();
		glutPostRedisplay();
		break;
	case GLUT_KEY_F4:	// �H�������j�p
		ReverseBlend();
		glutPostRedisplay();
		break;
	case GLUT_KEY_F5:	// �H���C��
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
		case 1:	// �u
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
		case 2:	// �T����
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
		case 3:	// �x��
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
		case 4:	// ���
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
		case 5:	// ����
			pos[0][0] = x;
			pos[0][1] = y;
			obj.push_back( new Quads(pos[0], size) );
			break;
		case 6:	// �e��
			pos[0][0] = x;
			pos[0][1] = y;
			obj.push_back( new Pen(pos[0], color, size, BLEND) );
			break;
		case 7: // �M��������ø�Ϫ���
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