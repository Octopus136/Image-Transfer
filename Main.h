#pragma once
#include "afxdialogex.h"
#include <iostream>
#include <string>
#include <cstdlib>


// Main 对话框

class Main : public CDialogEx
{
	DECLARE_DYNAMIC(Main)

public:
	Main(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Main();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton3();
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnEnChangeEdit3();
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton1();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnCbnSelchangeCombo1();
	virtual BOOL OnInitDialog();
	afx_msg LRESULT UpdatePrograss(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT Warnings(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT PostProcess(WPARAM wParam, LPARAM lParam);
};
