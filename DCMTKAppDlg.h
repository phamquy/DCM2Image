// DCMTKAppDlg.h : header file
//

#if !defined(AFX_DCMTKAPPDLG_H__60B22CE6_3EE0_4560_AAB7_F21ED0FBB767__INCLUDED_)
#define AFX_DCMTKAPPDLG_H__60B22CE6_3EE0_4560_AAB7_F21ED0FBB767__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "DataElement.h"
#include <gdiplus.h>
using namespace Gdiplus;

/////////////////////////////////////////////////////////////////////////////
// CDCMTKAppDlg dialog

class CDCMTKAppDlg : public CDialog
{
// Construction
public:
	CDCMTKAppDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CDCMTKAppDlg)
	enum { IDD = IDD_DCMTKAPP_DIALOG };
	CButton	m_cmdConvert;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDCMTKAppDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CDCMTKAppDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnOpen();
	afx_msg void OnConvert();
	afx_msg void OnClose();
	afx_msg void OnHelpAbout();
	afx_msg void OnFileClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	void ResetData();
	void DrawFrame();
	void WriteOutToFile();
	void SetBMPPixelAt(INT xPos, INT yPos, LPVOID pBuffer, BYTE nBitmapVal);
	LONG GetDCMPixelAt(INT xPos, INT yPos);
	BYTE MapValue(LONG in_nPixelValue);
	void ConvertPixelsData();
	void MakeBitmapInfoHeader();
	void CreatBitmap();
	void UnloadFile();
	
	BOOL m_bOpen;
	BOOL m_bConverted;
	char* m_pBitmap;
	BITMAPINFOHEADER m_oBmpInfor;
	Image* m_pImage;
	Image* m_pConvertedImg;

	INT LoadPixels(char* in_pGroupBuf, LONG in_nLength);
	INT AnalyseImageInfor(char* in_pGroupBuff, LONG in_nGroupLength);
	//Check if it is DICOM file
	BOOL IsDICOMFile();

	//load file to mem
	void LoadFile();

	//Collect image infor
	INT GetImageInfor();

	//file path 
	CString m_sPath;
	CString m_sConvertedPath;

	//file buffer --> in case of demo program :)
	char*	m_pBuffer;

	//buffer length
	LONG	m_buffLenth;

	//DE: (0028,0010)
	CDataElement m_oUSRows;

	//DE: (0028,0011)
	CDataElement m_oUSColum;

	//DE: (0028,0100)
	CDataElement m_oUSBitAllocated;

	//DE: (0028,0101)
	CDataElement m_oUSBitStored;

	//DE: (0028,0101)
	CDataElement m_oUSHighBit;

	//DE: (0028,0106)
	CDataElement m_oSSSmallestPx;

	//DE: (0028,0107)
	CDataElement m_oSSLargestPx;

	//DE: (7FE0,0010) : Data Element of Pixel array 
	CDataElement m_oOWPixelData;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DCMTKAPPDLG_H__60B22CE6_3EE0_4560_AAB7_F21ED0FBB767__INCLUDED_)
