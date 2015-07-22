// Line.h: interface for the Line class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LINE_H__08485293_E1FB_415A_AF5E_43BC1FA1B773__INCLUDED_)
#define AFX_LINE_H__08485293_E1FB_415A_AF5E_43BC1FA1B773__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//////////////////////////////////////////////////////////////////////

#include "PaintObject.h"

class Line : public PaintObject  
{
private:
	int start_point[2];
	int end_point[2];
public:
	Line(int start[2], int end[2], GLfloat col[4], GLfloat size, bool bl);
	virtual void doDraw();
	virtual ~Line();

};

#endif // !defined(AFX_LINE_H__08485293_E1FB_415A_AF5E_43BC1FA1B773__INCLUDED_)
