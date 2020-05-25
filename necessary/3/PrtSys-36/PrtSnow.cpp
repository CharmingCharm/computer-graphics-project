//ѩ��Ч����
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

//double	RandMaxMin(double Max,double Min);

CPrt_Snow::CPrt_Snow()
{

}

CPrt_Snow::~CPrt_Snow()
{

}

void CPrt_Snow::GetInitInfo(void)//��ó�ʼ������
{
	PDD.MAX_PARTICLES=500;
	oldnum=PDD.MAX_PARTICLES;
	PDD.star_x=0;						//ѩ��������λ��
	PDD.star_y=5.0;
	PDD.star_z=0;
	PDD.lifefate=10.0f;					// ѩ���ĸ߶ȣ�
	oldHeight=PDD.lifefate;
	PDD.slowdown=25.8f;					// �������ӵ��ٶȣ���ֵԼ��Խ����ԽСԽ�죨�����������


	PDD.pram[0]=0.015;					// ��Ҷõ���߽Ƕ�����
	PDD.dead=false;						// �Ƿ���Ҫ��ɢ

	PDD.speedMax=10.0;					// �ٶȵ����ֵ
	PDD.speedMin=5.0;					// �ٶȵ���Сֵ

	PDD.AngleYStar=2;					// ��Ҷõ�������뾶
	PDD.AngleYEnd=0.5;					// ��Ҷõ������С�뾶
	
	PDD.AngleXZStar=10;					// ѩ���ĳ���X��
	PDD.AngleXZEnd=10;					// ѩ���Ŀ�Z��
	
	PDD.GetXg=0.0;						//�����ܵ�����������ʸ����
	PDD.GetYg=-0.2;
	PDD.GetZg=0.0;

	PDD.TextModel=0;		//��ͼģʽ
	PDD.TextWidth=0.1;		//��ͼ��С
	//strcpy(TextFileName,"����.bmp");		//������ͼ����

	Init();//��ʼ������ϵͳ������λ�á��ٶȡ�������
}

void CPrt_Snow::ReSatPrt(int loop)
{
		//particle[loop].life=1;//float((rand()%100)/100.0f);		// �����е��������������1.0F���0.0f���
		//particle[loop].fade=RandMaxMin(0.004f,0.001f);			// ���������������������ɫ�ٶ�

		//particle[loop].active=true;
		//ָ�����
		particle[loop].x=PDD.star_x+RandMaxMin(PDD.AngleXZStar/2.0,-PDD.AngleXZStar/2.0);	// ѩ���ĳ��ȣ�X��
		particle[loop].y=PDD.star_y;
		particle[loop].z=PDD.star_z+RandMaxMin(PDD.AngleXZEnd/2.0,-PDD.AngleXZEnd/2.0);	//ѩ���Ŀ�ȣ�Z��

		//���ӵ��ٶ�,�տ�ʼѩ��ֻ��������ٶ�
		//speed=RandMaxMin(PDD.speedMax,PDD.speedMin);//�ٶȵĴ�С
		particle[loop].xi=0;
		//particle[loop].yi=-speed;								// Random Speed On Y Axis
		particle[loop].zi=0;
		PrtSnowAngle[loop]=RandMaxMin(360.0,0.0);				//ת���Ƕ�
		PrtSnowRadius[loop]=RandMaxMin(PDD.AngleYStar,PDD.AngleYEnd);	//�뾶
		//changeColor(loop);
		changeForce(loop);
}


void CPrt_Snow::draw(float *Tar2Cam,bool Isplay)//��ʾ����
{
	//*******************************************************************************
	//ѭ����ʾ�����£�ÿ������
	glPushMatrix();
//	glDisable(GL_DEPTH_TEST);							// ������Ȳ���(WWWWWWWWWWWWWWW)
	glEnable(GL_BLEND);									// ���û��ģʽ
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);	// Type Of Blending To Perform
	glDepthMask(GL_FALSE);
	glBindTexture(GL_TEXTURE_2D, texture[PDD.TextModel]);

	//glTranslatef(PDD.star_x,PDD.star_y,PDD.star_z);//��������λ�á�
	glEnable(GL_TEXTURE_2D);
	if(oldnum!=PDD.MAX_PARTICLES)//���������ı��ˣ���Ҫ��ɢ
	{
		PDD.dead=true;
		oldnum=PDD.MAX_PARTICLES;
	}

	if(PDD.dead)//�����Ҫ��ɢ
	{
		for (loop=0;loop<PDD.MAX_PARTICLES;loop++)				// Loop Through All The Particles
		{
			particle[loop].active=true;
			ReSatPrt(loop);
			speed=RandMaxMin(PDD.speedMax,PDD.speedMin);//�ٶȵĴ�С
			particle[loop].yi=-speed;
			particle[loop].y=PDD.star_y-RandMaxMin(PDD.lifefate,0);//ѩ�����ȵķֲ��ڸ߶���
		}
		PDD.dead=false;
	}

	for (loop=0;loop<PDD.MAX_PARTICLES;loop++)				// Loop Through All The Particles
	{
		//����������У����е����Ӷ��ǻ��ŵģ����ǿ�����������
		//if (particle[loop].active)						// �鿴�����Ƿ�����
		//{
			//���ӵ�λ��
			//��ס��ֻ��particle[loop].x��y��z���������ĵ��������ģ�
			//ÿһ��������Χ��������ν����Ҷõ�����˶���
			float x,y,z;//���ӵ���ʾλ�ã���������Ȼ�������Ҷõ�������㡣
			y=particle[loop].y;
			x=particle[loop].x+PrtSnowRadius[loop]*cos(PrtSnowAngle[loop]);
			z=particle[loop].z+PrtSnowRadius[loop]*sin(PrtSnowAngle[loop]);

			if(Isplay)
				PrtSnowAngle[loop]+=PDD.pram[0];//ת���ĽǶ�����

			//�ı���ͼ����,ֻ������������XZƽ���ϵ�ͶӰ����������
			//Tar2Cam[1]=0.0;
			if(PDD.TextModel==4||PDD.TextModel==5)
					//RainExchangeShowXYZ(Tar2Cam,x,y,z,0.03*PDD.TextWidth);
					RainExchangeShowXYZ(Tar2Cam,x,y,z,0.5*PDD.TextWidth);
			else CParticle::ExchangeShowXYZ(Tar2Cam,x,y,z,PDD.TextWidth);	
			//�����Ӹ��趯̬��ɫ
			changeColor(loop);

			//ÿ�����ӵ���״����һ�������Σ�������������������������ι��ɵ�
			//�������Լӿ� �Կ� �� CPU �������ٶȣ�ע��һ�£��������ε���ͼ����˳��
			glBegin(GL_TRIANGLE_STRIP);				// Build Quad From A Triangle Strip
				glTexCoord2d(1,1); glVertex3f(ParShowXYZ[0][0],	ParShowXYZ[0][1],	ParShowXYZ[0][2]); // Top Right//0
				glTexCoord2d(0,1); glVertex3f(ParShowXYZ[1][0],	ParShowXYZ[1][1],	ParShowXYZ[1][2]); // Top Left	//1
				glTexCoord2d(1,0); glVertex3f(ParShowXYZ[2][0],	ParShowXYZ[2][1],	ParShowXYZ[2][2]); // Bottom Right//2
				glTexCoord2d(0,0); glVertex3f(ParShowXYZ[3][0],	ParShowXYZ[3][1],	ParShowXYZ[3][2]); // Bottom Left//3
			glEnd();								// Done Building Triangle Strip

			if(Isplay)
			{
			//������һ������Ļ���ֵ�λ�ã������ڵ�λ�ü����ٶȵ�������λ�á�
			particle[loop].x+=particle[loop].xi/(PDD.slowdown*50);
			particle[loop].y+=particle[loop].yi/(PDD.slowdown*10);
			particle[loop].z+=particle[loop].zi/(PDD.slowdown*50);

			//�����ٶȵĸı䣬Xg��ʵ���Ǽ��ٶ�!!!!
			particle[loop].xi+=particle[loop].xg;
			particle[loop].zi+=particle[loop].zg;
			}
			//�������ܳ�ѩ���涨�߶�ʱ��Ҫ����
			if((PDD.star_y-particle[loop].y)>=PDD.lifefate)
			{
				ReSatPrt(loop);

			}

	}
	//========================
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);							// ������Ȳ���(WWWWWWWWWWWWWWW)
	glDisable(GL_BLEND);								// ���û��ģʽ
	glDepthMask(GL_TRUE);
	glPopMatrix();

}


void CPrt_Snow::changeForce(int loop)//�������ӵļ��ٶȣ��ٶ��ɼ��ٶȶ��ı䣩
{
		//���ӵĳ�ʼ��������(�������ٶ�)
		particle[loop].xg=PDD.GetXg;
		particle[loop].yg=PDD.GetYg;
		particle[loop].zg=PDD.GetZg;
}





int CPrt_Snow::Init(void)//��ʼ������ϵͳ������λ�á��ٶȡ�������
{
	//װ�ز���
	if (!LoadGLTextures())
	{
		return FALSE;
	}	
	//*******************************************************************************
	//��ʼ����������
		for (loop=0;loop<PDD.MAX_PARTICLES;loop++)
		{
				particle[loop].active=true;					// ʹ���е����Ӷ�������
				//����������˥����
				ReSatPrt(loop);
				speed=RandMaxMin(PDD.speedMax,PDD.speedMin);//�ٶȵĴ�С
				particle[loop].yi=-speed;
				particle[loop].y=PDD.star_y-RandMaxMin(PDD.lifefate+0.001,-0.001);//ѩ�����ȵķֲ��ڸ߶���

		}
		//������ɫ��͸����
		PDD.PrtColor.Red[0]=1.0;
		PDD.PrtColor.Green[0]=1.0;
		PDD.PrtColor.Blue[0]=1.0;
		PDD.PrtColor.Red[1]=0.5;
	return TRUE;										// ��ʼ�� OK
}


int CPrt_Snow::LoadGLTextures(void)//��������ͼ
{
	if(!CParticle::LoadGLTextures("Բ��.bmp",texture[0]))	//��0�Ų���װ����ͼ
	{AfxMessageBox("Բ��.bmp error!");return FALSE;}
	if(!CParticle::LoadGLTextures("������.bmp",texture[1]))	//��1�Ų���װ����ͼ
	{AfxMessageBox("������.bmp error!");return FALSE;}
	if(!CParticle::LoadGLTextures("����.bmp",texture[2]))	//��2�Ų���װ����ͼ
	{AfxMessageBox("����.bmp error!");return FALSE;}
	if(!CParticle::LoadGLTextures("ѩ����.bmp",texture[3]))	//��3�Ų���װ����ͼ
	{AfxMessageBox("ѩ����.bmp error!");return FALSE;}
	if(!CParticle::LoadGLTextures("��2.bmp",texture[4]))	//��0�Ų���װ����ͼ
	{AfxMessageBox("��2.bmp error!");return FALSE;}
	if(!CParticle::LoadGLTextures("��M.bmp",texture[5]))	//��1�Ų���װ����ͼ
	{AfxMessageBox("��M.bmp error!");return FALSE;}

	return true;
}


//�������ӵ���ɫloop�����ӵı�ţ�modelΪȾɫģʽ
void CPrt_Snow::changeColor(int loop)
{
	glColor4f(PDD.PrtColor.Red[0],PDD.PrtColor.Green[0],PDD.PrtColor.Blue[0],PDD.PrtColor.Red[1]);
}

//�����Ӷ�׼�������ͼ����ת������
void CPrt_Snow::RainExchangeShowXYZ(float *CameraPos,float x,float y,float z,float a)
{
	//float ParShowXYZ[4][3];��������ͼ�����̼��ʼǱ�
	//Tar2Cam����Ŀ��ָ�������������
	//��������ƽ�淽�̣�A(X-x0)+B(Y-y0)+C(Z-z0)=0;
	//���巽�̣�(CameraPos[0]-x)*(X-x)+(CameraPos[1]-y)*(Y-y)+(CameraPos[2]-z)*(Z-z)=0;
	float	T0=CameraPos[0];
	float	T1=0;
	float	T2=CameraPos[2];
	float k;
	if(T0==0.0)
	{
		ParShowXYZ[0][0]=x+a;	//0��
		ParShowXYZ[0][1]=y+8*a;
		ParShowXYZ[0][2]=z;

		ParShowXYZ[3][0]=x-a;	//3��
		ParShowXYZ[3][1]=y-8*a;
		ParShowXYZ[3][2]=z;

		ParShowXYZ[1][0]=x-a;	//1��
		ParShowXYZ[1][1]=y+8*a;
		ParShowXYZ[1][2]=z;

		ParShowXYZ[2][0]=x+a;	//2��
		ParShowXYZ[2][1]=y-8*a;
		ParShowXYZ[2][2]=z;
	}
	else 
	{
		k=-T0/T2;
		ParShowXYZ[0][0]=x+a*cos(atan(k));	//0��
		ParShowXYZ[0][1]=y+8*a;
		ParShowXYZ[0][2]=z+a*sin(atan(k));

		ParShowXYZ[3][0]=x-a*cos(atan(k));	//3��
		ParShowXYZ[3][1]=y-8*a;
		ParShowXYZ[3][2]=z-a*sin(atan(k));

		ParShowXYZ[1][0]=x-a*cos(atan(k));	//1��
		ParShowXYZ[1][1]=y+8*a;
		ParShowXYZ[1][2]=z-a*sin(atan(k));

		ParShowXYZ[2][0]=x+a*cos(atan(k));	//2��
		ParShowXYZ[2][1]=y-8*a;
		ParShowXYZ[2][2]=z+a*sin(atan(k));
	}
}

