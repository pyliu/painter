// Quads.h: interface for the Quads class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_QUADS_H__2E039FCE_2828_4BAD_8034_0FCC577FF05F__INCLUDED_)
#define AFX_QUADS_H__2E039FCE_2828_4BAD_8034_0FCC577FF05F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "PaintObject.h"

class Quads : public PaintObject  
{
private:
	GLfloat mouse_position[2];
public:
	Quads(int mouse[2], GLfloat size);
	virtual ~Quads();

	virtual void doDraw();
	virtual void setColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
	virtual void reverseColor() {}

};

#endif // !defined(AFX_QUADS_H__2E039FCE_2828_4BAD_8034_0FCC577FF05F__INCLUDED_)
