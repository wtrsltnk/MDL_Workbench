#ifndef CBASE3DDOCUMENT_H
#define CBASE3DDOCUMENT_H

#ifndef MYDLL_DECL
#ifdef SMDDIALOG_EXPORTS
  #define MYDLL_DECL __declspec(dllexport)
#else
  #define MYDLL_DECL __declspec(dllimport)
#endif
#endif

#include <windows.h>

class MYDLL_DECL CBase3DDocument
{
protected:
public:
	CBase3DDocument();
	~CBase3DDocument();
	virtual bool Initialize(char* path) = 0;
	virtual bool Kill() = 0;
	virtual void DrawGL() = 0;
	virtual void ShowDialog() = 0;
	virtual void TriggerAnimation() = 0;
};
#endif