// Quads.cpp: implementation of the Quads class.
//
//////////////////////////////////////////////////////////////////////

#include "Quads.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Quads::Quads(int mouse[2], GLfloat size)
{
	mouse_position[0] = (GLfloat)mouse[0];
	mouse_position[1] = (GLfloat)mouse[1];
	setColor(0.8, 0.8, 0.8, 1.0);
	setSize(size);
}

Quads::~Quads()
{

}

//////////////////////////////////////////////////////////////////////
// Member function
//////////////////////////////////////////////////////////////////////

void
Quads::doDraw()
{
	glColor4f(color[0], color[1], color[2], color[3]);
	glRectf(mouse_position[0]-size/2.0,
			mouse_position[1]-size/2.0,
			mouse_position[0]+size/2.0,
			mouse_position[1]+size/2.0);
}

void
Quads::setColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
	color[0] = 0.8;
	color[1] = 0.8;
	color[2] = 0.8;
	color[3] = 1.0;
}