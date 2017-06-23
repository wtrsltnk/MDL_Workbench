#ifndef CBASE3DDOCUMENT_H
#define CBASE3DDOCUMENT_H

#include <windows.h>

class __declspec(dllexport) CBase3DDocument
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