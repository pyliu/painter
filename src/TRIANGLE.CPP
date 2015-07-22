// Triangle.cpp: implementation of the Triangle class.
//
//////////////////////////////////////////////////////////////////////

#include "Triangle.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Triangle::Triangle(int start[2], int middle[2], int end[2], GLfloat col[4], bool f, GLfloat size, bool bl)
{
	fill = f;
	start_point[0] = start[0];
	start_point[1] = start[1];
	middle_point[0] = middle[0];
	middle_point[1] = middle[1];
	end_point[0] = end[0];
	end_point[1] = end[1];
	color[0] = col[0];
	color[1] = col[1];
	color[2] = col[2];
	color[3] = col[3];
	setSize(size);
	blend = bl;
}

Triangle::~Triangle()
{

}

//////////////////////////////////////////////////////////////////////
// Member function
//////////////////////////////////////////////////////////////////////

void
Triangle::doDraw()
{
	glColor4f(color[0], color[1], color[2], color[3]);
	if (blend)
		glEnable(GL_BLEND);

	if (fill) 
		glBegin(GL_TRIANGLES); 
	else {
		glLineWidth(size);
		glBegin(GL_LINE_LOOP);
	}
			glVertex2i(start_point[0], start_point[1]);
			glVertex2i(middle_point[0], middle_point[1]);
			glVertex2i(end_point[0], end_point[1]);
		glEnd();

	if (blend)
		glEnable(GL_BLEND);
}