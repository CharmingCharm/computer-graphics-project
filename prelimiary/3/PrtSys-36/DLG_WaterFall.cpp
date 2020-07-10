// DLG_WaterFall.cpp : implementation file
//

#include "stdafx.h"
#include "PrtSys.h"
#include "DLG_WaterFall.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDLG_WaterFall dialog

//���û�������Χ�Ŀ�������
GLfloat Waterfall_Sld[13][2] =	//������Ի������Ʒ�Χ��
{
  {0,	9999} ,				//���ӵ����� unsigned long 1000		0
  {0.0001   , 9.9  } ,		//lifefate	1.0						1
  {0.0001   , 10.0  } ,		//slowdown  2.0						2
  {0.0   ,    500  } ,		//speedMax  50						3
  {0.0   ,    500  } ,		//speedMin  0						4
  {0.0   , 180.0  } ,		//AngleYStar 0	>û��ʹ��<			5
  {0.0   , 180.0  } ,		//AngleYEnd  90	��ǣ�0-180��		6
  {0.0   , 50.0  } ,		//AngleXZStar 0	�ٲ��Ŀ��			7
  {0.0   , 360.0  } ,		//AngleXZEnd 360	�����			8	
  {-100.0  , 100.0  } ,		//GetXg 0							9
  {-100.0  , 100.0  } ,		//GetYg 0.1							10
  {-100.0 ,  100.0  },		//GetZg 0							11
  {0.01,	  5.0  }		//��ͼ���							12
};


CDLG_WaterFall::CDLG_WaterFall(CWnd* pParent /*=NULL*/)
	: CDialog(CDLG_WaterFall::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDLG_WaterFall)
	m_E_xzend = 0.0f;
	m_E_xzstar = 0.0f;
	m_E_yend = 0.0f;
	m_E_getx = 0.0f;
	m_E_gety = 0.0f;
	m_E_getz = 0.0f;
	m_E_lifefate = 0.0001f;
	m_E_maxnum = 0;
	m_E_posy = 0.0f;
	m_E_posz = 0.0f;
	m_E_slowdown = 0.0001f;
	m_E_speedmax = 0.0f;
	m_E_speedmin = 0.0f;
	m_E_posx = 0.0f;
	m_E_TW = 1.5f;
	m_RW1 = 0;
	m_RW2 = -1;
	m_RW3 = -1;
	//}}AFX_DATA_INIT
}


CDLG_WaterFall::~CDLG_WaterFall()
{
//	delete this;
}

void CDLG_WaterFall::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDLG_WaterFall)
	DDX_Control(pDX, IDC_SW_TextWidth, m_S_TW);
	DDX_Control(pDX, IDC_SW_SPEEDMIN, m_S_speedmin);
	DDX_Control(pDX, IDC_SW_SPEEDMAX, m_S_speedmax);
	DDX_Control(pDX, IDC_SW_SLOWDOWN, m_S_slowdown);
	DDX_Control(pDX, IDC_SW_MAXNUM, m_S_maxnum);
	DDX_Control(pDX, IDC_SW_LIFEFATE, m_S_lifefate);
	DDX_Control(pDX, IDC_SW_GETZ, m_S_getz);
	DDX_Control(pDX, IDC_SW_GETY, m_S_gety);
	DDX_Control(pDX, IDC_SW_GETX, m_S_getx);
	DDX_Control(pDX, IDC_SW_ALYEND, m_S_yend);
	DDX_Control(pDX, IDC_SW_ALXZSTAR, m_S_xzstar);
	DDX_Control(pDX, IDC_SW_ALXZEND, m_S_xzend);
	DDX_Text(pDX, IDC_EW_ALXZEND, m_E_xzend);
	DDV_MinMaxFloat(pDX, m_E_xzend, 0.f, 360.f);
	DDX_Text(pDX, IDC_EW_ALXZSTAR, m_E_xzstar);
	DDV_MinMaxFloat(pDX, m_E_xzstar, 0.f, 100.f);
	DDX_Text(pDX, IDC_EW_ALYEND, m_E_yend);
	DDV_MinMaxFloat(pDX, m_E_yend, 0.f, 180.f);
	DDX_Text(pDX, IDC_EW_GETX, m_E_getx);
	DDV_MinMaxFloat(pDX, m_E_getx, -100.f, 100.f);
	DDX_Text(pDX, IDC_EW_GETY, m_E_gety);
	DDV_MinMaxFloat(pDX, m_E_gety, -100.f, 100.f);
	DDX_Text(pDX, IDC_EW_GETZ, m_E_getz);
	DDV_MinMaxFloat(pDX, m_E_getz, -100.f, 100.f);
	DDX_Text(pDX, IDC_EW_LIFEFATE, m_E_lifefate);
	DDV_MinMaxFloat(pDX, m_E_lifefate, 1.e-004f, 9.9f);
	DDX_Text(pDX, IDC_EW_MAXNUM, m_E_maxnum);
	DDV_MinMaxInt(pDX, m_E_maxnum, 0, 9999);
	DDX_Text(pDX, IDC_EW_POS_Y, m_E_posy);
	DDV_MinMaxFloat(pDX, m_E_posy, -1000.f, 1000.f);
	DDX_Text(pDX, IDC_EW_POS_Z, m_E_posz);
	DDV_MinMaxFloat(pDX, m_E_posz, -1000.f, 1000.f);
	DDX_Text(pDX, IDC_EW_SLOWDOWN, m_E_slowdown);
	DDV_MinMaxFloat(pDX, m_E_slowdown, 1.e-004f, 10.f);
	DDX_Text(pDX, IDC_EW_SPEEDMAX, m_E_speedmax);
	DDV_MinMaxFloat(pDX, m_E_speedmax, 0.f, 500.f);
	DDX_Text(pDX, IDC_EW_SPEEDMIN, m_E_speedmin);
	DDV_MinMaxFloat(pDX, m_E_speedmin, 0.f, 500.f);
	DDX_Text(pDX, IDC_EW_PPX, m_E_posx);
	DDV_MinMaxFloat(pDX, m_E_posx, -1000.f, 1000.f);
	DDX_Text(pDX, IDC_EW_TextWidth, m_E_TW);
	DDV_MinMaxFloat(pDX, m_E_TW, 1.e-002f, 5.f);
	DDX_Radio(pDX, IDC_RW_1, m_RW1);
	DDX_Radio(pDX, IDC_RW_2, m_RW2);
	DDX_Radio(pDX, IDC_RW_3, m_RW3);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDLG_WaterFall, CDialog)
	//{{AFX_MSG_MAP(CDLG_WaterFall)
	ON_EN_KILLFOCUS(IDC_EW_ALXZEND, OnKillfocusEwAlxzend)
	ON_EN_KILLFOCUS(IDC_EW_ALXZSTAR, OnKillfocusEwAlxzstar)
	ON_EN_KILLFOCUS(IDC_EW_ALYEND, OnKillfocusEwAlyend)
	ON_EN_KILLFOCUS(IDC_EW_GETX, OnKillfocusEwGetx)
	ON_EN_KILLFOCUS(IDC_EW_GETY, OnKillfocusEwGety)
	ON_EN_KILLFOCUS(IDC_EW_GETZ, OnKillfocusEwGetz)
	ON_EN_KILLFOCUS(IDC_EW_LIFEFATE, OnKillfocusEwLifefate)
	ON_EN_KILLFOCUS(IDC_EW_MAXNUM, OnKillfocusEwMaxnum)
	ON_EN_KILLFOCUS(IDC_EW_POS_X, OnKillfocusEwPosX)
	ON_EN_KILLFOCUS(IDC_EW_POS_Y, OnKillfocusEwPosY)
	ON_EN_KILLFOCUS(IDC_EW_POS_Z, OnKillfocusEwPosZ)
	ON_EN_KILLFOCUS(IDC_EW_SLOWDOWN, OnKillfocusEwSlowdown)
	ON_EN_KILLFOCUS(IDC_EW_SPEEDMAX, OnKillfocusEwSpeedmax)
	ON_EN_KILLFOCUS(IDC_EW_SPEEDMIN, OnKillfocusEwSpeedmin)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SW_ALXZEND, OnReleasedcaptureSwAlxzend)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SW_ALXZSTAR, OnReleasedcaptureSwAlxzstar)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SW_ALYEND, OnReleasedcaptureSwAlyend)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SW_GETX, OnReleasedcaptureSwGetx)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SW_GETY, OnReleasedcaptureSwGety)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SW_GETZ, OnReleasedcaptureSwGetz)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SW_LIFEFATE, OnReleasedcaptureSwLifefate)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SW_MAXNUM, OnReleasedcaptureSwMaxnum)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SW_SLOWDOWN, OnReleasedcaptureSwSlowdown)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SW_SPEEDMAX, OnReleasedcaptureSwSpeedmax)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SW_SPEEDMIN, OnReleasedcaptureSwSpeedmin)
	ON_WM_CLOSE()
	ON_EN_KILLFOCUS(IDC_EW_PPX, OnKillfocusEwPpx)
	ON_BN_CLICKED(IDC_BW_COLOR, OnBwColor)
	ON_EN_KILLFOCUS(IDC_EW_TextWidth, OnKillfocusEWTextWidth)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SW_TextWidth, OnReleasedcaptureSWTextWidth)
	ON_BN_CLICKED(IDC_RW_1, OnRw1)
	ON_BN_CLICKED(IDC_RW_2, OnRw2)
	ON_BN_CLICKED(IDC_RW_3, OnRw3)
	ON_BN_CLICKED(IDC_BW_LOAD, OnBwLoad)
	ON_BN_CLICKED(IDC_BW_SAVE, OnBwSave)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDLG_WaterFall message handlers
void CDLG_WaterFall::UpdateDLGDate(void)//���½�������
{
	m_E_maxnum=m_DLGData->MAX_PARTICLES;	//���ӵ�����������ɳ���10000��

	m_E_posx=m_DLGData->star_x;				//����Դ��λ��
	m_E_posy=m_DLGData->star_y;
	m_E_posz=m_DLGData->star_z;
	m_E_lifefate=m_DLGData->lifefate;		// �������ӵ���������ֵԼ�����ӵ�������Խ��

	m_E_slowdown=m_DLGData->slowdown;		// �������ӵ��ٶȣ���ֵԼ��Խ����ԽСԽ��
	m_E_speedmax=m_DLGData->speedMax;		// �ٶ����ֵ�������㣡���뷽���޹�
	m_E_speedmin=m_DLGData->speedMin;		// �ٶ���Сֵ�������㣡��

	m_E_yend=m_DLGData->AngleYEnd;			//�ٶ�������Y��ļн�(0~180)

	m_E_xzstar=m_DLGData->AngleXZStar;		//�ٶ�������XZƽ����X�ļнǣ���Y������˳ʱ�룩(0~360)
	m_E_xzend=m_DLGData->AngleXZEnd;		//Star<End;
	
	m_E_getx=m_DLGData->GetXg;				//����ϵͳ�ܵ��Ŀռ���������ʸ����
	m_E_gety=m_DLGData->GetYg;
	m_E_getz=m_DLGData->GetZg;
	m_E_TW=m_DLGData->TextWidth;			//��ͼ���


	//��ͼ��ʽѡ�������������������������������
	switch(m_DLGData->TextModel)
	{
	case 0:	m_RW1=0;	m_RW2=-1;	m_RW3=-1;break;
	case 1:	m_RW1=-1;	m_RW2=0;	m_RW3=-1;break;
	case 2:	m_RW1=-1;	m_RW2=-1;	m_RW3=0;break;
	}

	if(!colorEixst)
	{
		m_ColorDLG.Create(IDD_DLG_COLOR,NULL);//������ɫ�Ի��� ,���û�����ɹ�������
		m_ColorDLG.m_E_Title="�ٲ���ɫ����";	//�ı����
		m_ColorDLG.UpdateData(FALSE);
		colorEixst=true;
	}
	m_ColorDLG.GetExtColorData(m_DLGData->PrtColor);
	//***************************************************************
	UpdateData(FALSE);						//���������ֵ��ʱ���µ��ؼ�

	//�Ի��������г�ʼ��
	float pos[13] ;//= (m_E_MaxNum - Waterfall_Sld[0][0]) * 100.0 / (Waterfall_Sld[0][1] - Waterfall_Sld[0][0]);
	pos[0]= (m_E_maxnum - Waterfall_Sld[0][0]) * 100.0 / (Waterfall_Sld[0][1] - Waterfall_Sld[0][0]);
	pos[1]= (m_E_lifefate - Waterfall_Sld[1][0]) * 100.0 / (Waterfall_Sld[1][1] - Waterfall_Sld[1][0]);
	pos[2]= (m_E_slowdown - Waterfall_Sld[2][0]) * 100.0 / (Waterfall_Sld[2][1] - Waterfall_Sld[2][0]);
	pos[3]= (m_E_speedmax - Waterfall_Sld[3][0]) * 100.0 / (Waterfall_Sld[3][1] - Waterfall_Sld[3][0]);
	pos[4]= (m_E_speedmin - Waterfall_Sld[4][0]) * 100.0 / (Waterfall_Sld[4][1] - Waterfall_Sld[4][0]);
	pos[6]= (m_E_yend - Waterfall_Sld[6][0]) * 100.0 / (Waterfall_Sld[6][1] - Waterfall_Sld[6][0]);
	pos[7]= (m_E_xzstar - Waterfall_Sld[7][0]) * 100.0 / (Waterfall_Sld[7][1] - Waterfall_Sld[7][0]);
	pos[8]= (m_E_xzend - Waterfall_Sld[8][0]) * 100.0 / (Waterfall_Sld[8][1] - Waterfall_Sld[8][0]);
	pos[9]= (m_E_getx - Waterfall_Sld[9][0]) * 100.0 / (Waterfall_Sld[9][1] - Waterfall_Sld[9][0]);
	pos[10]= (m_E_gety - Waterfall_Sld[10][0]) * 100.0 / (Waterfall_Sld[10][1] - Waterfall_Sld[10][0]);
	pos[11]= (m_E_getz - Waterfall_Sld[11][0]) * 100.0 / (Waterfall_Sld[11][1] - Waterfall_Sld[11][0]);
	pos[12]= (m_E_TW - Waterfall_Sld[12][0]) * 100.0 / (Waterfall_Sld[12][1] - Waterfall_Sld[12][0]);

	m_S_maxnum.SetPos(pos[0]);
	m_S_lifefate.SetPos(pos[1]);
	m_S_slowdown.SetPos(pos[2]);
	m_S_speedmax.SetPos(pos[3]);
	m_S_speedmin.SetPos(pos[4]);
	m_S_yend.SetPos(pos[6]);
	m_S_xzstar.SetPos(pos[7]);
	m_S_xzend.SetPos(pos[8]);
	m_S_getx.SetPos(pos[9]);
	m_S_gety.SetPos(pos[10]);
	m_S_getz.SetPos(pos[11]);
	m_S_TW.SetPos(pos[12]);
}


//����ⲿ���ݣ�ˢ����ʾ���档
void CDLG_WaterFall::GetExtData(DlgData_PRT &Ex_DLGData)
{
	m_DLGData=&Ex_DLGData;	//ȡ�����洢���ݵĽṹ����Ϊ�Ǵ�ַ���ã�
							//����ֻҪ������ģ����������Ҳ�͸���
	UpdateDLGDate();

}

void CDLG_WaterFall::OnKillfocusEwAlxzend() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);						//�������ֵ���µ�����
	m_DLGData->AngleXZEnd=m_E_xzend;		//�������ֵ���µ����������ƵĶ���
	float pos = (m_E_xzend - Waterfall_Sld[8][0]) * 100.0 / 
		(Waterfall_Sld[8][1] - Waterfall_Sld[8][0]);
    m_S_xzend.SetPos(pos);
}

void CDLG_WaterFall::OnKillfocusEwAlxzstar() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);						//�������ֵ���µ�����
	m_DLGData->AngleXZStar=m_E_xzstar;		//�������ֵ���µ����������ƵĶ���
	float pos = (m_E_xzstar - Waterfall_Sld[7][0]) * 100.0 / 
		(Waterfall_Sld[7][1] - Waterfall_Sld[7][0]);
    m_S_xzstar.SetPos(pos);
}

void CDLG_WaterFall::OnKillfocusEwAlyend() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);						//�������ֵ���µ�����
	m_DLGData->AngleYEnd=m_E_yend;		//�������ֵ���µ����������ƵĶ���
	float pos = (m_E_yend - Waterfall_Sld[6][0]) * 100.0 / 
		(Waterfall_Sld[6][1] - Waterfall_Sld[6][0]);
    m_S_yend.SetPos(pos);
}

void CDLG_WaterFall::OnKillfocusEwGetx() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);						//�������ֵ���µ�����
	m_DLGData->GetXg=m_E_getx;		//�������ֵ���µ����������ƵĶ���
	float pos = (m_E_getx - Waterfall_Sld[9][0]) * 100.0 / 
		(Waterfall_Sld[9][1] - Waterfall_Sld[9][0]);
    m_S_getx.SetPos(pos);
}

void CDLG_WaterFall::OnKillfocusEwGety() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);						//�������ֵ���µ�����
	m_DLGData->GetYg=m_E_gety;		//�������ֵ���µ����������ƵĶ���
	float pos = (m_E_gety - Waterfall_Sld[10][0]) * 100.0 / 
		(Waterfall_Sld[10][1] - Waterfall_Sld[10][0]);
    m_S_gety.SetPos(pos);
}

void CDLG_WaterFall::OnKillfocusEwGetz() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);						//�������ֵ���µ�����
	m_DLGData->GetZg=m_E_getz;		//�������ֵ���µ����������ƵĶ���
	float pos = (m_E_getz - Waterfall_Sld[11][0]) * 100.0 / 
		(Waterfall_Sld[11][1] - Waterfall_Sld[11][0]);
    m_S_getz.SetPos(pos);
}

void CDLG_WaterFall::OnKillfocusEwLifefate() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);						//�������ֵ���µ�����
	m_DLGData->lifefate=m_E_lifefate;		//�������ֵ���µ����������ƵĶ���
	float pos = (m_E_lifefate - Waterfall_Sld[1][0]) * 100.0 / 
		(Waterfall_Sld[1][1] - Waterfall_Sld[1][0]);
    m_S_lifefate.SetPos(pos);
}

void CDLG_WaterFall::OnKillfocusEwMaxnum() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);						//�������ֵ���µ�����
	m_DLGData->MAX_PARTICLES=m_E_maxnum;		//�������ֵ���µ����������ƵĶ���
	float pos = (m_E_maxnum - Waterfall_Sld[0][0]) * 100.0 / 
		(Waterfall_Sld[0][1] - Waterfall_Sld[0][0]);
    m_S_maxnum.SetPos(pos);
}

void CDLG_WaterFall::OnKillfocusEwPosX() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);						//�������ֵ���µ�����
	//m_DLGData->star_x=m_E_posx;		//�������ֵ���µ����������ƵĶ���
}


void CDLG_WaterFall::OnKillfocusEwPosY() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);						//�������ֵ���µ�����
	m_DLGData->star_y=m_E_posy;		//�������ֵ���µ����������ƵĶ���
}

void CDLG_WaterFall::OnKillfocusEwPosZ() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);						//�������ֵ���µ�����
	m_DLGData->star_z=m_E_posz;		//�������ֵ���µ����������ƵĶ���
}

void CDLG_WaterFall::OnKillfocusEwSlowdown() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);						//�������ֵ���µ�����
	m_DLGData->slowdown=m_E_slowdown;		//�������ֵ���µ����������ƵĶ���
	float pos = (m_E_slowdown - Waterfall_Sld[2][0]) * 100.0 / 
		(Waterfall_Sld[2][1] - Waterfall_Sld[2][0]);
    m_S_slowdown.SetPos(pos);
}

void CDLG_WaterFall::OnKillfocusEwSpeedmax() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);						//�������ֵ���µ�����
	if(m_E_speedmax<m_E_speedmin)m_E_speedmax=m_E_speedmin;
	m_DLGData->speedMax=m_E_speedmax;		//�������ֵ���µ����������ƵĶ���
	float pos = (m_E_speedmax - Waterfall_Sld[3][0]) * 100.0 / 
		(Waterfall_Sld[3][1] - Waterfall_Sld[3][0]);
    m_S_speedmax.SetPos(pos);
	UpdateData(FALSE); 
}

void CDLG_WaterFall::OnKillfocusEwSpeedmin() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);						//�������ֵ���µ�����
	if(m_E_speedmin>m_E_speedmax)m_E_speedmin=m_E_speedmax;
	m_DLGData->speedMin=m_E_speedmin;		//�������ֵ���µ����������ƵĶ���
	float pos = (m_E_speedmin - Waterfall_Sld[4][0]) * 100.0 / 
		(Waterfall_Sld[4][1] - Waterfall_Sld[4][0]);
    m_S_speedmin.SetPos(pos);
	UpdateData(FALSE); 
}

////////////////////////////////////////////////////////////////////////////////
//				���������ݸ��µ����������
////////////////////////////////////////////////////////////////////////////////
void CDLG_WaterFall::OnReleasedcaptureSwAlxzend(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_E_xzend=(m_S_xzend.GetPos()/100.0)
		*(Waterfall_Sld[8][1] - Waterfall_Sld[8][0]) 
		+ Waterfall_Sld[8][0];
	m_DLGData->AngleXZEnd=m_E_xzend;
	UpdateData(FALSE); 
	*pResult = 0;
}

void CDLG_WaterFall::OnReleasedcaptureSwAlxzstar(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_E_xzstar=(m_S_xzstar.GetPos()/100.0)
		*(Waterfall_Sld[7][1] - Waterfall_Sld[7][0]) 
		+ Waterfall_Sld[7][0];
	m_DLGData->AngleXZStar=m_E_xzstar;
	UpdateData(FALSE); 
	*pResult = 0;
}

void CDLG_WaterFall::OnReleasedcaptureSwAlyend(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_E_yend=(m_S_yend.GetPos()/100.0)
		*(Waterfall_Sld[6][1] - Waterfall_Sld[6][0]) 
		+ Waterfall_Sld[6][0];
	m_DLGData->AngleYEnd=m_E_yend;
	UpdateData(FALSE); 
	*pResult = 0;
}

void CDLG_WaterFall::OnReleasedcaptureSwGetx(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_E_getx=(m_S_getx.GetPos()/100.0)
		*(Waterfall_Sld[9][1] - Waterfall_Sld[9][0]) 
		+ Waterfall_Sld[9][0];
	m_DLGData->GetXg=m_E_getx;
	UpdateData(FALSE); 
	*pResult = 0;
}

void CDLG_WaterFall::OnReleasedcaptureSwGety(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_E_gety=(m_S_gety.GetPos()/100.0)
		*(Waterfall_Sld[10][1] - Waterfall_Sld[10][0]) 
		+ Waterfall_Sld[10][0];
	m_DLGData->GetYg=m_E_gety;
	UpdateData(FALSE); 	
	*pResult = 0;
}

void CDLG_WaterFall::OnReleasedcaptureSwGetz(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_E_getz=(m_S_getz.GetPos()/100.0)
		*(Waterfall_Sld[11][1] - Waterfall_Sld[11][0]) 
		+ Waterfall_Sld[11][0];
	m_DLGData->GetZg=m_E_getz;
	UpdateData(FALSE); 	
	*pResult = 0;
}

void CDLG_WaterFall::OnReleasedcaptureSwLifefate(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_E_lifefate=(m_S_lifefate.GetPos()/100.0)
		*(Waterfall_Sld[1][1] - Waterfall_Sld[1][0]) 
		+ Waterfall_Sld[1][0];
	m_DLGData->lifefate=m_E_lifefate;
	UpdateData(FALSE); 	
	*pResult = 0;
}

void CDLG_WaterFall::OnReleasedcaptureSwMaxnum(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_E_maxnum=(m_S_maxnum.GetPos()/100.0)
		*(Waterfall_Sld[0][1] - Waterfall_Sld[0][0]) 
		+ Waterfall_Sld[0][0];
	m_DLGData->MAX_PARTICLES=m_E_maxnum;
	UpdateData(FALSE); 
	*pResult = 0;
}

void CDLG_WaterFall::OnReleasedcaptureSwSlowdown(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_E_slowdown=(m_S_slowdown.GetPos()/100.0)
		*(Waterfall_Sld[2][1] - Waterfall_Sld[2][0]) 
		+ Waterfall_Sld[2][0];

	m_DLGData->slowdown=m_E_slowdown;
	UpdateData(FALSE); 	
	*pResult = 0;
}

void CDLG_WaterFall::OnReleasedcaptureSwSpeedmax(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_E_speedmax=(m_S_speedmax.GetPos()/100.0)
		*(Waterfall_Sld[3][1] - Waterfall_Sld[3][0]) 
		+ Waterfall_Sld[3][0];

	if(m_E_speedmax<m_E_speedmin)
	{
		m_E_speedmax=m_E_speedmin;
		float pos = (m_E_speedmax - Waterfall_Sld[3][0]) * 100.0 / 
		(Waterfall_Sld[3][1] - Waterfall_Sld[3][0]);
		m_S_speedmax.SetPos(pos);
	}

	m_DLGData->speedMax=m_E_speedmax;
	UpdateData(FALSE); 	
	*pResult = 0;
}

void CDLG_WaterFall::OnReleasedcaptureSwSpeedmin(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_E_speedmin=(m_S_speedmin.GetPos()/100.0)
		*(Waterfall_Sld[4][1] - Waterfall_Sld[4][0]) 
		+ Waterfall_Sld[4][0];

	if(m_E_speedmin>m_E_speedmax)
	{
		m_E_speedmin=m_E_speedmax;
		float pos = (m_E_speedmin - Waterfall_Sld[4][0]) * 100.0 / 
		(Waterfall_Sld[4][1] - Waterfall_Sld[4][0]);
		m_S_speedmin.SetPos(pos);
	}

	m_DLGData->speedMin=m_E_speedmin;
	UpdateData(FALSE); 
	*pResult = 0;
}

void CDLG_WaterFall::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	if(colorEixst)//�����������ɫ�Ի���������Ҳ����
	{
		m_ColorDLG.ShowWindow(SW_HIDE);
	}
	CDialog::OnClose();
}

void CDLG_WaterFall::OnKillfocusEwPpx() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);						//�������ֵ���µ�����
	m_DLGData->star_x=m_E_posx;		//�������ֵ���µ����������ƵĶ���
}

void CDLG_WaterFall::OnBwColor() 
{
	// TODO: Add your control notification handler code here
	//��ɫ�ӶԻ�������ݵ���
	if(!colorEixst)
	{
		m_ColorDLG.Create(IDD_DLG_COLOR,NULL);//������ɫ�Ի��� ,���û�����ɹ�������
		m_ColorDLG.m_E_Title="�ٲ���ɫ����";	//�ı����
		m_ColorDLG.UpdateData(FALSE);
		colorEixst=true;
	}
	m_ColorDLG.GetExtColorData(m_DLGData->PrtColor);
	m_ColorDLG.ShowWindow(SW_SHOW);
}

void CDLG_WaterFall::OnKillfocusEWTextWidth() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);					//�������ֵ���µ�����
	m_DLGData->TextWidth=m_E_TW;		//�������ֵ���µ����������ƵĶ���
	float pos = (m_E_TW - Waterfall_Sld[12][0]) * 100.0 / 
		(Waterfall_Sld[12][1] - Waterfall_Sld[12][0]);
    m_S_TW.SetPos(pos);
}

void CDLG_WaterFall::OnReleasedcaptureSWTextWidth(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_E_TW=(m_S_TW.GetPos()/100.0)
		*(Waterfall_Sld[12][1] - Waterfall_Sld[12][0]) 
		+ Waterfall_Sld[12][0];
	m_DLGData->TextWidth=m_E_TW;
	UpdateData(FALSE); 
	*pResult = 0;
}

void CDLG_WaterFall::OnRw1() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_RW1=0;
	m_RW2=-1;
	m_RW3=-1;
	m_DLGData->TextModel=0;
	UpdateData(FALSE); 
}

void CDLG_WaterFall::OnRw2() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_RW1=-1;
	m_RW2=0;
	m_RW3=-1;
	m_DLGData->TextModel=1;
	UpdateData(FALSE); 
}

void CDLG_WaterFall::OnRw3() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_RW1=-1;
	m_RW2=-1;
	m_RW3=0;
	m_DLGData->TextModel=2;
	UpdateData(FALSE); 
}

void CDLG_WaterFall::OnBwLoad() 
{
	// TODO: Add your control notification handler code here
	char szCurDir[256];//���浱ǰĿ¼
	GetCurrentDirectory(sizeof(szCurDir),szCurDir);

	CString filename;
	CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY,"Ч���ļ�(*.pse)|*.pse||",NULL);

	if(dlg.DoModal()==IDOK)//��ʾ�ļ��Ի���
	{
		filename = dlg.GetPathName();//ȡ���ļ���
		FILE *fp;
		fp=fopen(filename,"rb+");//�򿪱�����ļ�
		if(!fp)MessageBox("���ļ�ʧ�ܣ�");
		else
		{
			fseek(fp,0L,0);//�Ƶ��ļ���ͷ
			char s[10];
			fgets(s,5,fp);//���뿪ͷ�ļ���ʾ
			if(strcmp(s,"PSES")!=0)MessageBox("��������Ч���ļ���");
			else
			{
				fseek(fp,4L,0);//��ȡЧ��
				int ch;
				ch=fgetc(fp);
				if(ch!=2)MessageBox("�����ٲ�Ч���ļ���");
				else
				{
					fseek(fp,5L,0);
					fread(m_DLGData,sizeof(*m_DLGData),1,fp);//�������ǵ�Ч������
				}
			}
			fclose(fp);//�ر��ļ�ָ��
		}
		UpdateDLGDate();//���½�������
	}
	SetCurrentDirectory(szCurDir);//�ָ���ǰ·����
}

void CDLG_WaterFall::OnBwSave() 
{
	// TODO: Add your control notification handler code here
	char szCurDir[256];//���浱ǰĿ¼
	GetCurrentDirectory(sizeof(szCurDir),szCurDir);

	CString filename;
	CFileDialog dlg(FALSE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,"Ч���ļ�(*.pse)|*.pse||",NULL);

	if(dlg.DoModal()==IDOK)//��ʾ�ļ��Ի���
	{
		filename = dlg.GetPathName();//ȡ���ļ���
		FILE *fp;
		fp=fopen(filename,"wb+");//����������ļ�
		if(!fp)MessageBox("д�ļ�ʧ�ܣ�");
		else{
		fseek(fp,0L,0);//�Ƶ��ļ���ͷ
		fputs("PSES",fp);//д�뿪ͷ�ļ���ʾ
		int ch=2;
		fputc(ch,fp);	//д������Ч���ı�ʾ��2�����ٲ���
		fwrite(m_DLGData,sizeof(*m_DLGData),1,fp);//д�����ǵ�Ч������
		fclose(fp);//�ر��ļ�ָ��
		}
	}
	SetCurrentDirectory(szCurDir);//�ָ���ǰ·����
}
