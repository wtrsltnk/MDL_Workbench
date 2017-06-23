#ifndef COPENGL_H
#define COPENGL_H

#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glaux.h>

#include "CControl.h"
#include "../resource/resource.h"

#define RENDERMODE_VERTEX			0
#define RENDERMODE_WIREFRAME		1
#define RENDERMODE_FLATSHADE		2
#define RENDERMODE_SMOOTHSHADE		3
#define RENDERMODE_TEXTURED			4

#define VIEWTYPE_CENTER				0
#define VIEWTYPE_PLAYER				1
#define VIEWTYPE_MATERIAL			2
#define VIEWTYPE_NORMAL				3

class COpenGl : public CControl
{
public:

    COpenGl( HINSTANCE hInstance, HWND hParent, int nX, int nY, int nWidth, int nHeight, int nId );

    ~COpenGl();

	bool CreateGLWindow(char* title, int x, int y, int width, int height, int bits);
	void KillGLWindow(GLvoid);

	void resize( int nX, int nY, int nWidth, int nHeight );

	bool init( void );
	void initfont( void );

	void drawstart( void );
	void drawend( void );
	void drawtext( int x, int y, const char *format, ...);

	void rotate( float, float, float );
	void move( float, float, float );

	int getPan(){return panz;};
	unsigned int getFont(){return font;};
	
	LRESULT MsgProc( HWND, UINT, WPARAM, LPARAM );

private:
	int									control_id;

	HWND								m_hParent;
	HINSTANCE							m_hInstance;
    HDC									m_hDC;
    HGLRC								m_hRC;
	int									m_nX, m_nY, m_nWidth, m_nHeight;

	float								oldx, oldy;
	float								oldpx, oldpy, oldpz;
	float								panx, pany, panz;
	float								oldrx, oldry, oldrz;
	float								rotx, roty, rotz;

	bool								m_bKeys[255];
	int									rendermode;
	float								bgcolor[3];
	float								txtcolor[3];
	float								LightAmbient[4];
	float								LightDiffuse[4];
	float								LightSpecular[4];
	float								LightPosition[4];
	float								LightShininess[1];

	unsigned int						font;

	void setupRenderMode( void );
	void setupLighting( void );
};

#endif