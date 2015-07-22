#ifndef _GLUTUI
#define _GLUTUI

void SetupCallback(void);
void CreateWindow(char *title, int ox, int oy, int width, int height);
void InitOpenGL(int width,int height);
void OnSize(int width, int height);
void OnPaint(void);
void OnKeyIn(unsigned char key, int x, int y);
void OnKeySPIn(int key, int x, int y);
void OnKeyUp(unsigned char key, int x, int y);
void OnMouseDown(int button, int state, int x, int y);
void OnMouseMove(int x, int y);
void OnIdle(void);
// effect function
void RandomColor(void);
void ReverseFill(void);
void ReverseBlend(void);
void ReverseColor(void);
void RandomSize(void);
// menu function
void right_menu(int id);
void fill_menu(int id);
void color_menu(int id);
void object_menu(int id);
void pixel_menu(int id);
void effect_menu(int id);
#endif