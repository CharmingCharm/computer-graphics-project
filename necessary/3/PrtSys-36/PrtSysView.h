// PrtSysView.h : interface of the CPrtSysView class
// ����ϵͳ��������
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_PRTSYSVIEW_H__9D19F39A_F765_4FAD_9FB7_73F33254A238__INCLUDED_)
#define AFX_PRTSYSVIEW_H__9D19F39A_F765_4FAD_9FB7_73F33254A238__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "mainfrm.h"			// ��������ȫ��
#include "3dsObject.h"			// 3ds����˵����
#include "cameye.h"				// ��������ļ�
#include "3dsDlg.h"				// 3ds�Ի�����
#include "glo.h"				// ȫ�ֽṹ�ͺ����Ķ���
#include "screen.h"				// ȫ����ʾ���ƶԻ���
#include "Particle.h"			// CParticle˵���ļ�,���������ܿض���
#include "DLG_Fire.h"			// ����Ի�����
#include "DLG_WaterFall.h"		// �ٲ��Ի�����
#include "DLG_FireWork.h"		// �񻨶Ի�����
#include "DLG_AtomicBomb.h"		// ԭ�ӵ��Ի�����
#include "DLG_Snow.h"			// ѩ���Ի�����
#include "DLG_Bmp.h"			// λͼ�Ի�����


class CPrtSysView : public CView
{
protected: // create from serialization only
	CPrtSysView();
	DECLARE_DYNCREATE(CPrtSysView)

// Attributes
public:
	CPrtSysDoc* GetDocument();
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPrtSysView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPrtSysView();
	//////////////////////////////////////////////////////////////////
	//��ӳ�Ա�������Ա����
	BOOL RenderScene();
	BOOL SetupPixelFormat(void);
	void SetLogicalPalette(void);
	BOOL InitializeOpenGL(CDC* pDC);

	HGLRC		m_hRC;			//OpenGL����������
	HPALETTE	m_hPalette;		//OpenGL��ɫ��
	CDC*	    m_pDC;			//OpenGL�豸������
	void Init(GLvoid);
	void Draw3ds();
	void DrawAxis();
	void ExitFullScreen();		//�˳�ȫ��

	//******************************************************
	//3ds�������
	C3dsObject	m_3dsobj;		//3DS�������
	BOOL		m_3dsLoaded;	//ȷ��3DS������롣

	//******************************************************
	CCamEye				m_camera;			//���������
	CParticleControl	m_particleControl;	//���ӿ��ƶ���
	CPrt_Demo_BIT		*m_Demo_Bit;		//��ʾ��ָ��

	BOOL		mouserightdown;			// ����Ҽ����±�־
	BOOL		mouseleftdown;			// ���������±�־
	CPoint		mouseprevpoint; 
	//*****************************************************
	//��ʾ���Ʊ���,Ϊ��ʱ��ʾ��Ϊ��ʱ����ʾ
	Dlg_PRT_Control	m_ptrCtrl;			//��ʾ���ƽṹ��


	//////////////////////////////////////////////////////////
	//�Ի�������˵������
	///////////////////////////////////////////////////////////
	void InitTotalDlgData(void);		// ��ʼ�����жԻ�������
	C3dsDlg		m_3dsCtrlDlg;			// 3ds�������ƶԻ���
	bool		DSdlgExist;				// 3ds�������ڱ�־ 
	DlgData_3ds	m_3dsDD;				// 3ds�������ƶԻ������ݽṹ
	//////////////////////
	//����������Ļ������ԵĶԻ���
	ScreenDataStruct	ScreenData;
	CScreen				m_screen;	//��Ļ���ԶԻ���
	bool				cross;		//��������ʾ��־��true��ʾ
	bool				demoPlay;	//��ʾ���ŵı�־
	bool				DemoAutoFinish;//��ʾ�Զ�����
	/////////////////////////
	CDLG_Fire			m_firedlg;				// ����Ի���
	CDLG_WaterFall		m_waterfalldlg;			// �ٲ��Ի���
	CDLG_FireWork		m_fireworkdlg;			// �񻨶Ի���
	CDLG_AtomicBomb		m_atomicbombdlg;		// ԭ�ӵ��Ի���
	CDLG_Snow			m_snowdlg;				// ѩ�ĶԻ���
	CDLG_Bmp			m_bmpdlg;				// λͼ�Ի���



//////////////////////////////////////////////////////////////////
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CPrtSysView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnFullscreen();
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnFaceorline();
	afx_msg void OnHideorshow();
	afx_msg void OnShow3dsdlg();
	afx_msg void OnPlay();
	afx_msg void OnShowFire();
	afx_msg void OnUpdateShowFire(CCmdUI* pCmdUI);
	afx_msg void OnSetfullscreen();
	afx_msg void OnShowWaterfall();
	afx_msg void OnUpdateShowWaterfall(CCmdUI* pCmdUI);
	afx_msg void OnShowFirework();
	afx_msg void OnUpdateShowFirework(CCmdUI* pCmdUI);
	afx_msg void OnEditFire();
	afx_msg void OnUpdateEditFire(CCmdUI* pCmdUI);
	afx_msg void OnEditFirework();
	afx_msg void OnUpdateEditFirework(CCmdUI* pCmdUI);
	afx_msg void OnEditWaterfall();
	afx_msg void OnUpdateEditWaterfall(CCmdUI* pCmdUI);
	afx_msg void OnShowAtomicbomb();
	afx_msg void OnUpdateShowAtomicbomb(CCmdUI* pCmdUI);
	afx_msg void OnEditAtomicbomb();
	afx_msg void OnUpdateEditAtomicbomb(CCmdUI* pCmdUI);
	afx_msg void OnShowSnow();
	afx_msg void OnUpdateShowSnow(CCmdUI* pCmdUI);
	afx_msg void OnEditSnow();
	afx_msg void OnUpdateEditSnow(CCmdUI* pCmdUI);
	afx_msg void OnEditRain();
	afx_msg void OnUpdateEditRain(CCmdUI* pCmdUI);
	afx_msg void OnShowRain();
	afx_msg void OnUpdateShowRain(CCmdUI* pCmdUI);
	afx_msg void OnKwCross();
	afx_msg void OnKwDemo();
	afx_msg void OnKwFileopen();
	afx_msg void OnEditBmp();
	afx_msg void OnShowBmp();
	afx_msg void OnUpdateEditBmp(CCmdUI* pCmdUI);
	afx_msg void OnUpdateShowBmp(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in PrtSysView.cpp
inline CPrtSysDoc* CPrtSysView::GetDocument()
   { return (CPrtSysDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PRTSYSVIEW_H__9D19F39A_F765_4FAD_9FB7_73F33254A238__INCLUDED_)
