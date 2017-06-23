#include "COpenGL.h"
#include <windows.h>

static COpenGl * g_pCWin		= NULL;

//////////////////////////////////////////////////////////////////
// Koppeling WIN32 -> Klasse
//////////////////////////////////////////////////////////////////
LRESULT CALLBACK GLProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return g_pCWin->MsgProc(hWnd, uMsg, wParam, lParam);
}


COpenGl::COpenGl( HINSTANCE hInstance, 
				 HWND hParent, 
				 int nX, int nY, 
				 int nWidth, int nHeight, 
				 int nId ) : CControl( hInstance, hParent, nX, nY , nWidth ,nHeight, nId )
{
	g_pCWin = this;

	this->control_id = nId;
	this->m_hInstance = hInstance;
	this->m_hParent = hParent;
	this->m_nX = nX;
	this->m_nY = nY;
	this->m_nWidth = nWidth;
	this->m_nHeight = nHeight;

	this->rotx = -90.0f;
	this->roty = 0.0f;
	this->rotz = -90.0f;

	this->panx = 0.0f;
	this->pany = 0.0f;
	this->panz = -20.0f;

	this->oldx = -1.0f;
	this->oldy = -1.0f;

	this->oldrx = -1.0f;
	this->oldry = -1.0f;
	this->oldrz = -1.0f;

	this->oldpx = -1.0f;
	this->oldpy = -1.0f;
	this->oldpz = -1.0f;


	for ( int i = 0; i < 255; i++ )
		m_bKeys[i] = false;
}

COpenGl::~COpenGl()
{
	KillGLWindow();
}

LRESULT COpenGl::MsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	float x, y;
	DWORD fwKeys;
	
	switch ( uMsg )
	{
	case WM_CREATE:
		init();
		break;

	case WM_RBUTTONDOWN:
	case WM_MBUTTONDOWN:
	case WM_LBUTTONDOWN:
		SetFocus(hWnd);
		SetCapture(hWnd);
		oldx = LOWORD(lParam);
		oldy = HIWORD(lParam);
		oldpx = panx;
		oldpy = pany;
		oldpz = panz;
		oldrx = rotx;
		oldry = roty;
		oldrz = rotz;
//		SetCursor( LoadCursor( m_hInstance, MAKEINTRESOURCE(IDC_HAND) ) );
		SetCursor( LoadCursor( NULL, IDC_SIZE ) );
		break;

	case WM_RBUTTONUP:
	case WM_MBUTTONUP:
	case WM_LBUTTONUP:
		ReleaseCapture();
		SetCursor( LoadCursor( NULL, IDC_ARROW ) );
		break;

	case WM_MOUSEMOVE:
		fwKeys = wParam;
		x = LOWORD(lParam);
		y = HIWORD(lParam);

		switch (fwKeys)
		{
		case MK_LBUTTON:
			rotz = oldrz - ( oldx - x );
			rotx = oldrx - ( oldy - y );
			//SetCursor( LoadCursor( m_hInstance, MAKEINTRESOURCE(IDC_HAND) ) );
			SetCursor( LoadCursor( NULL, IDC_SIZE ) );
			InvalidateRect(m_hParent, NULL, false);
			break;
		case MK_RBUTTON:
			panz = oldpz + ( ( oldy - y ) / 5 );
			//SetCursor( LoadCursor( m_hInstance, MAKEINTRESOURCE(IDC_HAND) ) );
			SetCursor( LoadCursor( NULL, IDC_SIZE ) );
			InvalidateRect(m_hParent, NULL, false);
			break;
		case MK_MBUTTON:
			panx = oldpx - ( ( oldx - x ) / 20 );
			pany = oldpy + ( ( oldy - y ) / 20 );
			//SetCursor( LoadCursor( m_hInstance, MAKEINTRESOURCE(IDC_HAND) ) );
			SetCursor( LoadCursor( NULL, IDC_SIZE ) );
			InvalidateRect(m_hParent, NULL, false);
			break;
		case MK_RBUTTON|MK_SHIFT:
			panx = oldpx - ( ( oldx - x ) / 20 );
			pany = oldpy + ( ( oldy - y ) / 20 );
			//SetCursor( LoadCursor( m_hInstance, MAKEINTRESOURCE(IDC_HAND) ) );
			SetCursor( LoadCursor( NULL, IDC_SIZE ) );
			InvalidateRect(m_hParent, NULL, false);
			break;
		case MK_LBUTTON|MK_SHIFT:
			roty = oldry - ( oldx - x );
			//SetCursor( LoadCursor( m_hInstance, MAKEINTRESOURCE(IDC_HAND) ) );
			SetCursor( LoadCursor( NULL, IDC_SIZE ) );
			InvalidateRect(m_hParent, NULL, false);
			break;
		default:
			break;
		}
		break;
	}
	return DefWindowProc( hWnd, uMsg, wParam, lParam );
}

void COpenGl::resize( int nX, int nY, int nWidth, int nHeight )
{
	this->m_nX = nX;
	this->m_nY = nY;
	this->m_nWidth = nWidth;
	this->m_nHeight = nHeight;

	MoveWindow( m_hWnd, m_nX, m_nY, m_nWidth, m_nHeight, true );
 
    wglMakeCurrent( m_hDC, m_hRC );   
	glViewport(0, 0, m_nWidth, m_nHeight);
}






// OPENGL FUNCTIES

////////////////////////////////////////////////////////////
// Initialize OpenGl window
// Set default values for rotating, translate, rendermode
// & colors
////////////////////////////////////////////////////////////
bool COpenGl::init( void )
{
	this->rotx = -90.0f;
	this->roty = 0.0f;
	this->rotz = -90.0f;

	this->panx = 0.0f;
	this->pany = 0.0f;
	this->panz = -20.0f;

	this->oldx = -1.0f;
	this->oldy = -1.0f;

	this->oldrx = -1.0f;
	this->oldry = -1.0f;
	this->oldrz = -1.0f;

	this->oldpx = -1.0f;
	this->oldpy = -1.0f;
	this->oldpz = -1.0f;

	this->rendermode = RENDERMODE_WIREFRAME;
	this->bgcolor[0] = 0.0f;
	this->bgcolor[1] = 0.0f;
	this->bgcolor[2] = 0.0f;
	this->txtcolor[0] = 0.0f;
	this->txtcolor[1] = 0.0f;
	this->txtcolor[2] = 1.0f;

	this->LightAmbient[0]	 = 1.0f;
	this->LightAmbient[1]	 = 1.0f;
	this->LightAmbient[2]	 = 1.0f;
	this->LightAmbient[3]	 = 1.0f;

	this->LightDiffuse[0]	 = 0.5f;
	this->LightDiffuse[1]	 = 0.5f;
	this->LightDiffuse[2]	 = 0.5f;
	this->LightDiffuse[3]	 = 1.0f;

	this->LightSpecular[0]	 = 0.9f;
	this->LightSpecular[1]	 = 0.9f;
	this->LightSpecular[2]	 = 0.9f;
	this->LightSpecular[3]	 = 1.0f;

	this->LightPosition[0]	 = 0.0f;
	this->LightPosition[1]	 = 5.0f;
	this->LightPosition[2]	 = 0.0f;
	this->LightPosition[3]	 = 1.0f;

	this->LightShininess[0]	 = 32.0f;
	return true;
}

////////////////////////////////////////////////////////////
// Iitialize font
// Initializes a font to draw in the OpenGl window
////////////////////////////////////////////////////////////
void COpenGl::initfont( void )
{
	font = glGenLists( 255 );

    HFONT verdana = CreateFont( 12, 0, 0, 0, FW_MEDIUM, FALSE,
                    FALSE, FALSE, DEFAULT_CHARSET, OUT_TT_PRECIS,
                    CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY,
                    FF_DONTCARE | DEFAULT_PITCH, "Verdana" );

    SelectObject( m_hDC, verdana );

    wglUseFontBitmaps( m_hDC, 1, 255, font );
}

////////////////////////////////////////////////////////////
// Open draw sequence
// Always call this function first before starting to draw
////////////////////////////////////////////////////////////
void COpenGl::drawstart()
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glClearColor( bgcolor[0], bgcolor[1], bgcolor[2], 0.0f );

	setupRenderMode();
	// setupLighting();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f,(GLfloat)m_nWidth/(GLfloat)m_nHeight,0.5f,300.0f);

	glTranslatef(panx, pany, panz);
	glRotatef(rotx,1,0,0);
	glRotatef(roty,0,1,0);
	glRotatef(rotz,0,0,1);
	glScalef( 0.1f, 0.1f, 0.1f );

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glHint (GL_LINE_SMOOTH_HINT, GL_NICEST );
	glPushMatrix();
}

////////////////////////////////////////////////////////////
// Close draw sequence
// Always call this function after drawing
////////////////////////////////////////////////////////////
void COpenGl::drawend()
{
	glPopMatrix();
	
	SwapBuffers( m_hDC );
}


////////////////////////////////////////////////////////////
// Draw a text on the screen
// use getFont() to specify a initilized font in 3rd param
////////////////////////////////////////////////////////////
void COpenGl::drawtext( int x, int y, const char *format, ...)
{
    va_list argp;
    char text[256];

    va_start( argp, format );
    vsprintf( text, format, argp );
    va_end( argp );

	for ( int i = 0; i < strlen(text); i++ )
	{
		text[i] -= 1;
	}
    glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
    glPushMatrix();

    gluOrtho2D( 0.0, (GLdouble) m_nWidth, 0.0, (GLdouble) m_nHeight );

	glEnable (GL_TEXTURE_2D);
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    glColor4f( txtcolor[0], txtcolor[1], txtcolor[2], 1.0f );
    glRasterPos2i( x, y );
    glListBase( font );
    glCallLists( strlen( text ), GL_BYTE, text );

    glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
    glPopMatrix();
}

////////////////////////////////////////////////////////////
// Rotate viewpoint
// Call this function to rotate the viewpoint
////////////////////////////////////////////////////////////
void COpenGl::rotate( float fRotX, float fRotY, float fRotZ )
{
	rotx += fRotX;
	roty += fRotY;
	rotz += fRotZ;
}

////////////////////////////////////////////////////////////
// Translate viewpoint
// Call this function to translate the viewpoint
////////////////////////////////////////////////////////////
void COpenGl::move( float fTranX, float fTranY, float fTranZ )
{
	panx += fTranX;
	pany += fTranY;
	panz += fTranZ;
}

////////////////////////////////////////////////////////////
// Setup rendermode
// Modes are RENDERMODE_VERTEX, _WIREFRAME, _FLATSHADE,
// _SMOOTHSHADE & _TEXTURED
////////////////////////////////////////////////////////////
void COpenGl::setupRenderMode( void )
{
	switch ( rendermode )
	{
	case RENDERMODE_VERTEX:
		glPointSize( 2 );

		glPolygonMode ( GL_FRONT_AND_BACK, GL_POINT );
		glDisable (GL_TEXTURE_2D);
		glEnable (GL_CULL_FACE);
		glEnable (GL_DEPTH_TEST);
		glShadeModel ( GL_SMOOTH );
		break;
	case RENDERMODE_WIREFRAME:
		glLineWidth( 1 );

		glPolygonMode ( GL_FRONT_AND_BACK, GL_LINE );
		glDisable (GL_TEXTURE_2D);
		glEnable (GL_CULL_FACE);
		glEnable (GL_DEPTH_TEST);
		glShadeModel ( GL_SMOOTH );
		break;
	case RENDERMODE_FLATSHADE:
		glPolygonMode ( GL_FRONT_AND_BACK, GL_FILL );
		glDisable (GL_TEXTURE_2D);
		glEnable (GL_CULL_FACE);
		glEnable (GL_DEPTH_TEST);
		glShadeModel ( GL_FLAT );
		break;
	case RENDERMODE_SMOOTHSHADE:
		glPolygonMode ( GL_FRONT_AND_BACK, GL_FILL );
		glDisable (GL_TEXTURE_2D);
		glEnable (GL_CULL_FACE);
		glEnable (GL_DEPTH_TEST);
		glShadeModel ( GL_SMOOTH );
		break;
	case RENDERMODE_TEXTURED:
		glPolygonMode ( GL_FRONT_AND_BACK, GL_FILL );
		glEnable (GL_TEXTURE_2D);
		glEnable (GL_CULL_FACE);
		glEnable (GL_DEPTH_TEST);
		glShadeModel ( GL_SMOOTH );
		break;
	}
}

void COpenGl::setupLighting( void )
{
	glPushMatrix();
	glLightfv( GL_LIGHT1, GL_AMBIENT, LightAmbient );
	glLightfv( GL_LIGHT1, GL_DIFFUSE, LightDiffuse );
	glLightfv( GL_LIGHT1, GL_SPECULAR, LightSpecular );
	glLightfv( GL_LIGHT1, GL_POSITION, LightPosition );
	glEnable( GL_LIGHT1 );

	glMaterialfv(GL_FRONT, GL_SPECULAR, LightSpecular);
	glMaterialfv(GL_FRONT, GL_SHININESS, LightShininess);
	glEnable( GL_LIGHTING );
	glPopMatrix();
}








void COpenGl::KillGLWindow(GLvoid)								// Properly Kill The Window
{
	if (m_hRC)											// Do We Have A Rendering Context?
	{
		if (!wglMakeCurrent(NULL,NULL))					// Are We Able To Release The DC And RC Contexts?
		{
			MessageBox(NULL,"Release Of DC And RC Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}

		if (!wglDeleteContext(m_hRC))						// Are We Able To Delete The RC?
		{
			MessageBox(NULL,"Release Rendering Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}
		m_hRC=NULL;										// Set RC To NULL
	}

	if (m_hDC && !ReleaseDC(m_hWnd,m_hDC))					// Are We Able To Release The DC
	{
		MessageBox(NULL,"Release Device Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		m_hDC=NULL;										// Set DC To NULL
	}

	if (m_hWnd && !DestroyWindow(m_hWnd))					// Are We Able To Destroy The Window?
	{
		MessageBox(NULL,"Could Not Release hWnd.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		m_hWnd=NULL;										// Set hWnd To NULL
	}

	if (!UnregisterClass("OpenGL",m_hInstance))			// Are We Able To Unregister Class
	{
		MessageBox(NULL,"Could Not Unregister Class.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		m_hInstance=NULL;									// Set hInstance To NULL
	}
}






bool COpenGl::CreateGLWindow(char* title, int x, int y, int width, int height, int bits)
{
	GLuint		PixelFormat;			// Holds The Results After Searching For A Match
	WNDCLASS	wc;						// Windows Class Structure
	DWORD		dwExStyle;				// Window Extended Style
	DWORD		dwStyle;				// Window Style
	RECT		WindowRect;				// Grabs Rectangle Upper Left / Lower Right Values
	WindowRect.left=(long)0;			// Set Left Value To 0
	WindowRect.right=(long)width;		// Set Right Value To Requested Width
	WindowRect.top=(long)0;				// Set Top Value To 0
	WindowRect.bottom=(long)height;		// Set Bottom Value To Requested Height

	m_hInstance			= GetModuleHandle(NULL);				// Grab An Instance For Our Window
	wc.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	// Redraw On Size, And Own DC For Window.
	wc.lpfnWndProc		= (WNDPROC) GLProc;					// WndProc Handles Messages
	wc.cbClsExtra		= 0;									// No Extra Window Data
	wc.cbWndExtra		= 0;									// No Extra Window Data
	wc.hInstance		= m_hInstance;							// Set The Instance
	wc.hIcon			= LoadIcon(NULL, IDI_WINLOGO);			// Load The Default Icon
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);			// Load The Arrow Pointer
	wc.hbrBackground	= NULL;									// No Background Required For GL
	wc.lpszMenuName		= NULL;									// We Don't Want A Menu
	wc.lpszClassName	= "OpenGL";								// Set The Class Name

	if (!RegisterClass(&wc))									// Attempt To Register The Window Class
	{
		MessageBox(NULL,"Failed To Register The Window Class.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;											// Return FALSE
	}

	dwExStyle=WS_EX_WINDOWEDGE;			// Window Extended Style
	dwStyle=WS_OVERLAPPED;

	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);		// Adjust Window To True Requested Size

	// Create The Window
	if (!(m_hWnd=CreateWindowEx(	dwExStyle,							// Extended Style For The Window
								"OpenGL",							// Class Name
								title,								// Window Title
								dwStyle |							// Defined Window Style
								WS_CHILD,
								x, y,								// Window Position
								width,
								height,
								m_hParent,								// No Parent Window
								NULL,								// No Menu
								m_hInstance,						// Instance
								NULL)))								// Dont Pass Anything To WM_CREATE
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Window Creation Error.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	static	PIXELFORMATDESCRIPTOR pfd=				// pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
		1,											// Version Number
		PFD_DRAW_TO_WINDOW |						// Format Must Support Window
		PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,							// Must Support Double Buffering
		PFD_TYPE_RGBA,								// Request An RGBA Format
		bits,										// Select Our Color Depth
		0, 0, 0, 0, 0, 0,							// Color Bits Ignored
		0,											// No Alpha Buffer
		0,											// Shift Bit Ignored
		0,											// No Accumulation Buffer
		0, 0, 0, 0,									// Accumulation Bits Ignored
		16,											// 16Bit Z-Buffer (Depth Buffer)  
		0,											// No Stencil Buffer
		0,											// No Auxiliary Buffer
		PFD_MAIN_PLANE,								// Main Drawing Layer
		0,											// Reserved
		0, 0, 0										// Layer Masks Ignored
	};
	
	if (!(m_hDC=GetDC(m_hWnd)))							// Did We Get A Device Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Create A GL Device Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!(PixelFormat=ChoosePixelFormat(m_hDC,&pfd)))	// Did Windows Find A Matching Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Find A Suitable PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if(!SetPixelFormat(m_hDC,PixelFormat,&pfd))		// Are We Able To Set The Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Set The PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!(m_hRC=wglCreateContext(m_hDC)))				// Are We Able To Get A Rendering Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Create A GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if(!wglMakeCurrent(m_hDC,m_hRC))					// Try To Activate The Rendering Context
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Activate The GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	ShowWindow(m_hWnd,SW_SHOW);						// Show The Window
	SetForegroundWindow(m_hWnd);						// Slightly Higher Priority
	SetFocus(m_hWnd);									// Sets Keyboard Focus To The Window

	initfont();
	return TRUE;									// Success
}
