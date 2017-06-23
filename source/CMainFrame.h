#ifndef CMAINFRAME_H
#define CMAINFRAME_H

#include "CWin.h"
#include "..\resource\resource.h"
#include "source/CSMDDocument.h"
#include "source/CMDLDocument.h"
#include "COpenGl.h"

#include "CCommonDialogs.h"

class CMainFrame : public CWin
{
protected:
	CMDLDocument* m_pMDLModel;
	CSMDDocument* m_pSMDModel;
	COpenGl* m_pGlWindow;
	CCommonDialogs* m_pDlgs;

	void ClearModels();
public:
	CMainFrame();
	~CMainFrame();

	LRESULT MsgProc(HWND, UINT, WPARAM, LPARAM);
};

#endif
