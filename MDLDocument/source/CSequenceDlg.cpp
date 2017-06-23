#include "CSequenceDlg.h"
#include "CMDLDocument.h"

/////////////////////////////////////
// Static variablen	               //
/////////////////////////////////////
StudioModel* CSequenceDlg::m_mdl = NULL;
CSlider* CSequenceDlg::m_pSpeed = NULL;

/////////////////////////////////////
// Constructors / Destructors      //
/////////////////////////////////////

CSequenceDlg::CSequenceDlg( HINSTANCE hInstance, HWND hWnd, StudioModel* mdl )
{
	this->m_hOwner		= hWnd;
	this->m_hInstance	= hInstance;
	this->m_mdl			= mdl;

	m_hWnd = CreateDialog( m_hInstance, MAKEINTRESOURCE( IDD_SEQUENCE ), m_hOwner, (DLGPROC)DlgProc );

	m_pSpeed = new CSlider(m_hInstance, m_hWnd, 5, 250, 180, 20, 0);
	m_pSpeed->create( NULL, TBS_ENABLESELRANGE );
	m_pSpeed->init(0, 100);
	m_pSpeed->setSel(m_mdl->GetSpeed()*10);
}

CSequenceDlg::~CSequenceDlg( void )
{
	DestroyWindow( m_hWnd );
}

/////////////////////////////////////
// Memberfuncties                  //
/////////////////////////////////////

BOOL CSequenceDlg::DlgProc( HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	HWND hwndList;
	int nItem, i;
	switch( uMsg )
	{
	case WM_INITDIALOG:
		break;

	case WM_SIZE:
		int nWidth, nHeight;
		nWidth = LOWORD(lParam);
		nHeight = HIWORD(lParam);
		break;

	case WM_COMMAND:
		switch( LOWORD(wParam) )
		{
		case IDC_SEQUENCE:
			switch (HIWORD(wParam))
			{
			case LBN_SELCHANGE:
				hwndList = GetDlgItem(hDlg, IDC_SEQUENCE); 
				nItem = SendMessage(hwndList, LB_GETCURSEL , 0, 0); 
				i = SendMessage(hwndList, LB_GETITEMDATA, nItem, 0);

				m_mdl->SetSequence(i);
			   break; 
			}
			break;

  		case IDOK:
			EndDialog( hDlg, IDOK );
			break;
		}
		break;

		
	case WM_HSCROLL:
		if ( (HWND)lParam == m_pSpeed->getHandle() )
		{
			m_mdl->SetSpeed((float)m_pSpeed->getSel() / 10);
		}
		break;
	}
	return FALSE;
}

void CSequenceDlg::show()
{
	SendMessage(GetDlgItem(m_hWnd, IDC_SEQUENCE), LB_RESETCONTENT  , 0, 0);
	studiohdr_t *hdr = m_mdl->getStudioHeader();
	if ( hdr )
	{
		mstudioseqdesc_t *pseqdescs = (mstudioseqdesc_t *) ((byte *) hdr + hdr->seqindex);
		for (int i = 0; i < hdr->numseq; i++)
		{
			int res = SendMessage(GetDlgItem(m_hWnd, IDC_SEQUENCE), LB_ADDSTRING, 0, (LPARAM) pseqdescs[i].label); 
			SendMessage(GetDlgItem(m_hWnd, IDC_SEQUENCE), LB_SETITEMDATA, res, (LPARAM) i); 
		}
	}
	ShowWindow( m_hWnd, SW_SHOWNORMAL );
}

bool CSequenceDlg::isDlg( void )
{
	if ( IsWindowVisible( m_hWnd ) == 1 )
		return true;
	return false;
}
