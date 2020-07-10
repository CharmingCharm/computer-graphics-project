// Particle.h: interface for the CParticle class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PARTICLE_H__A617780B_5DDA_4730_951D_ECB307C8D1AF__INCLUDED_)
#define AFX_PARTICLE_H__A617780B_5DDA_4730_951D_ECB307C8D1AF__INCLUDED_


#include "glo.h"	//����ȫ���ܽṹ��
#include "cameye.h"	//�����������
#include "3dsObject.h"			// 3ds����˵����
#include <math.h>


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CParticle  
{
public:
	CParticle();
	virtual ~CParticle();
	
	void draw(float *camPos);					//��ʾ����,���õ�ǰ���λ��

	//loopΪÿ�����ӵ�Ψһ���0��MAX_PARTICLES,modelΪ����ģʽ
	void changeForce(int loop);					//�������ӵļ��ٶȣ��ٶ��ɼ��ٶȶ��ı䣩
	void changeColor(int loop,int model);		//�������ӵ���ɫ
	void changeInitParticle(int model);

	int Init(void);								//��ʼ������ϵͳ������λ�á��ٶȡ�������
												//����ReSatPrt(int loop)
	void ReSatPrt(int loop){};					//�����ʼ���ٶȵȵ�

	AUX_RGBImageRec *LoadBMP(char *Filename);					//����ͼ�ļ��������ؾ��
	int		LoadGLTextures(char *Filename,GLuint &texture);		//��texture���ʸ���Filename��ͼ
	void	GetInitInfo(void);									//��ó�ʼ������


	//���Ӷ�׼�������ͼ����ת������
	void ExchangeShowXYZ(float *CameraPos,float x,float y,float z,float ADDwidth);
	float			ParShowXYZ[4][3];	//���ӵ���ʾ��ͼ���꣬��ƽ��ʼ�մ�ֱ���������0��1��2��3�ĵ㣩
	particleModel	particle[10000];
	GLuint			texture[8];			//���ӵĲ��ʣ���֧��8��
	int				Particle_type;		//���ӵ�����
	char			TextFileName[250];	//������ͼ���ļ���
	GLuint	loop;						// ÿ�����ӵ�Ψһ���
	DlgData_PRT		PDD;				//�������Ի������ݵĽṹ��

	//////////////////////////
	//�������ֵ
	//////////////////////////
	float	speed;					// ���ӵ��ٶȣ���speedMax��speedMin֮�䣩
	float	ay;						// �ٶ�������Y��ļн�(0~AngleY)
	float	axz;					// �ٶ�������XZƽ����X�ļн�(0~AngleXZ)

};


//�̻���
class CPrt_Fire:public CParticle
{
public:
	CPrt_Fire();
	virtual ~CPrt_Fire();
	void	draw(float *camPos,bool Isplay);		//��ʾ����
	//loopΪÿ�����ӵ�Ψһ���0��MAX_PARTICLES,modelΪ����ģʽ
	void	changeForce(int loop);					//�������ӵļ��ٶȣ��ٶ��ɼ��ٶȶ��ı䣩
	void	changeColor(int loop);					//�������ӵ���ɫ
	int		Init(void);								//��ʼ������ϵͳ������λ�á��ٶȡ�������
	void	ReSatPrt(int loop);
	int		LoadGLTextures(void);					//��������ͼ
	void	GetInitInfo(void);						//��ó�ʼ������
	void	InitColor(void);						//��ʼ�����ӵ���ɫ
};


//�ٲ���
class CPrt_WaterFall:public CParticle
{
public:
	CPrt_WaterFall();
	virtual ~CPrt_WaterFall();
	void	draw(float *camPos,bool Isplay);	//��ʾ����
	//loopΪÿ�����ӵ�Ψһ���0��MAX_PARTICLES,modelΪ����ģʽ
	void	changeForce(int loop);				//�������ӵļ��ٶȣ��ٶ��ɼ��ٶȶ��ı䣩
	void	changeColor(int loop);				//�������ӵ���ɫ
	int		Init(void);							//��ʼ������ϵͳ������λ�á��ٶȡ�������
	void	ReSatPrt(int loop);					//�����ʼ���ٶȵȵ�
	int		LoadGLTextures(void);				//��������ͼ
	void	GetInitInfo(void);					//��ó�ʼ������
	void	InitColor(void);					//��ʼ�����ӵ���ɫ
};




//////////////////////////////////////////////////////////////////////////////////////
//��ը����
//////////////////////////////////////////////////////////////////////////////////////
class CPrt_ExplodePRT
{
public:
	CPrt_ExplodePRT();	//���캯��
	virtual ~CPrt_ExplodePRT();

	//��ʾ����,���õ�ǰ���λ��,ע�����ǰ�ĵ���ʾ������ͬ��
	//��Ϊ����Ҳ�Ƕ��ڸ�����Դ��˵Ҳ��һ�����ӣ�����������ʾҪ�������������ء�
	void draw(float *camPos,bool Isplay,float selflife);

	//loopΪÿ�����ӵ�Ψһ���0��MAX_PARTICLES,modelΪ����ģʽ
	void changeForce(int loop);					//�������ӵļ��ٶȣ��ٶ��ɼ��ٶȶ��ı䣩

	//�������ӵ���ɫ,���������Լ���������С���ӵ������йأ�������������Դ���������
	void changeColor(int loop,float selflife);	

	int Init(void);								//��ʼ������ϵͳ������λ�á��ٶȡ�������
	void ReSatPrt(int loop);
	void	GetInitInfo(void);

	//���Ӷ�׼�������ͼ����ת������
	void ExchangeShowXYZ(float *CameraPos,float x,float y,float z,float ADDwidth);
	float ParShowXYZ[4][3];				//���ӵ���ʾ��ͼ���꣬��ƽ��ʼ�մ�ֱ���������0��1��2��3�ĵ㣩
	particleModel particle[1500];
	GLuint	loop;						// ÿ�����ӵ�Ψһ���
	GLuint	*texture[5];				//���ӵĲ���


	DlgData_PRT		PDD;				//�������Ի������ݵĽṹ��
	//////////////////////////
	//�������ֵ
	//////////////////////////
	float	speed;					// ���ӵ��ٶȣ���speedMax��speedMin֮�䣩

	//����Դ������
	bool	active;					// �Ƿ���ţ�Active (Yes/No)
	float	life;					// ���ӵ�������Particle Life
	float	fade;					// ���ӵ���ɫ�ٶ�Fade Speed����ʵ����Lifeÿ�εļ�����

	//����Դ���˶�����
	float	xi;	
	float	yi;
	float	zi;

	//����Դ����������
	float	xg;
	float	yg;
	float	zg;
};

///////////////////////////////////////////////
//��ը��(���Ǳ�ը����)
///////////////////////////////////////////////
class CPrt_Explode
{
public:
	CPrt_Explode();	//���캯��
	virtual ~CPrt_Explode();
	void GetInitInfo(void);						//��ó�ʼ������
	void draw(float *camPos,bool Isplay);		//��ʾ����
	void changeForce(int loop);					//�������ӵļ��ٶȣ��ٶ��ɼ��ٶȶ��ı䣩
	int Init(void);								//��ʼ������ϵͳ������λ�á��ٶȡ�������
	void ReSatPrt(int loop);
	GLuint	loop;								// ÿ�����ӵ�Ψһ���
	CPrt_ExplodePRT	explodePar[200];			//���֧��200��С�ı�ը����Դ
	AUX_RGBImageRec * CPrt_Explode::LoadBMP(char *Filename);
	int LoadGLTextures(void);									//��������ͼ
	int LoadTextures(char *Filename,GLuint &texture);			//��������ͼ
	GLuint	texture[5];							//���ӵĲ���

	DlgData_PRT		PDD;						//�������Ի������ݵĽṹ��
	//���������
	float speed;				//��ɫģʽ��
	

};


//////////////////////////////////////////////////
//���࣬�̳б�ը�ࡣ
//////////////////////////////////////////////////
class CPrt_FireWork:public CPrt_Explode
{
public:
	CPrt_FireWork();	//���캯��
	virtual ~CPrt_FireWork();
	void GetInitInfo(void);						//��ó�ʼ������
	void draw(float *Tar2Cam,bool Isplay);		//��ʾ����
};


///////////////////////////////////////////////////////////////
//ԭ�ӵ�Ч���ࣨ���ࣩ
///////////////////////////////////////////////////////////////

//*********************
//��������-Ϊԭ�ӵ��Ĵ�����
//*********************
class CPrt_AB_GroudShockWave:public CParticle
{
public:
	CPrt_AB_GroudShockWave(){};			//���캯��
	virtual ~CPrt_AB_GroudShockWave(){};

	int Init(void);							//��ʼ������ϵͳ������λ�á��ٶȡ�������
	void draw(float *Tar2Cam,bool Isplay);				//��ʾ����
	int LoadGLTextures(void);				//��������ͼ
	void changeColor(int loop,int model);	//������ɫ
	float	GWspeed[5000];	//ÿһ�����ӵ��ٶȡ�
};

//*********************
//�ײ���Ϊԭ�ӵ��Ĵ�����
//*********************
class CPrt_AB_BaseWave:public CParticle
{
public:
	CPrt_AB_BaseWave(){};	//���캯��
	virtual ~CPrt_AB_BaseWave(){};

	int Init(void);							//��ʼ������ϵͳ������λ�á��ٶȡ�������
	void draw(float *Tar2Cam,bool Isplay);				//��ʾ����
	int LoadGLTextures(void);				//��������ͼ
	void changeColor(int loop,int model);	//������ɫ
	void ExchangeShowXYZ(float x,float y,float z,float a);//ת����ͼ����
	float prtAngle[10000];					//���ÿһ��������ͼ�ĽǶ�
};

//*********************
//���ˣ�Ϊԭ�ӵ��Ĵ�����
//*********************
class CPrt_AB_BombCore:public CParticle
{
public:
	CPrt_AB_BombCore(){};	//���캯��
	virtual ~CPrt_AB_BombCore(){};

	int Init(void);							//��ʼ������ϵͳ������λ�á��ٶȡ�������
	void draw(float *Tar2Cam,bool Isplay);				//��ʾ����
	int LoadGLTextures(void);				//��������ͼ
	void changeColor(int loop,int model);	//������ɫ
	void changeForce(int loop);				//�ı�����
	float core_y;	//�˵�Y����
	float corei;	//�˵��ٶ� Y��
	float coreg;	//�˵ļ��ٶ� Y��

	float prtAy[5000];		//���ӵĽǶ� Y��
	float prtAxz[5000];		//XZƽ��

	float a[5000];			//������������뾶
};

//*********************
//������Ϊԭ�ӵ��Ĵ�����
//*********************
class CPrt_AB_BombCircle:public CParticle
{
public:
	CPrt_AB_BombCircle(){};	//���캯��
	virtual ~CPrt_AB_BombCircle(){};

	int Init(void);							//��ʼ������ϵͳ������λ�á��ٶȡ�������
	void draw(float *Tar2Cam,bool Isplay);				//��ʾ����
	int LoadGLTextures(void);				//��������ͼ
	void changeColor(int loop,int model);	//������ɫ
};

//*********************
//������Ϊԭ�ӵ��Ĵ�����
//*********************
class CPrt_AB_BombColumn:public CParticle
{
public:
	CPrt_AB_BombColumn(){};	//���캯��
	virtual ~CPrt_AB_BombColumn(){};

	int Init(void);							//��ʼ������ϵͳ������λ�á��ٶȡ�������
	void draw(float *Tar2Cam,bool Isplay);				//��ʾ����
	int LoadGLTextures(void);				//��������ͼ
	void changeColor(int loop,int model);	//������ɫ
};


//##################################################
//ԭ�ӵ�����ʵ�࣭������ʵ�����յ�Ч��
//##################################################
class CPrt_AtomicBomb
{
public:
	CPrt_AtomicBomb();	//���캯��
	virtual ~CPrt_AtomicBomb();

	void GetInitInfo(void);						//��ó�ʼ������
	void draw(float *Tar2Cam,bool Isplay);		//��ʾ����
	void Init(void);							//��ʼ������
	int LoadGLTextures(void);					//��������ͼ

	//--------------------------------------------------------
	DlgData_PRT		PDD;			//�������Ի������ݵĽṹ��
	//-------------------------------------------------------

	//�������ʵ������
	CPrt_AB_GroudShockWave	kw_GroudShockWave;	//��������
	CPrt_AB_BaseWave		kw_BaseWave;		//�ײ�
	CPrt_AB_BombCore		kw_BombCore;		//����
	CPrt_AB_BombCircle		kw_BombCircle;		//����
	CPrt_AB_BombColumn		kw_BombColumn;		//����

	//-----------------------------------------------------
	//��Ļ������,������Ļ������
	float screenLife;	//���Ϊ1����СΪ0
	float screenLifeFate;//����������
};

//*****************************************************************
//ѩ���ࡪ��ʵ����ѩ�������Ч��
//*****************************************************************
class CPrt_Snow:public CParticle
{
public:
	CPrt_Snow();	//���캯��
	virtual ~CPrt_Snow();

	int Init(void);								//��ʼ������ϵͳ������λ�á��ٶȡ�������
	void draw(float *camPos,bool Isplay);		//��ʾ����
	//loopΪÿ�����ӵ�Ψһ���0��MAX_PARTICLES,modelΪ����ģʽ
	void changeForce(int loop);					//�������ӵļ��ٶȣ��ٶ��ɼ��ٶȶ��ı䣩
	void changeColor(int loop);		//�������ӵ���ɫ
	void changeInitParticle(int model);
	void ReSatPrt(int loop);
	int LoadGLTextures(void);					//��������ͼ
	void GetInitInfo(void);						//��ó�ʼ������
	//���������Ӷ�׼�������ͼ����ת������
	void RainExchangeShowXYZ(float *CameraPos,float x,float y,float z,float ADDwidth);

	float PrtSnowAngle[10000];					//�������ÿ��ѩ�����ӵ���Ҷõ���ߵ�ת���Ƕ�
	float PrtSnowRadius[10000];					//�������ÿ��ѩ�����ӵ���Ҷõ���ߵİ뾶a
	float oldHeight;							//�������ѩ��ԭ���ĸ߶ȣ����߶ȱ��ʱ��Ҫ������������
	float oldnum;							//��Ҷõ���߽Ƕȵ�����,ʹ��PDD.pram[0]������
};

/////////////////////////////////////////////////////////////////////////
//		��������ʾ��Ч�ĸ��࣬һ�㲻�߱��ɲٿ�����
///////////////////////////////////////////////////////////////////////////
//С������
class CPrt_Missile  
{
public:
	CPrt_Missile(){};
	virtual ~CPrt_Missile(){};
	void Init(void);						//��ʼ��
	
	//��ʾ��������������
	void draw(float *Tar2Cam,bool &Isplay,float x,float y,float z);	
	void drawModel(void);//������ģ��

	CPrt_Fire			RearFire;		//β��
	float pos[3];//λ��
	float speed[3];//�ٶȣ��������ʾ��ֻ���õ�X����ٶ�
};


///////////////////////////////////////////////
//		��ʾ��������
///////////////////////////////////////////////
class CPrt_Demo_BIT:public CParticle
{
public:
	CPrt_Demo_BIT();	//���캯��
	virtual ~CPrt_Demo_BIT();

	void Init(void);							//��ʼ������ϵͳ
	void InitGraphic(void);						//��ʼ��ͼ��λͼ

	//============================================================
	//��ʾ�Ŀ���
	void draw(CCamEye &camera,bool &Isplay,bool &DemoAutoFinish);		//����֡���ܿ���ʾ���ӣ�����������������л���ͷ
	void draw_BITlogo(float *Tar2Cam,bool &Isplay);		//��ʾBITlogo

	//�����ļ���ʾλͼ,������BMP�ļ�������ʼ֡���������ȣ�֡����
	void draw_PrtBMP(float *Tar2Cam,bool &Isplay);//��ʾ��ǰ�����λͼ
	void draw_world(void);//�������

	//=======================================================
	//����Ч����ʼ��
	void Init_BITlogo(void);				//��ʼ��BITlogo��
	void Init_Plane(void);					//��ʼ���ɻ��������
	void Init_FireWork(void);				//��ʼ����

	//loopΪÿ�����ӵ�Ψһ���0��MAX_PARTICLES,
	void ReSatPrt(int loop);
	int LoadGLTextures(void);				//��������ͼ
	void GetInitInfo(void);					//��ó�ʼ������
	void Read_TXT_Graph(void);				//��ȡTXT�ļ����λͼ��Ϣ
	bool Read_BMP_Graph(char *BMPFileName);	//��ȡBMP�ļ����λͼ��Ϣ Ŀǰֻ֧��128*128 24bit λͼ
											//�ɹ�����true
	//bool Read_BMP_Graph(LPCTSTR lpszPathName);
	void GenRandGXGY(void);					//����һ�Ե������ʾ����GX��GY

	//================================================================
	//ͼ����������������֧��256��256���� 24��ɫ��
	int Graphic_1[256][256];				//256*256�����λͼ
	int GX,GY;								//����ʾ�ĵ�������
	int width,height;						//ͼ��Ŀ�Ⱥ͸߶�

	CPrt_ExplodePRT	explodePar[4];			//���֧��4��С���ǡ�
	float	ex_Rot[4][2];					//��¼�ĸ�С���ǵ�ת���Ƕ�,�ͷ���
	int		ret[4];							//С���ǵ��˶�����

	//==============================================================
	//��Ļ��ʾ����
	unsigned int FrameCount;				//��Ļ֡�����ƴ�0��ʼ
	unsigned int FrameENDCount;				//����֡
	float	Tar2Cam[3];						//��Ŀ��ָ��������ķ�������λ��
	bool	CartoonEnd;						//��ʾ�Ƿ�������Զ���ʾ��ɲŽ���
	//===================================================
	//���Ӷ���
	CPrt_Fire			Demo_Fire;			//������ʵ�ַɻ���β��
	CPrt_Missile		Demo_Missile[6];	//�����࣬��Ϊһ������
	CPrt_AtomicBomb		Demo_AtomicBomb;	//ԭ�ӵ���
	CPrt_FireWork		Demo_FireWork[2];	//����
	//===================================================
	//3DS���壬��Ҫ�Ƿɻ���
	C3dsObject	Demo_3DSobj;		//3DS�������,��ȡF16�ɻ�
	BOOL		D_IsLine;			//3DS��������������
	float		D_scale;
	BOOL		D_hide;
	TraData		D_t_data;
	RotData		D_r_data;
	GLuint		WorldTexture[6];	//������ͼ����Ҫ����͵أ�0Ϊ�ء�1234Ϊ���ܵ��죬5Ϊ������
};
////////////////////////////////////////////



//Bmp����λͼ��
class CPrt_BMP:public CParticle
{
public:
	CPrt_BMP();
	virtual ~CPrt_BMP();
	void	draw(float *camPos,bool Isplay);		//��ʾλͼ����
	void	changeForce(int loop);					//�������ӵļ��ٶȣ��ٶ��ɼ��ٶȶ��ı䣩
	void	ReSatPrt(int loop);
	int		LoadGLTextures(void);					//��������ͼ
	int		Init(void);								//��ʼ������ϵͳ������λ�á��ٶȡ�������
	void	GetInitInfo(void);						//��ó�ʼ������

	bool Read_BMP_Graph(char *BMPFileName);	//��ȡBMP�ļ����λͼ��Ϣ Ŀǰֻ֧��128*128 24bit λͼ
											//�ɹ�����true
	void GenRandGXGY(void);					//����һ�Ե������ʾ����GX��GY

	//================================================================
	//ͼ����������������֧��256��256���� 24��ɫ��
	int Graphic_1[256][256];				//256*256�����λͼ
	int GX,GY;								//����ʾ�ĵ�������
	int width,height;						//ͼ��Ŀ�Ⱥ͸߶�
	char BMP_FileName[256];					//ͼ���ļ���

};

////////////////////////////////////////////

//ʹ��Ҫ�����к󣡣�
//���ӿ����࣬Ҳ����������ͳһ�������е�����ϵͳ������ͽ���ӿ�
class CParticleControl
{
public:
	CParticleControl(){}
	virtual ~CParticleControl(){}
	void	GetInitInfo(void);					//��ó�ʼ������
	void	draw(CCamEye &camera,Dlg_PRT_Control	&ptrCtrl);		//��ʾ����,ʹ�õ�ǰ�����
	float	Tar2Cam[3];							//��Ŀ��ָ��������ķ�������λ��
	CPrt_Fire			m_prtFire;			//������
	CPrt_WaterFall		m_prtWaterFall;		//�ٲ���
	CPrt_FireWork		m_prtFireWork;		//����
	CPrt_AtomicBomb		m_prtAtomicBomb;	//ԭ�ӵ���
	CPrt_Snow			m_prtSnow;			//ѩ��
	CPrt_BMP			m_prtBMP;			//λͼ������
};




#endif // !defined(AFX_PARTICLE_H__A617780B_5DDA_4730_951D_ECB307C8D1AF__INCLUDED_)
