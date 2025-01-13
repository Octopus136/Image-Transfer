
// Image_Transfer.cpp: 定义应用程序的类行为。
//

#include "pch.h"
#include "framework.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "Image_Transfer.h"
#include "Main.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CImageTransferApp

BEGIN_MESSAGE_MAP(CImageTransferApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CImageTransferApp::OnAppAbout)
END_MESSAGE_MAP()


// CImageTransferApp 构造

CImageTransferApp::CImageTransferApp() noexcept
{
	m_bHiColorIcons = TRUE;
	m_nAppLook = 0;
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif
	SetAppID(_T("ImageTransfer.AppID.NoVersion"));
}

CImageTransferApp theApp;

BOOL CImageTransferApp::InitInstance()
{
	Main maindialog;
	maindialog.DoModal();
	return TRUE;
}

int CImageTransferApp::ExitInstance()
{
	AfxOleTerm(FALSE);
	return CWinAppEx::ExitInstance();
}

void CImageTransferApp::OnAppAbout()
{
}

void CImageTransferApp::PreLoadState()
{
}

void CImageTransferApp::LoadCustomState()
{
}

void CImageTransferApp::SaveCustomState()
{
}




