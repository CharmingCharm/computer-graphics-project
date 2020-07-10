// DLG_Fire.cpp : implementation file
//

#include "stdafx.h"
#include "PrtSys.h"
#include "DLG_Fire.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDLG_Fire dialog

//���û�������Χ�Ŀ�������
GLfloat Fire_Sld[13][2] =	//������Ի������Ʒ�Χ��
{
  {0,	9999} ,				//���ӵ����� unsigned long 1000		0
  {0.0001   , 10.0  } ,		//lifefate	1.0						1
  {0.0001   , 10.0  } ,		//slowdown  2.0						2
  {0.0   ,    500  } ,		//speedMax  50						3
  {0.0   ,    500  } ,		//speedMin  0						4
  {0.0   , 180.0  } ,		//AngleYStar 0						5
  {0.0   , 180.0  } ,		//AngleYEnd  90						6
  {0.0   , 360.0  } ,		//AngleXZStar 0						7
  {0.0   , 360.0  } ,		//AngleXZEnd 360					8	
  {-100.0  , 100.0  } ,		//GetXg 0							9
  {-100.0  , 100.0  } ,		//GetYg 0.1							10
  {-100.0 ,  100.0  },		//GetZg 0							11
  {0.01,	  5.0  }		//��ͼ���							12
};


CDLG_Fire::CDLG_Fire(CWnd* pParent /*=NULL*/)
	: CDialog(CDLG_Fire::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDLG_Fire)
	m_E_xzend = 0.0f;
	m_E_xzstar = 0.0f;
	m_E_yend = 0.0f;
	m_E_ystar = 0.0f;
	m_E_getx = 0.0f;
	m_E_gety = 0.0f;
	m_E_getz = 0.0f;
	m_E_lifefate = 0.0f;
	m_E_maxnum = 0;
	m_E_slowdown = 0.0f;
	m_E_speedmax = 0.0f;
	m_E_speedmin = 0.0f;
	m_E_posx = 0.0f;
	m_E_posy = 0.0f;
	m_E_posz = 0.0f;
	m_E_TW = 0.0f;
	m_RF1 = 0;
	m_RF2 = -1;
	m_RF3 = -1;
	m_RF4 = -1;
	//}}AFX_DATA_INIT
}

CDLG_Fire::~CDLG_Fire()
{

}

void CDLG_Fire::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDLG_Fire)
	DDX_Control(pDX, IDC_S_TextWitdh, m_S_TW);
	DDX_Control(pDX, IDC_SLD_SPEEDMIN, m_S_speedmin);
	DDX_Control(pDX, IDC_SLD_SPEEDMAX, m_S_speedmax);
	DDX_Control(pDX, IDC_SLD_SLOWDOWN, m_S_slowdown);
	DDX_Control(pDX, IDC_SLD_MAXNUM, m_S_maxnum);
	DDX_Control(pDX, IDC_SLD_LIFEFATE, m_S_lifefate);
	DDX_Control(pDX, IDC_SLD_GETZ, m_S_getz);
	DDX_Control(pDX, IDC_SLD_GETY, m_S_gety);
	DDX_Control(pDX, IDC_SLD_GETX, m_S_getx);
	DDX_Control(pDX, IDC_SLD_ALYSTAR, m_S_ystar);
	DDX_Control(pDX, IDC_SLD_ALYEND, m_S_yend);
	DDX_Control(pDX, IDC_SLD_ALXZSTAR, m_S_xzstar);
	DDX_Control(pDX, IDC_SLD_ALXZEND, m_S_xzend);
	DDX_Text(pDX, IDC_E_ALXZEND, m_E_xzend);
	DDV_MinMaxFloat(pDX, m_E_xzend, 0.f, 360.f);
	DDX_Text(pDX, IDC_E_ALXZSTAR, m_E_xzstar);
	DDV_MinMaxFloat(pDX, m_E_xzstar, 0.f, 360.f);
	DDX_Text(pDX, IDC_E_ALYEND, m_E_yend);
	DDV_MinMaxFloat(pDX, m_E_yend, 0.f, 180.f);
	DDX_Text(pDX, IDC_E_ALYSTAR, m_E_ystar);
	DDV_MinMaxFloat(pDX, m_E_ystar, 0.f, 180.f);
	DDX_Text(pDX, IDC_E_GETX, m_E_getx);
	DDV_MinMaxFloat(pDX, m_E_getx, -100.f, 100.f);
	DDX_Text(pDX, IDC_E_GETY, m_E_gety);
	DDV_MinMaxFloat(pDX, m_E_gety, -100.f, 100.f);
	DDX_Text(pDX, IDC_E_GETZ, m_E_getz);
	DDV_MinMaxFloat(pDX, m_E_getz, -100.f, 100.f);
	DDX_Text(pDX, IDC_E_LIFEFATE, m_E_lifefate);
	DDV_MinMaxFloat(pDX, m_E_lifefate, 1.e-004f, 10.f);
	DDX_Text(pDX, IDC_E_MAXNUM, m_E_maxnum);
	DDV_MinMaxInt(pDX, m_E_maxnum, 0, 9999);
	DDX_Text(pDX, IDC_E_SLOWDOWN, m_E_slowdown);
	DDV_MinMaxFloat(pDX, m_E_slowdown, 1.e-004f, 10.f);
	DDX_Text(pDX, IDC_E_SPEEDMAX, m_E_speedmax);
	DDV_MinMaxFloat(pDX, m_E_speedmax, 0.f, 500.f);
	DDX_Text(pDX, IDC_E_SPEEDMIN, m_E_speedmin);
	DDV_MinMaxFloat(pDX, m_E_speedmin, 0.f, 500.f);
	DDX_Text(pDX, IDC_E_POS_X, m_E_posx);
	DDX_Text(pDX, IDC_E_POS_Y, m_E_posy);
	DDV_MinMaxFloat(pDX, m_E_posy, -1000.f, 1000.f);
	DDX_Text(pDX, IDC_E_POS_Z, m_E_posz);
	DDV_MinMaxFloat(pDX, m_E_posz, -1000.f, 1000.f);
	DDX_Text(pDX, IDC_E_TextWidth, m_E_TW);
	DDV_MinMaxFloat(pDX, m_E_TW, 1.e-002f, 5.f);
	DDX_Radio(pDX, IDC_R_F1, m_RF1);
	DDX_Radio(pDX, IDC_R_F2, m_RF2);
	DDX_Radio(pDX, IDC_R_F3, m_RF3);
	DDX_Radio(pDX, IDC_R_F4, m_RF4);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDLG_Fire, CDialog)
	//{{AFX_MSG_MAP(CDLG_Fire)
	ON_WM_DESTROY()
	ON_EN_KILLFOCUS(IDC_E_ALXZEND, OnKillfocusEAlxzend)
	ON_EN_KILLFOCUS(IDC_E_ALXZSTAR, OnKillfocusEAlxzstar)
	ON_EN_KILLFOCUS(IDC_E_ALYEND, OnKillfocusEAlyend)
	ON_EN_KILLFOCUS(IDC_E_ALYSTAR, OnKillfocusEAlystar)
	ON_EN_KILLFOCUS(IDC_E_GETX, OnKillfocusEGetx)
	ON_EN_KILLFOCUS(IDC_E_GETY, OnKillfocusEGety)
	ON_EN_KILLFOCUS(IDC_E_GETZ, OnKillfocusEGetz)
	ON_EN_KILLFOCUS(IDC_E_LIFEFATE, OnKillfocusELifefate)
	ON_EN_KILLFOCUS(IDC_E_MAXNUM, OnKillfocusEMaxnum)
	ON_EN_KILLFOCUS(IDC_E_POS_X, OnKillfocusEPosX)
	ON_EN_KILLFOCUS(IDC_E_POS_Y, OnKillfocusEPosY)
	ON_EN_KILLFOCUS(IDC_E_POS_Z, OnKillfocusEPosZ)
	ON_EN_KILLFOCUS(IDC_E_SLOWDOWN, OnKillfocusESlowdown)
	ON_EN_KILLFOCUS(IDC_E_SPEEDMAX, OnKillfocusESpeedmax)
	ON_EN_KILLFOCUS(IDC_E_SPEEDMIN, OnKillfocusESpeedmin)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLD_ALXZEND, OnReleasedcaptureSldAlxzend)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLD_ALXZSTAR, OnReleasedcaptureSldAlxzstar)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLD_ALYEND, OnReleasedcaptureSldAlyend)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLD_ALYSTAR, OnReleasedcaptureSldAlystar)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLD_GETX, OnReleasedcaptureSldGetx)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLD_GETY, OnReleasedcaptureSldGety)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLD_GETZ, OnReleasedcaptureSldGetz)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLD_LIFEFATE, OnReleasedcaptureSldLifefate)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLD_MAXNUM, OnReleasedcaptureSldMaxnum)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLD_SLOWDOWN, OnReleasedcaptureSldSlowdown)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLD_SPEEDMAX, OnReleasedcaptureSldSpeedmax)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLD_SPEEDMIN, OnReleasedcaptureSldSpeedmin)
	ON_EN_KILLFOCUS(IDC_E_TextWidth, OnKillfocusETextWidth)
	ON_BN_CLICKED(IDC_R_F1, OnRF1)
	ON_BN_CLICKED(IDC_R_F2, OnRF2)
	ON_BN_CLICKED(IDC_R_F3, OnRF3)
	ON_BN_CLICKED(IDC_R_F4, OnRF4)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_S_TextWitdh, OnReleasedcaptureSTextWitdh)
	ON_BN_CLICKED(IDC_B_Color, OnBColor)
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BF_LOAD, OnBfLoad)
	ON_BN_CLICKED(IDC_BF_SAVE, OnBfSave)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDLG_Fire message handlers
//���¿ؼ�����
void CDLG_Fire::UpdateDLGDate(void)
{
	m_E_maxnum=m_fireDLG->MAX_PARTICLES;	//���ӵ�����������ɳ���10000��

	m_E_posx=m_fireDLG->star_x;				//����Դ��λ��
	m_E_posy=m_fireDLG->star_y;
	m_E_posz=m_fireDLG->star_z;
	m_E_lifefate=m_fireDLG->lifefate;		// �������ӵ���������ֵԼ�����ӵ�������Խ��

	m_E_slowdown=m_fireDLG->slowdown;		// �������ӵ��ٶȣ���ֵԼ��Խ����ԽСԽ��
	m_E_speedmax=m_fireDLG->speedMax;		// �ٶ����ֵ�������㣡���뷽���޹�
	m_E_speedmin=m_fireDLG->speedMin;		// �ٶ���Сֵ�������㣡��

	m_E_ystar=m_fireDLG->AngleYStar;		//�ٶ�������Y��ļн�Star<End;
	m_E_yend=m_fireDLG->AngleYEnd;			//�ٶ�������Y��ļн�(0~180)

	m_E_xzstar=m_fireDLG->AngleXZStar;		//�ٶ�������XZƽ����X�ļнǣ���Y������˳ʱ�룩(0~360)
	m_E_xzend=m_fireDLG->AngleXZEnd;		//Star<End;
	
	m_E_getx=m_fireDLG->GetXg;				//����ϵͳ�ܵ��Ŀռ���������ʸ����
	m_E_gety=m_fireDLG->GetYg;
	m_E_getz=m_fireDLG->GetZg;
	m_E_TW=m_fireDLG->TextWidth;

	//��ͼ��ʽѡ�������������������������������
	switch(m_fireDLG->TextModel)
	{
	case 0:	m_RF1=0;	m_RF2=-1;	m_RF3=-1;	m_RF4=-1;break;
	case 1:	m_RF1=-1;	m_RF2=0;	m_RF3=-1;	m_RF4=-1;break;
	case 2:	m_RF1=-1;	m_RF2=-1;	m_RF3=0;	m_RF4=-1;break;
	case 3:	m_RF1=-1;	m_RF2=-1;	m_RF3=-1;	m_RF4=0;break;
	}
	//***************************************************************
	UpdateData(FALSE);						//���������ֵ��ʱ���µ��ؼ�
	//������ɫ��
	if(!colorEixst)
	{
		m_FireColor.Create(IDD_DLG_COLOR,NULL);//������ɫ�Ի��� ,���û�����ɹ�������
		m_FireColor.m_E_Title="������ɫ����";	//�ı����
		m_FireColor.UpdateData(FALSE);
		colorEixst=true;
	}
	m_FireColor.GetExtColorData(m_fireDLG->PrtColor);
	//�Ի��������г�ʼ��
	float pos[13] ;//= (m_E_MaxNum - Fire_Sld[0][0]) * 100.0 / (Fire_Sld[0][1] - Fire_Sld[0][0]);
	pos[0]= (m_E_maxnum - Fire_Sld[0][0]) * 100.0 / (Fire_Sld[0][1] - Fire_Sld[0][0]);
	pos[1]= (m_E_lifefate - Fire_Sld[1][0]) * 100.0 / (Fire_Sld[1][1] - Fire_Sld[1][0]);
	pos[2]= (m_E_slowdown - Fire_Sld[2][0]) * 100.0 / (Fire_Sld[2][1] - Fire_Sld[2][0]);
	pos[3]= (m_E_speedmax - Fire_Sld[3][0]) * 100.0 / (Fire_Sld[3][1] - Fire_Sld[3][0]);
	pos[4]= (m_E_speedmin - Fire_Sld[4][0]) * 100.0 / (Fire_Sld[4][1] - Fire_Sld[4][0]);
	pos[5]= (m_E_ystar - Fire_Sld[5][0]) * 100.0 / (Fire_Sld[5][1] - Fire_Sld[5][0]);
	pos[6]= (m_E_yend - Fire_Sld[6][0]) * 100.0 / (Fire_Sld[6][1] - Fire_Sld[6][0]);
	pos[7]= (m_E_xzstar - Fire_Sld[7][0]) * 100.0 / (Fire_Sld[7][1] - Fire_Sld[7][0]);
	pos[8]= (m_E_xzend - Fire_Sld[8][0]) * 100.0 / (Fire_Sld[8][1] - Fire_Sld[8][0]);
	pos[9]= (m_E_getx - Fire_Sld[9][0]) * 100.0 / (Fire_Sld[9][1] - Fire_Sld[9][0]);
	pos[10]= (m_E_gety - Fire_Sld[10][0]) * 100.0 / (Fire_Sld[10][1] - Fire_Sld[10][0]);
	pos[11]= (m_E_getz - Fire_Sld[11][0]) * 100.0 / (Fire_Sld[11][1] - Fire_Sld[11][0]);
	pos[12]= (m_E_TW - Fire_Sld[12][0]) * 100.0 / (Fire_Sld[12][1] - Fire_Sld[12][0]);

	m_S_maxnum.SetPos(pos[0]);
	m_S_lifefate.SetPos(pos[1]);
	m_S_slowdown.SetPos(pos[2]);
	m_S_speedmax.SetPos(pos[3]);
	m_S_speedmin.SetPos(pos[4]);
	m_S_ystar.SetPos(pos[5]);
	m_S_yend.SetPos(pos[6]);
	m_S_xzstar.SetPos(pos[7]);
	m_S_xzend.SetPos(pos[8]);
	m_S_getx.SetPos(pos[9]);
	m_S_gety.SetPos(pos[10]);
	m_S_getz.SetPos(pos[11]);
	m_S_TW.SetPos(pos[12]);
}
// �����������
void CDLG_Fire::GetExtFireData(DlgData_PRT &Ex_fireDLG)
{
	m_fireDLG=&Ex_fireDLG;	//ȡ�����洢���ݵĽṹ����Ϊ�Ǵ�ַ���ã�
							//����ֻҪ������ģ����������Ҳ�͸���
	UpdateDLGDate();//���½��棡

}

//�ر�ʱ�����Լ�
void CDLG_Fire::OnDestroy() 
{
	CDialog::OnDestroy();
	ShowWindow(SW_HIDE);

	// TODO: Add your message handler code here
}

///////////////////////////////////////////////////////////////////////
//				���Ի����ϵ����� Edit ���µ�����
///////////////////////////////////////////////////////////////////////

void CDLG_Fire::OnKillfocusEAlxzend() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);						//�������ֵ���µ�����
	if(m_E_xzend<m_E_xzstar)m_E_xzend=m_E_xzstar;
	m_fireDLG->AngleXZEnd=m_E_xzend;		//�������ֵ���µ����������ƵĶ���
	float pos = (m_E_xzend - Fire_Sld[8][0]) * 100.0 / 
		(Fire_Sld[8][1] - Fire_Sld[8][0]);
    m_S_xzend.SetPos(pos);
	UpdateData(FALSE);
	
}

void CDLG_Fire::OnKillfocusEAlxzstar() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);						//�������ֵ���µ�����
	if(m_E_xzstar>m_E_xzend)m_E_xzstar=m_E_xzend;
	m_fireDLG->AngleXZStar=m_E_xzstar;		//�������ֵ���µ����������ƵĶ���
	float pos = (m_E_xzstar - Fire_Sld[7][0]) * 100.0 / 
		(Fire_Sld[7][1] - Fire_Sld[7][0]);
    m_S_xzstar.SetPos(pos);
	UpdateData(FALSE);
}

void CDLG_Fire::OnKillfocusEAlyend() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);						//�������ֵ���µ�����
	if(m_E_yend<m_E_ystar)m_E_yend=m_E_ystar;
	m_fireDLG->AngleYEnd=m_E_yend;		//�������ֵ���µ����������ƵĶ���
	float pos = (m_E_yend - Fire_Sld[6][0]) * 100.0 / 
		(Fire_Sld[6][1] - Fire_Sld[6][0]);
    m_S_yend.SetPos(pos);
	UpdateData(FALSE);
}

void CDLG_Fire::OnKillfocusEAlystar() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);						//�������ֵ���µ�����
	if(m_E_ystar>m_E_yend)m_E_ystar=m_E_yend;
	m_fireDLG->AngleYStar=m_E_ystar;		//�������ֵ���µ����������ƵĶ���
	float pos = (m_E_ystar - Fire_Sld[5][0]) * 100.0 / 
		(Fire_Sld[5][1] - Fire_Sld[5][0]);
    m_S_ystar.SetPos(pos);
	UpdateData(FALSE);
}

void CDLG_Fire::OnKillfocusEGetx() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);						//�������ֵ���µ�����
	m_fireDLG->GetXg=m_E_getx;		//�������ֵ���µ����������ƵĶ���
	float pos = (m_E_getx - Fire_Sld[9][0]) * 100.0 / 
		(Fire_Sld[9][1] - Fire_Sld[9][0]);
    m_S_getx.SetPos(pos);
}

void CDLG_Fire::OnKillfocusEGety() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);						//�������ֵ���µ�����
	m_fireDLG->GetYg=m_E_gety;		//�������ֵ���µ����������ƵĶ���
	float pos = (m_E_gety - Fire_Sld[10][0]) * 100.0 / 
		(Fire_Sld[10][1] - Fire_Sld[10][0]);
    m_S_gety.SetPos(pos);
}

void CDLG_Fire::OnKillfocusEGetz() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);						//�������ֵ���µ�����
	m_fireDLG->GetZg=m_E_getz;		//�������ֵ���µ����������ƵĶ���
	float pos = (m_E_getz - Fire_Sld[11][0]) * 100.0 / 
		(Fire_Sld[11][1] - Fire_Sld[11][0]);
    m_S_getz.SetPos(pos);
}

void CDLG_Fire::OnKillfocusELifefate() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);						//�������ֵ���µ�����
	m_fireDLG->lifefate=m_E_lifefate;		//�������ֵ���µ����������ƵĶ���
	float pos = (m_E_lifefate - Fire_Sld[1][0]) * 100.0 / 
		(Fire_Sld[1][1] - Fire_Sld[1][0]);
    m_S_lifefate.SetPos(pos);
}

void CDLG_Fire::OnKillfocusEMaxnum() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);						//�������ֵ���µ�����
	m_fireDLG->MAX_PARTICLES=m_E_maxnum;		//�������ֵ���µ����������ƵĶ���
	float pos = (m_E_maxnum - Fire_Sld[0][0]) * 100.0 / 
		(Fire_Sld[0][1] - Fire_Sld[0][0]);
    m_S_maxnum.SetPos(pos);
}

void CDLG_Fire::OnKillfocusEPosX() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);						//�������ֵ���µ�����
	m_fireDLG->star_x=m_E_posx;		//�������ֵ���µ����������ƵĶ���
}

void CDLG_Fire::OnKillfocusEPosY() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);						//�������ֵ���µ�����
	m_fireDLG->star_y=m_E_posy;		//�������ֵ���µ����������ƵĶ���
}

void CDLG_Fire::OnKillfocusEPosZ() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);				//�������ֵ���µ�����
	m_fireDLG->star_z=m_E_posz;		//�������ֵ���µ����������ƵĶ���
}

void CDLG_Fire::OnKillfocusESlowdown() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);						//�������ֵ���µ�����
	m_fireDLG->slowdown=m_E_slowdown;		//�������ֵ���µ����������ƵĶ���
	float pos = (m_E_slowdown - Fire_Sld[2][0]) * 100.0 / 
		(Fire_Sld[2][1] - Fire_Sld[2][0]);
    m_S_slowdown.SetPos(pos);
}

void CDLG_Fire::OnKillfocusESpeedmax() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);						//�������ֵ���µ�����
	//�������С���м��
	if(m_E_speedmax<m_E_speedmin)
			m_E_speedmax=m_E_speedmin;

	m_fireDLG->speedMax=m_E_speedmax;		//�������ֵ���µ����������ƵĶ���
	float pos = (m_E_speedmax - Fire_Sld[3][0]) * 100.0 / 
		(Fire_Sld[3][1] - Fire_Sld[3][0]);
    m_S_speedmax.SetPos(pos);
	UpdateData(FALSE);
}

void CDLG_Fire::OnKillfocusESpeedmin() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);						//�������ֵ���µ�����
	//�������С���м��
	if(m_E_speedmin>m_E_speedmax)
			m_E_speedmin=m_E_speedmax;

	m_fireDLG->speedMin=m_E_speedmin;		//�������ֵ���µ����������ƵĶ���
	float pos = (m_E_speedmin - Fire_Sld[4][0]) * 100.0 / 
		(Fire_Sld[4][1] - Fire_Sld[4][0]);
    m_S_speedmin.SetPos(pos);
	UpdateData(FALSE);
}

////////////////////////////////////////////////////////////////////////////////
//				���������ݸ��µ����������
////////////////////////////////////////////////////////////////////////////////
void CDLG_Fire::OnReleasedcaptureSldAlxzend(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_E_xzend=(m_S_xzend.GetPos()/100.0)
		*(Fire_Sld[8][1] - Fire_Sld[8][0]) 
		+ Fire_Sld[8][0];

	//�������С���м��
	if(m_E_xzend<m_E_xzstar)
	{
		m_E_xzend=m_E_xzstar;
		float pos = (m_E_xzend - Fire_Sld[8][0]) * 100.0 / 
		(Fire_Sld[8][1] - Fire_Sld[8][0]);
		m_S_xzend.SetPos(pos);
	}

	m_fireDLG->AngleXZEnd=m_E_xzend;
	UpdateData(FALSE); 
	*pResult = 0;
}

void CDLG_Fire::OnReleasedcaptureSldAlxzstar(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_E_xzstar=(m_S_xzstar.GetPos()/100.0)
		*(Fire_Sld[7][1] - Fire_Sld[7][0]) 
		+ Fire_Sld[7][0];

	//�������С���м��
	if(m_E_xzstar>m_E_xzend)
	{
		m_E_xzstar=m_E_xzend;
		float pos = (m_E_xzstar - Fire_Sld[7][0]) * 100.0 / 
		(Fire_Sld[7][1] - Fire_Sld[7][0]);
		m_S_xzstar.SetPos(pos);
	}

	m_fireDLG->AngleXZStar=m_E_xzstar;
	UpdateData(FALSE); 
	*pResult = 0;
}

void CDLG_Fire::OnReleasedcaptureSldAlyend(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_E_yend=(m_S_yend.GetPos()/100.0)
		*(Fire_Sld[6][1] - Fire_Sld[6][0]) 
		+ Fire_Sld[6][0];


	if(m_E_yend<m_E_ystar)
	{
		m_E_yend=m_E_ystar;
		float pos = (m_E_yend - Fire_Sld[6][0]) * 100.0 / 
		(Fire_Sld[6][1] - Fire_Sld[6][0]);
		m_S_yend.SetPos(pos);
	}
	m_fireDLG->AngleYEnd=m_E_yend;
	UpdateData(FALSE); 
	*pResult = 0;
}

void CDLG_Fire::OnReleasedcaptureSldAlystar(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_E_ystar=(m_S_ystar.GetPos()/100.0)
		*(Fire_Sld[5][1] - Fire_Sld[5][0]) 
		+ Fire_Sld[5][0];

	//�������С���м��
	if(m_E_ystar>m_E_yend)
	{
		m_E_ystar=m_E_yend;
		float pos = (m_E_ystar - Fire_Sld[5][0]) * 100.0 / 
		(Fire_Sld[5][1] - Fire_Sld[5][0]);
		m_S_ystar.SetPos(pos);
	}

	m_fireDLG->AngleYStar=m_E_ystar;
	UpdateData(FALSE); 	
	*pResult = 0;
}

void CDLG_Fire::OnReleasedcaptureSldGetx(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_E_getx=(m_S_getx.GetPos()/100.0)
		*(Fire_Sld[9][1] - Fire_Sld[9][0]) 
		+ Fire_Sld[9][0];
	m_fireDLG->GetXg=m_E_getx;
	UpdateData(FALSE); 
	*pResult = 0;
}

void CDLG_Fire::OnReleasedcaptureSldGety(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_E_gety=(m_S_gety.GetPos()/100.0)
		*(Fire_Sld[10][1] - Fire_Sld[10][0]) 
		+ Fire_Sld[10][0];
	m_fireDLG->GetYg=m_E_gety;
	UpdateData(FALSE); 	
	*pResult = 0;
}

void CDLG_Fire::OnReleasedcaptureSldGetz(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_E_getz=(m_S_getz.GetPos()/100.0)
		*(Fire_Sld[11][1] - Fire_Sld[11][0]) 
		+ Fire_Sld[11][0];
	m_fireDLG->GetZg=m_E_getz;
	UpdateData(FALSE); 	
	*pResult = 0;
}

void CDLG_Fire::OnReleasedcaptureSldLifefate(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_E_lifefate=(m_S_lifefate.GetPos()/100.0)
		*(Fire_Sld[1][1] - Fire_Sld[1][0]) 
		+ Fire_Sld[1][0];
	m_fireDLG->lifefate=m_E_lifefate;
	UpdateData(FALSE); 	
	*pResult = 0;
}

void CDLG_Fire::OnReleasedcaptureSldMaxnum(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_E_maxnum=(m_S_maxnum.GetPos()/100.0)
		*(Fire_Sld[0][1] - Fire_Sld[0][0]) 
		+ Fire_Sld[0][0];
	m_fireDLG->MAX_PARTICLES=m_E_maxnum;
	UpdateData(FALSE); 
	*pResult = 0;
}

void CDLG_Fire::OnReleasedcaptureSldSlowdown(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_E_slowdown=(m_S_slowdown.GetPos()/100.0)
		*(Fire_Sld[2][1] - Fire_Sld[2][0]) 
		+ Fire_Sld[2][0];
	m_fireDLG->slowdown=m_E_slowdown;
	UpdateData(FALSE); 	
	*pResult = 0;
}

void CDLG_Fire::OnReleasedcaptureSldSpeedmax(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_E_speedmax=(m_S_speedmax.GetPos()/100.0)
		*(Fire_Sld[3][1] - Fire_Sld[3][0]) 
		+ Fire_Sld[3][0];

	//�������С���м��
	if(m_E_speedmax<m_E_speedmin)
	{
		m_E_speedmax=m_E_speedmin;
		float pos = (m_E_speedmax - Fire_Sld[3][0]) * 100.0 / 
		(Fire_Sld[3][1] - Fire_Sld[3][0]);
		m_S_speedmax.SetPos(pos);
	}

	m_fireDLG->speedMax=m_E_speedmax;
	UpdateData(FALSE); 	
	*pResult = 0;
}

void CDLG_Fire::OnReleasedcaptureSldSpeedmin(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_E_speedmin=(m_S_speedmin.GetPos()/100.0)
		*(Fire_Sld[4][1] - Fire_Sld[4][0]) 
		+ Fire_Sld[4][0];

	//�������С���м��
	if(m_E_speedmin>m_E_speedmax)
	{
		m_E_speedmin=m_E_speedmax;
		float pos = (m_E_speedmin - Fire_Sld[4][0]) * 100.0 / 
		(Fire_Sld[4][1] - Fire_Sld[4][0]);
		m_S_speedmin.SetPos(pos);
	}

	m_fireDLG->speedMin=m_E_speedmin;
	UpdateData(FALSE); 
	*pResult = 0;
}

void CDLG_Fire::OnKillfocusETextWidth() 
{

	// TODO: Add your control notification handler code here
	UpdateData(TRUE);						//�������ֵ���µ�����
	m_fireDLG->TextWidth=m_E_TW;		//�������ֵ���µ����������ƵĶ���
	float pos = (m_E_TW - Fire_Sld[12][0]) * 100.0 / 
		(Fire_Sld[12][1] - Fire_Sld[12][0]);
    m_S_TW.SetPos(pos);

}

void CDLG_Fire::OnRF1() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_RF1=0;
	m_RF2=-1;
	m_RF3=-1;
	m_RF4=-1;
	m_fireDLG->TextModel=0;
	UpdateData(FALSE); 
}

void CDLG_Fire::OnRF2() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_RF1=-1;
	m_RF2=0;
	m_RF3=-1;
	m_RF4=-1;
	m_fireDLG->TextModel=1;
	UpdateData(FALSE); 
}

void CDLG_Fire::OnRF3() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_RF1=-1;
	m_RF2=-1;
	m_RF3=0;
	m_RF4=-1;
	m_fireDLG->TextModel=2;
	UpdateData(FALSE); 
}

void CDLG_Fire::OnRF4() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_RF1=-1;
	m_RF2=-1;
	m_RF3=-1;
	m_RF4=0;
	m_fireDLG->TextModel=3;
	UpdateData(FALSE); 
}

void CDLG_Fire::OnReleasedcaptureSTextWitdh(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_E_TW=(m_S_TW.GetPos()/100.0)
		*(Fire_Sld[12][1] - Fire_Sld[12][0]) 
		+ Fire_Sld[12][0];
	m_fireDLG->TextWidth=m_E_TW;
	UpdateData(FALSE); 
	*pResult = 0;
}

//����ɫ�༭�Ի���
void CDLG_Fire::OnBColor() 
{
	// TODO: Add your control notification handler code here
	//��ɫ�ӶԻ�������ݵ���
	if(!colorEixst)
	{
		m_FireColor.Create(IDD_DLG_COLOR,NULL);//������ɫ�Ի��� ,���û�����ɹ�������
		m_FireColor.m_E_Title="������ɫ����";	//�ı����
		m_FireColor.UpdateData(FALSE);
		colorEixst=true;
	}
	m_FireColor.GetExtColorData(m_fireDLG->PrtColor);
	m_FireColor.ShowWindow(SW_SHOW);
}


int CDLG_Fire::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	return 0;
}

void CDLG_Fire::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	//AfxMessageBox("BBB");
	if(colorEixst)//�����������ɫ�Ի���������Ҳ����
	{
		m_FireColor.ShowWindow(SW_HIDE);
	}
	CDialog::OnClose();
}

//��Ч��
void CDLG_Fire::OnBfLoad() 
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
			if(ch!=1)MessageBox("���ǻ���Ч���ļ���");
			else
			{
				fseek(fp,5L,0);
				fread(m_fireDLG,sizeof(*m_fireDLG),1,fp);//�������ǵ�Ч������
			}
		}
		fclose(fp);//�ر��ļ�ָ��
	}
	UpdateDLGDate();//���½�������
	}
	SetCurrentDirectory(szCurDir);//�ָ���ǰ·����

}

//����Ч��
void CDLG_Fire::OnBfSave() 
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
	int ch=1;
	fputc(ch,fp);	//д������Ч���ı�ʾ��1���ǻ��棡
	fwrite(m_fireDLG,sizeof(*m_fireDLG),1,fp);//д�����ǵ�Ч������
	fclose(fp);//�ر��ļ�ָ��
	}
	}
	SetCurrentDirectory(szCurDir);//�ָ���ǰ·����
}
