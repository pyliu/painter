// PaintObject.h: interface for the PaintObject class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PAINTOBJECT_H__0CCAB377_189B_4E4C_8135_ABBB00032AEC__INCLUDED_)
#define AFX_PAINTOBJECT_H__0CCAB377_189B_4E4C_8135_ABBB00032AEC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//////////////////////////////////////////////////////////////////////

#include <gl/glut.h>

class PaintObject  
{
protected:
	GLfloat color[4];
	GLfloat size;
	bool fill;
	bool blend;
public:
	virtual void setColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
	virtual void setSize(GLfloat si);
	virtual void reverseFill();
	virtual void reverseBlend();
	virtual void reverseColor();
	virtual void randomSize();
	virtual void doDraw() = 0;
};

#endif // !defined(AFX_PAINTOBJECT_H__0CCAB377_189B_4E4C_8135_ABBB00032AEC__INCLUDED_)
