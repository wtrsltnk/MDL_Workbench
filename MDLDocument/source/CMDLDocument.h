#ifndef CMDLDOCUMENT_H
#define CMDLDOCUMENT_H

#ifdef MDLDIALOG_EXPORTS
  #define MDLDLL_DECL __declspec(dllexport)
#else
  #define MDLDLL_DECL __declspec(dllimport)
#endif

#include "CBase3DDocument.h"

#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glaux.h>

#include "..\hlsdk\mathlib.h"
#include "..\hlsdk\studio.h"
#include "..\hlsdk\studio_render.h"

#include "CDialog.h"

class __declspec(dllexport) CMDLDocument : public CBase3DDocument
{
protected:
	StudioModel* m_pModel;
	CDialog* m_pDialog;
	HWND m_hParent;

public:
	CMDLDocument(HWND hWnd);
	~CMDLDocument();
	
	bool Initialize(char* path);
	bool Kill();
	void DrawGL();
	void ShowDialog();
	void TriggerAnimation();
};
#endif
