// PrtSysView.cpp : implementation of the CPrtSysView class
//

#include "stdafx.h"
#include "PrtSys.h"
#include <math.h>
#include "PrtSysDoc.h"
#include "PrtSysView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPrtSysView

IMPLEMENT_DYNCREATE(CPrtSysView, CView)

BEGIN_MESSAGE_MAP(CPrtSysView, CView)
	//{{AFX_MSG_MAP(CPrtSysView)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_COMMAND(ID_KW_FULLSCREEN, OnFullscreen)
	ON_WM_KEYUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_MOUSEWHEEL()
	ON_WM_KEYDOWN()
	ON_COMMAND(ID_KW_FACEORLINE, OnFaceorline)
	ON_COMMAND(ID_KW_HIDEORSHOW, OnHideorshow)
	ON_COMMAND(ID_KW_SHOW3DSDLG, OnShow3dsdlg)
	ON_COMMAND(ID_KW_PLAY, OnPlay)
	ON_COMMAND(ID_SHOW_FIRE, OnShowFire)
	ON_UPDATE_COMMAND_UI(ID_SHOW_FIRE, OnUpdateShowFire)
	ON_COMMAND(ID_KW_SETFULLSCREEN, OnSetfullscreen)
	ON_COMMAND(ID_SHOW_WATERFALL, OnShowWaterfall)
	ON_UPDATE_COMMAND_UI(ID_SHOW_WATERFALL, OnUpdateShowWaterfall)
	ON_COMMAND(ID_SHOW_FIREWORK, OnShowFirework)
	ON_UPDATE_COMMAND_UI(ID_SHOW_FIREWORK, OnUpdateShowFirework)
	ON_COMMAND(ID_EDIT_FIRE, OnEditFire)
	ON_UPDATE_COMMAND_UI(ID_EDIT_FIRE, OnUpdateEditFire)
	ON_COMMAND(ID_EDIT_FIREWORK, OnEditFirework)
	ON_UPDATE_COMMAND_UI(ID_EDIT_FIREWORK, OnUpdateEditFirework)
	ON_COMMAND(ID_EDIT_WATERFALL, OnEditWaterfall)
	ON_UPDATE_COMMAND_UI(ID_EDIT_WATERFALL, OnUpdateEditWaterfall)
	ON_COMMAND(ID_SHOW_ATOMICBOMB, OnShowAtomicbomb)
	ON_UPDATE_COMMAND_UI(ID_SHOW_ATOMICBOMB, OnUpdateShowAtomicbomb)
	ON_COMMAND(ID_EDIT_ATOMICBOMB, OnEditAtomicbomb)
	ON_UPDATE_COMMAND_UI(ID_EDIT_ATOMICBOMB, OnUpdateEditAtomicbomb)
	ON_COMMAND(ID_SHOW_SNOW, OnShowSnow)
	ON_UPDATE_COMMAND_UI(ID_SHOW_SNOW, OnUpdateShowSnow)
	ON_COMMAND(ID_EDIT_SNOW, OnEditSnow)
	ON_UPDATE_COMMAND_UI(ID_EDIT_SNOW, OnUpdateEditSnow)
	ON_COMMAND(ID_KW_CROSS, OnKwCross)
	ON_COMMAND(ID_KW_DEMO, OnKwDemo)
	ON_COMMAND(ID_KW_FILEOPEN, OnKwFileopen)
	ON_COMMAND(ID_EDIT_BMP, OnEditBmp)
	ON_COMMAND(ID_SHOW_BMP, OnShowBmp)
	ON_UPDATE_COMMAND_UI(ID_EDIT_BMP, OnUpdateEditBmp)
	ON_UPDATE_COMMAND_UI(ID_SHOW_BMP, OnUpdateShowBmp)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPrtSysView construction/destruction

CPrtSysView::CPrtSysView()
{
	// TODO: add construction code here
	InitTotalDlgData();//��ʼ�����жԻ�������
}

//��ʼ���жԻ�������
void CPrtSysView::InitTotalDlgData()
{
	//��ʼ��3ds�����Ի�������
	m_3dsDD.hide=false;
	m_3dsDD.IsLine=true;
	m_3dsDD.scale=0.02;
	m_3dsDD.r_data.Angle_x=0.0;
	m_3dsDD.r_data.Angle_y=0.0;
	m_3dsDD.r_data.Angle_z=0.0;
	m_3dsDD.t_data.x=0.0;
	m_3dsDD.t_data.y=0.0;
	m_3dsDD.t_data.z=0.0;

	//**************************
	//������Ϣ��ʼ��
	m_ptrCtrl.p_fire=false;
	m_ptrCtrl.p_waterfall=false;
	m_ptrCtrl.p_firework=false;
	m_ptrCtrl.p_atomicbomb=false;
	m_ptrCtrl.p_snow=false;
	m_ptrCtrl.p_rain=false;
	m_ptrCtrl.p_demo=false;	//��ʼ��ʾ�ر�
	m_ptrCtrl.p_bmp=false;
	m_ptrCtrl.IsPlay=true;


	//*******************************
	//ȫ����ʾ��Ϣ
	ScreenData.Width=640;
	ScreenData.Height=480;
	ScreenData.IsFullScreen=false;	//ȫ���ر�
	cross=true;			//��ʾ�����ᡣ
	demoPlay=false;		//��ʾ�ر�
	DemoAutoFinish=false;
	//**************************
	//���ɸ����Ի���
	m_screen.Create(IDD_SCREEN,NULL); 

	m_firedlg.Create(IDD_DLG_Fire,NULL); 
	m_firedlg.colorEixst=false;//û�����ɹ���ɫ�Ի���

	m_waterfalldlg.Create(IDD_DLG_WaterFall,NULL);
	m_waterfalldlg.colorEixst=false;//û�����ɹ���ɫ�Ի���

	m_fireworkdlg.Create(IDD_DLG_FireWork,NULL);
	m_fireworkdlg.colorEixst=false;//û�����ɹ���ɫ�Ի���

	m_atomicbombdlg.Create(IDD_DLG_AtomicBomb,NULL);

	m_snowdlg.Create(IDD_DLG_Snow,NULL);

	m_bmpdlg.Create(IDD_DLG_BMP,NULL);

	DSdlgExist=false;	//3ds �Ի��򻹲�����
}

CPrtSysView::~CPrtSysView()
{
}

BOOL CPrtSysView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	////////////////////////////////////////////////////////////////
	//���ô�������
	cs.style |=WS_CLIPCHILDREN | WS_CLIPSIBLINGS;
	////////////////////////////////////////////////////////////////
	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CPrtSysView drawing

void CPrtSysView::OnDraw(CDC* pDC)
{
	CPrtSysDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	//////////////////////////////////////////////////////////////////
	RenderScene();	//��Ⱦ����
	//////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////
// CPrtSysView printing

BOOL CPrtSysView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CPrtSysView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CPrtSysView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CPrtSysView diagnostics

#ifdef _DEBUG
void CPrtSysView::AssertValid() const
{
	CView::AssertValid();
}

void CPrtSysView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPrtSysDoc* CPrtSysView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPrtSysDoc)));
	return (CPrtSysDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPrtSysView message handlers

int CPrtSysView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	//////////////////////////////////////////////////////////////////
	//��ʼ��OpenGL�����ö�ʱ��
	m_pDC = new CClientDC(this);
	SetTimer(1, 20, NULL);
	InitializeOpenGL(m_pDC);
	//////////////////////////////////////////////////////////////////
	Init();	
	return 0;
}

void CPrtSysView::OnDestroy() 
{
	CView::OnDestroy();
	
	// TODO: Add your message handler code here
	/////////////////////////////////////////////////////////////////
	//ɾ����ɫ�����Ⱦ�����ġ���ʱ��
	::wglMakeCurrent(0,0);
	::wglDeleteContext( m_hRC);
	if (m_hPalette)
	    DeleteObject(m_hPalette);
	if ( m_pDC )
	{
		delete m_pDC;
	}
	KillTimer(1);		
	/////////////////////////////////////////////////////////////////
}


void CPrtSysView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	/////////////////////////////////////////////////////////////////
	//��Ӵ�������ʱ��ͼ�α任����
	glViewport(0,0,cx,cy);
	GLdouble aspect_ratio;
	aspect_ratio = (GLdouble)cx/(GLdouble)cy;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(40.0F, aspect_ratio, 1.0F, 10000.0F);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	/////////////////////////////////////////////////////////////////
}


void CPrtSysView::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	/////////////////////////////////////////////////////////////////
	//��Ӷ�ʱ����Ӧ�����ͳ������º���
	Invalidate(FALSE);	
	/////////////////////////////////////////////////////////////////
	CView::OnTimer(nIDEvent);
}

/////////////////////////////////////////////////////////////////////
//	                  �����߼���ɫ��
//////////////////////////////////////////////////////////////////////
void CPrtSysView::SetLogicalPalette(void)
{
    struct
    {
        WORD Version;
        WORD NumberOfEntries;
        PALETTEENTRY aEntries[256];
    } logicalPalette = { 0x300, 256 };

	BYTE reds[] = {0, 36, 72, 109, 145, 182, 218, 255};
	BYTE greens[] = {0, 36, 72, 109, 145, 182, 218, 255};
	BYTE blues[] = {0, 85, 170, 255};

    for (int colorNum=0; colorNum<256; ++colorNum)
    {
        logicalPalette.aEntries[colorNum].peRed =
            reds[colorNum & 0x07];
        logicalPalette.aEntries[colorNum].peGreen =
            greens[(colorNum >> 0x03) & 0x07];
        logicalPalette.aEntries[colorNum].peBlue =
            blues[(colorNum >> 0x06) & 0x03];
        logicalPalette.aEntries[colorNum].peFlags = 0;
    }

    m_hPalette = CreatePalette ((LOGPALETTE*)&logicalPalette);
}

//////////////////////////////////////////////////////////
//						��ʼ��openGL����
//////////////////////////////////////////////////////////
BOOL CPrtSysView::InitializeOpenGL(CDC* pDC)
{
	m_pDC = pDC;
	SetupPixelFormat();
	//���ɻ���������
	m_hRC = ::wglCreateContext(m_pDC->GetSafeHdc());
	//�õ�ǰ����������
	::wglMakeCurrent(m_pDC->GetSafeHdc(), m_hRC);
	//*************************************************************************
	glClearDepth(1.0f);									// ������Ȼ���
	glDisable(GL_ALPHA_TEST);							// ����Alpha����
	glEnable(GL_DEPTH_TEST);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);	// ������ϸ��͸������
	glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);				// Really Nice Point Smoothing

	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// ��ɫ����
	glShadeModel(GL_SMOOTH);							// ������Ӱƽ��


	GLfloat ambientLight[] = { 0.3f, 0.3f, 0.3f, 1.0f};
	GLfloat diffuseLight[] = { 0.3f, 0.3f, 0.3f, 1.0f};
	GLfloat specularLight[] = {1.0,1.0,1.0,1.0};
	GLfloat lightPos[]     = {6000.0f,6000.0f,6000.0f, 1.0f};
	GLfloat lightPos1[]     = {-300.0f,300.0f,300.0f, 1.0f};

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

	glLightfv(GL_LIGHT1, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT1, GL_SPECULAR, specularLight);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);


	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
	
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	//**********************************************************************
	return TRUE;
}

//////////////////////////////////////////////////////////
//						�������ظ�ʽ
//////////////////////////////////////////////////////////
BOOL CPrtSysView::SetupPixelFormat()
{
	PIXELFORMATDESCRIPTOR pfd = { 
	    sizeof(PIXELFORMATDESCRIPTOR),    // pfd�ṹ�Ĵ�С 
	    1,                                // �汾�� 
	    PFD_DRAW_TO_WINDOW |              // ֧���ڴ����л�ͼ 
	    PFD_SUPPORT_OPENGL |              // ֧�� OpenGL 
	    PFD_DOUBLEBUFFER,                 // ˫����ģʽ 
	    PFD_TYPE_RGBA,                    // RGBA ��ɫģʽ 
	    24,                               // 24 λ��ɫ��� 
	    0, 0, 0, 0, 0, 0,                 // ������ɫλ 
	    0,                                // û�з�͸���Ȼ��� 
	    0,                                // ������λλ 
	    0,                                // ���ۼӻ��� 
	    0, 0, 0, 0,                       // �����ۼ�λ 
	    32,                               // 32 λ��Ȼ���     
	    0,                                // ��ģ�建�� 
	    0,                                // �޸������� 
	    PFD_MAIN_PLANE,                   // ���� 
	    0,                                // ���� 
	    0, 0, 0                           // ���Բ�,�ɼ��Ժ������ģ 
	}; 	
	int pixelformat;
	pixelformat = ::ChoosePixelFormat(m_pDC->GetSafeHdc(), &pfd);//ѡ�����ظ�ʽ
	::SetPixelFormat(m_pDC->GetSafeHdc(), pixelformat, &pfd);	//�������ظ�ʽ
	if(pfd.dwFlags & PFD_NEED_PALETTE)
		SetLogicalPalette();	//�����߼���ɫ��
	return TRUE;
}

//����ʾ�Ķ����ٴ˵���
//////////////////////////////////////////////////////////
//						������������Ⱦ
//////////////////////////////////////////////////////////
BOOL CPrtSysView::RenderScene() 
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//�۾����ӵ㣡������
	gluLookAt(m_camera.eyePos[0],m_camera.eyePos[1],m_camera.eyePos[2], 
				m_camera.target[0],m_camera.target[1],m_camera.target[2], 
				m_camera.eyeUp[0], m_camera.eyeUp[1], m_camera.eyeUp[2]);

	if(cross)DrawAxis();//��������

	Draw3ds(); //��3D����
	SwapBuffers(m_pDC->GetSafeHdc());		//����������
	return TRUE;
}

//////////////////////////////////////////////////////////
//							DrawAxis()
//////////////////////////////////////////////////////////
void CPrtSysView::DrawAxis()
{
	float len=10.0;
	glBegin( GL_LINES);
			// x��		(��ɫ)
			glColor3f(1.0F, 0.0F, 0.0F);
			glVertex3f(-len, 0.0f, 0.0f);
			glVertex3f( len, 0.0f, 0.0f);
			glVertex3f( len-0.5, 0.5f, 0.0f);
			glVertex3f( len, 0.0f, 0.0f);
			glVertex3f( len-0.5,-0.5f,-0.0f);
			glVertex3f( len, 0.0f, 0.0f);

			glColor3f(1.0F, 1.0F, 0.0F);//����X��
			glVertex3f( len,		0.0f,		0.0f);
			glVertex3f( len+1.0f,	1.0f,		0.0f);
			glVertex3f( len+1.0f,	0.0f,		0.0f);
			glVertex3f( len,		1.0f,		0.0f);

			
			// y��		����ɫ��
			glColor3f(0.0F, 1.0F, 0.0F);
			glVertex3f( 0.0f, -len, 0.0f);
			glVertex3f( 0.0f,  len, 0.0f);
			glVertex3f(-0.5f,  len-0.5f, 0.0f);
			glVertex3f( 0.0f,  len, 0.0f);
			glVertex3f( 0.5f,  len-0.5f, 0.0f);
			glVertex3f( 0.0f,  len, 0.0f);

			glColor3f(1.0F, 1.0F, 0.0F);//����Y��
			glVertex3f( 0.0f,	len,		0.0f);
			glVertex3f( 0.0f,	len+0.5f,	0.0f);
			glVertex3f( 0.0f,	len+0.5f,	0.0f);
			glVertex3f( 0.5f,	len+1.0f,	0.0f);
			glVertex3f( 0.0f,	len+0.5f,	0.0f);
			glVertex3f( -0.5f,	len+1.0f,	0.0f);

			// z��		����ɫ��
			glColor3f(0.0F, 0.0F, 1.0F);
			glVertex3f( 0.0f, 0.0f, -len);
			glVertex3f( 0.0f, 0.0f,  len);
			glVertex3f(-0.5f, 0.0f,  len-0.5f);
			glVertex3f( 0.0f, 0.0f,  len);
			glVertex3f( 0.5f, 0.0f,  len-0.5f);
			glVertex3f( 0.0f, 0.0f,  len);

			glColor3f(1.0F, 1.0F, 0.0F);//����Z��
			glVertex3f( 0.0f,	0.0f,		len);
			glVertex3f( 1.0f,	0.0f,		len);
			glVertex3f( 0.0f,	0.0f,		len);
			glVertex3f( 1.0f,	1.0f,		len);
			glVertex3f( 1.0f,	1.0f,		len);
			glVertex3f( 0.0f,	1.0f,		len);

			///////////////////////////////////////
			//������
			glColor3f(1.0F, 0.0F, 1.0F);
			for(int i=0;i<=10;i++)
			{
				glVertex3f( -len,	0.0f,	len/5.0*i-len);
				glVertex3f( len,	0.0f,	len/5.0*i-len);

				glVertex3f( len/5.0*i-len,	0.0f,	-len);
				glVertex3f( len/5.0*i-len,	0.0f,	len);
			}


	glEnd();
}

//////////////////////////////////////////////////////////
//	��ʾ��������ʾ���еĶ���
//////////////////////////////////////////////////////////
void CPrtSysView::Draw3ds()
{
	if(!demoPlay)
	{
		if (m_3dsLoaded) //3DSģ�͵���ʾ,������ʾ�ֶ�����ʱ����ʾ
		{

			m_3dsobj.Draw(m_3dsDD.IsLine
				,m_3dsDD.scale
				,m_3dsDD.hide
				,m_3dsDD.t_data
				,m_3dsDD.r_data);
		}
		m_particleControl.draw(m_camera,m_ptrCtrl);	//��ʾ���ӣ����õ�ǰ�����
	}
	else
	{
		bool t=true;
		m_Demo_Bit->draw(m_camera,t,DemoAutoFinish);
	}
	if((demoPlay)&&(DemoAutoFinish))//�����ʾ�Զ�����
	{
		delete m_Demo_Bit;//ɾ����ʾ��
		demoPlay=false;		
		ShowCursor(TRUE);		//�����ָ��
		cross=true;				//��������
		glClearColor(0,0,0,0.5);		//�����Ļ
		ExitFullScreen();//�˳�ȫ��
		ScreenData.IsFullScreen=false;
	}


}

/////////////////////////////////////////////////////////
//							��ʼ����ʾ����
/////////////////////////////////////////////////////////
void CPrtSysView::Init(GLvoid)
{

	m_3dsLoaded  = FALSE;
	m_camera.InitCamera();//��ʼ�������

	mouseprevpoint.x = 0;
	mouseprevpoint.y = 0;
	mouserightdown = FALSE;
	mouseleftdown = FALSE;
	m_particleControl.GetInitInfo();	//����ϵͳ��ʼ����ʼ
	
}

/////////////////////////////////////////////////////////////
//ȫ����ʾ
////////////////////////////////////////////////////////////
void CPrtSysView::OnFullscreen() 
{
	// TODO: Add your command handler code here
	DEVMODE dmSettings;								

	memset(&dmSettings,0,sizeof(dmSettings));		

	if(!EnumDisplaySettings(NULL,ENUM_CURRENT_SETTINGS,&dmSettings))
	{
		MessageBox(/*NULL, */"Could Not Enum Display Settings", "Error", MB_OK);
		return;
	}
			CMainFrame* pFrame = (CMainFrame*) AfxGetApp()->m_pMainWnd;

			dmSettings.dmPelsWidth	= ScreenData.Width;//640;//SCREEN_WIDTH;		
			dmSettings.dmPelsHeight	= ScreenData.Height;//480;//SCREEN_HEIGHT;	
				//��ȡ��ǰ��Ļ�ķֱ��� 
				pFrame->OLDWidth=GetSystemMetrics(SM_CXSCREEN); 
				pFrame->OLDHeight=GetSystemMetrics(SM_CYSCREEN); 

			int result = ChangeDisplaySettings(&dmSettings,CDS_FULLSCREEN);	

			if(result != DISP_CHANGE_SUCCESSFUL)
			{

				MessageBox(/*NULL, */ "Display Mode Not Compatible", "Error", MB_OK);
				PostQuitMessage(0);
			}
				// ȫ����ʾ
		pFrame->FullScreen();
	/////////////////////////////////////////////////////////////////
	//��Ӵ�������ʱ��ͼ�α任����
	glViewport(0,0,dmSettings.dmPelsWidth,dmSettings.dmPelsHeight);
	/////////////////////////////////////////////////////////////////
	GLdouble aspect_ratio;
	aspect_ratio = (GLdouble)dmSettings.dmPelsWidth/(GLdouble)dmSettings.dmPelsHeight;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(40.0F, aspect_ratio, 1.0F, 10000.0F);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	ScreenData.IsFullScreen=true;
}

/////////////////////////////////////////////////////////////////////////
//			�˳�ȫ��
/////////////////////////////////////////////////////////////////////////
void CPrtSysView::ExitFullScreen()
{
		DEVMODE dmSettings;								

	memset(&dmSettings,0,sizeof(dmSettings));		

	if(!EnumDisplaySettings(NULL,ENUM_CURRENT_SETTINGS,&dmSettings))
	{
		MessageBox(/*NULL, */"Could Not Enum Display Settings", "Error", MB_OK);
		return;
	}
	CMainFrame* pFrame = (CMainFrame*) AfxGetApp()->m_pMainWnd;

	dmSettings.dmPelsWidth	= pFrame->OLDWidth;//SCREEN_WIDTH;		
	dmSettings.dmPelsHeight	= pFrame->OLDHeight;//SCREEN_HEIGHT;
	
	int result = ChangeDisplaySettings(&dmSettings,CDS_FULLSCREEN);	

	if(result != DISP_CHANGE_SUCCESSFUL)
	{
		MessageBox(/*NULL, */ "Display Mode Not Compatible", "Error", MB_OK);
		PostQuitMessage(0);
	}

	// �ָ�������ʾ
	pFrame->ShowWithWindows();
}



/////////////////////////////////////////////////////////////////////////
//			��ESC�˳�ȫ��
/////////////////////////////////////////////////////////////////////////
void CPrtSysView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	if (nChar == VK_ESCAPE)
	{
		if(ScreenData.IsFullScreen)
		{ExitFullScreen();//�˳�ȫ��
		ScreenData.IsFullScreen=false;
		}
		if(demoPlay)
		{
		delete m_Demo_Bit;//ɾ����ʾ��
		demoPlay=false;
		ShowCursor(TRUE);			//�����ָ��
		cross=true;					//��������
		DemoAutoFinish=false;
		m_camera.InitCamera();
		glClearColor(0,0,0,0.5);		//�����Ļ
		}
	}

	CView::OnKeyUp(nChar, nRepCnt, nFlags);
}



//////////////////////////////////////////////////////////////////////////////
//				������ϵ��
//////////////////////////////////////////////////////////////////////////////
void CPrtSysView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	SetCapture( );
	SetCursor(AfxGetApp()->LoadCursor(IDC_ROT));
	mouseleftdown = TRUE;
	mouseprevpoint.x = point.x;
	mouseprevpoint.y = point.y;	
	CView::OnLButtonDown(nFlags, point);
	CView::OnLButtonDown(nFlags, point);
}

void CPrtSysView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	ReleaseCapture( );
	mouseleftdown = FALSE;
	CView::OnLButtonUp(nFlags, point);
}

//˫���ӽǻ�ԭ
void CPrtSysView::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	m_camera.InitCamera();//��ʼ�������
	RenderScene();
	CView::OnLButtonDblClk(nFlags, point);
}

void CPrtSysView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	SetCapture( );
	SetCursor(AfxGetApp()->LoadCursor(IDC_MAGNIFI));
	mouserightdown = TRUE;
	mouseprevpoint.x = point.x;
	mouseprevpoint.y = point.y;
	CView::OnRButtonDown(nFlags, point);
}

void CPrtSysView::OnRButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	ReleaseCapture( );
	mouserightdown = FALSE;
	CView::OnRButtonUp(nFlags, point);
}

//�����ֿ������쾵ͷ����ʵ���Ҽ�һ����
BOOL CPrtSysView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{
	// TODO: Add your message handler code here and/or call default
	SetCursor(AfxGetApp()->LoadCursor(IDC_WHEEL));
	m_camera.SetEyeRadius(zDelta/5.0);
	return CView::OnMouseWheel(nFlags, zDelta, pt);
}


//����ƶ����ƺ���
void CPrtSysView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	//�����������ˣ�Ӧ�ý��о�ͷ��ת����
	if(mouseleftdown)
	{

		m_camera.SetEyePos(0, (point.x - mouseprevpoint.x));
		m_camera.SetEyePos(1, (point.y - mouseprevpoint.y)); 
	}
	else
	//����Ҽ������ˣ�Ӧ�ý��о�ͷ�������������׼target������
		if(mouserightdown)		
		{	
		//��Զ����
		m_camera.SetEyeRadius(point.y - mouseprevpoint.y);
		}
	CView::OnMouseMove(nFlags, point);

	mouseprevpoint.x = point.x;
	mouseprevpoint.y = point.y;	
}


///////////////////////////////////////////////////////////////////////////
//					���̿��ƺ���
///////////////////////////////////////////////////////////////////////////
void CPrtSysView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	m_camera.SliderCamera(nChar);//�ƶ��������

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

//�л��������桢����ʾ��
void CPrtSysView::OnFaceorline() 
{
	// TODO: Add your command handler code here
	m_3dsDD.IsLine=!m_3dsDD.IsLine;
	
}
//���ػ�����ʾ3ds����
void CPrtSysView::OnHideorshow() 
{
	// TODO: Add your command handler code here
	m_3dsDD.hide=!m_3dsDD.hide;
	if(DSdlgExist)
		m_3dsCtrlDlg.ShowWindow(SW_HIDE); 
}

//��3ds���������޸���
void CPrtSysView::OnShow3dsdlg() 
{
	// TODO: Add your command handler code here
	if((m_3dsLoaded)&&(!m_3dsDD.hide))
	{
		if(DSdlgExist==false)//���û�����ɹ�������
		{
			m_3dsCtrlDlg.Create(IDD_3dsCtrlDlg,NULL);
			DSdlgExist=true;
		}
	m_3dsCtrlDlg.ShowWindow(SW_SHOW); 
	m_3dsCtrlDlg.GetExtData(m_3dsDD);	//����������
	
	}
	else AfxMessageBox("ע�⣺����û��3DS����!");
}

//���Ż���ֹͣ���Ӷ�����
void CPrtSysView::OnPlay() 
{
	// TODO: Add your command handler code here
	m_ptrCtrl.IsPlay=!m_ptrCtrl.IsPlay;
}


//��ȫ��������ʾ�Ի����޸���ʾ������
void CPrtSysView::OnSetfullscreen() 
{
	// TODO: Add your command handler code here
		m_screen.ShowWindow(SW_SHOW);	//��ʾ
		switch(m_screen.GetScreenset())
		{
		case 3:
			ScreenData.Width=640;
			ScreenData.Height=480;
			break;
		case 2:
			ScreenData.Width=800;
			ScreenData.Height=600;
			break;
		case 1:
			ScreenData.Width=1024;
			ScreenData.Height=768;
		default:break;
		}
}

////////////////////////////////////////////////////////////////////////////
//��ʾ��������Ч��
void CPrtSysView::OnShowFire() 
{
	// TODO: Add your command handler code here
	m_ptrCtrl.p_fire=!m_ptrCtrl.p_fire;

	if(!m_ptrCtrl.p_fire)
	{
		m_firedlg.ShowWindow(SW_HIDE);	//����ı༭�Ի�����������֮����ɫ�Ի���Ҳ���ء�
		if(m_firedlg.colorEixst)m_firedlg.m_FireColor.ShowWindow(SW_HIDE);
	}
}

//������ʾ����˵�ǰ��С�Թ�
void CPrtSysView::OnUpdateShowFire(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(m_ptrCtrl.p_fire)
	{
      pCmdUI->SetCheck();
	}else
	{
      pCmdUI->SetCheck(0);
	}
}

//����򿪱༭�Ի���
void CPrtSysView::OnEditFire() 
{
	// TODO: Add your command handler code here
	if(m_ptrCtrl.p_fire)
	{
		m_firedlg.GetExtFireData(m_particleControl.m_prtFire.PDD);	//����������
		m_firedlg.ShowWindow(SW_SHOW);	//��ʾ
	}
}
//��ֹ��ʱ���Ի�����
void CPrtSysView::OnUpdateEditFire(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_ptrCtrl.p_fire);
}

/////////////////////////////////////////////////////////////////////
//�ٲ�Ч���Ĳ˵��༭
void CPrtSysView::OnShowWaterfall() 
{
	// TODO: Add your command handler code here
	m_ptrCtrl.p_waterfall=!m_ptrCtrl.p_waterfall;

	if(!m_ptrCtrl.p_waterfall)
	{
		m_waterfalldlg.ShowWindow(SW_HIDE);	//�༭�Ի�����������֮����ɫ�Ի���Ҳ���ء�
		if(m_waterfalldlg.colorEixst)m_waterfalldlg.m_ColorDLG.ShowWindow(SW_HIDE);
	}
}

void CPrtSysView::OnUpdateShowWaterfall(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(m_ptrCtrl.p_waterfall)
	{
      pCmdUI->SetCheck();
	}else
	{
      pCmdUI->SetCheck(0);
	}
}

void CPrtSysView::OnEditWaterfall() 
{
	// TODO: Add your command handler code here
	if(m_ptrCtrl.p_waterfall)
	{
		m_waterfalldlg.GetExtData(m_particleControl.m_prtWaterFall.PDD);	//����������
		m_waterfalldlg.ShowWindow(SW_SHOW);	//��ʾ
	}
}

void CPrtSysView::OnUpdateEditWaterfall(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_ptrCtrl.p_waterfall);
}

/////////////////////////////////////////////////////
//��Ч���Ĳ˵�
void CPrtSysView::OnShowFirework() 
{
	// TODO: Add your command handler code here
		m_ptrCtrl.p_firework=!m_ptrCtrl.p_firework;

	if(!m_ptrCtrl.p_firework)
	{
		m_fireworkdlg.ShowWindow(SW_HIDE);	//�༭�Ի�����������֮����ɫ�Ի���Ҳ���ء�
		if(m_fireworkdlg.colorEixst)m_fireworkdlg.m_ColorDLG.ShowWindow(SW_HIDE);
	}
	
}

void CPrtSysView::OnUpdateShowFirework(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(m_ptrCtrl.p_firework)
	{
      pCmdUI->SetCheck();
	}else
	{
      pCmdUI->SetCheck(0);
	}
}


void CPrtSysView::OnEditFirework() 
{
	// TODO: Add your command handler code here
	if(m_ptrCtrl.p_firework)
	{
		m_fireworkdlg.GetExtData(m_particleControl.m_prtFireWork.PDD);	//����������
		m_fireworkdlg.ShowWindow(SW_SHOW);	//��ʾ
	}
}

void CPrtSysView::OnUpdateEditFirework(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_ptrCtrl.p_firework);
}


///////////////////////////////////////////////////////////
//ԭ�ӵ��Ĳ˵�
void CPrtSysView::OnShowAtomicbomb() 
{
	
	// TODO: Add your command handler code here
	m_ptrCtrl.p_atomicbomb=!m_ptrCtrl.p_atomicbomb;
	
	if(!m_ptrCtrl.p_atomicbomb)
	{
		m_atomicbombdlg.ShowWindow(SW_HIDE);	//�༭�Ի�����������֮����ɫ�Ի���Ҳ���ء�
	}
	
}

void CPrtSysView::OnUpdateShowAtomicbomb(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(m_ptrCtrl.p_atomicbomb)
	{
      pCmdUI->SetCheck();
	}else
	{
      pCmdUI->SetCheck(0);
	}
}

void CPrtSysView::OnEditAtomicbomb() 
{
	// TODO: Add your command handler code here
	
	if(m_ptrCtrl.p_atomicbomb)
	{
		m_atomicbombdlg.GetExtData(m_particleControl.m_prtAtomicBomb.PDD);	//����������
		m_atomicbombdlg.ShowWindow(SW_SHOW);	//��ʾ
	}

}

void CPrtSysView::OnUpdateEditAtomicbomb(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_ptrCtrl.p_atomicbomb);
}


//////////////////////////////////////////////////////////
//ѩ�����Ʋ˵�
void CPrtSysView::OnShowSnow() 
{
	// TODO: Add your command handler code here
	m_ptrCtrl.p_snow=!m_ptrCtrl.p_snow;

	if(!m_ptrCtrl.p_snow)
	{
		m_snowdlg.ShowWindow(SW_HIDE);	//�༭�Ի�����������֮����ɫ�Ի���Ҳ���ء�
	}

}

void CPrtSysView::OnUpdateShowSnow(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_ptrCtrl.p_snow);
}

void CPrtSysView::OnEditSnow() 
{
	// TODO: Add your command handler code here

	if(m_ptrCtrl.p_snow)
	{
		m_snowdlg.GetExtData(m_particleControl.m_prtSnow.PDD);	//����������
		m_snowdlg.ShowWindow(SW_SHOW);	//��ʾ
	}

}

void CPrtSysView::OnUpdateEditSnow(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_ptrCtrl.p_snow);
}

//////////////////////////////////////////////////////////////
//�������������ʾ
void CPrtSysView::OnKwCross() 
{
	// TODO: Add your command handler code here
	cross=!cross;
}

//��ʾ����
void CPrtSysView::OnKwDemo() 
{
	// TODO: Add your command handler code here
	DemoAutoFinish=false;
	CPrt_Demo_BIT *db=new CPrt_Demo_BIT;//������ʾ��
	m_Demo_Bit=db;
	m_Demo_Bit->GetInitInfo();			//����ʾ���г�ʼ����
	ShowCursor(FALSE);					//�������ָ��
	cross=false;
	demoPlay=true;
	OnFullscreen();					//ȫ����ʾ
	ScreenData.IsFullScreen=true;
}

//�ҵĴ��ļ��Ի��򣬾ܾ�ϵͳ�Դ�
void CPrtSysView::OnKwFileopen() 
{

	// TODO: Add your command handler code here
	char szCurDir[256];//���浱ǰĿ¼
	GetCurrentDirectory(sizeof(szCurDir),szCurDir);

	CString filename;
	CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY,"3DS(*.3ds)|*.3ds||",NULL);

	if(dlg.DoModal()==IDOK)//��ʾ�ļ��Ի���
	{
		filename = dlg.GetPathName();//ȡ���ļ���
		m_3dsLoaded=m_3dsobj.LoadFile(filename);
	}
	SetCurrentDirectory(szCurDir);//�ָ���ǰ·����

}

void CPrtSysView::OnEditBmp() 
{
	// TODO: Add your command handler code here
	if(m_ptrCtrl.p_bmp)
	{
		m_bmpdlg.GetExtData(m_particleControl.m_prtBMP.PDD,&m_particleControl.m_prtBMP.BMP_FileName);	//����������
		m_bmpdlg.ShowWindow(SW_SHOW);	//��ʾ
	}
}

void CPrtSysView::OnShowBmp() 
{
	// TODO: Add your command handler code here
	m_ptrCtrl.p_bmp=!m_ptrCtrl.p_bmp;

	if(!m_ptrCtrl.p_bmp)
	{
		m_bmpdlg.ShowWindow(SW_HIDE);	//����ı༭�Ի�����������֮����ɫ�Ի���Ҳ���ء�
	}

}

void CPrtSysView::OnUpdateEditBmp(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_ptrCtrl.p_bmp);
}

void CPrtSysView::OnUpdateShowBmp(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(m_ptrCtrl.p_bmp)
	{
      pCmdUI->SetCheck();
	}else
	{
      pCmdUI->SetCheck(0);
	}
}
