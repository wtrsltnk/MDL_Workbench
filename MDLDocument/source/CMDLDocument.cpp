#include "CMDLDocument.h"

float		g_lambert = 1.5;
vec3_t g_vright = { 100, 100, 50 };		// needs to be set to viewer's 
										// right in order for chrome to work

//////////////////////////////////////////////////////////////////////////////////////////
// Constructor
// Destructor 
//////////////////////////////////////////////////////////////////////////////////////////
CMDLDocument::CMDLDocument( HWND hWnd )
{
	m_hParent = hWnd;
	m_pModel = new StudioModel();
	m_pDialog = new CDialog(GetModuleHandle("MDLDialog.dll"), hWnd, m_pModel);
}

CMDLDocument::~CMDLDocument()
{
}

//////////////////////////////////////////////////////////////////////////////////////////
// Purpose : Create a new Model Document
// Input   : 
// Output  : new object of class CBase3DDocument
//////////////////////////////////////////////////////////////////////////////////////////
bool CMDLDocument::Initialize(char* path)
{
	try
	{
		m_pModel->Init(path);
		m_pModel->SetSelHitbox( -1 );
		m_pModel->SetSelBone( -1 );
		m_pModel->SetSequence( 0 );
		m_pModel->SetController( 0, 0.0 );
		m_pModel->SetController( 1, 0.0 );
		m_pModel->SetController( 2, 0.0 );
		m_pModel->SetController( 3, 0.0 );
		m_pModel->SetMouth( 0 );
	}
	catch( char* err )
	{
		MessageBox(NULL, err, "ERROR :", MB_OK | MB_ICONEXCLAMATION);
		return false;
	}
	return true;
}

//////////////////////////////////////////////////////////////////////////////////////////
// Purpose : Create a new Model Document
// Input   : 
// Output  : new object of class CBase3DDocument
//////////////////////////////////////////////////////////////////////////////////////////
bool CMDLDocument::Kill()
{
	m_pModel->FreeModel();
	return true;
}

//////////////////////////////////////////////////////////////////////////////////////////
// Purpose : Draw the Scene
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////////////////////////
void CMDLDocument::DrawGL()
{
	m_pModel->DrawModel();
	glDisable(GL_LIGHTING);
	if ( m_pDialog->show_bones )
		m_pModel->DrawBones();
	if ( m_pDialog->show_attach )
		m_pModel->DrawAtachments();
	if ( m_pDialog->show_hbox )
		m_pModel->DrawHitboxes();
}

//////////////////////////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////////////////////////
void CMDLDocument::ShowDialog()
{
	m_pDialog->show();
}

//////////////////////////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////////////////////////
void CMDLDocument::TriggerAnimation()
{	
	static float prev;
	float curr;

	curr = GetTickCount( ) / 1000.0f;
	m_pModel->AdvanceFrame( (curr - prev)*m_pModel->GetSpeed() );
	prev = curr;
}
