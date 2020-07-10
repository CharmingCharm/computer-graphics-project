// ColorEdit.cpp : implementation file
//

#include "stdafx.h"
#include "PrtSys.h"
#include "ColorEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CColorEdit dialog


CColorEdit::CColorEdit(CWnd* pParent /*=NULL*/)
	: CDialog(CColorEdit::IDD, pParent)
{
	//{{AFX_DATA_INIT(CColorEdit)
	m_B1 = 0.0f;
	m_B2 = 0.0f;
	m_B3 = 0.0f;
	m_B4 = 0.0f;
	m_B5 = 0.0f;
	m_G1 = 0.0f;
	m_G2 = 0.0f;
	m_G3 = 0.0f;
	m_G4 = 0.0f;
	m_G5 = 0.0f;
	m_R1 = 0.0f;
	m_R2 = 0.0f;
	m_R3 = 0.0f;
	m_R4 = 0.0f;
	m_R5 = 0.0f;
	m_E_Title = _T("");
	//}}AFX_DATA_INIT
}

void CColorEdit::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CColorEdit)
	DDX_Text(pDX, IDC_B1, m_B1);
	DDV_MinMaxFloat(pDX, m_B1, 0.f, 1.f);
	DDX_Text(pDX, IDC_B2, m_B2);
	DDV_MinMaxFloat(pDX, m_B2, 0.f, 1.f);
	DDX_Text(pDX, IDC_B3, m_B3);
	DDV_MinMaxFloat(pDX, m_B3, 0.f, 1.f);
	DDX_Text(pDX, IDC_B4, m_B4);
	DDV_MinMaxFloat(pDX, m_B4, 0.f, 1.f);
	DDX_Text(pDX, IDC_B5, m_B5);
	DDV_MinMaxFloat(pDX, m_B5, 0.f, 1.f);
	DDX_Text(pDX, IDC_G1, m_G1);
	DDV_MinMaxFloat(pDX, m_G1, 0.f, 1.f);
	DDX_Text(pDX, IDC_G2, m_G2);
	DDV_MinMaxFloat(pDX, m_G2, 0.f, 1.f);
	DDX_Text(pDX, IDC_G3, m_G3);
	DDV_MinMaxFloat(pDX, m_G3, 0.f, 1.f);
	DDX_Text(pDX, IDC_G4, m_G4);
	DDV_MinMaxFloat(pDX, m_G4, 0.f, 1.f);
	DDX_Text(pDX, IDC_G5, m_G5);
	DDV_MinMaxFloat(pDX, m_G5, 0.f, 1.f);
	DDX_Text(pDX, IDC_R1, m_R1);
	DDV_MinMaxFloat(pDX, m_R1, 0.f, 1.f);
	DDX_Text(pDX, IDC_R2, m_R2);
	DDV_MinMaxFloat(pDX, m_R2, 0.f, 1.f);
	DDX_Text(pDX, IDC_R3, m_R3);
	DDV_MinMaxFloat(pDX, m_R3, 0.f, 1.f);
	DDX_Text(pDX, IDC_R4, m_R4);
	DDV_MinMaxFloat(pDX, m_R4, 0.f, 1.f);
	DDX_Text(pDX, IDC_R5, m_R5);
	DDV_MinMaxFloat(pDX, m_R5, 0.f, 1.f);
	DDX_Text(pDX, IDC_E_Title, m_E_Title);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CColorEdit, CDialog)
	//{{AFX_MSG_MAP(CColorEdit)
	ON_EN_KILLFOCUS(IDC_B1, OnKillfocusB1)
	ON_EN_KILLFOCUS(IDC_B2, OnKillfocusB2)
	ON_EN_KILLFOCUS(IDC_B3, OnKillfocusB3)
	ON_EN_KILLFOCUS(IDC_B4, OnKillfocusB4)
	ON_EN_KILLFOCUS(IDC_B5, OnKillfocusB5)
	ON_EN_KILLFOCUS(IDC_G1, OnKillfocusG1)
	ON_EN_KILLFOCUS(IDC_G2, OnKillfocusG2)
	ON_EN_KILLFOCUS(IDC_G3, OnKillfocusG3)
	ON_EN_KILLFOCUS(IDC_G4, OnKillfocusG4)
	ON_EN_KILLFOCUS(IDC_G5, OnKillfocusG5)
	ON_EN_KILLFOCUS(IDC_R1, OnKillfocusR1)
	ON_EN_KILLFOCUS(IDC_R2, OnKillfocusR2)
	ON_EN_KILLFOCUS(IDC_R3, OnKillfocusR3)
	ON_EN_KILLFOCUS(IDC_R4, OnKillfocusR4)
	ON_EN_KILLFOCUS(IDC_R5, OnKillfocusR5)
	ON_BN_CLICKED(IDC_BE1, OnBe1)
	ON_BN_CLICKED(IDC_BE2, OnBe2)
	ON_BN_CLICKED(IDC_BE3, OnBe3)
	ON_BN_CLICKED(IDC_BE4, OnBe4)
	ON_BN_CLICKED(IDC_BE5, OnBe5)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CColorEdit message handlers
void CColorEdit::GetExtColorData(Dlg_COLOR_EDIT &Ex_color)	//����������
{
	m_color=&Ex_color;		//��ȡ�������ָ�롣
	m_R1=m_color->Red[0];
	m_R2=m_color->Red[1];
	m_R3=m_color->Red[2];
	m_R4=m_color->Red[3];
	m_R5=m_color->Red[4];

	m_G1=m_color->Green[0];
	m_G2=m_color->Green[1];
	m_G3=m_color->Green[2];
	m_G4=m_color->Green[3];
	m_G5=m_color->Green[4];

	m_B1=m_color->Blue[0];
	m_B2=m_color->Blue[1];
	m_B3=m_color->Blue[2];
	m_B4=m_color->Blue[3];
	m_B5=m_color->Blue[4];

	UpdateData(FALSE);						//���������ֵ��ʱ���µ��ؼ�
}


void CColorEdit::OnKillfocusB1() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);			//�������ֵ���µ�����
	m_color->Blue[0]=m_B1;		//�������ֵ���µ����������ƵĶ���
}

void CColorEdit::OnKillfocusB2() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);			//�������ֵ���µ�����
	m_color->Blue[1]=m_B1;		//�������ֵ���µ����������ƵĶ���
}

void CColorEdit::OnKillfocusB3() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);			//�������ֵ���µ�����
	m_color->Blue[2]=m_B3;		//�������ֵ���µ����������ƵĶ���
}

void CColorEdit::OnKillfocusB4() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);			//�������ֵ���µ�����
	m_color->Blue[3]=m_B4;		//�������ֵ���µ����������ƵĶ���
}

void CColorEdit::OnKillfocusB5() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);			//�������ֵ���µ�����
	m_color->Blue[4]=m_B5;		//�������ֵ���µ����������ƵĶ���
}

void CColorEdit::OnKillfocusG1() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);			//�������ֵ���µ�����
	m_color->Green[0]=m_G1;		//�������ֵ���µ����������ƵĶ���
}

void CColorEdit::OnKillfocusG2() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);			//�������ֵ���µ�����
	m_color->Green[1]=m_G2;		//�������ֵ���µ����������ƵĶ���
}

void CColorEdit::OnKillfocusG3() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);			//�������ֵ���µ�����
	m_color->Green[2]=m_G3;		//�������ֵ���µ����������ƵĶ���
}

void CColorEdit::OnKillfocusG4() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);			//�������ֵ���µ�����
	m_color->Green[3]=m_G4;		//�������ֵ���µ����������ƵĶ���
}

void CColorEdit::OnKillfocusG5() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);			//�������ֵ���µ�����
	m_color->Green[4]=m_G5;		//�������ֵ���µ����������ƵĶ���
}

void CColorEdit::OnKillfocusR1() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);			//�������ֵ���µ�����
	m_color->Red[0]=m_R1;		//�������ֵ���µ����������ƵĶ���
}

void CColorEdit::OnKillfocusR2() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);			//�������ֵ���µ�����
	m_color->Red[1]=m_R2;		//�������ֵ���µ����������ƵĶ���
}

void CColorEdit::OnKillfocusR3() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);			//�������ֵ���µ�����
	m_color->Red[2]=m_R3;		//�������ֵ���µ����������ƵĶ���
}

void CColorEdit::OnKillfocusR4() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);			//�������ֵ���µ�����
	m_color->Red[3]=m_R4;		//�������ֵ���µ����������ƵĶ���
}

void CColorEdit::OnKillfocusR5() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);			//�������ֵ���µ�����
	m_color->Red[4]=m_R5;		//�������ֵ���µ����������ƵĶ���
}

void CColorEdit::OnBe1() 
{
	// TODO: Add your control notification handler code here
	CColorDialog cdlg;		//����Ի���
	COLORREF cr;
	if(cdlg.DoModal()==IDOK)	//��ʾ�Ի���
	{
		cr=cdlg.GetColor();	//�����ɫ
	}
	m_R1=(float)GetRValue(cr)/255.0;
	m_G1=(float)GetGValue(cr)/255.0;
	m_B1=(float)GetBValue(cr)/255.0;

	m_color->Red[0]=m_R1;
	m_color->Green[0]=m_G1;
	m_color->Blue[0]=m_B1;
	UpdateData(FALSE);		//��������
}

void CColorEdit::OnBe2() 
{
	// TODO: Add your control notification handler code here
	CColorDialog cdlg;		//����Ի���
	COLORREF cr;
	if(cdlg.DoModal()==IDOK)	//��ʾ�Ի���
	{
		cr=cdlg.GetColor();	//�����ɫ
	}
	m_R2=(float)GetRValue(cr)/255.0;
	m_G2=(float)GetGValue(cr)/255.0;
	m_B2=(float)GetBValue(cr)/255.0;

	m_color->Red[1]=m_R2;
	m_color->Green[1]=m_G2;
	m_color->Blue[1]=m_B2;
	UpdateData(FALSE);		//��������
}

void CColorEdit::OnBe3() 
{
	// TODO: Add your control notification handler code here
	CColorDialog cdlg;		//����Ի���
	COLORREF cr;
	if(cdlg.DoModal()==IDOK)	//��ʾ�Ի���
	{
		cr=cdlg.GetColor();	//�����ɫ
	}
	m_R3=(float)GetRValue(cr)/255.0;
	m_G3=(float)GetGValue(cr)/255.0;
	m_B3=(float)GetBValue(cr)/255.0;

	m_color->Red[2]=m_R3;
	m_color->Green[2]=m_G3;
	m_color->Blue[2]=m_B3;
	UpdateData(FALSE);		//��������
}

void CColorEdit::OnBe4() 
{
	// TODO: Add your control notification handler code here
	CColorDialog cdlg;		//����Ի���
	COLORREF cr;
	if(cdlg.DoModal()==IDOK)	//��ʾ�Ի���
	{
		cr=cdlg.GetColor();	//�����ɫ
	}
	m_R4=(float)GetRValue(cr)/255.0;
	m_G4=(float)GetGValue(cr)/255.0;
	m_B4=(float)GetBValue(cr)/255.0;

	m_color->Red[3]=m_R4;
	m_color->Green[3]=m_G4;
	m_color->Blue[3]=m_B4;
	UpdateData(FALSE);		//��������	
}

void CColorEdit::OnBe5() 
{
	// TODO: Add your control notification handler code here
	CColorDialog cdlg;		//����Ի���
	COLORREF cr;
	if(cdlg.DoModal()==IDOK)	//��ʾ�Ի���
	{
		cr=cdlg.GetColor();	//�����ɫ
	}
	m_R5=(float)GetRValue(cr)/255.0;
	m_G5=(float)GetGValue(cr)/255.0;
	m_B5=(float)GetBValue(cr)/255.0;

	m_color->Red[4]=m_R5;
	m_color->Green[4]=m_G5;
	m_color->Blue[4]=m_B5;
	UpdateData(FALSE);		//��������
}

//ע��ʱ�����Լ���
void CColorEdit::OnDestroy() 
{
	CDialog::OnDestroy();
	ShowWindow(SW_HIDE);
	// TODO: Add your message handler code here
}
