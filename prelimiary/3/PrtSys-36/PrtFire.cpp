
#include "stdafx.h"
#include "PrtSys.h"
#include "Particle.h"

//ȫ�ֺ���˵����
#include "glo.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CPrt_Fire::CPrt_Fire()
{

}

CPrt_Fire::~CPrt_Fire()
{

}

void CPrt_Fire::draw(float *Tar2Cam,bool Isplay)//��ʾ����
{
	//*******************************************************************************
	//ѭ����ʾ�����£�ÿ������
	glPushMatrix();
	glEnable(GL_BLEND);										// ���û��ģʽ
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);

	glDepthMask(GL_FALSE);
	glBindTexture(GL_TEXTURE_2D, texture[PDD.TextModel]);	//ѡ��ǰ��ͼ��ʽ
	glEnable(GL_TEXTURE_2D);
	glTranslatef(PDD.star_x,PDD.star_y,PDD.star_z);			//�ƶ�����Դ����λ��
	for (loop=0;loop<PDD.MAX_PARTICLES;loop++)
	{
		//����������У����е����Ӷ��ǻ��ŵģ����ǿ�����������
		if (particle[loop].active)							// �鿴�����Ƿ�����
		{
			//���ӵ�λ��
			float x=particle[loop].x;
			float y=particle[loop].y;
			float z=particle[loop].z;

			CParticle::ExchangeShowXYZ(Tar2Cam,x,y,z,0.1*PDD.TextWidth);	//�ı���ͼ����
			//�����Ӹ��趯̬��ɫ
			changeColor(loop);

			//ÿ�����ӵ���״����һ�������Σ�������������������������ι��ɵ�
			//�������Լӿ� �Կ� �� CPU �������ٶȣ�ע��һ�£��������ε���ͼ����˳��
			glBegin(GL_TRIANGLE_STRIP);
				glTexCoord2d(1,1); glVertex3f(ParShowXYZ[0][0],	ParShowXYZ[0][1],	ParShowXYZ[0][2]);
				glTexCoord2d(0,1); glVertex3f(ParShowXYZ[1][0],	ParShowXYZ[1][1],	ParShowXYZ[1][2]);
				glTexCoord2d(1,0); glVertex3f(ParShowXYZ[2][0],	ParShowXYZ[2][1],	ParShowXYZ[2][2]);
				glTexCoord2d(0,0); glVertex3f(ParShowXYZ[3][0],	ParShowXYZ[3][1],	ParShowXYZ[3][2]);
			glEnd();

			if(Isplay)//�����������������ӵĸ���
			{
			//������һ������Ļ���ֵ�λ�ã������ڵ�λ�ü����ٶȵ�������λ�á�
			particle[loop].x+=particle[loop].xi/(PDD.slowdown*1000)*(particle[loop].life-0.1);
			particle[loop].y+=particle[loop].yi/(PDD.slowdown*1000)*(particle[loop].life-0.1);
			particle[loop].z+=particle[loop].zi/(PDD.slowdown*1000)*(particle[loop].life-0.1);

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
				//�����Ӹ���������ɫ
				particle[loop].active=false;
			}
		}
		else 
		{
			particle[loop].active=true;
			ReSatPrt(loop);
		}
	}
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);									// ���û��ģʽ
	glDepthMask(GL_TRUE);
	glPopMatrix();

}


void CPrt_Fire::changeForce(int loop)//�������ӵļ��ٶȣ��ٶ��ɼ��ٶȶ��ı䣩
{
		//���ӵĳ�ʼ��������(�������ٶ�)
		particle[loop].xg=PDD.GetXg;
		particle[loop].yg=PDD.GetYg;
		particle[loop].zg=PDD.GetZg;
}


void CPrt_Fire::ReSatPrt(int loop)
{
		particle[loop].life=1.0f;// �����е��������������1.0F���0.0f���
		particle[loop].fade=float(((rand()%100)/1000.0f+0.003f)*PDD.lifefate);		// ���������������������ɫ�ٶ�

		particle[loop].x=0;
		particle[loop].y=0;
		particle[loop].z=0;
		//���ӵ��ٶ�
		speed=RandMaxMin(PDD.speedMax,PDD.speedMin);//�ٶȵĴ�С
		   ay=RandMaxMin(PDD.AngleYEnd,PDD.AngleYStar)/180.0*PAI;//�ٶȵķ���
		  axz=RandMaxMin(PDD.AngleXZEnd,PDD.AngleXZStar)/180.0*PAI;
		particle[loop].xi=speed*sin(ay)*cos(axz);
		particle[loop].yi=speed*cos(ay);
		particle[loop].zi=speed*sin(ay)*sin(axz);
		changeForce(loop);
}


int CPrt_Fire::Init(void)//��ʼ������ϵͳ������λ�á��ٶȡ�������
{
	//װ�ز���
	if (!LoadGLTextures())
	{
		return FALSE;
	}	
	for (loop=0;loop<9999;loop++)
	{
		particle[loop].active=false;					// ʹ���е����Ӷ�������
	}
	return TRUE;										// ��ʼ�� OK
}


int CPrt_Fire::LoadGLTextures(void)//��������ͼ
{
	if(!CParticle::LoadGLTextures("Բ��.bmp",texture[0]))	//��0�Ų���װ����ͼ
	{AfxMessageBox("Բ��.bmp error!");return FALSE;}
	if(!CParticle::LoadGLTextures("����1.bmp",texture[1]))	//��1�Ų���װ����ͼ
	{AfxMessageBox("����1.bmp error!");return FALSE;}
	if(!CParticle::LoadGLTextures("����2.bmp",texture[2]))	//��2�Ų���װ����ͼ
	{AfxMessageBox("����2.bmp error!");return FALSE;}
	if(!CParticle::LoadGLTextures("����3.bmp",texture[3]))	//��3�Ų���װ����ͼ
	{AfxMessageBox("����3.bmp error!");return FALSE;}
	return true;
}


void CPrt_Fire::GetInitInfo(void)//��ó�ʼ������
{
	PDD.MAX_PARTICLES=1000;
	PDD.star_x=0;
	PDD.star_y=0.0;
	PDD.star_z=0;
	PDD.lifefate=1.0f;							// �������ӵ���������ֵԼ�����ӵ�������Խ��
	PDD.slowdown=2.0f;							// �������ӵ��ٶȣ���ֵԼ��Խ����ԽСԽ�죨�����������
	PDD.speedMax=50.0;							// �ٶȵ����ֵ
	PDD.speedMin=0.0;							// �ٶȵ���Сֵ

	PDD.AngleYStar=0;							// Y����ŽǴ�С
	PDD.AngleYEnd=90;
	
	PDD.AngleXZStar=0;							// XZƽ���ͶӰ�ŽǴ�С
	PDD.AngleXZEnd=360;	
	
	PDD.GetXg=0.0;								//�����ܵ�����������ʸ����
	PDD.GetYg=0.1;
	PDD.GetZg=0.0;

	////////////////////////////////////////////
	PDD.TextModel=0;						//��ͼ��ʽ
	PDD.TextWidth=1.0;						//��ͼ��С
	InitColor();							//��ʼ����ɫ
	Particle_type=1;						//1�Ŵ������
	Init();//��ʼ������ϵͳ������λ�á��ٶȡ�������
}

//��ʼ�����ӵ���ɫ
void CPrt_Fire::InitColor(void)
{
	PDD.PrtColor.Red[0]=1.0f;		//ǳ�ƣ������ǰ�ɫ�Ļƣ�
	PDD.PrtColor.Green[0]=0.996f;
	PDD.PrtColor.Blue[0]=0.953f;

	PDD.PrtColor.Red[1]=0.953f;		//��ɫ��ƫ��ɫ��
	PDD.PrtColor.Green[1]=0.757f;
	PDD.PrtColor.Blue[1]=0.125f;

	PDD.PrtColor.Red[2]=0.965f;			//����ɫ�����ɫ��
	PDD.PrtColor.Green[2]=0.627f;
	PDD.PrtColor.Blue[2]=0.09f;

	PDD.PrtColor.Red[3]=0.843f;			//�Ұ�ɫ
	PDD.PrtColor.Green[3]=0.816f;
	PDD.PrtColor.Blue[3]=0.784f;

	PDD.PrtColor.Red[4]=0.001;			//��ɫ
	PDD.PrtColor.Green[4]=0.001f;
	PDD.PrtColor.Blue[4]=0.001f;
}


//�������ӵ���ɫloop�����ӵı�ţ�modelΪȾɫģʽ
void CPrt_Fire::changeColor(int loop)
{
		int lifecolorset;					//������ɫѡȡֵ

		float alpha;
		alpha=particle[loop].life*0.5;
		if(particle[loop].life<=1.0f&&particle[loop].life>=0.8f){lifecolorset=0;alpha=0.01;}
		if(particle[loop].life<0.8f&&particle[loop].life>=0.6f)lifecolorset=1;
		if(particle[loop].life<0.6f&&particle[loop].life>=0.4f)lifecolorset=2;
		if(particle[loop].life<0.4f&&particle[loop].life>=0.2f)lifecolorset=3;
		if(particle[loop].life<0.2f)lifecolorset=4;

		particle[loop].r=PDD.PrtColor.Red[lifecolorset];
		particle[loop].g=PDD.PrtColor.Green[lifecolorset];
		particle[loop].b=PDD.PrtColor.Blue[lifecolorset];

		//��ÿ�����Ӹ���ɫ�ʣ�����������ֵ��ΪAlpha,���Կ����������
		glColor4f(particle[loop].r,particle[loop].g,particle[loop].b,alpha);
}

