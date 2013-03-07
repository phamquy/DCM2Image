// DEFactory.h: interface for the DEFactory class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DEFACTORY_H__3BAE98A3_C446_47C6_923D_D382CDE2EF14__INCLUDED_)
#define AFX_DEFACTORY_H__3BAE98A3_C446_47C6_923D_D382CDE2EF14__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DataElement.h"

class DEFactory  
{
public:
 	static INT ReadValue(CDataElement& in_objData, DWORD&  out_nValue);
	static INT ReadValue(CDataElement& in_objData, CString&  out_nValue);
	static INT ReadValue(CDataElement& in_objData, LONG&  out_nValue);
	static INT ReadValue(CDataElement& in_objData, USHORT&  out_nValue);
	static INT ReadValue(CDataElement& in_objData, SHORT&  out_nValue);
	DEFactory();
	virtual ~DEFactory();

};

#endif // !defined(AFX_DEFACTORY_H__3BAE98A3_C446_47C6_923D_D382CDE2EF14__INCLUDED_)
