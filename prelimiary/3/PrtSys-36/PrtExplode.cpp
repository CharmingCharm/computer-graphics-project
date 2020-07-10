#include "stdafx.h"
#include "PrtSys.h"
#include "Particle.h"
#include <math.h>
#include "glo.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif



CPrt_Explode::CPrt_Explode()
{
}
CPrt_Explode::~CPrt_Explode()
{
}


//��ʼ����ը����
void CPrt_Explode::GetInitInfo()
{
	PDD.MAX_PARTICLES=100;			//100��С������Դ
	PDD.star_x=0;					//��λ��
	PDD.star_y=0;
	PDD.star_z=0;
	PDD.lifefate=0.5f;				// �������ӵ���������ֵԼ�����ӵ�������Խ��
	PDD.slowdown=1.0f;				// �������ӵ��ٶȣ���ֵԼ��Խ����ԽСԽ��

	PDD.speedMax=100.0;				// ��ը�ٶȵ�ֵ
	PDD.speedMin=100.0;

	PDD.AngleYStar=0;				// Y����ŽǴ�С
	PDD.AngleYEnd=180;
	
	PDD.AngleXZStar=0;				// XZƽ���ͶӰ�ŽǴ�С
	PDD.AngleXZEnd=360;	

	PDD.GetXg=0.0f;					//�����ܵ�����������ʸ����
	PDD.GetYg=-15.0f;
	PDD.GetZg=0.0f;

	PDD.TextWidth=1.0;
	PDD.TextModel=0;

	/////////////////////////////////////// //��ɫ
	PDD.PrtColor.Red[0]=1.0f;
	PDD.PrtColor.Green[0]=1.0f;
	PDD.PrtColor.Blue[0]=1.0f;

	PDD.PrtColor.Red[1]=1.0f;
	PDD.PrtColor.Green[1]=0.706f;
	PDD.PrtColor.Blue[1]=0.706f;

	PDD.PrtColor.Red[2]=1.0f;
	PDD.PrtColor.Green[2]=0.392f;
	PDD.PrtColor.Blue[2]=0.392f;

	PDD.PrtColor.Red[3]=0.843f;	
	PDD.PrtColor.Green[3]=0.392f;
	PDD.PrtColor.Blue[3]=0.784f;

	PDD.PrtColor.Red[4]=0.196;
	PDD.PrtColor.Green[4]=0.95f;
	PDD.PrtColor.Blue[4]=0.390f;

	/////////////////////////////////////////////////////////////
	//�����������ӵ�����
	PDD.SonPDD.MAX_PARTICLES=100;
	PDD.SonPDD.lifefate=2.0;				// �������ӵ���������ֵԼ�����ӵ�������Խ��
	PDD.SonPDD.slowdown=0.5;				// �������ӵ��ٶȣ���ֵԼ��Խ����ԽСԽ��

	PDD.SonPDD.GetXg=0;
	PDD.SonPDD.GetYg=0;
	PDD.SonPDD.GetZg=0;

	PDD.SonPDD.speedMax=1;
	PDD.SonPDD.speedMin=1;

	Init();
}

void CPrt_Explode::ReSatPrt(int loop)
{
	//����������˥����
	explodePar[loop].life=1.0f;					// �����е��������������1.0F���0.0f���
	explodePar[loop].fade=0.03*PDD.lifefate;

	//ָ�����
	explodePar[loop].PDD.star_x=PDD.star_x;
	explodePar[loop].PDD.star_y=PDD.star_y;
	explodePar[loop].PDD.star_z=PDD.star_z;

	float	a=RandMaxMin(PDD.AngleYEnd,PDD.AngleYStar)/180.0f*PAI;
	float	b=RandMaxMin(PDD.AngleXZEnd,PDD.AngleXZStar)/180.0f*PAI;

	speed=RandMaxMin(PDD.speedMax,PDD.speedMin);
	explodePar[loop].xi=speed*sin(a)*cos(b);
	explodePar[loop].yi=speed*cos(a);
	explodePar[loop].zi=speed*sin(a)*sin(b);

	/////////////////////////////////////
	//������Դ�����Լ�ʱ����
	explodePar[loop].PDD.MAX_PARTICLES=PDD.SonPDD.MAX_PARTICLES;
	explodePar[loop].PDD.lifefate=PDD.SonPDD.lifefate;				// �������ӵ���������ֵԼ�����ӵ�������Խ��
	explodePar[loop].PDD.slowdown=PDD.SonPDD.slowdown;				// �������ӵ��ٶȣ���ֵԼ��Խ����ԽСԽ��
	explodePar[loop].PDD.GetXg=PDD.SonPDD.GetXg;
	explodePar[loop].PDD.GetYg=PDD.SonPDD.GetYg;
	explodePar[loop].PDD.GetZg=PDD.SonPDD.GetZg;
	explodePar[loop].PDD.speedMax=PDD.SonPDD.speedMax;
	explodePar[loop].PDD.speedMin=PDD.SonPDD.speedMin;
	explodePar[loop].PDD.TextModel=PDD.TextModel;
	explodePar[loop].PDD.TextWidth=PDD.TextWidth;

	//������ɫ
	for(int i=0;i<=4;i++)
	{
		explodePar[loop].PDD.PrtColor.Red[i]=PDD.PrtColor.Red[i];
		explodePar[loop].PDD.PrtColor.Green[i]=PDD.PrtColor.Green[i];
		explodePar[loop].PDD.PrtColor.Blue[i]=PDD.PrtColor.Blue[i];
	}
	changeForce(loop);
}

int CPrt_Explode::Init(void)//��ʼ������ϵͳ������λ�á��ٶȡ�������
{
	//*******************************************************************************
	//��ʼ����������
	//װ�ز���
	if (!LoadGLTextures())							
	{
		return FALSE;
	}
		for (loop=0;loop<200;loop++)
		{
				explodePar[loop].active=true;// ʹ���е����Ӷ�������	explodePar[loop].PDD.MAX_PARTICLES=100;//��max 1500��
				ReSatPrt(loop);
				for(int i=0;i<=3;i++)
					explodePar[loop].texture[i]=&texture[i];
				explodePar[loop].Init();
		}


	return TRUE;										// ��ʼ�� OK
}

void CPrt_Explode::draw(float *Tar2Cam,bool Isplay)//��ʾ����
{
	for (loop=0;loop<PDD.MAX_PARTICLES;loop++)
	{
		//����������У����е����Ӷ��ǻ��ŵģ����ǿ�����������
		if (explodePar[loop].active)
		{
			//��ʾ����
			explodePar[loop].draw(Tar2Cam,Isplay,explodePar[loop].life);

			if(Isplay)
			{
			//������һ������Ļ���ֵ�λ�ã������ڵ�λ�ü����ٶȵ�������λ�á�
			explodePar[loop].PDD.star_x+=explodePar[loop].xi/(PDD.slowdown*1000);
			explodePar[loop].PDD.star_y+=explodePar[loop].yi/(PDD.slowdown*1000);
			explodePar[loop].PDD.star_z+=explodePar[loop].zi/(PDD.slowdown*1000);

			//�����ٶȵĸı䣬Xg��ʵ���Ǽ��ٶ�!!!!
			explodePar[loop].xi+=explodePar[loop].xg;
			explodePar[loop].yi+=explodePar[loop].yg;
			explodePar[loop].zi+=explodePar[loop].zg;

			//���ӵ�������С
			explodePar[loop].life-=explodePar[loop].fade;
			}

			//�����ӵ�����������Ҫ��������������������������ˣ��ﲻ��ѭ����Ч����
			if (explodePar[loop].life<0.0f)					// If Particle Is Burned Out
			{
				ReSatPrt(loop);	
			}
		}
	}
}

void CPrt_Explode::changeForce(int loop)//�������ӵļ��ٶȣ��ٶ��ɼ��ٶȶ��ı䣩
{
		//���ӵĳ�ʼ��������(�������ٶ�)
		explodePar[loop].xg=PDD.GetXg*0.1;
		explodePar[loop].yg=PDD.GetYg*0.1;
		explodePar[loop].zg=PDD.GetZg*0.1;
}



AUX_RGBImageRec * CPrt_Explode::LoadBMP(char *Filename)//����ͼ�ļ��������ؾ��
{
	CFileStatus status;
	if(!CFile::GetStatus(Filename, status ))//�����Ƿ���ļ�
		return NULL;
	else
	{
		return auxDIBImageLoad(Filename);
	}
}

int CPrt_Explode::LoadTextures(char *Filename,GLuint &texture)//��������ͼ
{
	int Status=FALSE;
	AUX_RGBImageRec *TextureImage[1];
	memset(TextureImage,0,sizeof(void *)*1);
	if (TextureImage[0]=LoadBMP(Filename))
	{
		Status=TRUE;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);
	}	
	if (TextureImage[0])
	{
		if (TextureImage[0]->data)
		{
			free(TextureImage[0]->data);
		}
		free(TextureImage[0]);
	}
	return Status;
}

int CPrt_Explode::LoadGLTextures(void)//��������ͼ
{
	if(!LoadTextures("Բ��.bmp",texture[0]))	//��0�Ų���װ����ͼ
	{AfxMessageBox("Բ��.bmp error!");return FALSE;}
	if(!LoadTextures("������.bmp",texture[1]))	//��0�Ų���װ����ͼ
	{AfxMessageBox("������.bmp error!");return FALSE;}
	if(!LoadTextures("����.bmp",texture[2]))	//��0�Ų���װ����ͼ
	{AfxMessageBox("����.bmp error!");return FALSE;}
	if(!LoadTextures("ѩ����.bmp",texture[3]))	//��0�Ų���װ����ͼ
	{AfxMessageBox("ѩ����.bmp error!");return FALSE;}
	return true;
}

//////////////////////////////////////////////////////////////////////////////////
///
//////////////////////////////////////////////////////////////////////////////////
CPrt_ExplodePRT::CPrt_ExplodePRT()
{
}

CPrt_ExplodePRT::~CPrt_ExplodePRT()
{

}

void	CPrt_ExplodePRT::GetInitInfo(void)
{

}

//���Ӷ�׼�������ͼ����ת������
void CPrt_ExplodePRT::ExchangeShowXYZ(float *Tar2Cam,float x,float y,float z,float a)//a=ADDwidth)
{
	//float ParShowXYZ[4][3];��������ͼ�����̼��ʼǱ�
	//Tar2Cam����Ŀ��ָ�������������
	//��������ƽ�淽�̣�A(X-x0)+B(Y-y0)+C(Z-z0)=0;
	//���巽�̣�(CameraPos[0]-x)*(X-x)+(CameraPos[1]-y)*(Y-y)+(CameraPos[2]-z)*(Z-z)=0;
	float	T0=Tar2Cam[0];
	float	T1=Tar2Cam[1];
	float	T2=Tar2Cam[2];
	float	l,m,n,t;
	if((T0*T0+T1*T1)!=0)
	{
		float	K1=sqrt((2*T1*T1*a*a)/(T0*T0+T1*T1));
		float	K0=sqrt((2*T0*T0*a*a)/(T0*T0+T1*T1));
		if( ((T0>=0)&&(T1>=0)) || ((T0<=0)&&(T1<=0)) )
		{
			l=2*T2*K0;
			m=2*T2*K1;
			n=-2*T1*K1-2*T0*K0;
			t=sqrt((2*a*a)/(l*l+m*m+n*n));

			ParShowXYZ[3][0]=x+K1;	//3��
			ParShowXYZ[3][1]=y-K0;
			ParShowXYZ[3][2]=z;

			ParShowXYZ[0][0]=x-K1;	//0��
			ParShowXYZ[0][1]=y+K0;
			ParShowXYZ[0][2]=z;

			ParShowXYZ[1][0]=x+l*t;	//1��
			ParShowXYZ[1][1]=y+m*t;
			ParShowXYZ[1][2]=z+n*t;

			ParShowXYZ[2][0]=x-l*t;	//2��
			ParShowXYZ[2][1]=y-m*t;
			ParShowXYZ[2][2]=z-n*t;
		}
		if( ((T0<0)&&(T1>=0)) || ((T0>0)&&(T1<=0)) )
		{
			l=2*T2*K0;
			m=-2*T2*K1;
			n=2*T1*K1-2*T0*K0;
			t=sqrt((2*a*a)/(l*l+m*m+n*n));

			ParShowXYZ[3][0]=x-K1;	//3��
			ParShowXYZ[3][1]=y-K0;
			ParShowXYZ[3][2]=z;

			ParShowXYZ[0][0]=x+K1;	//0��
			ParShowXYZ[0][1]=y+K0;
			ParShowXYZ[0][2]=z;

			ParShowXYZ[1][0]=x+l*t;	//1��
			ParShowXYZ[1][1]=y+m*t;
			ParShowXYZ[1][2]=z+n*t;

			ParShowXYZ[2][0]=x-l*t;	//2��
			ParShowXYZ[2][1]=y-m*t;
			ParShowXYZ[2][2]=z-n*t;
		}
	}
	else
	{

		ParShowXYZ[0][0]=x+a;	//0��
		ParShowXYZ[0][1]=y+a;
		ParShowXYZ[0][2]=z;

		ParShowXYZ[3][0]=x-a;	//3��
		ParShowXYZ[3][1]=y-a;
		ParShowXYZ[3][2]=z;

		ParShowXYZ[1][0]=x-a;	//1��
		ParShowXYZ[1][1]=y+a;
		ParShowXYZ[1][2]=z;

		ParShowXYZ[2][0]=x+a;	//2��
		ParShowXYZ[2][1]=y-a;
		ParShowXYZ[2][2]=z;
	}
}



void CPrt_ExplodePRT::draw(float *Tar2Cam,bool Isplay,float selflife)//��ʾ����
{
	//*******************************************************************************
	//ѭ����ʾ�����£�ÿ������
	glPushMatrix();
	glEnable(GL_BLEND);									// ���û��ģʽ
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);
	glDepthMask(GL_FALSE);
	glBindTexture(GL_TEXTURE_2D, *texture[PDD.TextModel]);


	glEnable(GL_TEXTURE_2D);
	for (loop=0;loop<PDD.MAX_PARTICLES;loop++)
	{
		//����������У����е����Ӷ��ǻ��ŵģ����ǿ�����������
		if (particle[loop].active)						// �鿴�����Ƿ�����
		{
			//���ӵ�λ��
			float x=particle[loop].x;
			float y=particle[loop].y;
			float z=particle[loop].z;

			ExchangeShowXYZ(Tar2Cam,x,y,z,0.1*PDD.TextWidth);	//�ı���ͼ����
			//�����Ӹ��趯̬��ɫ
			glColor4f(particle[loop].r,particle[loop].g,particle[loop].b,particle[loop].life*0.5);

			//changeColor(loop,selflife);

			//ÿ�����ӵ���״����һ�������Σ�������������������������ι��ɵ�
			//�������Լӿ� �Կ� �� CPU �������ٶȣ�ע��һ�£��������ε���ͼ����˳��
			glBegin(GL_TRIANGLE_STRIP);
				glTexCoord2d(1,1); glVertex3f(ParShowXYZ[0][0],	ParShowXYZ[0][1],	ParShowXYZ[0][2]);
				glTexCoord2d(0,1); glVertex3f(ParShowXYZ[1][0],	ParShowXYZ[1][1],	ParShowXYZ[1][2]);
				glTexCoord2d(1,0); glVertex3f(ParShowXYZ[2][0],	ParShowXYZ[2][1],	ParShowXYZ[2][2]);
				glTexCoord2d(0,0); glVertex3f(ParShowXYZ[3][0],	ParShowXYZ[3][1],	ParShowXYZ[3][2]);
			glEnd();
		
			if(Isplay)
			{
				//������һ������Ļ���ֵ�λ�ã������ڵ�λ�ü����ٶȵ�������λ�á�
				particle[loop].x+=particle[loop].xi/(PDD.slowdown*1000);
				particle[loop].y+=particle[loop].yi/(PDD.slowdown*1000);
				particle[loop].z+=particle[loop].zi/(PDD.slowdown*1000);

				//�����ٶȵĸı䣬Xg��ʵ���Ǽ��ٶ�!!!!
				particle[loop].xi+=particle[loop].xg;
				particle[loop].yi+=particle[loop].yg;
				particle[loop].zi+=particle[loop].zg;

				//���ӵ�������С
				particle[loop].life-=particle[loop].fade;
			}

			//�����ӵ�����������Ҫ��������������������������ˣ��ﲻ��ѭ����Ч����
			if (particle[loop].life<0.0f)
			{
				ReSatPrt(loop);
				changeColor(loop,selflife);

			}
		}
	}
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);						// ������Ȳ���(WWWWWWWWWWWWWWW)
	glDisable(GL_BLEND);							// ���û��ģʽ
	glDepthMask(GL_TRUE);
	glPopMatrix();

}


void CPrt_ExplodePRT::changeForce(int loop)//�������ӵļ��ٶȣ��ٶ��ɼ��ٶȶ��ı䣩
{
		//���ӵĳ�ʼ��������(�������ٶ�)
		particle[loop].xg=PDD.GetXg;
		particle[loop].yg=PDD.GetYg;
		particle[loop].zg=PDD.GetZg;
}

void CPrt_ExplodePRT::ReSatPrt(int loop)
{
	//����������˥����
	particle[loop].life=1.0f;// �����е��������������1.0F���0.0f���
	particle[loop].fade=float(((rand()%100)/1000.0f+0.003f)*PDD.lifefate);//0.002*RandMaxMin(PDD.lifefate,PDD.lifefate/2.0);		// ���������������������ɫ�ٶ�

	//ָ�����
	particle[loop].x=PDD.star_x;
	particle[loop].y=PDD.star_y;
	particle[loop].z=PDD.star_z;

	speed=RandMaxMin(PDD.speedMax,PDD.speedMin);
	particle[loop].xi=float((rand()%50)-26.0f)/10.0*speed;//*10.0f;			// Random Speed On X Axis
	particle[loop].yi=float((rand()%50)-25.0f)/10.0*speed;//*10.0f;			// Random Speed On Y Axis
	particle[loop].zi=float((rand()%50)-26.0f)/10.0*speed;//*10.0f;;//float((rand()%50)-25.0f);//*10.0f;			// Random Speed On Z Axis
	changeForce(loop);
}



int CPrt_ExplodePRT::Init(void)//��ʼ������ϵͳ������λ�á��ٶȡ�������
{

	//*******************************************************************************
	//��ʼ����������
		for (loop=0;loop<1500;loop++)			// Initials All The Textures
		{
				particle[loop].active=true;					// ʹ���е����Ӷ�������
				ReSatPrt(loop);
				//�����Ӹ�����ɫ
				//changeColor(loop);
				changeColor(loop,1.0);
				changeForce(loop);//�������ӵļ��ٶȣ��ٶ��ɼ��ٶȶ��ı䣩
		}
	//��ʼ�����ӵ���ɫ

	return TRUE;										// ��ʼ�� OK
}


//�������ӵ���ɫloop�����ӵı�ţ�modelΪȾɫģʽ
void CPrt_ExplodePRT::changeColor(int loop,float selflife)
{

	int lifecolorset;					//������ɫѡȡֵ

	//�����Ӹ����ʼ��ɫ
		if(selflife<=1.0f&&selflife>=0.8f)lifecolorset=0;
		if(selflife<0.8f&&selflife>=0.6f)lifecolorset=1;
		if(selflife<0.6f&&selflife>=0.4f)lifecolorset=2;
		if(selflife<0.4f&&selflife>=0.2f)lifecolorset=3;
		if(selflife<0.2f)lifecolorset=4;

		particle[loop].r=PDD.PrtColor.Red[lifecolorset];			// Select Red From Color Table
		particle[loop].g=PDD.PrtColor.Green[lifecolorset];			// Select Green From Color Table
		particle[loop].b=PDD.PrtColor.Blue[lifecolorset];			// Select Blue From Color Table

}