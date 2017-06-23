#ifndef CSMDDOCUMENT_H
#define CSMDDOCUMENT_H

#ifdef SMDDOCUMENT_EXPORTS
  #define SMDDLL_DECL __declspec(dllexport)
#else
  #define SMDDLL_DECL __declspec(dllimport)
#endif

#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glaux.h>

#include "CBase3DDocument.h"
#include "CDataSMD.h"

class __declspec(dllexport) CSMDDocument : public CBase3DDocument
{
protected:
	CDataSMD*	m_pSMD;
public:
	CSMDDocument();
	~CSMDDocument();
	
	bool Initialize(char* path);
	bool Kill();
	void DrawGL();
	void ShowDialog();
	void TriggerAnimation();
};
#endif