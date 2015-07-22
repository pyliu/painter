// Circle.cpp: implementation of the Circle class.
//
//////////////////////////////////////////////////////////////////////

#include "Circle.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Circle::Circle(int start[2], int end[2], GLfloat col[3], bool f, GLfloat size, bool bl)
{
	fill = f;
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

Circle::~Circle()
{

}

//////////////////////////////////////////////////////////////////////
// Member function
//////////////////////////////////////////////////////////////////////

void
Circle::doDraw()
{
	glColor4f(color[0], color[1], color[2], color[3]);
	if (blend)
		glEnable(GL_BLEND);
	
	if (fill) 
		;
	else 
		;
	
	if (blend)
		glDisable(GL_BLEND);
}