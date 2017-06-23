#include "CMainFrame.h"

/////////////////////////////////////
// Constructors / Destructors      //
/////////////////////////////////////
CMainFrame::CMainFrame()
{
	this->m_dwCreationFlags  = 0L;
	this->m_dwWindowStyle	 = WS_OVERLAPPEDWINDOW;
	this->m_dwExWindowStyle	 = WS_EX_WINDOWEDGE;
	this->m_dwCreationFlags  = SW_SHOW;
	this->m_PosX			 = CW_USEDEFAULT;	
	this->m_PosY			 = CW_USEDEFAULT;	
	this->m_dwCreationWidth  = CW_USEDEFAULT;
	this->m_dwCreationHeight = CW_USEDEFAULT;
	this->m_hbrWindowColor	 = (HBRUSH)(COLOR_WINDOW);
	this->m_hIcon			 = LoadIcon( m_hInstance, MAKEINTRESOURCE(IDI_WORKSHOP) );
	this->m_strWindowTitle	 = "Model Workshop";
	this->m_hMenu			 = LoadMenu( m_hInstance, MAKEINTRESOURCE(IDR_MENU) );

	m_pMDLModel = NULL;
	m_pSMDModel = NULL;
}


CMainFrame::~CMainFrame()
{
}

/////////////////////////////////////
// Memberfuncties                  //
/////////////////////////////////////

LRESULT CMainFrame::MsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	char* pDlgResult;

	switch (uMsg)
	{
	case WM_CREATE:
		m_pGlWindow = new COpenGl(m_hInstance, m_hWnd, 0, 0, 100, 100, 0);
		m_pGlWindow->CreateGLWindow("haha", 0, 0, 10, 10, 16);

		m_pDlgs = new CCommonDialogs(m_hInstance, m_hWnd);

		SetTimer(hWnd, 1, 30, NULL);
		break;

	case WM_SIZE:
		m_pGlWindow->resize(0, 0, LOWORD(lParam), HIWORD(lParam));
		break;

	case WM_PAINT:
		m_pGlWindow->drawstart();
		{
			if ( m_pMDLModel )
				m_pMDLModel->DrawGL();
			if ( m_pSMDModel )
				m_pSMDModel->DrawGL();
		}
		m_pGlWindow->drawend();
		ValidateRect(hWnd, NULL);
		break;

	case WM_TIMER:
		{
			if ( m_pMDLModel )
			{
				m_pMDLModel->TriggerAnimation();
				InvalidateRect(hWnd, NULL, true);
			}
			if ( m_pSMDModel )
			{
				m_pSMDModel->TriggerAnimation();
				InvalidateRect(hWnd, NULL, true);
			}
		}
		break;

	case WM_COMMAND:
		switch (wParam)
		{
		case ID_OPTIONS_MODELOPTIONS:
			{
				if ( m_pMDLModel )
					m_pMDLModel->ShowDialog();
				if ( m_pSMDModel )
					m_pSMDModel->ShowDialog();
			}
			break;

		case ID_BESTAND_OPEN_MDL:
			pDlgResult = m_pDlgs->open( "Open Half-Life model file...", "MDL Files\0*.mdl\0", "mdl" );
			
			if ( pDlgResult  )
			{
				RECT rc;
				GetClientRect(hWnd, &rc);

				m_pGlWindow->KillGLWindow();
				m_pGlWindow->CreateGLWindow("haha", 0,0, rc.right, rc.bottom, 16);

				ClearModels();
				m_pMDLModel = new CMDLDocument(m_hWnd);
				m_pMDLModel->Initialize(pDlgResult);
			}
			break;

		case ID_BESTAND_OPEN_SMD:
			pDlgResult = m_pDlgs->open( "Open Half-Life mesh file...", "SMD Files\0*.smd\0", "smd" );

			if ( pDlgResult  )
			{
				RECT rc;
				GetClientRect(hWnd, &rc);

				m_pGlWindow->KillGLWindow();
				m_pGlWindow->CreateGLWindow("haha", 0,0, rc.right, rc.bottom, 16);

				ClearModels();
				m_pSMDModel = new CSMDDocument();
				m_pSMDModel->Initialize(pDlgResult);
			}
			break;

		case ID_BESTAND_CLOSE:
			ClearModels();
			break;

		case ID_BESTAND_EXIT:
			delete m_pGlWindow;
			delete m_pDlgs;

			ClearModels();
			PostQuitMessage(0);
			break;
		}
		break;
	}
	return CWin::MsgProc(hWnd, uMsg, wParam, lParam);
}


void CMainFrame::ClearModels()
{
	if ( m_pMDLModel )
	{
		m_pMDLModel->Kill();
		delete m_pMDLModel;
		m_pMDLModel = NULL;
	}
	if ( m_pSMDModel )
	{
		m_pSMDModel->Kill();
		delete m_pSMDModel;
		m_pSMDModel = NULL;
	}
}