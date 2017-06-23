#include "CDialog.h"
#include "CMDLDocument.h"

/////////////////////////////////////
// Static variablen	               //
/////////////////////////////////////
StudioModel* CDialog::m_mdl = NULL;
CSequenceDlg* CDialog::m_pSeqDlg = NULL;
HWND CDialog::m_hOwner = NULL;
HINSTANCE CDialog::m_hInstance = NULL;
CSlider* CDialog::m_pController = NULL;
long CDialog::show_bones = false;
long CDialog::show_hbox = true;
long CDialog::show_attach = false;

/////////////////////////////////////
// Constructors / Destructors      //
/////////////////////////////////////

CDialog::CDialog( HINSTANCE hInstance, HWND hWnd, StudioModel* mdl )
{
	this->m_hOwner		= hWnd;
	this->m_hInstance	= hInstance;
	this->m_mdl			= mdl;

}

CDialog::~CDialog( void )
{
}

/////////////////////////////////////
// Memberfuncties                  //
/////////////////////////////////////

BOOL CDialog::DlgProc( HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	HWND hwndList;
	int nItem, i;
	switch( uMsg )
	{
	case WM_INITDIALOG:
		init(hDlg);
		m_pSeqDlg = new CSequenceDlg(m_hInstance, hDlg, m_mdl);
		break;

	case WM_COMMAND:
		switch( LOWORD(wParam) )
		{
  		case IDOK:
			EndDialog( hDlg, IDOK );
			break;
  		case IDCANCEL:
			EndDialog( hDlg, IDCANCEL );
			break;
		case IDC_BUTTON_SEQ:
			m_pSeqDlg->show();
			break;

		case IDC_BONES:
			show_bones = SendMessage( GetDlgItem(hDlg, IDC_BONES), BM_GETCHECK, 0, 0 );
			break;
		case IDC_ATTACH:
			show_attach = SendMessage( GetDlgItem(hDlg, IDC_ATTACH), BM_GETCHECK, 0, 0 );
			break;
		case IDC_HITBOXES:
			show_hbox = SendMessage( GetDlgItem(hDlg, IDC_HITBOXES), BM_GETCHECK, 0, 0 );
			break;

		case IDC_CONTROLLERS:
			switch (HIWORD(wParam))
			{
			case LBN_SELCHANGE:
				hwndList = GetDlgItem(hDlg, IDC_CONTROLLERS); 
				nItem = SendMessage(hwndList, LB_GETCURSEL , 0, 0); 
				i = SendMessage(hwndList, LB_GETITEMDATA, nItem, 0);
				studiohdr_t *hdr = m_mdl->getStudioHeader ();	
				if (hdr)
				{
					mstudiobonecontroller_t *pbonecontrollers = (mstudiobonecontroller_t *) ((byte *) hdr + hdr->bonecontrollerindex);
					
					if ( i == 4 )
					{
						m_mdl->SetMouth( 0.0f );
					}
					else
					{
						m_mdl->SetController( i, 0.0f );
					}
					m_pController->init((int) pbonecontrollers[i].start, (int) pbonecontrollers[i].end);
					m_pController->setSel(0);
				}
				break; 
			}
			break;
		}
		break;

		case WM_HSCROLL:
			if ( (HWND)lParam == m_pController->getHandle() )
			{
				studiohdr_t *hdr = m_mdl->getStudioHeader ();
				if (hdr)
				{
					mstudiobonecontroller_t *pbonecontrollers = (mstudiobonecontroller_t *) ((byte *) hdr + hdr->bonecontrollerindex);
						
					hwndList = GetDlgItem(hDlg, IDC_SEQUENCE); 
					nItem = SendMessage(hwndList, LB_GETCURSEL , 0, 0); 
					i = SendMessage(hwndList, LB_GETITEMDATA, nItem, 0);

					if ( i == 4 )
						m_mdl->SetMouth ( m_pController->getSel() );
					else
						m_mdl->SetController ( i, m_pController->getSel() );
				}	 
			}
			break;
	}
	return FALSE;
}

void CDialog::show()
{
	DialogBox( m_hInstance, MAKEINTRESOURCE( IDD_DIALOG ), m_hOwner, (DLGPROC)DlgProc );
}

void CDialog::init(HWND hWnd)
{
	char str[64];

	m_pController = new CSlider(m_hInstance, hWnd, 15, 120, 110, 20, 0);
	m_pController->create( NULL, TBS_ENABLESELRANGE );
//	m_pController->init(0, 100);
	m_pController->setSel(m_mdl->GetSpeed()*10);


	studiohdr_t *hdr = m_mdl->getStudioHeader();
	if (hdr)
	{
		mstudiobonecontroller_t *pbonecontrollers = (mstudiobonecontroller_t *) ((byte *) hdr + hdr->bonecontrollerindex);
		for (int i = 0; i < hdr->numbonecontrollers; i++)
		{
			if (pbonecontrollers[i].index == 4)
				sprintf (str, "Mouth %d", i);
			else
				sprintf (str, "Controller %d", i);
			int res = SendMessage(GetDlgItem(hWnd, IDC_CONTROLLERS), LB_ADDSTRING, 0, (LPARAM)str);
			SendMessage(GetDlgItem(hWnd, IDC_CONTROLLERS), LB_SETITEMDATA, res, (LPARAM) pbonecontrollers[i].index); 
		}
	}
	SendMessage( GetDlgItem(hWnd, IDC_BONES), BM_SETCHECK, ( WPARAM ) show_bones, 0 );
	SendMessage( GetDlgItem(hWnd, IDC_HITBOXES), BM_SETCHECK, ( WPARAM ) show_hbox, 0 );
	SendMessage( GetDlgItem(hWnd, IDC_ATTACH), BM_SETCHECK, ( WPARAM ) show_attach, 0 );
}