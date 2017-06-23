#ifndef CNEWDLG_H
#define CNEWDLG_H

#include <windows.h>
#include <string>
using namespace std;

#include "resource.h"
#include "CSequenceDlg.h"

class StudioModel;
class CDialog
{
private:
	static HWND				m_hOwner;
	static HINSTANCE			m_hInstance;

	static StudioModel*	m_mdl;

	static CSequenceDlg* m_pSeqDlg;
	static void init(HWND hWnd);
	static CSlider* m_pController;
public:
	static long show_bones;
	static long show_hbox;
	static long show_attach;

	CDialog( HINSTANCE, HWND, StudioModel* mdl );
	~CDialog( void );
	static BOOL DlgProc( HWND, UINT, WPARAM, LPARAM );

	void show();
};

#endif
