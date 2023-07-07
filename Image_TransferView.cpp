
// Image_TransferView.cpp: CImageTransferView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Image_Transfer.h"
#endif

#include "Image_TransferDoc.h"
#include "Image_TransferView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CImageTransferView

IMPLEMENT_DYNCREATE(CImageTransferView, CView)

BEGIN_MESSAGE_MAP(CImageTransferView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CImageTransferView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CImageTransferView 构造/析构

CImageTransferView::CImageTransferView() noexcept
{
	// TODO: 在此处添加构造代码

}

CImageTransferView::~CImageTransferView()
{
}

BOOL CImageTransferView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CImageTransferView 绘图

void CImageTransferView::OnDraw(CDC* /*pDC*/)
{
	CImageTransferDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CImageTransferView 打印


void CImageTransferView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CImageTransferView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CImageTransferView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CImageTransferView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CImageTransferView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CImageTransferView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CImageTransferView 诊断

#ifdef _DEBUG
void CImageTransferView::AssertValid() const
{
	CView::AssertValid();
}

void CImageTransferView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CImageTransferDoc* CImageTransferView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImageTransferDoc)));
	return (CImageTransferDoc*)m_pDocument;
}
#endif //_DEBUG


// CImageTransferView 消息处理程序
