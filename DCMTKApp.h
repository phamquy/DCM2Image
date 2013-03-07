// DCMTKApp.h : main header file for the DCMTKAPP application
//

#if !defined(AFX_DCMTKAPP_H__79AEE6F5_D8C4_47AB_B763_D5318707492B__INCLUDED_)
#define AFX_DCMTKAPP_H__79AEE6F5_D8C4_47AB_B763_D5318707492B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CDCMTKAppApp:
// See DCMTKApp.cpp for the implementation of this class
//

class CDCMTKAppApp : public CWinApp
{
public:
	CDCMTKAppApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDCMTKAppApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CDCMTKAppApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	ULONG_PTR m_gdiplusToken;

};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DCMTKAPP_H__79AEE6F5_D8C4_47AB_B763_D5318707492B__INCLUDED_)
