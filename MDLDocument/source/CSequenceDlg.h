#ifndef CSQUENCEDLG_H
#define CSQUENCEDLG_H

#include <windows.h>
#include <string>
using namespace std;

#include "resource.h"
#include "CSlider.h"

class StudioModel;
class CSequenceDlg
{
private:
	HWND				m_hOwner;
	HWND				m_hWnd;
	HINSTANCE			m_hInstance;

	static StudioModel*	m_mdl;
	static CSlider* m_pSpeed;
public:
	CSequenceDlg( HINSTANCE, HWND, StudioModel* mdl );
	~CSequenceDlg( void );
	static BOOL DlgProc( HWND, UINT, WPARAM, LPARAM );

	void show();
	bool isDlg( void );
};

#endif
