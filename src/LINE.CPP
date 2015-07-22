// Line.cpp: implementation of the Line class.
//
//////////////////////////////////////////////////////////////////////

#include "Line.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Line::Line(int start[2], int end[2], GLfloat col[4], GLfloat size, bool bl)
{
	start_point[0] = start[0];
	start_point[1] = start[1];
	end_point[0] = end[0];
	end_point[1] = end[1];
	color[0] = col[0];
	color[1] = col[1];
	color[2] = col[2];
	color[3] = col[3];
	setSize(size);
	blend = bl;
}

Line::~Line()
{

}

//////////////////////////////////////////////////////////////////////
// Member Function
//////////////////////////////////////////////////////////////////////

void
Line::doDraw()
{
	glColor4f(color[0], color[1], color[2], color[3]);
	if (blend)
		glEnable(GL_BLEND);

	glLineWidth(size);
	glBegin(GL_LINES); 
		glVertex2i(start_point[0], start_point[1]);
		glVertex2i(end_point[0], end_point[1]);
	glEnd();

	if (blend)
		glDisable(GL_BLEND);
}