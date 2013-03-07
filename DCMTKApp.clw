; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CDCMTKAppDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "DCMTKApp.h"

ClassCount=3
Class1=CDCMTKAppApp
Class2=CDCMTKAppDlg
Class3=CAboutDlg

ResourceCount=7
Resource1=IDD_DCMTKAPP_DIALOG
Resource2=IDR_MAINFRAME
Resource3=IDD_DCMTKAPP_DIALOG (English (U.S.))
Resource4=IDD_ABOUTBOX (English (U.S.))
Resource5=IDR_MENU1
Resource6=IDD_ABOUTBOX
Resource7=IDR_TOOLBAR

[CLS:CDCMTKAppApp]
Type=0
HeaderFile=DCMTKApp.h
ImplementationFile=DCMTKApp.cpp
Filter=N
BaseClass=CWinApp
VirtualFilter=AC

[CLS:CDCMTKAppDlg]
Type=0
HeaderFile=DCMTKAppDlg.h
ImplementationFile=DCMTKAppDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=ID_FILE_EXIT

[CLS:CAboutDlg]
Type=0
HeaderFile=DCMTKAppDlg.h
ImplementationFile=DCMTKAppDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_DCMTKAPP_DIALOG]
Type=1
Class=CDCMTKAppDlg
ControlCount=1
Control1=IDC_BTN_CONVERT,button,1342242816

[DLG:IDD_DCMTKAPP_DIALOG (English (U.S.))]
Type=1
Class=CDCMTKAppDlg
ControlCount=2
Control1=IDC_OPEN,button,1342242816
Control2=IDC_CONVERT,button,1342242816

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MENU1]
Type=1
Class=?
Command1=ID_FILE_OPEN
Command2=ID_FILE_CLOSE
Command3=ID_APP_EXIT
Command4=ID_HELP_ABOUT
CommandCount=4

[TB:IDR_TOOLBAR]
Type=1
Class=?
Command1=ID_TBL_OPEN
Command2=ID_TBL_CONVERT
Command3=ID_TBL_CLOSE
Command4=ID_TBL_EXIT
CommandCount=4

