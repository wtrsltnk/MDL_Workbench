#include "CSMDDocument.h"

//////////////////////////////////////////////////////////////////////////////////////////
// Constructor
// Destructor 
//////////////////////////////////////////////////////////////////////////////////////////
CSMDDocument::CSMDDocument()
{
}

CSMDDocument::~CSMDDocument()
{
}

//////////////////////////////////////////////////////////////////////////////////////////
// Purpose : Create a new Model Document
// Input   : 
// Output  : new object of class CBase3DDocument
//////////////////////////////////////////////////////////////////////////////////////////
bool CSMDDocument::Initialize(char* path)
{
	m_pSMD = new CDataSMD();
	return m_pSMD->Load(path);
}

//////////////////////////////////////////////////////////////////////////////////////////
// Purpose : Create a new Model Document
// Input   : 
// Output  : new object of class CBase3DDocument
//////////////////////////////////////////////////////////////////////////////////////////
bool CSMDDocument::Kill()
{
	return m_pSMD->Unload();
}

//////////////////////////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////////////////////////
void CSMDDocument::DrawGL()
{
	m_pSMD->Render(NULL);
}

//////////////////////////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////////////////////////
void CSMDDocument::ShowDialog()
{
}

//////////////////////////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////////////////////////
void CSMDDocument::TriggerAnimation()
{
}