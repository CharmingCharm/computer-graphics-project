// Particle.cpp: implementation of the CParticle class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PrtSys.h"
#include "Particle.h"
#include "cameye.h"
#include "glo.h"
#include <math.h>
#pragma comment(lib,"glaux.lib") 


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////





CParticle::CParticle()
{
}

CParticle::~CParticle()
{
}

void CParticle::draw(float *camPos)//��ʾ����
{
}


void CParticle::changeForce(int loop)//�������ӵļ��ٶȣ��ٶ��ɼ��ٶȶ��ı䣩
{
}



int CParticle::Init(void)//��ʼ������ϵͳ������λ�á��ٶȡ�������
{
	return true;
}



//���Ӷ�׼�������ͼ����ת������
 void CParticle::ExchangeShowXYZ(float *Tar2Cam,float x,float y,float z,float a)//a=ADDwidth)
{
	//float ParShowXYZ[4][3];��������ͼ�����̼��ʼǱ�
	//Tar2Cam����Ŀ��ָ�������������
	//��������ƽ�淽�̣�A(X-x0)+B(Y-y0)+C(Z-z0)=0;
	//���巽�̣�(CameraPos[0]-x)*(X-x)+(CameraPos[1]-y)*(Y-y)+(CameraPos[2]-z)*(Z-z)=0;
	float	T0=Tar2Cam[0];//-x;
	float	T1=Tar2Cam[1];//-y;
	float	T2=Tar2Cam[2];//-z;
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


//��texture���ʸ���Filename��ͼ
int CParticle::LoadGLTextures(char *Filename,GLuint &texture)//��������ͼ
{
	int Status=FALSE;									// Status Indicator
	AUX_RGBImageRec *TextureImage[1];					// Create Storage Space For The Texture
	memset(TextureImage,0,sizeof(void *)*1);			// Set The Pointer To NULL
	if (TextureImage[0]=CParticle::LoadBMP(Filename))	// Load Particle Texture
	{
		Status=TRUE;									// Set The Status To TRUE
		glGenTextures(1, &texture);						// Create One Textures
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);
	}	
	if (TextureImage[0])								// If Texture Exists
	{
		if (TextureImage[0]->data)						// If Texture Image Exists
		{
			free(TextureImage[0]->data);				// Free The Texture Image Memory
		}
		free(TextureImage[0]);							// Free The Image Structure
	}
	return Status;										// Return The Status
}

AUX_RGBImageRec * CParticle::LoadBMP(char *Filename)//����ͼ�ļ��������ؾ��
{

	CFile InFile;
	CFileException e;
	if(!InFile.Open(Filename,CFile::modeRead,&e) )//�����Ƿ���ļ�
		return NULL;
	else
	{
		InFile.Close();
		return auxDIBImageLoad(Filename);
	}

}


void CParticle::GetInitInfo(void)//��ó�ʼ������
{
}


//�������ӵ���ɫloop�����ӵı�ţ�modelΪȾɫģʽ
void CParticle::changeColor(int loop,int model)
{
}

//�������ӵĳ�ʼ״̬
void CParticle::changeInitParticle(int model)
{
}


//���ӿ����ຯ��
void CParticleControl::GetInitInfo(void)
{

	m_prtFire.GetInitInfo();
	m_prtWaterFall.GetInitInfo();
	m_prtFireWork.GetInitInfo();

	m_prtAtomicBomb.GetInitInfo();
	m_prtSnow.GetInitInfo();
	m_prtBMP.GetInitInfo();

}

void CParticleControl::draw(CCamEye &camera,Dlg_PRT_Control	&ptrCtrl)
{
	for(int i=0;i<=2;i++)
		Tar2Cam[i]=camera.eyePos[i]-camera.target[i];	//��������λ��
	
		if(ptrCtrl.p_fire)
			m_prtFire.draw(Tar2Cam,ptrCtrl.IsPlay);
		if(ptrCtrl.p_waterfall)
			m_prtWaterFall.draw(Tar2Cam,ptrCtrl.IsPlay);
		if(ptrCtrl.p_firework)
			m_prtFireWork.draw(Tar2Cam,ptrCtrl.IsPlay);
		if(ptrCtrl.p_atomicbomb)
		{
			m_prtAtomicBomb.draw(Tar2Cam,ptrCtrl.IsPlay);
		}
		else glClearColor(0,0,0,0.5);

		if(ptrCtrl.p_snow)
			m_prtSnow.draw(Tar2Cam,ptrCtrl.IsPlay);
		if(ptrCtrl.p_bmp)
			m_prtBMP.draw(Tar2Cam,ptrCtrl.IsPlay);

}
