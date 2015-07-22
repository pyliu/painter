// Pen.h: interface for the Pen class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PEN_H__34D9E31E_B790_4DF8_9EC3_9A82FFC00A31__INCLUDED_)
#define AFX_PEN_H__34D9E31E_B790_4DF8_9EC3_9A82FFC00A31__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "PaintObject.h"

class Pen : public PaintObject  
{
private:
	int mouse_position[2];
public:
	Pen(int mouse[2], GLfloat col[4], GLfloat size, bool bl);
	virtual ~Pen();

	virtual void doDraw();


};

#endif // !defined(AFX_PEN_H__34D9E31E_B790_4DF8_9EC3_9A82FFC00A31__INCLUDED_)
