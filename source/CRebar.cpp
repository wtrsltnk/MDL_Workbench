#include "CRebar.h"

/////////////////////////////////////
// Constructors / Destructors      //
/////////////////////////////////////
CRebar::CRebar( HINSTANCE hInstance, 
					 HWND hParent,
					 int nX, int nY , 
					 int nWidth ,int nHeight, int id ) : CControl( hInstance, 
					 hParent,
					 nX, nY , 
					 nWidth ,nHeight, id )
{
}

CRebar::CRebar( HINSTANCE hInstance, HWND hParent ) : CControl( hInstance, hParent )
{
}

/////////////////////////////////////
// Memberfuncties                  //
/////////////////////////////////////

void CRebar::create( void )
{   
   REBARINFO     rbi;
   REBARBANDINFO rbBand;
   RECT          rc;
   HWND   hwndCB, hwndTB, hwndRB;
   DWORD  dwBtnSize;
   INITCOMMONCONTROLSEX icex;

   icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
   icex.dwICC   = ICC_COOL_CLASSES|ICC_BAR_CLASSES;


	m_hWnd = CreateWindowEx( WS_EX_WINDOWEDGE,
		 "REBARCLASSNAME", 
		 "Caption", 
		 WS_CHILD | WS_VISIBLE, 
		 m_nX, 
		 m_nY, 
		 m_nWidth, 
		 m_nHeight, 
		 m_hParent, 
		 (HMENU)control_id, 
		 NULL, 
		 NULL );

	// Initialize and send the REBARINFO structure.
   rbi.cbSize = sizeof(REBARINFO);  // Required when using this struct.
   rbi.fMask  = 0;
   rbi.himl   = (HIMAGELIST)NULL;
   if(!SendMessage(m_hWnd, RB_SETBARINFO, 0, (LPARAM)&rbi))
      return;

   // Initialize structure members that both bands will share.
   rbBand.cbSize = sizeof(REBARBANDINFO);  // Required
   rbBand.fMask  = RBBIM_COLORS | RBBIM_TEXT | RBBIM_BACKGROUND | 
                   RBBIM_STYLE | RBBIM_CHILD  | RBBIM_CHILDSIZE | 
                   RBBIM_SIZE;
   rbBand.fStyle = RBBS_CHILDEDGE | RBBS_FIXEDBMP;
   rbBand.hbmBack= LoadBitmap(m_hInstance, MAKEINTRESOURCE(NULL));   
   
   // Create the combo box control to be added.
   hwndCB = CreateWindowEx( WS_EX_WINDOWEDGE,
		 "COMBOBOX", 
		 "Caption", 
		 WS_CHILD | WS_VISIBLE, 
		 0, 
		 0, 
		 100, 
		 10, 
		 m_hWnd, 
		 (HMENU)0, 
		 NULL, 
		 NULL );
   
   // Set values unique to the band with the combo box.
   GetWindowRect(hwndCB, &rc);
   rbBand.lpText     = "Combo Box";
   rbBand.hwndChild  = hwndCB;
   rbBand.cxMinChild = 0;
   rbBand.cyMinChild = rc.bottom - rc.top;
   rbBand.cx         = 200;

   // Add the band that has the combo box.
   SendMessage(m_hWnd, RB_INSERTBAND, (WPARAM)-1, (LPARAM)&rbBand);


}

void CRebar::create( DWORD ex_style )
{
	m_hWnd = CreateWindowEx( ex_style,
		 "REBARCLASSNAME", 
		 "Caption", 
		 WS_CHILD | WS_VISIBLE, 
		 m_nX, 
		 m_nY, 
		 m_nWidth, 
		 m_nHeight, 
		 m_hParent, 
		 (HMENU)control_id, 
		 NULL, 
		 NULL );
}

void CRebar::create( DWORD ex_style, DWORD styles )
{
	m_hWnd = CreateWindowEx( ex_style,
		 "REBARCLASSNAME", 
		 "Caption", 
		 WS_CHILD | WS_VISIBLE |
		 SS_NOPREFIX | styles,
		 m_nX, 
		 m_nY, 
		 m_nWidth, 
		 m_nHeight, 
		 m_hParent, 
		 (HMENU)control_id, 
		 NULL, 
		 NULL );
}
