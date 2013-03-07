// DataElement.h: interface for the CDataElement class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DATAELEMENT_H__FD88F9A2_A646_4660_A95C_8EC2E19D2E7C__INCLUDED_)
#define AFX_DATAELEMENT_H__FD88F9A2_A646_4660_A95C_8EC2E19D2E7C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#define DCM_VR_NONE	"  "


class CDataElement  
{
public:
	BOOL IsImpicitVR();
	BOOL IsSpecialVR();
	// TODO: read data from buffer to this object
	INT ReadData(char const* in_pDataBuffer);
	INT ReadLength(const char* in_pBuff);

	CDataElement();
	CDataElement(
		WORD	in_nGroup, 
		WORD	in_nElement, 
		CString	in_sVR
	);
	virtual ~CDataElement();


	// TODO: get group ID
	WORD GetGroupID()
	{
		return m_nGroup;
	};

	// TODO: get VR string
	CString GetVR()
	{
		//CString sTemp(m_szVR);
		return m_szVR;
	};

	// TODO: to get element id
	WORD GetElementID()
	{
		return m_nElement;
	};

	DWORD GetValueLength()
	{
		return m_nDataLength;
	};

	void* GetValuePointer()
	{
		return m_pValue;
	};

	void SetGroupID(WORD in_nGroup)
	{
		m_nGroup = in_nGroup;
	};


	void SetElementID(WORD in_nElement)
	{
		m_nElement = in_nElement;
	};


	void SetTagID(WORD in_nGroup, WORD in_nElement)
	{
		SetGroupID(in_nGroup);
		SetElementID(in_nElement);
	}

	void SetVR(CString in_sString)
	{		
		ASSERT(in_sString.GetLength() >= 2);
		m_szVR = in_sString;
	}

	void SetValueLength(DWORD in_nLen)
	{
		m_nDataLength = in_nLen;
	};

	INT DeleteData();
private:

	//Tag information
	WORD	m_nGroup;	//Group ID
	WORD	m_nElement;	//Data Element ID

	//VR field
	CString	m_szVR;

	//Data field length
	DWORD	m_nDataLength; 

	void*	m_pValue;
protected:

	void InitInstance(WORD in_nGroup = 0, WORD in_nElement = 0, CString in_sVR = DCM_VR_NONE);
};

#endif // !defined(AFX_DATAELEMENT_H__FD88F9A2_A646_4660_A95C_8EC2E19D2E7C__INCLUDED_)
