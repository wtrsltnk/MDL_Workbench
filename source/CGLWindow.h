#ifndef CGLWINDOW_H
#define CGLWINDOW_H

#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glaux.h>

#include "resource.h"

#include "CGLCamera.h"

class CGLWindow;
typedef void (*RENDER_CALLBACK)(CGLWindow*, VOID*);
typedef void (*SELECT_CALLBACK)(CGLWindow*, VOID*, RECT*);

class CGLWindow
{
private:
	HWND								m_hWnd, m_hLabel;
	HWND								m_hParent;
	HINSTANCE							m_hInstance;
    HDC									m_hDC;
    HGLRC								m_hRC;

	int									m_nX, m_nY, m_nWidth, m_nHeight;

	DWORD								m_nId;
	DWORD								m_dwWindowStyle;
	DWORD								m_dwExWindowStyle;
 	DWORD								m_dwCreationFlags;
	CHAR								*m_strWindowTitle;
	HBRUSH								m_hbrWindowColor;
	HICON								m_hIcon;

	BOOL								m_bFocus;

	CGLCamera*							m_pCamera;
	RENDER_CALLBACK						m_pfnRender;
	VOID*								m_pMain;
protected:
public:
	CGLWindow( HINSTANCE hInstance, HWND hParent, int nX, int nY, int nWidth, int nHeight, int nId );
	~CGLWindow();
	
	virtual LRESULT ClassProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
	void SetHWND( HWND hWnd ) { m_hWnd = hWnd; };

	HWND Create( void );
	void Kill( void );
	void Resize( int, int, int, int );

	void SetCamera( CGLCamera* pCamera );
	void SetRender( RENDER_CALLBACK pfnRender, VOID* pMain );

	void Use();
	void Start();
	void End();
};
#endif