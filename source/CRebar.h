#ifndef CREBAR_H
#define CREBAR_H

#include <windows.h>
#include <commctrl.h>
#include <string>
#include "CControl.h"
using namespace std;

class CRebar : public CControl
{
private:
public:
	CRebar( HINSTANCE, HWND, int, int, int, int, int );
	CRebar( HINSTANCE, HWND );
	void create( void );
	void create( DWORD );
	void create( DWORD, DWORD );
};
#endif
