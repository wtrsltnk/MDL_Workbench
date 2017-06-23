#include "CGLWindow.h"

//////////////////////////////////////////////////////////////////
// Koppeling WIN32 -> Klasse
//////////////////////////////////////////////////////////////////
LRESULT CALLBACK GLProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	CGLWindow *wnd = 0; 

	if(uMsg == WM_NCCREATE) 
	{
		wnd = reinterpret_cast<CGLWindow *>(((LPCREATESTRUCT)lParam)->lpCreateParams); 
		::SetWindowLong(hWnd, GWL_USERDATA, reinterpret_cast<long>(wnd));

		wnd->SetHWND( hWnd );
	}
	else 
		wnd = reinterpret_cast<CGLWindow *>(::GetWindowLong(hWnd, GWL_USERDATA)); 

	return wnd->ClassProc(hWnd, uMsg, wParam, lParam); 
}

CGLWindow::CGLWindow( HINSTANCE hInstance, HWND hParent, int nX, int nY, int nWidth, int nHeight, int nId)
{
	this->m_nId				 = nId;
	this->m_hInstance		 = hInstance;
	this->m_hParent			 = hParent;
	this->m_nX				 = nX;
	this->m_nY				 = nY;
	this->m_nWidth			 = nWidth;
	this->m_nHeight			 = nHeight;

	this->m_hWnd			 = NULL;
	this->m_dwWindowStyle	 = WS_VISIBLE | WS_CHILD;
	this->m_dwExWindowStyle	 = WS_EX_WINDOWEDGE;
	this->m_dwCreationFlags  = SW_SHOW;
	this->m_hbrWindowColor	 = (HBRUSH)(COLOR_WINDOW);
	this->m_hIcon			 = LoadIcon( m_hInstance, (LPCTSTR)IDI_APPLICATION );
	this->m_strWindowTitle	 = "Title";
	this->m_bFocus			 = TRUE;

	this->m_pCamera			 = NULL;

	this->m_pfnRender		 = NULL;
	this->m_pMain			 = NULL;

	WNDCLASS	wc;
	
	wc.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc		= (WNDPROC) GLProc;
	wc.cbClsExtra		= 0;
	wc.cbWndExtra		= 0;
	wc.hInstance		= m_hInstance;
	wc.hIcon			= m_hIcon;
	wc.hCursor			= LoadCursor( NULL, IDC_ARROW );
	wc.hbrBackground	= m_hbrWindowColor;
	wc.lpszMenuName		= NULL;
	wc.lpszClassName	= "GLWindow";

	RegisterClass(&wc);
}

CGLWindow::~CGLWindow()
{
	Kill();
}

HWND CGLWindow::Create()
{
	int		PixelFormat;

	// Window maken
	if (!(m_hWnd=CreateWindowEx(	this->m_dwExWindowStyle,
								"GLWindow",
								"",
								this->m_dwWindowStyle |
								WS_CLIPSIBLINGS |
								WS_CLIPCHILDREN,
								m_nX, m_nY,
								m_nWidth,
								m_nHeight,
								m_hParent,
								NULL,
								m_hInstance,
								this)))
	{
		Kill();
		MessageBox(NULL,"Window Creation Error.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;
	}

	// Pixel format difinieren
	static	PIXELFORMATDESCRIPTOR pfd=
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW |
		PFD_SUPPORT_OPENGL |
		PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		16,
		0, 0, 0, 0, 0, 0,
		0,
		0,
		0,
		0, 0, 0, 0,
		16,
		0,
		0,
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	};
	
	// Device Context opvragen
	if (!(m_hDC=GetDC(m_hWnd)))
	{
		Kill();
		MessageBox(NULL,"Can't Create A GL Device Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;
	}

	// Huidige Pixel format opvragen
	if (!(PixelFormat=ChoosePixelFormat(m_hDC,&pfd)))
	{
		Kill();
		MessageBox(NULL,"Can't Find A Suitable PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;
	}

	// Nieuwe Pixelformat instellen
	if(!SetPixelFormat(m_hDC,PixelFormat,&pfd))
	{
		Kill();
		MessageBox(NULL,"Can't Set The PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;
	}

	// Render Context maken
	if (!(m_hRC=wglCreateContext(m_hDC)))
	{
		Kill();
		MessageBox(NULL,"Can't Create A GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;
	}

	// Render context van dit scherm de huidige OpenGL context maken
	if(!wglMakeCurrent(m_hDC,m_hRC))
	{
		Kill();
		MessageBox(NULL,"Can't Activate The GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;
	}

	// Window Juist Weergeven en de Focus geven
	ShowWindow(m_hWnd,SW_SHOW);
	SetForegroundWindow(m_hWnd);
	SetFocus(m_hWnd);

	// Window Laten initialiseren
	SendMessage( m_hWnd, WM_INITDIALOG, NULL, 0 );

	return m_hWnd;
}

void CGLWindow::Kill()
{
	if (m_hRC)
	{
		if (!wglMakeCurrent(NULL,NULL))
		{
			MessageBox(NULL,"Release Of DC And RC Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}

		if (!wglDeleteContext(m_hRC))
		{
			MessageBox(NULL,"Release Rendering Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}
		m_hRC=NULL;
	}

	if (m_hDC && !ReleaseDC(m_hWnd,m_hDC))
	{
		MessageBox(NULL,"Release Device Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		m_hDC=NULL;
	}

	if (m_hWnd && !DestroyWindow(m_hWnd))
	{
		MessageBox(NULL,"Could Not Release hWnd.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		m_hWnd=NULL;
	}

	if (!UnregisterClass("OpenGL",m_hInstance))
	{
		MessageBox(NULL,"Could Not Unregister Class.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		m_hInstance=NULL;
	}
}

//////////////////////////////////////////////////////////////////
// Klasse Functies
//////////////////////////////////////////////////////////////////
LRESULT CGLWindow::ClassProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	static int X = 0;
	static int Y = 0;

	switch (uMsg)
	{
	case WM_INITDIALOG:
		break;

	case WM_SETFOCUS:
		m_bFocus = true;
		InvalidateRect(hWnd, NULL, true);
		break;
	case WM_KILLFOCUS:
		m_bFocus = false;
		InvalidateRect(hWnd, NULL, true);
		break;

	case WM_LBUTTONUP:
	case WM_MBUTTONUP:
	case WM_RBUTTONUP:
		ReleaseCapture();
		break;

	case WM_LBUTTONDOWN:
	case WM_MBUTTONDOWN:
	case WM_RBUTTONDOWN:
		SetFocus(hWnd);
		SetCapture(hWnd);

		X = HIWORD(lParam);
		Y = LOWORD(lParam);

		InvalidateRect(hWnd, NULL, true);
		break;

	case WM_MOUSEMOVE:
			switch (wParam)
			{
			case MK_LBUTTON:
				{
				float fRotx = (float) -(X - HIWORD(lParam));
				float fRoty = (float) -(Y - LOWORD(lParam));

				X = HIWORD(lParam);
				Y = LOWORD(lParam);

				m_pCamera->Rotate(fRotx, fRoty, 0.0f);
				InvalidateRect(hWnd, NULL, true);
				}
				break;

			case MK_MBUTTON:
				{
				float fPanx = (float) (X - HIWORD(lParam));
				float fPany = (float) (Y - LOWORD(lParam));

				X = HIWORD(lParam);
				Y = LOWORD(lParam);

				m_pCamera->Translate(-fPany/100, fPanx/100, 0.0f);
				InvalidateRect(hWnd, NULL, true);
				}
				break;

			case MK_RBUTTON:
				{
				float fPanx = (float) (X - HIWORD(lParam));
				float fPany = (float) (Y - LOWORD(lParam));

				X = HIWORD(lParam);
				Y = LOWORD(lParam);

				m_pCamera->Translate(0.0f, 0.0f, fPanx/10);
				InvalidateRect(hWnd, NULL, true);
				}
				break;
			}
		break;

	case WM_PAINT:
		if (m_pfnRender && m_pMain)
			m_pfnRender(this, m_pMain);
		ValidateRect(hWnd,NULL);
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

void CGLWindow::Resize( int nX, int nY, int nWidth, int nHeight )
{
	this->m_nX = nX;
	this->m_nY = nY;
	this->m_nWidth = nWidth;
	this->m_nHeight = nHeight;

	MoveWindow( m_hWnd, m_nX, m_nY, m_nWidth, m_nHeight, true );
	
    wglMakeCurrent( m_hDC, m_hRC );

	glViewport(2, 3, m_nWidth-4, m_nHeight-4);

	m_pCamera->Init(m_nWidth, m_nHeight);
}

void CGLWindow::SetCamera( CGLCamera* pCamera )
{
	this->m_pCamera = pCamera;
}

void CGLWindow::SetRender( RENDER_CALLBACK pfnRender, VOID* pMain )
{
	this->m_pfnRender = pfnRender;
	this->m_pMain = pMain;
}

void CGLWindow::Use()
{
    wglMakeCurrent( m_hDC, m_hRC );

	glEnable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
}

void CGLWindow::Start()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	m_pCamera->Update();

	glClearColor( 0.4f, 0.4f, 0.4f, 0.0f );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}

void CGLWindow::End()
{
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);

	glOrtho( -1, 1, -1, 1, -300.0f, 300.0f );
	glLoadIdentity();
	glTranslatef(-0.4f, -0.3f, -1.0f);

	glRotatef(m_pCamera->GetRotX(), 1.0f, 0.0f, 0.0f);
	glRotatef(m_pCamera->GetRotY(), 0.0f, 1.0f, 0.0f);
	glRotatef(m_pCamera->GetRotZ(), 0.0f, 0.0f, 1.0f);

	glBegin(GL_LINES);

		// X-AS
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(0, 0, 0); glVertex3f(0.1f, 0, 0);

		// Y-AS
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(0, 0, 0); glVertex3f(0, 0.1f, 0);

		// Z-AS
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(0, 0, 0); glVertex3f(0, 0, 0.1f);
	glEnd();

	SwapBuffers( m_hDC );
/*
	if ( m_bFocus )
	{
		SelectObject(m_hDC, CreatePen(PS_SOLID,3,RGB(100,200,255)));
		SelectObject(m_hDC, GetStockObject(NULL_BRUSH));
		Rectangle(m_hDC, 1, 1, m_nWidth, m_nHeight);
	}
	else
	{
		SelectObject(m_hDC, CreatePen(PS_SOLID,2,RGB(50,50,50)));
		SelectObject(m_hDC, GetStockObject(NULL_BRUSH));
		Rectangle(m_hDC, 1, 1, m_nWidth, m_nHeight);
	}
*/
}