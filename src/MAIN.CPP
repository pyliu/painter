#include <gl/glut.h>

#include "glutuiframe.h"

void main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	CreateWindow("OpenGL Painter", 100, 100, 640, 480);
	SetupCallback();
	InitOpenGL(640, 480);
	glutMainLoop();
}