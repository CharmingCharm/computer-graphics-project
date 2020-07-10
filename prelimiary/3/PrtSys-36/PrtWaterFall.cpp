//�ٲ����ʵ�ֺ������䶨����"Particle.h"��
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


CPrt_WaterFall::CPrt_WaterFall()
{

}

CPrt_WaterFall::~CPrt_WaterFall()
{

}

void CPrt_WaterFall::draw(float *Tar2Cam,bool Isplay)//��ʾ����
{
	//*******************************************************************************
	//ѭ����ʾ�����£�ÿ������
	glPushMatrix();
	glEnable(GL_BLEND);									// ���û��ģʽ
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glDepthMask(GL_FALSE);
	glBindTexture(GL_TEXTURE_2D, texture[PDD.TextModel]);
	glEnable(GL_TEXTURE_2D);

	glTranslatef(PDD.star_x,PDD.star_y,PDD.star_z);
	//�����
	glRotatef(PDD.AngleXZEnd,0,1,0);
	float ADDwidth;

	//������ʾ������Ū��
	for (loop=PDD.MAX_PARTICLES;loop<=9999;loop++)
	{
			particle[loop].active=false;
	}

	for (loop=0;loop<PDD.MAX_PARTICLES;loop++)
	{
		//����������У����е����Ӷ��ǻ��ŵģ����ǿ�����������
		if (particle[loop].active)						// �鿴�����Ƿ�����
		{
			//���ӵ�λ��
			float x=particle[loop].x;
			float y=particle[loop].y;
			float z=particle[loop].z;

			ADDwidth=(1.1f-particle[loop].life)*PDD.TextWidth;

			CParticle::ExchangeShowXYZ(Tar2Cam,x,y,z,ADDwidth);	//�ı���ͼ����

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
			
			if(Isplay)//���û����ͣ��
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
				particle[loop].life=1;
				ReSatPrt(loop);
			}
		}
		else
		{
				particle[loop].active=true;
				particle[loop].life=float((rand()%100)/100.0f);	
				ReSatPrt(loop);
		}
	}
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);							// ������Ȳ���(WWWWWWWWWWWWWWW)
	glDisable(GL_BLEND);								// ���û��ģʽ
	glDepthMask(GL_TRUE);
	glPopMatrix();
}


void CPrt_WaterFall::changeForce(int loop/*particleModel *particle*/)//�������ӵļ��ٶȣ��ٶ��ɼ��ٶȶ��ı䣩
{
		//���ӵĳ�ʼ��������(�������ٶ�)
		particle[loop].xg=PDD.GetXg;
		particle[loop].yg=PDD.GetYg;
		particle[loop].zg=PDD.GetZg;
}

void CPrt_WaterFall::ReSatPrt(int loop)					//�����ʼ���ٶȵȵ�
{
	//����������˥����
	particle[loop].fade=0.004*PDD.lifefate;		// ���������������������ɫ�ٶ�

	//ָ�����
	particle[loop].x=PDD.AngleXZStar*float((rand()%100)/50.0f-1.0f);
	particle[loop].y=0;					
	particle[loop].z=0;					
	//���ӵ��ٶ�
	speed=RandMaxMin(PDD.speedMax,PDD.speedMin);//�ٶȴ�С
	//�ٲ������䷽��
	ay=PDD.AngleYEnd/180.0*PAI;	//��ǣ�0-180��
	particle[loop].xi=speed*0.01*particle[loop].x*float((rand()%100)/100.0f);
	particle[loop].yi=speed*cos(ay);
	particle[loop].zi=speed*sin(ay);
	changeForce(loop);//�������ӵļ��ٶȣ��ٶ��ɼ��ٶȶ��ı䣩

}



int CPrt_WaterFall::Init(void)//��ʼ������ϵͳ������λ�á��ٶȡ�������
{
	//װ�ز���
	if (!LoadGLTextures())
	{
		return FALSE;
	}
	
	//*******************************************************************************
	//��ʼ����������
		for (loop=0;loop<=9999;loop++)
		{
				particle[loop].active=true;					// ʹ���е����Ӷ�������
				particle[loop].life=float((rand()%100)/100.0f);	
				ReSatPrt(loop);
		}
	return TRUE;										// ��ʼ�� OK
}


int CPrt_WaterFall::LoadGLTextures(void)//��������ͼ
{
	if(!CParticle::LoadGLTextures("�ٲ�.bmp",texture[0]))	//��0�Ų���װ����ͼ
	{AfxMessageBox("�ٲ�.bmp error!");return FALSE;}
	if(!CParticle::LoadGLTextures("�ٲ�1.bmp",texture[1]))	//��1�Ų���װ����ͼ
	{AfxMessageBox("�ٲ�1.bmp error!");return FALSE;}
	if(!CParticle::LoadGLTextures("�ٲ�2.bmp",texture[2]))	//��2�Ų���װ����ͼ
	{AfxMessageBox("�ٲ�2.bmp error!");return FALSE;}
	return true;
}

void CPrt_WaterFall::GetInitInfo(void)//��ó�ʼ������
{
	PDD.MAX_PARTICLES=1500;
	PDD.star_x=0;
	PDD.star_y=0;
	PDD.star_z=0;
	PDD.lifefate=2.0f;				// �������ӵ���������ֵԼ�����ӵ�������Խ��
	PDD.slowdown=1.0f;				// �������ӵ��ٶȣ���ֵԼ��Խ����ԽСԽ��

	PDD.AngleXZStar=5;				// �ٲ��Ŀ�ȣ�����Ϊ��ֵ

	PDD.speedMax=150.0;					// �����ٶȵ����ֵ
	PDD.speedMin=100.0;					// �����ٶȵ���Сֵ

	PDD.GetXg=0.0;						//�����ܵ�����������ʸ����
	PDD.GetYg=-3.8;
	PDD.GetZg=0.0;

	//�ٲ������䷽��
	PDD.AngleYEnd=80;	//��ǣ�0-180��
	PDD.AngleXZEnd=0;	//����ǣ�0-360��

	PDD.TextModel=0;						//��ͼ��ʽ
	PDD.TextWidth=1.5;						//��ͼ��С

	Init();//��ʼ������ϵͳ������λ�á��ٶȡ�������
	InitColor();
}

//��ʼ�����ӵ���ɫ
void CPrt_WaterFall::InitColor(void)
{
	PDD.PrtColor.Red[0]=1.0f;
	PDD.PrtColor.Green[0]=1.0f;
	PDD.PrtColor.Blue[0]=1.0f;

	PDD.PrtColor.Red[1]=1.0f;
	PDD.PrtColor.Green[1]=1.0f;
	PDD.PrtColor.Blue[1]=1.0f;

	PDD.PrtColor.Red[2]=1.0f;
	PDD.PrtColor.Green[2]=1.0f;
	PDD.PrtColor.Blue[2]=1.0f;

	PDD.PrtColor.Red[3]=1.0f;
	PDD.PrtColor.Green[3]=1.0f;
	PDD.PrtColor.Blue[3]=1.0f;

	PDD.PrtColor.Red[4]=1.0f;
	PDD.PrtColor.Green[4]=1.0f;
	PDD.PrtColor.Blue[4]=1.0f;
}

//�������ӵ���ɫloop�����ӵı�ţ�modelΪȾɫģʽ
void CPrt_WaterFall::changeColor(int loop)
{
		int lifecolorset;					//������ɫѡȡֵ
		if(particle[loop].life<=1.0f&&particle[loop].life>=0.8f)lifecolorset=0;
		if(particle[loop].life<0.8f&&particle[loop].life>=0.6f)lifecolorset=1;
		if(particle[loop].life<0.6f&&particle[loop].life>=0.4f)lifecolorset=2;
		if(particle[loop].life<0.4f&&particle[loop].life>=0.2f)lifecolorset=3;
		if(particle[loop].life<0.2f)lifecolorset=4;

		particle[loop].r=PDD.PrtColor.Red[lifecolorset];
		particle[loop].g=PDD.PrtColor.Green[lifecolorset];
		particle[loop].b=PDD.PrtColor.Blue[lifecolorset];
		glColor4f(particle[loop].r,particle[loop].g,particle[loop].b,particle[loop].life*0.2);

}


