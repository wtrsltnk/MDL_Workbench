#ifndef CGLCAMERA_H
#define CGLCAMERA_H

#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glaux.h>

class CGLCamera
{
private:
	float	m_fPanx, m_fPany, m_fPanz;
	float	m_fRotx, m_fRoty, m_fRotz;
public:
	enum ViewType
	{
		ThreeD,
		TwoD
	} m_Viewtype;
protected:
public:
	CGLCamera();
	~CGLCamera();

	void Init( int nWidth, int nHeight );
	void Update();

	void Rotate( float fRotx, float fRoty, float fRotz );
	void Translate( float fPanx, float fPany, float fPanz );

	float GetRotX() { return m_fRotx; };
	float GetRotY() { return m_fRoty; };
	float GetRotZ() { return m_fRotz; };
};
#endif