// Main.cpp: 实现文件
//
#include "pch.h"
#include "Image_Transfer.h"
#include "afxdialogex.h"
#include "Main.h"
#include <bits/stdc++.h>
#include <fstream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

// Main 对话框

IMPLEMENT_DYNAMIC(Main, CDialogEx)

LPCWSTR stringToLPCWSTR(std::string orig)
{
	size_t origsize = orig.length() + 1;
	const size_t newsize = 100;
	size_t convertedChars = 0;
	wchar_t* wcstring = (wchar_t*)malloc(sizeof(wchar_t) * (orig.length() - 1));
	mbstowcs_s(&convertedChars, wcstring, origsize, orig.c_str(), _TRUNCATE);

	return wcstring;
}

Main::Main(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

Main::~Main()
{
	
}

BOOL Main::OnInitDialog() {
	CDialogEx::OnInitDialog();
	CComboBox* Switcher = (CComboBox*)GetDlgItem(IDC_COMBO1);
	CProgressCtrl* bar = (CProgressCtrl*)GetDlgItem(IDC_PROGRESS1);
	Switcher->AddString(stringToLPCWSTR(std::string("MB")));
	Switcher->AddString(stringToLPCWSTR(std::string("KB")));
	Switcher->SetCurSel(0);
	bar->SetRange(0, 99);
	bar->SetPos(0);
}

void Main::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

#define BIG_WARNINGS (WM_USER + 1)
#define UPDATE_PROGRESS (WM_USER + 2)
#define POST_PROCESS (WM_USER + 3)

BEGIN_MESSAGE_MAP(Main, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON3, &Main::OnBnClickedButton3)
	ON_EN_CHANGE(IDC_EDIT2, &Main::OnEnChangeEdit2)
	ON_BN_CLICKED(IDC_BUTTON4, &Main::OnBnClickedButton4)
	ON_EN_CHANGE(IDC_EDIT3, &Main::OnEnChangeEdit3)
	ON_EN_CHANGE(IDC_EDIT1, &Main::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_BUTTON2, &Main::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &Main::OnBnClickedButton1)
	ON_CBN_SELCHANGE(IDC_COMBO1, &Main::OnCbnSelchangeCombo1)
	ON_MESSAGE(BIG_WARNINGS, Warnings)
	ON_MESSAGE(UPDATE_PROGRESS, UpdatePrograss)
	ON_MESSAGE(POST_PROCESS, PostProcess)
END_MESSAGE_MAP()


// Main 消息处理程序


void Main::OnBnClickedButton3()
{
	CEdit* path_edit = (CEdit*)GetDlgItem(IDC_EDIT2);
	CString FilePath;
	CFileDialog dlg(TRUE,
		NULL,
		NULL,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		(LPCTSTR)_TEXT("JPG Files (*.jpg)|*.jpg|PNG Files (*.png)|*.png||"),
		NULL);
	if (dlg.DoModal() == IDOK) {
		FilePath = dlg.GetPathName();
		SetDlgItemTextW(IDC_EDIT2, FilePath);
	}
	else {
		return;
	}
	// TODO: 在此添加控件通知处理程序代码
}


void Main::OnEnChangeEdit2()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void Main::OnBnClickedButton4()
{
	CString SavePath;
	CFileDialog dlg(FALSE,
		(LPCTSTR)_TEXT("jpg"),
		(LPCTSTR)_TEXT("output"),
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		(LPCTSTR)_TEXT("JPG Files (*.jpg)|*.jpg|PNG Files (*.png)|*.png||"),
		NULL);
	CEdit* Save_Edit = (CEdit*)GetDlgItem(IDC_EDIT3);
	if (dlg.DoModal() == IDOK) {
		SavePath = dlg.GetPathName();
		SetDlgItemText(IDC_EDIT3, SavePath);
	}
	else {
		return;
	}
	// TODO: 在此添加控件通知处理程序代码
}


void Main::OnEnChangeEdit3()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void Main::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void Main::OnBnClickedButton2()
{
	MessageBox(_T("图片大小转换工具v1.2\nPower by Burnside.\n版权所有 (C) 2023\n\n历史版本：\n\nv1.2\n图片转换时主线程不会被阻塞了\n增加了进度条显示目前的转换进度\n\nv1.1:\n图片路径已支持中文\n重写了内核并使处理速度更快\n更新了部分提示词\n增加了大小选择功能\n\nv1.0\n图片大小转换工具诞生"), _T("关于"));
	// TODO: 在此添加控件通知处理程序代码
}

size_t getFileSize(const char* fileName) {
	if (fileName == NULL) {
		return 0;
	}
	struct stat statbuf;
	stat(fileName, &statbuf);
	size_t filesize = statbuf.st_size;
	return filesize;
}

std::string input, output;
int transfer_count;
double aim_b;
int state;

LRESULT Main::UpdatePrograss(WPARAM wParam, LPARAM lParam)
{
	// 在主线程中更新窗口控件
	CProgressCtrl* bar = (CProgressCtrl*)GetDlgItem(IDC_PROGRESS1);
	// 更新进度条的值
	double ratio = (double)(transfer_count - 1) / (20 - 1);
	int result = static_cast<int>(ratio * 99);
	bar->SetPos(result);
	return 0;
}

LRESULT Main::Warnings(WPARAM wParam, LPARAM lParam)
{
	MessageBox(_T("输出文件过于庞大！请控制在十倍以内！"), _T("出错了！"));
	state = 1;
	return 0;
}

LRESULT Main::PostProcess(WPARAM wParam, LPARAM lParam)
{
	CProgressCtrl* bar = (CProgressCtrl*)GetDlgItem(IDC_PROGRESS1);
	bar->SetPos(99);
	if (transfer_count > 20) {
		MessageBox(_T("转换完成！但无法避免地误差大于1%！"), _T("转换完成"));
	}
	else if (state == 0) MessageBox(_T("转换完成！"), _T("转换完成"));
	bar->SetPos(0);
	transfer_count = 0;
	return 0;
}

UINT BackgroundTaskThread(LPVOID pParam)
{
	Main* pWnd = (Main*)pParam;
	cv::Mat input_img = cv::imread(input);
	int height = input_img.rows;
	int width = input_img.cols;
	cv::Mat resize_img;
	transfer_count = 0;
	double l = 0, r = 10;
	double ori_size = getFileSize(input.c_str());
	if (aim_b > 10 * ori_size) {
		::PostMessage(pWnd->GetSafeHwnd(), BIG_WARNINGS, 0, 0);
		return 0;
	}
	while (l <= r) {
		transfer_count++;
		if (transfer_count > 20) {
			break;
		}
		double mid = (l + r) / 2;
		cv::resize(input_img, resize_img, cv::Size(int(1.0 * mid * width), int(1.0 * mid * height)));
		cv::imwrite(output, resize_img);
		double now_b = getFileSize(output.c_str());
		::PostMessage(pWnd->GetSafeHwnd(), UPDATE_PROGRESS, 0, 0);
		if (std::abs(now_b - aim_b) / aim_b < 0.01) {
			break;
		}
		else if (now_b > aim_b) r = mid;
		else if (now_b < aim_b) l = mid;
	}
	::PostMessage(pWnd->GetSafeHwnd(), POST_PROCESS, 0, 0);
	return 0;
}

void Main::OnBnClickedButton1()
{
	state = 0;
	// CEdit* input_edit = (CEdit*)GetDlgItem(IDC_EDIT2);
	CString input_path, output_path, size_temp;
	GetDlgItemText(IDC_EDIT2, input_path);
	
	GetDlgItemText(IDC_EDIT3, output_path);
	GetDlgItemText(IDC_EDIT1, size_temp);
	bool transfer = true;
	std::string str_temp = CT2A(size_temp.GetString());
	input = CT2A(input_path.GetString());
	if (input.length() == 0) {
		MessageBox(_T("没有指定输入文件！"), _T("出错了！"));
		return;
	}
	//input = Change_Format(input);
	output = CT2A(output_path.GetString());
	if (output.length() == 0) {
		MessageBox(_T("没有指定输出文件！"), _T("出错了！"));
		return;
	}
	if (input == output) {
		MessageBox(_T("输入文件和输出文件不能一致！"), _T("出错了！"));
		return;
	}
	CComboBox* Switcher = (CComboBox*)GetDlgItem(IDC_COMBO1);
	CString strChoosed;
	Switcher->GetLBText(Switcher->GetCurSel(), strChoosed);
	std::string choosed = CT2A(strChoosed.GetString());
	//output = Change_Format(output);
	try {
		if (str_temp.length() == 0) throw "no_data";
		int cnt = 0;
		for (int i = 0; i < str_temp.size(); i++) {
			if ((str_temp[i] < '0' || str_temp[i]>'9') && str_temp[i] != '.') {
				throw "bad";
			}
			if (str_temp[i] == '.') cnt++;
		}
		if (str_temp[0] == '.' || str_temp[str_temp.size() - 1] == '.') throw "illegal";
		if (cnt > 1) throw "illegal";
	}
	catch (...) {
		transfer = false;
	}
	if (transfer == false) {
		MessageBox(_T("大小设置不正确！"), _T("出错了！"));
		return;
	}
	aim_b = std::stod(str_temp);
	if (choosed == "MB") {
		aim_b *= 1024 * 1024;
	}
	else {
		aim_b *= 1024;
	}
	CWinThread* m_pBackgroundThread;
	m_pBackgroundThread = AfxBeginThread(BackgroundTaskThread, this);
	// ::WaitForSingleObject(m_pBackgroundThread->m_hThread, INFINITE);
	// m_pBackgroundThread->Delete();
	// m_pBackgroundThread = NULL;
}


BOOL Main::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE) return TRUE;
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN) return TRUE;
	return CDialogEx::PreTranslateMessage(pMsg);
}


void Main::OnCbnSelchangeCombo1()
{

	// TODO: 在此添加控件通知处理程序代码
}
