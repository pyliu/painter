// PaintObject.cpp: implementation of the PaintObject class.
//
//////////////////////////////////////////////////////////////////////

#include "PaintObject.h"
#include <cstdlib>
#include <ctime>

void
PaintObject::setColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
	color[0] = r;
	color[1] = g;
	color[2] = b;
	color[3] = a;
}

void
PaintObject::setSize(GLfloat si)
{
	size = si;
}

void
PaintObject::reverseFill()
{
	fill = !fill;
}

void
PaintObject::reverseBlend()
{
	blend = !blend;
}

void
PaintObject::reverseColor()
{
	for (int i=0; i<4; ++i)
		color[i] = 1.0-color[i];
}

void
PaintObject::randomSize()
{
	size = rand()%32;
}