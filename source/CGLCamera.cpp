#include "CGLCamera.h"

CGLCamera::CGLCamera()
{
	// Standaard Translation opgeven
	m_fPanx = 0.0f;
	m_fPany = 0.0f;
	m_fPanz = -2.0f;

	// Standaard Rotation opgeven
	m_fRotx = 0.0f;
	m_fRoty = 0.0f;
	m_fRotz = 0.0f;

	// Type view (2D of 3D)
	m_Viewtype = ThreeD;
}

CGLCamera::~CGLCamera()
{
}

void CGLCamera::Init( int nWidth, int nHeight )
{
	// Ratio van het scherm uitrekenen
	float ratio = (float)nHeight / (float)nWidth;

	glMatrixMode(GL_PROJECTION);					// PROJECTION matrix selecteren
	glLoadIdentity();								// Matrix resetten

	// Wat is het type VIEW?
	switch ( this->m_Viewtype )
	{
	case ThreeD:
		// Perspectief (3D)
		gluPerspective( 45.0f, (float)nWidth/(float)nHeight, 0.01f, 300.0f );
		break;

	case TwoD:
		// 2D
		glOrtho( -1, 1, -ratio, ratio, -300.0f, 300.0f );
		break;
	}
}

void CGLCamera::Update()
{
	glTranslatef( m_fPanx, m_fPany, m_fPanz );				// Voer de translatie uit
	glRotatef( m_fRotx,1,0,0 );								// Voer de rotatie uit op X-as
	glRotatef( m_fRoty,0,1,0 );								// Voer de rotatie uit op Y-as					
	glRotatef( m_fRotz,0,0,1 );								// Voer de rotatie uit op Z-as
	glScalef( 0.5f, 0.5f, 0.5f );							// Voer de Scaling uit
}

void CGLCamera::Rotate( float fRotx, float fRoty, float fRotz )
{
	// Voer de nieuwe rotatie waarden in
	m_fRotx += fRotx;
	m_fRoty += fRoty;
	m_fRotz += fRotz;

	// Controleer of ze niet groter dan 360, of kleiner dan 0 zijn
	if ( m_fRotx > 360.0f )
		m_fRotx = 0;
	if ( m_fRoty > 360.0f )
		m_fRoty = 0;
	if ( m_fRotz > 360.0f )
		m_fRotz = 0;
}
	
void CGLCamera::Translate( float fPanx, float fPany, float fPanz )
{
	// Voer de nieuwe translatie waarden in
	m_fPanx += fPanx;
	m_fPany += fPany;
	m_fPanz += fPanz;
}