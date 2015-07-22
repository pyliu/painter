// Pen.cpp: implementation of the Pen class.
//
//////////////////////////////////////////////////////////////////////

#include "Pen.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Pen::Pen(int mouse[2], GLfloat col[4], GLfloat size, bool bl)
{
	mouse_position[0] = mouse[0];
	mouse_position[1] = mouse[1];
	color[0] = col[0];
	color[1] = col[1];
	color[2] = col[2];
	color[3] = col[3];
	setSize(size);
	blend = bl;
}

Pen::~Pen()
{

}

//////////////////////////////////////////////////////////////////////
// Member function
//////////////////////////////////////////////////////////////////////

void
Pen::doDraw()
{
	glColor4f(color[0], color[1], color[2], color[3]);
	if (blend)
		glEnable(GL_BLEND);

	glPointSize(size);
	glBegin(GL_POINTS);
		glVertex2i(mouse_position[0], mouse_position[1]);
	glEnd();

	if (blend)
		glDisable(GL_BLEND);
}