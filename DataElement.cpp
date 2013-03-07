// DataElement.cpp: implementation of the CDataElement class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DCMTKApp.h"
#include "DataElement.h"
#include "Include.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDataElement::CDataElement()
{
	InitInstance();
}

CDataElement::CDataElement(	WORD in_nGroup, WORD in_nElement, CString in_sVR)
{
	InitInstance(in_nGroup, in_nElement, in_sVR);
}

CDataElement::~CDataElement()
{

}

void CDataElement::InitInstance(WORD in_nGroup, WORD in_nElement, CString in_sVR)
{
	SetGroupID(in_nGroup);
	SetElementID(in_nElement);
	SetVR(in_sVR);
	m_pValue = NULL;
}

//************************************
// Method:    ReadData
// FullName:  Read data to this data element depend on other setting
// Access:    
// Returns:   
// Qualifier: 
// Parameter: in_pDataBuffer: pointer to buffer data of value field
//************************************
INT CDataElement::ReadData(char const* in_pDataBuffer)
{
	if(m_pValue != NULL)
	{
		DeleteData();
	}
	
	if(m_nDataLength != 0)
		m_pValue = new char[m_nDataLength];
	else
		return DCM_APP_NORMAL;

	if(m_pValue == NULL) 
		return DCM_APP_MEMERR;

	memcpy(m_pValue, in_pDataBuffer, m_nDataLength);

	return DCM_APP_NORMAL;
}

//************************************
// Method:    IsAvailable
// FullName:  Return true if all field is valid, False if not
// Access:    
// Returns:   
// Qualifier: this function check validation of VR and value field
// Parameter: 
//************************************
//DEL BOOL CDataElement::IsAvailable()
//DEL {
//DEL 	//not yet implement
//DEL 	return TRUE;
//DEL }

//************************************
// Method:    DeleteData
// FullName:  Delete data from value field of this object
// Access:    
// Returns:   
// Qualifier: 
// Parameter: 
//************************************
INT CDataElement::DeleteData()
{
	delete [] m_pValue;
	m_pValue = NULL;
	return DCM_APP_NORMAL;
}

//************************************
// Method:    ReadLength
// FullName:  Read value length field of this data element
// Access:    
// Returns:   err code 
// Qualifier: 
// Parameter: 
//************************************
INT CDataElement::ReadLength(const char *in_pBuff)
{
	if(IsSpecialVR() || IsImpicitVR()) //data length field is 4byte  field
	{
		PDWORD p4BytesLength = (PDWORD) in_pBuff;
		m_nDataLength = *p4BytesLength;
	}	
	else	//data length field is 2byte  field
	{
		PWORD p2BytesLength = (PWORD) in_pBuff;
		m_nDataLength = *p2BytesLength;
	}	
	return DCM_APP_NORMAL;
}

//************************************
// Method:    IsSpecialVR
// FullName:  Return true if this Data Element is special element
// Access:    
// Returns:   
// Qualifier: 
// Parameter: 
//************************************
BOOL CDataElement::IsSpecialVR()
{
	CString str(m_szVR);

	if(	(str == DCM_VR_OB)||
		(str == DCM_VR_OW)||
		(str == DCM_VR_OF)||
		(str == DCM_VR_SQ)||
		(str == DCM_VR_UT)||
		(str == DCM_VR_UN))
	{
		return TRUE;
	}
	else 
	{
		return FALSE;
	}
}


//************************************
// Method:    IsImpicitVR
// FullName:  return true if this data element has implicit VR
// Access:    
// Returns:   
// Qualifier: 
// Parameter: 
//************************************
BOOL CDataElement::IsImpicitVR()
{
	CString str(m_szVR);
	if(str == DCM_VR_NONE)	
	{
		return TRUE;
	}
	else
	{
		return FALSE;			
	}
}