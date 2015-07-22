// Triangle.h: interface for the Triangle class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRIANGLE_H__4139652E_BCA4_4E2E_8994_553645C59823__INCLUDED_)
#define AFX_TRIANGLE_H__4139652E_BCA4_4E2E_8994_553645C59823__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "PaintObject.h"

class Triangle : public PaintObject  
{
private:
	int start_point[2];
	int middle_point[2];
	int end_point[2];
public:
	Triangle(int start[2], int middle[2], int end[2], GLfloat col[4], bool f, GLfloat size, bool bl);
	virtual void doDraw();
	virtual ~Triangle();

};

#endif // !defined(AFX_TRIANGLE_H__4139652E_BCA4_4E2E_8994_553645C59823__INCLUDED_)
