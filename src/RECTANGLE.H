// Rectangle.h: interface for the Rectangle class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RECTANGLE_H__0AF38779_AE13_41BA_AA1A_201C35EBD24A__INCLUDED_)
#define AFX_RECTANGLE_H__0AF38779_AE13_41BA_AA1A_201C35EBD24A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "PaintObject.h"

class Rectangle : public PaintObject  
{
private:
	int start_point[2];
	int end_point[2];
public:
	Rectangle(int start[2], int end[2], GLfloat col[4], bool f, GLfloat size, bool bl);
	virtual void doDraw();
	virtual ~Rectangle();

};

#endif // !defined(AFX_RECTANGLE_H__0AF38779_AE13_41BA_AA1A_201C35EBD24A__INCLUDED_)
