// Circle.h: interface for the Circle class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CIRCLE_H__128EC1C7_84C6_49ED_B8EE_69E5369C34E0__INCLUDED_)
#define AFX_CIRCLE_H__128EC1C7_84C6_49ED_B8EE_69E5369C34E0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "PaintObject.h"

class Circle : public PaintObject  
{
private:
	int start_point[2];
	int end_point[2];
public:
	Circle(int start[2], int end[2], GLfloat col[4], bool f, GLfloat size, bool bl);
	virtual ~Circle();

	virtual void doDraw();
};

#endif // !defined(AFX_CIRCLE_H__128EC1C7_84C6_49ED_B8EE_69E5369C34E0__INCLUDED_)
