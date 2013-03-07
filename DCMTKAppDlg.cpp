// DCMTKAppDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DCMTKApp.h"
#include "DCMTKAppDlg.h"
#include "Include.h"
#include "DEFactory.h"

#include <gdiplus.h>
using namespace Gdiplus;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDCMTKAppDlg dialog

CDCMTKAppDlg::CDCMTKAppDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDCMTKAppDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDCMTKAppDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	
	m_pBuffer = NULL;
	m_pBitmap = NULL;
	m_buffLenth = 0;
	m_bOpen = FALSE;
	m_bConverted  =FALSE;
	m_pImage = NULL;
	m_pConvertedImg = NULL;

	m_oUSRows.SetTagID(DCM_IMAGE_GROUP, DCM_IMAGE_ROWS);
	m_oUSRows.SetVR(DCM_VR_US);

	m_oUSColum.SetTagID(DCM_IMAGE_GROUP, DCM_IMAGE_COLUMNS);
	m_oUSColum.SetVR(DCM_VR_US);

	m_oUSBitAllocated.SetTagID(DCM_IMAGE_GROUP, DCM_IMAGE_BITALLOC);
	m_oUSBitAllocated.SetVR(DCM_VR_US);

	m_oUSBitStored.SetTagID(DCM_IMAGE_GROUP, DCM_IMAGE_BITSTORE);
	m_oUSBitStored.SetVR(DCM_VR_US);
	
	m_oUSHighBit.SetTagID(DCM_IMAGE_GROUP, DCM_IMAGE_HIGHBIT);
	m_oUSHighBit.SetVR(DCM_VR_US);

	m_oSSSmallestPx.SetTagID(DCM_IMAGE_GROUP, DCM_IMAGE_PX_MIN);
	m_oSSSmallestPx.SetVR(DCM_VR_SS);

	m_oSSLargestPx.SetTagID(DCM_IMAGE_GROUP, DCM_IMAGE_PX_MAX);
	m_oSSLargestPx.SetVR(DCM_VR_SS);
	
	m_oOWPixelData.SetTagID(DCM_PIXEL_GROUP, DCM_PIXEL_DATA);
	m_oOWPixelData.SetVR(DCM_VR_OW);

}

void CDCMTKAppDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDCMTKAppDlg)
	DDX_Control(pDX, IDC_BTN_CONVERT, m_cmdConvert);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDCMTKAppDlg, CDialog)
	//{{AFX_MSG_MAP(CDCMTKAppDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_FILE_OPEN, OnOpen)
	ON_COMMAND(ID_FILE_CONVERT, OnConvert)
	ON_WM_CLOSE()
	ON_COMMAND(ID_HELP_ABOUT, OnHelpAbout)
	ON_COMMAND(ID_FILE_CLOSE, OnFileClose)
	ON_BN_CLICKED(IDC_BTN_CONVERT, OnConvert)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDCMTKAppDlg message handlers

BOOL CDCMTKAppDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	WINDOWPLACEMENT wndPlacement;
	wndPlacement.length = sizeof(WINDOWPLACEMENT);
	wndPlacement.showCmd = SW_SHOWNORMAL;	
	wndPlacement.rcNormalPosition = CRect(DCM_APP_DLG_X,DCM_APP_DLG_Y, DCM_APP_DLG_X + DCM_APP_DLG_WIDTH, DCM_APP_DLG_Y + DCM_APP_DLG_HEIGH);
	SetWindowPlacement(&wndPlacement);
	
	m_cmdConvert.EnableWindow(FALSE);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDCMTKAppDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.
void CDCMTKAppDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting
		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);
		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{	
		CPaintDC dc(this);
		Graphics graphics(dc.m_hDC);

		//Draw DCM image
		if(m_bOpen)
		{
			DOUBLE nImgHeigh = DCM_APP_DLG_IMHEIGH;
			DOUBLE nImgWidth = DCM_APP_DLG_IMWIDTH;			
			
			if(m_pImage->GetWidth() > m_pImage->GetHeight())
			{
				nImgHeigh  =  ((DOUBLE)DCM_APP_DLG_IMWIDTH /(DOUBLE)m_pImage->GetWidth())  * ((DOUBLE)m_pImage->GetHeight());
			}
			else
			{
				nImgWidth  =  ((DOUBLE)DCM_APP_DLG_IMWIDTH/(DOUBLE)m_pImage->GetHeight())  * ((DOUBLE)m_pImage->GetWidth());
			}
		
			graphics.DrawImage(m_pImage, DCM_APP_DLG_SPACING, DCM_APP_DLG_SPACING, (UINT)nImgWidth, (UINT)nImgHeigh);
			m_cmdConvert.EnableWindow(TRUE);
		}
		
		if(m_bConverted)
		{
			DOUBLE nImgHeigh1 = DCM_APP_DLG_IMHEIGH;
			DOUBLE nImgWidth1 = DCM_APP_DLG_IMWIDTH;			
			
			if(m_pConvertedImg->GetWidth() > m_pConvertedImg->GetHeight())
			{
				nImgHeigh1  =  ((DOUBLE)DCM_APP_DLG_IMWIDTH /(DOUBLE)m_pConvertedImg->GetWidth())  * ((DOUBLE)m_pConvertedImg->GetHeight());
			}
			else
			{
				nImgWidth1  =  ((DOUBLE)DCM_APP_DLG_IMWIDTH/(DOUBLE)m_pConvertedImg->GetHeight())  * ((DOUBLE)m_pConvertedImg->GetWidth());
			}
			
			graphics.DrawImage(m_pConvertedImg, 
				DCM_APP_DLG_SPACING * 3 + DCM_APP_DLG_IMWIDTH + DCM_APP_DLG_BUTTON, 
				DCM_APP_DLG_SPACING, 
				(UINT)nImgWidth1, 
			(UINT)nImgHeigh1);
		}

		DrawFrame();
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDCMTKAppDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


//************************************
// Method:    OnOpen
// FullName:  Handle function for Open menu event
// Access:    
// Returns:   
// Qualifier: 
// Parameter: 
//************************************
void CDCMTKAppDlg::OnOpen() 
{
	// TODO: Add your control notification handler code here
	CString str = "DICOM files (*.dcm)|*.dcm||";
	CFileDialog cFile(TRUE,"*.dcm", NULL, OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, str);	//open file dialog

	if(cFile.DoModal() == IDOK)
	{
		OnFileClose();
		m_sPath = cFile.GetPathName();
		//Create buffer and load file in to the buffer
		LoadFile();
		//Read buffer and collect parameter
		if(GetImageInfor() != DCM_APP_NORMAL)
			return;
		//release buffer
		UnloadFile();
		//Create bitmap object for DICOM 
		CreatBitmap();

		if(m_pImage != NULL) 
		{
			delete m_pImage;
			m_pImage = NULL;
		}
		m_pImage = Image::FromFile(L"./temp.bmp");

		m_bOpen = TRUE;

		Invalidate();
	}
}

//************************************
// Method:    LoadFile
// FullName:  Load all file content to memory
// Access:    
// Returns:   
// Qualifier: 
// Parameter: 
//************************************
void CDCMTKAppDlg::LoadFile()
{
	CFile myFile;
	CFileException fileException;
	

	if ( !myFile.Open(m_sPath, CFile::modeReadWrite, &fileException ))
	{
		TRACE( "Can't open file %s, error = %u\n",   m_sPath, fileException.m_cause );
		AfxMessageBox("This file is corrupted, or being used by another program");
	}
	else
	{	
		m_buffLenth = myFile.GetLength();
		if(m_pBuffer != NULL)
		{
			delete [] m_pBuffer;
			m_pBuffer = NULL;
		}
		m_pBuffer = new char[m_buffLenth];
		if(m_pBuffer == NULL) 
		{
			myFile.Close();
			return;
		}

		FillMemory(m_pBuffer, m_buffLenth, 0);

		HGLOBAL hBuffer = GlobalAlloc(GHND, m_buffLenth);
		LPVOID pBuffer = GlobalLock(hBuffer);
		myFile.Seek(0, CFile::begin);
		myFile.Read(pBuffer, m_buffLenth);
		memcpy(m_pBuffer, pBuffer, m_buffLenth);
		GlobalUnlock(hBuffer);
		pBuffer = NULL;
		GlobalFree(hBuffer);	

		myFile.Close();
	}
}

//************************************
// Method:    GetImageInfor
// FullName:  Read buffer and collect parameter information
// Access:    
// Returns:   
// Qualifier: 
// Parameter: 
//************************************
INT CDCMTKAppDlg::GetImageInfor()
{	
	if(!IsDICOMFile())
	{
		AfxMessageBox("This file is not DICOM file");
		return -1;
	}	

	LONG nCurrentPos = DCM_PREAMBLESIZE + DCM_SIGN_SIZE;
	
	//move to start of data
	char* pCurrentPointer = m_pBuffer + nCurrentPos;

	WORD nGroup = 0;
	WORD nElement = 0;
	PWORD	pWord = NULL;
			
	CDataElement oGroupLen(0,0x0000, DCM_VR_UL);
	
 	while (nCurrentPos < m_buffLenth)
 	{

		DWORD nLengthOfGroup = 0;

		//TODO: Get group information		
		pWord = (WORD*)pCurrentPointer;
		oGroupLen.SetGroupID(*pWord);
		//point to value field
		pWord += 4; 

		oGroupLen.SetValueLength(DCM_GROUP_VALUELEN);
		oGroupLen.ReadData((char*)pWord);
		DEFactory::ReadValue(oGroupLen, nLengthOfGroup);

		if(oGroupLen.GetGroupID() == DCM_IMAGE_GROUP)
		{			
			AnalyseImageInfor(pCurrentPointer + DCM_GROUPDE_LEN, nLengthOfGroup);		
		}
		else if(oGroupLen.GetGroupID() == DCM_PIXEL_GROUP)
		{
			LoadPixels(pCurrentPointer + DCM_GROUPDE_LEN, nLengthOfGroup);
		}

		pCurrentPointer += DCM_GROUPDE_LEN;
		pCurrentPointer += nLengthOfGroup;
		nCurrentPos += nLengthOfGroup;
		nCurrentPos += DCM_GROUPDE_LEN;
 	}
	oGroupLen.DeleteData();
	return DCM_APP_NORMAL;
}

//************************************
// Method:    IsDICOMFile
// FullName:  return TRUE if this file is DICOM file, FALSE if not
// Access:    
// Returns:   
// Qualifier: 
// Parameter: 
//************************************
BOOL CDCMTKAppDlg::IsDICOMFile()
{
	char szStr[5];
	FillMemory(szStr, 5, 0);
	CopyMemory(szStr, m_pBuffer + DCM_PREAMBLESIZE, 4);
	CString sSIGN(szStr);

	if(sSIGN == DCM_DICM)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

//************************************
// Method:    AnalyseImageInfor
// FullName:  Parse a mem buffer of image group, to fill all Data Element 
// Access:    
// Returns:   
// Qualifier: 
// Parameter: in_pGroupBuff: pointer to buffer of group Data
//************************************
INT CDCMTKAppDlg::AnalyseImageInfor(char *in_pGroupBuff, LONG in_nGroupLength)
{

	PWORD pWord = 0;
	LONG nCurrentPos = 0;
	char* pCurrentPointer = in_pGroupBuff;
	
	CDataElement oDE;

	while (nCurrentPos < in_nGroupLength)
	{
		// TODO: Read tag information				
		pWord = (PWORD)pCurrentPointer;
		oDE.SetGroupID(*pWord);
		pWord++;

		oDE.SetElementID(*pWord);
		pWord++;						

		char szVR[3];
		FillMemory(szVR, 3, 0);
		szVR[0] = *((PCHAR)pWord);
		szVR[1] = *(((PCHAR)pWord)+ 1);

		CString str(szVR);
		oDE.SetVR(str);

		pWord++;
		
		if (oDE.IsSpecialVR())
		{
			pWord++;
		}
		oDE.ReadLength((PCHAR) pWord);		

		//update pointer to point to data field
		if(oDE.IsSpecialVR()|| oDE.IsImpicitVR())
		{
			pWord+=2;
		}
		else
		{
			pWord++;
		}

		switch(oDE.GetElementID())
		{
		case DCM_IMAGE_ROWS:
			m_oUSRows.SetValueLength(oDE.GetValueLength());
			m_oUSRows.ReadData((char*)pWord);			
			break;

		case DCM_IMAGE_COLUMNS:
			m_oUSColum.SetValueLength(oDE.GetValueLength());
			m_oUSColum.ReadData((char*)pWord);
			break;

		case DCM_IMAGE_BITALLOC:
			m_oUSBitAllocated.SetValueLength(oDE.GetValueLength());
			m_oUSBitAllocated.ReadData((char*)pWord);
		    break;

		case DCM_IMAGE_BITSTORE:
			m_oUSBitStored.SetValueLength(oDE.GetValueLength());
			m_oUSBitStored.ReadData((char*)pWord);
		    break;

		case DCM_IMAGE_HIGHBIT:
			m_oUSHighBit.SetValueLength(oDE.GetValueLength());
			m_oUSHighBit.ReadData((char*)pWord);
			break;

		case DCM_IMAGE_PX_MIN:
			m_oSSSmallestPx.SetValueLength(oDE.GetValueLength());
			m_oSSSmallestPx.ReadData((char*)pWord);
			break;

		case DCM_IMAGE_PX_MAX:
			m_oSSLargestPx.SetValueLength(oDE.GetValueLength());
			m_oSSLargestPx.ReadData((char*)pWord);
		    break;

		default:

		    break;
		}
		pWord += (oDE.GetValueLength()/2);
		nCurrentPos += (((PCHAR)pWord) - pCurrentPointer);
		pCurrentPointer = (char*) pWord;
	}
	oDE.DeleteData();
	return DCM_APP_NORMAL;
}

//************************************
// Method:    LoadPixels
// FullName:  Parse a mem buffer of pixel group, load pixel to object
// Access:    
// Returns:   
// Qualifier: 
// Parameter: in_pGroupBuff: pointer to buffer of group Data
//************************************
INT CDCMTKAppDlg::LoadPixels(char *in_pGroupBuff, LONG in_nGroupLength)
{

	PWORD	pWord = 0;
	LONG	nCurrentPos = 0;
	char*	pCurrentPointer = in_pGroupBuff;
	
	CDataElement oDE;

	while (nCurrentPos < in_nGroupLength)
	{
		// TODO: Read tag information				
		pWord = (PWORD)pCurrentPointer;
		oDE.SetGroupID(*pWord);
		pWord++;

		oDE.SetElementID(*pWord);
		pWord++;						

		char szVR[3];
		FillMemory(szVR, 3, 0);
		szVR[0] = *((PCHAR)pWord);
		szVR[1] = *(((PCHAR)pWord )+ 1);

		CString str(szVR);
		oDE.SetVR(str);

		pWord++;
		
		if (oDE.IsSpecialVR())
		{
			pWord++;
		}
		oDE.ReadLength((PCHAR) pWord);		

		//update pointer to point to data field
		if(oDE.IsSpecialVR()|| oDE.IsImpicitVR())
		{
			pWord+=2;
		}
		else
		{
			pWord++;
		}

		if(oDE.GetElementID() == DCM_PIXEL_DATA)
		{
			m_oOWPixelData.SetValueLength(oDE.GetValueLength());
			m_oOWPixelData.ReadData((char*)pWord);
		}
		
		pWord += (oDE.GetValueLength()/2);
		nCurrentPos += (((PCHAR)pWord) - pCurrentPointer);
		pCurrentPointer = (char*) pWord;
	}

	oDE.DeleteData();
	return DCM_APP_NORMAL;
}

//************************************
// Method:    UnLoadFile
// FullName:  Unload file buffer in mem
// Access:    
// Returns:   
// Qualifier: 
// Parameter: 
//************************************
void CDCMTKAppDlg::UnloadFile()
{
	if(m_pBuffer != NULL)
	{
		delete[] m_pBuffer;
		m_pBuffer = NULL;
	}
}

//************************************
// Method:    CreateBitmap
// FullName:  Create DIB bitmap correspond this DICOM image
// Access:    
// Returns:   
// Qualifier: 
// Parameter: 
//************************************
void CDCMTKAppDlg::CreatBitmap()
{	
	//Create bitmap infor header
	MakeBitmapInfoHeader();

	//Convert pixel array from DICOM form to bitmapp form
	ConvertPixelsData();

	//Write to file
	WriteOutToFile();
}

//************************************
// Method:    MakeBitmapInfoHeader
// FullName:  Calculate and make bitmap info header for this bitmap
// Access:    
// Returns:   
// Qualifier: 
// Parameter: 
//************************************
void CDCMTKAppDlg::MakeBitmapInfoHeader()
{
	USHORT nTemp = 0;

	memset(&m_oBmpInfor, 0, sizeof(m_oBmpInfor));
	m_oBmpInfor.biSize = sizeof(BITMAPINFOHEADER);
	
	DEFactory::ReadValue(m_oUSColum, nTemp);
	m_oBmpInfor.biWidth = nTemp;
	DEFactory::ReadValue(m_oUSRows, nTemp);
	m_oBmpInfor.biHeight = nTemp;

	m_oBmpInfor.biPlanes = 1;
	m_oBmpInfor.biCompression = BI_RGB;
	m_oBmpInfor.biBitCount = DCM_APP_BITCOUNT;		//RGB color format
	m_oBmpInfor.biSizeImage = m_oBmpInfor.biWidth * m_oBmpInfor.biHeight * (DCM_APP_BITCOUNT/8);
//	m_oBmpInfor.biXPelsPerMeter = DCM_APP_XRES;		//= 96 % 0.0254
//	m_oBmpInfor.biYPelsPerMeter = DCM_APP_XRES;		//= 96 % 0.0254	
}


//************************************
// Method:    ConvertPixelsData
// FullName:  Convert pixel data array from DICOM standard to bitmap form
// Access:    
// Returns:   
// Qualifier: 
// Parameter: 
//************************************
void CDCMTKAppDlg::ConvertPixelsData()
{
	// TODO: calculate size of image
	LONG nSizeOfImage = (m_oBmpInfor.biBitCount / 8) * m_oBmpInfor.biWidth * m_oBmpInfor.biHeight;	
	if (m_pBitmap != NULL)
	{
		delete [] m_pBitmap;
		m_pBitmap = NULL;
	}

	// TODO: allocate memory for this bitmap's pixels	
	m_pBitmap = new char[nSizeOfImage];
	memset(m_pBitmap, 0, nSizeOfImage);
	HGLOBAL hBitmapBuf = GlobalAlloc(GHND, nSizeOfImage);
	LPVOID pBuffer = GlobalLock(hBitmapBuf);

	for(INT j=1; j<= m_oBmpInfor.biHeight; j++)
	{
		for(INT i=1; i <= m_oBmpInfor.biWidth; i++)
		{
			LONG nDCMPixelVal = GetDCMPixelAt(i,j);
			BYTE nBitmapVal = MapValue(nDCMPixelVal);
			SetBMPPixelAt(i,m_oBmpInfor.biHeight - j + 1, pBuffer, nBitmapVal);
		}
	}

	memcpy(m_pBitmap, pBuffer, nSizeOfImage);
	GlobalUnlock(hBitmapBuf);
	pBuffer = NULL;
	GlobalFree(hBitmapBuf);
}

//************************************
// Method:    MapValue
// FullName:  map pixel value from DICOM value range to bit map value range (0..255)
// Access:    
// Returns:   mapped value
// Qualifier: 
// Parameter: in_nPixelValue: DICOM pixel value
//************************************
BYTE CDCMTKAppDlg::MapValue(LONG in_nPixelValue)
{
	DOUBLE nRetVal = 0;
	SHORT nMaxPixelVal;
	SHORT nMinPixelVal;
	DOUBLE dRatio;

	DEFactory::ReadValue(m_oSSSmallestPx, nMinPixelVal);
	DEFactory::ReadValue(m_oSSLargestPx, nMaxPixelVal);

	dRatio = (DOUBLE)((DOUBLE)in_nPixelValue-(DOUBLE)nMinPixelVal)/((DOUBLE)nMaxPixelVal - (DOUBLE)nMinPixelVal);

	nRetVal = dRatio * DCM_APP_MAXCOLOR;

	return (BYTE)nRetVal;
}


//************************************
// Method:    GetDCMPixelAt
// FullName:  Get pixel value at position
// Access:    
// Returns:   
// Qualifier: 
// Parameter: 
//************************************
LONG CDCMTKAppDlg::GetDCMPixelAt(INT xPos, INT yPos)
{
	PCHAR pImage = (PCHAR)m_oOWPixelData.GetValuePointer();
	PCHAR pCurrentPos = NULL;
	//TODO: Calculate necessary information to read pixel array of the DCM image
	USHORT nTemp;
	INT nBitAllocated;
	INT nBytePerPixel;
// 	INT nBitStored;
// 	INT nHighBit;
	
 	DEFactory::ReadValue(m_oUSBitAllocated, nTemp);
	nBitAllocated = nTemp;
	nBytePerPixel = nBitAllocated / 8;

// 	DEFactory::ReadValue(m_oUSBitStored, nTemp);
// 	nBitStored = nTemp;
// 
// 	DEFactory::ReadValue(m_oUSHighBit,nTemp);
// 	nHighBit = nTemp;
	
	INT nSizeOfLine = nBytePerPixel * m_oBmpInfor.biWidth;
	
	// TODO: move pointer to current pixel
	ASSERT(((yPos-1) * nSizeOfLine + (xPos-1)*nBytePerPixel) < m_oOWPixelData.GetValueLength());
	pCurrentPos = pImage + (yPos-1) * nSizeOfLine + (xPos-1)*nBytePerPixel;
	
	//Get the value
	SHORT nValue = *((PSHORT)pCurrentPos);
	return (LONG)nValue;
}

//************************************
// Method:    SetBMPPixelAt
// FullName:  Set value for pixel in Bitmap image
// Access:    
// Returns:   
// Qualifier: 
// Parameter: 
//************************************
void CDCMTKAppDlg::SetBMPPixelAt(INT xPos, INT yPos, LPVOID pBuffer, BYTE nBitmapVal)
{
	INT nSizeOfLine;
	nSizeOfLine = m_oBmpInfor.biWidth * 3;

	PBYTE pCharBuf = (PBYTE) pBuffer;
	PBYTE pCurrentPos = NULL;

	pCurrentPos = pCharBuf + (yPos - 1) * nSizeOfLine + (xPos - 1)*3;
	*pCurrentPos = nBitmapVal;
	*(pCurrentPos + 1) = nBitmapVal;
	*(pCurrentPos + 2) = nBitmapVal;	
}

//************************************
// Method:    WriteOutToFile
// FullName:  Write this file to BMP file
// Access:    
// Returns:   
// Qualifier: 
// Parameter: 
//************************************
void CDCMTKAppDlg::WriteOutToFile()
{
	//write to bitmap file

	char* pszFileName = "./temp.bmp";
	CFile bmpFile;
	CFileException fileException;
	
	if ( !bmpFile.Open( pszFileName, CFile::modeCreate | CFile::modeWrite, &fileException ) )
	{
		TRACE( "Can't open file %s, error = %u\n", pszFileName, fileException.m_cause );
		AfxMessageBox("This file is broken or openned by other program");
	}
	else
	{
		// TODO: write bitmap file header
		BITMAPFILEHEADER oFileHeader;
		memset(&oFileHeader, 0, sizeof(BITMAPFILEHEADER));
		oFileHeader.bfType = 0x4D42;	//BM
		oFileHeader.bfSize = 54 + m_oBmpInfor.biHeight *  m_oBmpInfor.biWidth * 3;
		oFileHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
		bmpFile.Write(&oFileHeader, sizeof(BITMAPFILEHEADER));

		// TODO: write bitmap image header
		bmpFile.Write(&m_oBmpInfor, sizeof(BITMAPINFOHEADER));

		// TODO: write bimap data
		bmpFile.Write(m_pBitmap, m_oBmpInfor.biSizeImage);		
		bmpFile.Close();
	}
}

int GetEncoderClsid(const WCHAR* format, CLSID* pClsid)
{
   UINT  num = 0;          // number of image encoders
   UINT  size = 0;         // size of the image encoder array in bytes

   ImageCodecInfo* pImageCodecInfo = NULL;

   GetImageEncodersSize(&num, &size);
   if(size == 0)
      return -1;  // Failure

   pImageCodecInfo = (ImageCodecInfo*)(malloc(size));
   if(pImageCodecInfo == NULL)
      return -1;  // Failure

   GetImageEncoders(num, size, pImageCodecInfo);

   for(UINT j = 0; j < num; ++j)
   {
      if( wcscmp(pImageCodecInfo[j].MimeType, format) == 0 )
      {
         *pClsid = pImageCodecInfo[j].Clsid;
         free(pImageCodecInfo);
         return j;  // Success
      }    
   }

   free(pImageCodecInfo);
   return -1;  // Failure
}

void CDCMTKAppDlg::OnConvert() 
{
	//Open file dialog with filter to: JPG, GIF, TIFF, PNG. RAW
	CString str = "Raw files (*.raw)|*.raw|Bitmap file (*.bmp)|*.bmp|JPEG file (*.jpg)|*.jpg|Giff files(*.gif)|*.gif|TIFF files(*.tif)|*.tif|PNG files (*.png)|*.png||";
	CFileDialog oFileDlg(FALSE,"raw", "*.raw", OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, str);

	CLSID pngClsid;	
	if(oFileDlg.DoModal() == IDOK)
	{
		m_sConvertedPath = oFileDlg.GetPathName();
		CString ext = oFileDlg.GetFileExt();

		if( ext == "raw")
		{
			CFile bmpFile;
			CFileException fileException;
			if ( !bmpFile.Open( m_sConvertedPath, CFile::modeCreate | CFile::modeWrite, &fileException ) )
			{
				TRACE( "Can't open file %s, error = %u\n", str, fileException.m_cause );
				AfxMessageBox("This file is broken or openned by other program");
			}
			else
			{
				// TODO: write bimap data
				bmpFile.Write(m_pBitmap, m_oBmpInfor.biSizeImage);		
				bmpFile.Close();
			}				
		}
		else if(ext == "bmp")
		{
			GetEncoderClsid(L"image/bmp", &pngClsid);
			m_pImage->Save(m_sConvertedPath.AllocSysString(), &pngClsid, NULL);
		}
		else if(ext == "jpg")
		{
			GetEncoderClsid(L"image/jpeg", &pngClsid);
			m_pImage->Save(m_sConvertedPath.AllocSysString(), &pngClsid, NULL);
		}
		else if(ext == "gif")
		{
			GetEncoderClsid(L"image/gif", &pngClsid);
			m_pImage->Save(m_sConvertedPath.AllocSysString(), &pngClsid, NULL);
		}
		else if(ext == "tif")
		{
			GetEncoderClsid(L"image/tiff", &pngClsid);
			m_pImage->Save(m_sConvertedPath.AllocSysString(), &pngClsid, NULL);
		}
		else if(ext == "png")
		{
			GetEncoderClsid(L"image/png", &pngClsid);
			m_pImage->Save(m_sConvertedPath.AllocSysString(), &pngClsid, NULL);
		}		

		if(m_pConvertedImg != NULL) 
		{
			delete m_pConvertedImg;
			m_pConvertedImg = NULL;
		}

		if(ext == "raw")
		{
			m_pConvertedImg = Image::FromFile(L"./temp.bmp");
		}
		else
		{
			m_pConvertedImg = Image::FromFile(m_sConvertedPath.AllocSysString());
		}
		

		m_bConverted = TRUE;

		Invalidate();
	}

}

void CDCMTKAppDlg::OnClose() 
{
	Bitmap myBitmap(L"Picture.bmp");
	
	UINT numEntries;
	myBitmap.GetHistogramSize(HistogramFormatRGB, &numEntries);
	
	UINT* ch0 = new UINT[numEntries];
	UINT* ch1 = new UINT[numEntries];
	UINT* ch2 = new UINT[numEntries];
	
	myBitmap.GetHistogram(HistogramFormatRGB, numEntries, ch0, ch1, ch2, NULL);
	
	// Print the histogram values for the three channels: red, green, blue.
	for(UINT j = 0; j < numEntries; ++j)
	{
		printf("%u\t%u\t%u\t%u\n", j, ch0[j], ch1[j], ch2[j]);
	}
	
	delete ch0;
	delete ch1;
	delete ch2;

	ResetData();
	CDialog::OnClose();
}

void CDCMTKAppDlg::OnHelpAbout() 
{
	// TODO: Add your command handler code here
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
}

//////////////////////////////////////////////////////////////////////////
void CDCMTKAppDlg::DrawFrame()
{
	CRect rcDlgClient;
	//GetClientRect(&rcDlgClient);
	CClientDC dc(this);
	CPoint topleft;
	
	CRect rcShowDCM;


	//Draw DCM image retangle
	rcShowDCM.SetRect(
		DCM_APP_DLG_SPACING,
		DCM_APP_DLG_SPACING, 
		DCM_APP_DLG_SPACING + DCM_APP_DLG_IMWIDTH, 
		DCM_APP_DLG_SPACING + DCM_APP_DLG_IMHEIGH
	);
	dc.DrawEdge(&rcShowDCM, EDGE_SUNKEN ,BF_RECT);


	rcShowDCM.SetRect(
		(DCM_APP_DLG_SPACING * 3 + DCM_APP_DLG_IMWIDTH + DCM_APP_DLG_BUTTON),
		DCM_APP_DLG_SPACING, 
		DCM_APP_DLG_SPACING * 3 + 2 * DCM_APP_DLG_IMWIDTH + DCM_APP_DLG_BUTTON, 
		DCM_APP_DLG_SPACING + DCM_APP_DLG_IMHEIGH
	);
	dc.DrawEdge(&rcShowDCM, EDGE_SUNKEN ,BF_RECT);

}

void CDCMTKAppDlg::OnFileClose() 
{
	ResetData();
	Invalidate();

}

void CDCMTKAppDlg::ResetData()
{
	if(m_pBuffer != NULL)
	{
		delete [] m_pBuffer;
		m_pBuffer = NULL;
	}

	if(m_pBitmap != NULL)
	{
		delete [] m_pBitmap;
		m_pBitmap = NULL;
	}

	if(m_pImage != NULL)
	{
		delete m_pImage;
		m_pImage = NULL;
	}

	if(m_pConvertedImg != NULL)
	{
		delete m_pConvertedImg;
		m_pConvertedImg = NULL;
	}

	m_oUSRows.DeleteData();

	//DE: (0028,0011)
	m_oUSColum.DeleteData();

	//DE: (0028,0100)
	m_oUSBitAllocated.DeleteData();

	//DE: (0028,0101)
	m_oUSBitStored.DeleteData();

	//DE: (0028,0101)
	m_oUSHighBit.DeleteData();

	//DE: (0028,0106)
	m_oSSSmallestPx.DeleteData();

	//DE: (0028,0107)
	m_oSSLargestPx.DeleteData();

	//DE: (7FE0,0010) : Data Element of Pixel array 
	m_oOWPixelData.DeleteData();
	m_bConverted = FALSE;
	m_bOpen = FALSE;
}

