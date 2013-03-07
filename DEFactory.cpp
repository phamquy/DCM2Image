// DEFactory.cpp: implementation of the DEFactory class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DCMTKApp.h"
#include "DEFactory.h"
#include "Include.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

DEFactory::DEFactory()
{

}

DEFactory::~DEFactory()
{

}

//************************************
// Method:    ReadValue
// FullName:  Read value of data element 
// Access:    
// Returns:   return code: if VR is not compabible with integer value 
//			  it returns error code
// Qualifier: 
// Parameter: Input: DataElement Object
//			  Output: iteger value of this object
//************************************
INT DEFactory::ReadValue(CDataElement& in_objData, DWORD&  out_nValue)
{		
	PDWORD p = (PDWORD)in_objData.GetValuePointer();
	out_nValue = *p;
	return DCM_APP_NORMAL;
}

//************************************
// Method:    ReadValue
// FullName:  Read value of data element 
// Access:    
// Returns:   return code: if VR is not compabible with integer value 
//			  it returns error code
// Qualifier: 
// Parameter: Input: DataElement Object
//			  Output: string value of this object
//************************************
INT DEFactory::ReadValue(CDataElement& in_objData, CString&  out_nValue)
{		

	return DCM_APP_NORMAL;
}

INT DEFactory::ReadValue(CDataElement& in_objData, LONG&  out_nValue)
{		
	PLONG p = (PLONG)in_objData.GetValuePointer();
	out_nValue = *p;
	return DCM_APP_NORMAL;
}


INT DEFactory::ReadValue(CDataElement& in_objData, USHORT&  out_nValue)
{		
	PUSHORT p = (PUSHORT)in_objData.GetValuePointer();
	out_nValue = *p;
	return DCM_APP_NORMAL;
}

INT DEFactory::ReadValue(CDataElement& in_objData, SHORT&  out_nValue)
{		
	PSHORT p = (PSHORT)in_objData.GetValuePointer();
	out_nValue = *p;
	return DCM_APP_NORMAL;
}