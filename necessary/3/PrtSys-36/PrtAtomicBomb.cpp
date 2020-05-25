//ԭ�ӵ�Ч����
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

CPrt_AtomicBomb::CPrt_AtomicBomb()	//���캯��
{
}

CPrt_AtomicBomb::~CPrt_AtomicBomb()
{
}


void CPrt_AtomicBomb::GetInitInfo(void)			//��ó�ʼ������
{
	PDD.MAX_PARTICLES=1000;						//���ӵ�����������ɳ���10000��

	PDD.star_x=0.0f;							//����Դ��λ��
	PDD.star_y=-10.0f;
	PDD.star_z=0.0f;

	PDD.lifefate=1.0f;							// �������ӵ���������ֵԼ�����ӵ�������Խ��
	PDD.slowdown=1.0f;							// �������ӵ��ٶȣ���ֵԼ��Խ����ԽСԽ��
	PDD.speedMax=50.0f;							// �ٶ�ֵ
	LoadGLTextures();
	Init();
}

int CPrt_AtomicBomb::LoadGLTextures(void)					//��������ͼ
{
	kw_GroudShockWave.LoadGLTextures();//��������
	kw_BaseWave.LoadGLTextures();		//�ײ�
	kw_BombCore.LoadGLTextures();		//����
	kw_BombCircle.LoadGLTextures();		//����
	kw_BombColumn.LoadGLTextures();		//����
	return true;
}


void CPrt_AtomicBomb::Init(void)					//��ʼ������
{
	screenLife=1.0f;	//���Ϊ1����СΪ0
	screenLifeFate=0.003;

	//�������ʵ������
	//���������ĳ�ʼ��********************************
	kw_GroudShockWave.PDD.MAX_PARTICLES=PDD.MAX_PARTICLES/2;		//������Ŀ
	kw_GroudShockWave.PDD.star_x=0;//PDD.star_x;					//����λ��
	kw_GroudShockWave.PDD.star_y=0;//PDD.star_y;
	kw_GroudShockWave.PDD.star_z=0;//PDD.star_z;
	kw_GroudShockWave.PDD.lifefate=PDD.lifefate;					//����������
	kw_GroudShockWave.PDD.slowdown=PDD.slowdown;					//�ٶȼ�����
	kw_GroudShockWave.speed=PDD.speedMax/5000;
	kw_GroudShockWave.PDD.dead=false;//������
	kw_GroudShockWave.PDD.diecount=0;//û������������
	kw_GroudShockWave.Init();
	
	//�ײ��ĳ�ʼ��**************************************
	kw_BaseWave.PDD.MAX_PARTICLES=PDD.MAX_PARTICLES/2;				//������Ŀ
	kw_BaseWave.PDD.star_x=0;//PDD.star_x;								//����λ��
	kw_BaseWave.PDD.star_y=0;//PDD.star_y;
	kw_BaseWave.PDD.star_z=0;//PDD.star_z;
	kw_BaseWave.PDD.lifefate=PDD.lifefate;							//����������
	kw_BaseWave.PDD.slowdown=PDD.slowdown;							//�ٶȼ�����
	kw_BaseWave.speed=PDD.speedMax/12;
	kw_BaseWave.PDD.dead=false;//������
	kw_BaseWave.PDD.diecount=0;//û������������
	kw_BaseWave.Init();

	//���˵ĳ�ʼ��***************************************
	kw_BombCore.PDD.MAX_PARTICLES=PDD.MAX_PARTICLES/2;				//������Ŀ�����ɳ���5000������
	kw_BombCore.PDD.star_x=0;//PDD.star_x;								//����λ��
	kw_BombCore.PDD.star_y=0;//PDD.star_y;
	kw_BombCore.PDD.star_z=0;//PDD.star_z;
	kw_BombCore.PDD.lifefate=PDD.lifefate;							//����������
	kw_BombCore.PDD.slowdown=PDD.slowdown;							//�ٶȼ�����
	kw_BombCore.speed=PDD.speedMax/10;
	kw_BombCore.PDD.dead=false;//������
	kw_BombCore.PDD.diecount=0;//û������������

	kw_BombCore.Init();

	//�����ĳ�ʼ��********************************
	kw_BombCircle.PDD.MAX_PARTICLES=PDD.MAX_PARTICLES/10;			//������Ŀ
	kw_BombCircle.PDD.star_x=0;//PDD.star_x;							//����λ��
	kw_BombCircle.PDD.star_y=0;//star_y;
	kw_BombCircle.PDD.star_z=0;//PDD.star_z;
	kw_BombCircle.PDD.lifefate=PDD.lifefate;						//����������
	kw_BombCircle.PDD.slowdown=PDD.slowdown;						//�ٶȼ�����
	kw_BombCircle.speed=PDD.speedMax/10;
	kw_BombCircle.PDD.dead=false;//������
	kw_BombCircle.PDD.diecount=0;//û������������

	kw_BombCircle.Init();

	//�����ĳ�ʼ��***********************************

	kw_BombColumn.PDD.MAX_PARTICLES=PDD.MAX_PARTICLES/5;			//������Ŀ
	kw_BombColumn.PDD.star_x=0;//PDD.star_x;							//����λ��
	kw_BombColumn.PDD.star_y=0;//star_y;
	kw_BombColumn.PDD.star_z=0;//PDD.star_z;
	kw_BombColumn.PDD.lifefate=PDD.lifefate;						//����������
	kw_BombColumn.PDD.slowdown=PDD.slowdown;						//�ٶȼ�����
	kw_BombColumn.speed=PDD.speedMax/10;
	kw_BombColumn.PDD.dead=false;//������
	kw_BombColumn.PDD.diecount=0;//û������������

	kw_BombColumn.Init();
}

void CPrt_AtomicBomb::draw(float *Tar2Cam,bool Isplay)					//��ʾ����
{
	if(Isplay)	//���û����ͣ
	{
		if(screenLife<0.0)
		{
			screenLife=1.0;
			Init();
		}
		else screenLife-=screenLifeFate;
	}
	glClearColor(screenLife,screenLife,screenLife,0.5);

	glPushMatrix();
	glTranslatef(PDD.star_x,PDD.star_y,PDD.star_z);
		kw_GroudShockWave.draw(Tar2Cam,Isplay);						//��������
		kw_BaseWave.draw(Tar2Cam,Isplay);							//�ײ�
		kw_BombCore.draw(Tar2Cam,Isplay);							//����
		kw_BombCircle.draw(Tar2Cam,Isplay);							//����
		kw_BombColumn.draw(Tar2Cam,Isplay);							//����
	glPopMatrix();
}


///////////////////////////////////////////////////////////////////////////////////////////////////
//������ĺ���ʵ��
///////////////////////////////////////////////////////////////////////////////////////////////////
//����������ʵ��
int CPrt_AB_GroudShockWave::Init(void)//��ʼ������ϵͳ������λ�á��ٶȡ�������
{
	//��ʼ����������
		speed*=450;
		for (loop=0;loop<PDD.MAX_PARTICLES;loop++)			// Initials All The Textures
		{
				particle[loop].active=true;					// ʹ���е����Ӷ�������
				//����������˥����
				particle[loop].life=1.0f;					// �����е��������������1.0F���0.0f���
				particle[loop].fade=0.003f*PDD.lifefate;		// ͳһ������������

				//����λ�ã�����
				particle[loop].x=PDD.star_x;					// Center On X Axis
				particle[loop].y=PDD.star_y;					// Center On Y Axis
				particle[loop].z=PDD.star_z;					// Center On Z Axis
				//���ӵ��ٶ�

				GWspeed[loop]=speed;
				PDD.speedMax=speed;
				PDD.speedMin=speed;
				//�����Ӹ�����ɫ
				changeColor(loop,0);			
		}
	return TRUE;										// ��ʼ�� OK
}


void CPrt_AB_GroudShockWave::draw(float *Tar2Cam,bool Isplay)//��ʾ����
{
	//*******************************************************************************
	//ѭ����ʾ�����£�ÿ������
	glPushMatrix();
	glEnable(GL_BLEND);									// ���û��ģʽ
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);	 
	glDepthMask(GL_FALSE);
	glBindTexture(GL_TEXTURE_2D, texture[0]);

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

			CParticle::ExchangeShowXYZ(Tar2Cam,x,y,z,(1.1-particle[loop].life)*2);	//�ı���ͼ����
			//�����Ӹ��趯̬��ɫ
			changeColor(loop,1);

			//ÿ�����ӵ���״����һ�������Σ�������������������������ι��ɵ�
			//�������Լӿ� �Կ� �� CPU �������ٶȣ�ע��һ�£��������ε���ͼ����˳��
			glBegin(GL_TRIANGLE_STRIP);	
				glTexCoord2d(1,1); glVertex3f(ParShowXYZ[0][0],	ParShowXYZ[0][1],	ParShowXYZ[0][2]); // Top Right//0
				glTexCoord2d(0,1); glVertex3f(ParShowXYZ[1][0],	ParShowXYZ[1][1],	ParShowXYZ[1][2]); // Top Left	//1
				glTexCoord2d(1,0); glVertex3f(ParShowXYZ[2][0],	ParShowXYZ[2][1],	ParShowXYZ[2][2]); // Bottom Right//2
				glTexCoord2d(0,0); glVertex3f(ParShowXYZ[3][0],	ParShowXYZ[3][1],	ParShowXYZ[3][2]); // Bottom Left//3
			glEnd();

			if(Isplay)
			{
				//������һ������Ļ���ֵ�λ�ã������ڵ�λ�ü����ٶȵ�������λ�á�

				  axz=RandMaxMin(3600,0)/1800.0*PAI;			//��ը�ĽǶ���ȫ��λ��
				  ay=RandMaxMin(GWspeed[loop],GWspeed[loop]*0.8);
					particle[loop].x=ay*cos(axz);
					particle[loop].y=PDD.star_y;
					particle[loop].z=ay*sin(axz);

				//�����ٶȵĸı䣬��������С��0.8���ٶ�Ҫ��ʱ������
				if((particle[loop].life<0.95)&&(particle[loop].life>0.95-particle[loop].fade))
				{
				GWspeed[loop]+=PDD.speedMax*2;
				}
				else GWspeed[loop]+=PDD.speedMax/100;
				//���ӵ�������С
				particle[loop].life-=particle[loop].fade;
			}
			//û�б�Ҫ��������
			//�����ӵ�����������Ҫ��������������������������ˣ��ﲻ��ѭ����Ч����
			if (particle[loop].life<0.0f)
			{
				//����������˥����
				particle[loop].active=false;
				PDD.diecount++;//��������������
				if(PDD.diecount>=PDD.MAX_PARTICLES)//�������ȫ�������������ԴҲ������
					PDD.dead=true;
			}
		}
	}
	glDisable(GL_TEXTURE_2D);

	//////////////////////////////////////////////////////////////////
	//�������ͼ
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glEnable(GL_TEXTURE_2D);

	if(Isplay)
		PDD.speedMin*=1.25;

	glColor4f(1.0,1.0,1.0,speed/PDD.speedMin);

	glBegin(GL_TRIANGLE_STRIP);
		glTexCoord2d(1,1); glVertex3f(PDD.speedMin,		PDD.star_y,	PDD.speedMin); 
		glTexCoord2d(0,1); glVertex3f(-PDD.speedMin,	PDD.star_y,	PDD.speedMin); 
		glTexCoord2d(1,0); glVertex3f(PDD.speedMin,		PDD.star_y,	-PDD.speedMin); 
		glTexCoord2d(0,0); glVertex3f(-PDD.speedMin,	PDD.star_y,	-PDD.speedMin);
	glEnd();

	
	glDisable(GL_TEXTURE_2D);
	//////////////////////////////////////////////////////////
	glEnable(GL_DEPTH_TEST);							// ������Ȳ���(WWWWWWWWWWWWWWW)
	glDisable(GL_BLEND);								// ���û��ģʽ
	glDepthMask(GL_TRUE);
	glPopMatrix();

}

int CPrt_AB_GroudShockWave::LoadGLTextures(void)//��������ͼ
{

	if(!CParticle::LoadGLTextures("������������.BMP",texture[0]))	//��0�Ų���װ����ͼ
	{AfxMessageBox("������������.BMP error!");return FALSE;}
	if(!CParticle::LoadGLTextures("��������.bmp",texture[1]))	//��1�Ų���װ����ͼ
	{AfxMessageBox("��������.bmp error!");return FALSE;}
	return true;
}


//�������ӵ���ɫloop�����ӵı�ţ�modelΪȾɫģʽ
void CPrt_AB_GroudShockWave::changeColor(int loop,int model)
{

	static GLfloat colors[5][3]=	//���ڱ�ըЧ����5����ɫ��Glfloatѡֵ��
	{
		{1.0f,0.996f,0.824f},		//ǳ�ƣ������ǰ�ɫ�Ļƣ�
		{0.953f,0.757f,0.125f},		//��ɫ��ƫ��ɫ��
		{0.965f,0.627f,0.09f},		//����ɫ�����ɫ��
		{0.843f,0.816f,0.784f},		//�Ұ�ɫ
		{0.0001f,0.0001f,0.0001f}	//��ɫ
	};
	int lifecolorset;				//������ɫѡȡֵ

	switch(model)
	{
	case 0:	//�����Ӹ����ʼ��ɫ
		particle[loop].r=colors[loop*(5/PDD.MAX_PARTICLES)][0];		// Select Red Rainbow Color
		particle[loop].g=colors[loop*(5/PDD.MAX_PARTICLES)][1];		// Select Red Rainbow Color
		particle[loop].b=colors[loop*(5/PDD.MAX_PARTICLES)][2];		// Select Red Rainbow Color
		break;
	case 1:
		if(particle[loop].life<=1.0f&&particle[loop].life>=0.8f)lifecolorset=0;
		if(particle[loop].life<0.8f&&particle[loop].life>=0.6f)lifecolorset=1;
		if(particle[loop].life<0.6f&&particle[loop].life>=0.4f)lifecolorset=2;
		if(particle[loop].life<0.4f&&particle[loop].life>=0.2f)lifecolorset=3;
		if(particle[loop].life<0.2f)lifecolorset=4;

		particle[loop].r=colors[lifecolorset][0];
		particle[loop].g=colors[lifecolorset][1];
		particle[loop].b=colors[lifecolorset][2];
		//��ÿ�����Ӹ���ɫ�ʣ�����������ֵ��ΪAlpha,���Կ����������
		glColor4f(particle[loop].r,particle[loop].g,particle[loop].b,(0.5-fabs(particle[loop].life-0.5))*0.05);
		break;
	default:
		particle[loop].r=colors[loop*(5/PDD.MAX_PARTICLES)][0];	
		particle[loop].g=colors[loop*(5/PDD.MAX_PARTICLES)][1];	
		particle[loop].b=colors[loop*(5/PDD.MAX_PARTICLES)][2];	
		break;
	}
}


////////////////////////////////////////////////////////////////////////////////////
//********************************************************************************
//�ײ���ʵ��
//********************************************************************************
////////////////////////////////////////////////////////////////////////////////////
int CPrt_AB_BaseWave::Init(void)//��ʼ������ϵͳ������λ�á��ٶȡ�������
{
	//��ʼ����������
	//���ӵ��ٶ�
	PDD.speedMax=speed;
	PDD.speedMin=speed;
		for (loop=0;loop<PDD.MAX_PARTICLES;loop++)
		{
				particle[loop].active=true;					// ʹ���е����Ӷ�������
				//����������˥����
				particle[loop].life=1.0f;					// �����е��������������1.0F���0.0f���
				particle[loop].fade=0.003f*PDD.lifefate;	// ͳһ������������

				//����λ�ã�����
				particle[loop].x=PDD.star_x;
				particle[loop].y=PDD.star_y+RandMaxMin(0.1,0);
				particle[loop].z=PDD.star_z;

				speed=RandMaxMin(PDD.speedMax,PDD.speedMax/5.0);	//��ը���ٶ�
				  prtAngle[loop]=RandMaxMin(360,0)/180.0*PAI;			//��ը�ĽǶ���ȫ��λ��
												//��¼��ת���ǶȺ���ͼ
				particle[loop].xi=speed*cos(prtAngle[loop]);
				particle[loop].yi=0;
				particle[loop].zi=speed*sin(prtAngle[loop]);

				//�����Ӹ�����ɫ
				changeColor(loop,0);			
		}
	return TRUE;// ��ʼ�� OK
}


void CPrt_AB_BaseWave::draw(float *Tar2Cam,bool Isplay)//��ʾ����
{
	//*******************************************************************************
	//ѭ����ʾ�����£�ÿ������
	glPushMatrix();
	glEnable(GL_BLEND);									// ���û��ģʽ
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);

	//�ײ��ĳ����
	glDepthMask(GL_FALSE);
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glEnable(GL_TEXTURE_2D);
	for (loop=0;loop<PDD.MAX_PARTICLES/2;loop++)
	{
		//����������У����е����Ӷ��ǻ��ŵģ����ǿ�����������
		if (particle[loop].active)						// �鿴�����Ƿ�����
		{
			//���ӵ�λ��
			float x=particle[loop].x;
			float y=particle[loop].y;
			float z=particle[loop].z;
			//�ı���ͼ����
			float a=(1.1-particle[loop].life)*2;	//��ͼ���
			//�����Ӹ��趯̬��ɫ
			changeColor(loop,1);

			ExchangeShowXYZ(x,y,z,a);	//�ı���ͼ����
			
			//ÿ�����ӵ���״����һ�������Σ�������������������������ι��ɵ�
			//�������Լӿ� �Կ� �� CPU �������ٶȣ�ע��һ�£��������ε���ͼ����˳��
			glBegin(GL_TRIANGLE_STRIP);
				glTexCoord2d(1,1); glVertex3f(ParShowXYZ[0][0],	ParShowXYZ[0][1],	ParShowXYZ[0][2]); // Top Right//0
				glTexCoord2d(0,1); glVertex3f(ParShowXYZ[1][0],	ParShowXYZ[1][1],	ParShowXYZ[1][2]); // Top Left	//1
				glTexCoord2d(1,0); glVertex3f(ParShowXYZ[2][0],	ParShowXYZ[2][1],	ParShowXYZ[2][2]); // Bottom Right//2
				glTexCoord2d(0,0); glVertex3f(ParShowXYZ[3][0],	ParShowXYZ[3][1],	ParShowXYZ[3][2]); // Bottom Left//3
			glEnd();
		

		if(Isplay)
		{
			//������һ������Ļ���ֵ�λ�ã������ڵ�λ�ü����ٶȵ�������λ�á�
			particle[loop].x+=particle[loop].xi/(PDD.slowdown*10);
			particle[loop].y+=particle[loop].yi/(PDD.slowdown*10);
			particle[loop].z+=particle[loop].zi/(PDD.slowdown*10);

			//�����ٶȵĸı䣬��������С��0.8���ٶ�Ҫ��ʱ������
			if((particle[loop].life<0.95)&&(particle[loop].life>0.95-particle[loop].fade))
			{

			particle[loop].xi*=0.1;
			particle[loop].yi*=0.1;
			particle[loop].zi*=0.1;

			}

			//���ӵ�������С
			particle[loop].life-=particle[loop].fade;
		}
			//û�б�Ҫ��������
			//�����ӵ�����������Ҫ��������������������������ˣ��ﲻ��ѭ����Ч����
			if (particle[loop].life<0.0f)
			{

				//����������˥����
				particle[loop].active=false;
				PDD.diecount++;//��������������
				if(PDD.diecount>=PDD.MAX_PARTICLES)//�������ȫ�������������ԴҲ������
					PDD.dead=true;
			}
		}
	}
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);								// ���û��ģʽ
	glDepthMask(GL_TRUE);
	glPopMatrix();

	//////////////////////////////////////////////////////////////////
	//�ײ�������
	glPushMatrix();
	glEnable(GL_BLEND);									// ���û��ģʽ
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);	 
	glDepthMask(GL_FALSE);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glEnable(GL_TEXTURE_2D);

	for (loop=PDD.MAX_PARTICLES/2;loop<PDD.MAX_PARTICLES;loop++)
	{
		//����������У����е����Ӷ��ǻ��ŵģ����ǿ�����������
		if (particle[loop].active)						// �鿴�����Ƿ�����
		{
			//���ӵ�λ��
			float x=particle[loop].x;				 
			float y=particle[loop].y;
			float z=particle[loop].z;
			
			//�����Ӹ��趯̬��ɫ
			changeColor(loop,2);
			//�ı���ͼ����
			CParticle::ExchangeShowXYZ(Tar2Cam,x,y,z,(1.1-particle[loop].life));

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
				particle[loop].x+=particle[loop].xi/(PDD.slowdown*10);
				particle[loop].y+=particle[loop].yi/(PDD.slowdown*10);
				particle[loop].z+=particle[loop].zi/(PDD.slowdown*10);
				//������һ������Ļ���ֵ�λ�ã������ڵ�λ�ü����ٶȵ�������λ�á�
				//�����ٶȵĸı䣬��������С��0.95���ٶ�Ҫ��ʱ������

				if((particle[loop].life<0.9)&&(particle[loop].life>0.9-particle[loop].fade))
				{
				particle[loop].xi*=-0.05;
				particle[loop].yi=1/(particle[loop].x*particle[loop].x+particle[loop].z*particle[loop].z);			// Take Pull On Y Axis Into Account
				particle[loop].zi*=-0.05;
				}

				//���ӵ�������С
				particle[loop].life-=particle[loop].fade;
			}
			//û�б�Ҫ��������
			//�����ӵ�����������Ҫ��������������������������ˣ��ﲻ��ѭ����Ч����
			if (particle[loop].life<0.0f)
			{
				//����������˥����
				particle[loop].active=false;
				PDD.diecount++;//��������������
				if(PDD.diecount>=PDD.MAX_PARTICLES)//�������ȫ�������������ԴҲ������
					PDD.dead=true;
			}
		}
	}
	glDisable(GL_ALPHA_TEST);
	glDisable(GL_TEXTURE_2D);
	//////////////////////////////////////////////////////////
	glDisable(GL_BLEND);								// ���û��ģʽ
	glDepthMask(GL_TRUE);
	glPopMatrix();

}

int CPrt_AB_BaseWave::LoadGLTextures(void)//��������ͼ
{

	if(!CParticle::LoadGLTextures("����21.bmp",texture[0]))	//��0�Ų���װ����ͼ
	{AfxMessageBox("����21.bmp error!");return FALSE;}
	if(!CParticle::LoadGLTextures("����4.bmp",texture[1]))	//��1�Ų���װ����ͼ
	{AfxMessageBox("����4.bmp error!");return FALSE;}
	return true;
}


//�������ӵ���ɫloop�����ӵı�ţ�modelΪȾɫģʽ
void CPrt_AB_BaseWave::changeColor(int loop,int model)
{

	static GLfloat colors[5][3]=	//���ڱ�ըЧ����5����ɫ��Glfloatѡֵ��
	{
		{1.0f,0.996f,0.824f},		//ǳ�ƣ������ǰ�ɫ�Ļƣ�
		{0.953f,0.757f,0.125f},		//��ɫ��ƫ��ɫ��
		{0.965f,0.627f,0.09f},		//����ɫ�����ɫ��
		{0.843f,0.816f,0.784f},		//�Ұ�ɫ
		{0.001f,0.001f,0.001f}			//��ɫ
	};
	int lifecolorset;					//������ɫѡȡֵ

	switch(model)
	{
	case 0:	//�����Ӹ����ʼ��ɫ
		particle[loop].r=colors[loop*(5/PDD.MAX_PARTICLES)][0];
		particle[loop].g=colors[loop*(5/PDD.MAX_PARTICLES)][1];
		particle[loop].b=colors[loop*(5/PDD.MAX_PARTICLES)][2];
		break;
	case 1:
		if(particle[loop].life<=1.0f&&particle[loop].life>=0.8f)lifecolorset=0;
		if(particle[loop].life<0.8f&&particle[loop].life>=0.6f)lifecolorset=1;
		if(particle[loop].life<0.6f&&particle[loop].life>=0.4f)lifecolorset=2;
		if(particle[loop].life<0.4f&&particle[loop].life>=0.2f)lifecolorset=3;
		if(particle[loop].life<0.2f)lifecolorset=4;

		particle[loop].r=colors[lifecolorset][0];
		particle[loop].g=colors[lifecolorset][1];
		particle[loop].b=colors[lifecolorset][2];
		//��ÿ�����Ӹ���ɫ�ʣ�����������ֵ��ΪAlpha,���Կ����������
		glColor4f(particle[loop].r,particle[loop].g,particle[loop].b,particle[loop].life*0.2);
		break;
	case 2:	//�����Ӹ����ʼ��ɫ
		float g;
		if(particle[loop].life<=1.0f&&particle[loop].life>=0.5f)
		{
			g=(1-particle[loop].life)*0.7;

		}
		if(particle[loop].life<0.5f)
		{
			g=particle[loop].life*0.7;
		}
			glColor4f(0.965f,0.627f,0.09f,g);
		break;
	default:
		particle[loop].r=colors[loop*(5/PDD.MAX_PARTICLES)][0];
		particle[loop].g=colors[loop*(5/PDD.MAX_PARTICLES)][1];
		particle[loop].b=colors[loop*(5/PDD.MAX_PARTICLES)][2];
		break;
	}
}

void CPrt_AB_BaseWave::ExchangeShowXYZ(float x,float y,float z,float a)
{
	
	float z0=z-PDD.star_z;
	float x0=x-PDD.star_x;
	if(x0==0)//б�ʵ�������������⿼��
	{
		if(z<PDD.star_z)
		{
			ParShowXYZ[0][0]=0;//x+a;
			ParShowXYZ[0][1]=0;//y;
			ParShowXYZ[0][2]=0;//z+2*a;

			ParShowXYZ[1][0]=0;//x-a;
			ParShowXYZ[1][1]=0;//y;
			ParShowXYZ[1][2]=0;//z+2*a;

			ParShowXYZ[2][0]=0;//x+a;
			ParShowXYZ[2][1]=0;//y;
			ParShowXYZ[2][2]=0;//z-2*a;

			ParShowXYZ[3][0]=0;//x-a;
			ParShowXYZ[3][1]=0;//y;
			ParShowXYZ[3][2]=0;//z-2*a;
		}
		else
		{
			ParShowXYZ[3][0]=x+a;
			ParShowXYZ[3][1]=y;
			ParShowXYZ[3][2]=z+2*a;

			ParShowXYZ[2][0]=x-a;
			ParShowXYZ[2][1]=y;
			ParShowXYZ[2][2]=z+2*a;

			ParShowXYZ[1][0]=x+a;
			ParShowXYZ[1][1]=y;
			ParShowXYZ[1][2]=z-2*a;

			ParShowXYZ[0][0]=x-a;
			ParShowXYZ[0][1]=y;
			ParShowXYZ[0][2]=z-2*a;
		}
	}
	else if(z0==0)
		{
		if(x<=PDD.star_x)
			{
				ParShowXYZ[0][0]=x+2*a;
				ParShowXYZ[0][1]=y;
				ParShowXYZ[0][2]=z-a;

				ParShowXYZ[1][0]=x+2*a;
				ParShowXYZ[1][1]=y;
				ParShowXYZ[1][2]=z+a;

				ParShowXYZ[2][0]=x-2*a;
				ParShowXYZ[2][1]=y;
				ParShowXYZ[2][2]=z+a;

				ParShowXYZ[3][0]=x-2*a;
				ParShowXYZ[3][1]=y;
				ParShowXYZ[3][2]=z-a;
			}
			else
			{
				ParShowXYZ[2][0]=x+2*a;
				ParShowXYZ[2][1]=y;
				ParShowXYZ[2][2]=z-a;

				ParShowXYZ[3][0]=x+2*a;
				ParShowXYZ[3][1]=y;
				ParShowXYZ[3][2]=z+a;

				ParShowXYZ[0][0]=x-2*a;
				ParShowXYZ[0][1]=y;
				ParShowXYZ[0][2]=z+a;

				ParShowXYZ[1][0]=x-2*a;
				ParShowXYZ[1][1]=y;
				ParShowXYZ[1][2]=z-a;
			}
		}
	else //�ų�б�ʵ����������ļ���,������̼��ʼǱ�
	{
		float k=z0/x0;
		float t=k/(k*k+1);
		float m1=z-k*x-a*sqrt(1+k*k);
		float m2=z-k*x+a*sqrt(1+k*k);
		float m3=z+(1/k)*x-2*a/k*sqrt(1+k*k);
		float m4=z+(1/k)*x+2*a/k*sqrt(1+k*k);

		int a,b,c,d;
		if(x0>0)
		{a=0;b=1;c=2;d=3;
		}
		else
		{
			a=3;b=2;c=1;d=0;
		}
				ParShowXYZ[a][0]=t*(m3-m1);
				ParShowXYZ[a][1]=y;
				ParShowXYZ[a][2]=k*t*(m3-m1)+m1;

				ParShowXYZ[b][0]=t*(m3-m2);
				ParShowXYZ[b][1]=y;
				ParShowXYZ[b][2]=k*t*(m3-m2)+m2;

				ParShowXYZ[c][0]=t*(m4-m1);
				ParShowXYZ[c][1]=y;
				ParShowXYZ[c][2]=k*t*(m4-m1)+m1;

				ParShowXYZ[d][0]=t*(m4-m2);
				ParShowXYZ[d][1]=y;
				ParShowXYZ[d][2]=k*t*(m4-m2)+m2;
	}
}

///////////////////////////////////////////////////////////////////////////////////////
//========================================================================================
//���˵�ʵ��
//=======================================================================================
/////////////////////////////////////////////////////////////////////////////////////////
int CPrt_AB_BombCore::Init(void)//��ʼ������ϵͳ������λ�á��ٶȡ�������
{

	core_y=PDD.star_y;	//���ĵ�λ�� Y��
	corei=speed/80;		//���ĵ��ٶ� Y��
	coreg=0;			//���ĵļ��ٶ� Y��
	PDD.speedMax=speed;
	PDD.speedMin=corei;
	//*******************************************************************************
	//��ʼ����������
		for (loop=0;loop<PDD.MAX_PARTICLES;loop++)
		{
				particle[loop].active=true;					// ʹ���е����Ӷ�������
				//����������˥����
				particle[loop].life=1.0;					// �����е��������������1.0F���0.0f���
				particle[loop].fade=0.003f*PDD.lifefate;		// ͳһ������������

				//����λ�ã�����
				particle[loop].x=PDD.star_x;
				particle[loop].y=core_y;
				particle[loop].z=PDD.star_z;

				//���ӵ��ٶ�
				speed=RandMaxMin(PDD.speedMax,PDD.speedMax/1.5);
				  prtAxz[loop]=RandMaxMin(360,0)/180.0*PAI;			//��ը�ĽǶ���ȫ��λ��
				   prtAy[loop]=RandMaxMin(90,0)/180.0*PAI;
				particle[loop].xi=speed*cos(prtAxz[loop])*sin(prtAy[loop])*2;	
				particle[loop].yi=speed*cos(prtAy[loop]);						
				particle[loop].zi=speed*sin(prtAxz[loop])*sin(prtAy[loop])*2;			
				a[loop]=-1;
				//�����Ӹ�����ɫ
				changeColor(loop,1);			
		}
	return TRUE;										// ��ʼ�� OK
}


void CPrt_AB_BombCore::draw(float *Tar2Cam,bool Isplay)//��ʾ����
{
	//*******************************************************************************
	//ѭ����ʾ�����£�ÿ������
	glPushMatrix();
	glEnable(GL_BLEND);									// ���û��ģʽ
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);	 
	glDepthMask(GL_FALSE);
	glBindTexture(GL_TEXTURE_2D, texture[0]);

	glEnable(GL_TEXTURE_2D);
	if(Isplay)
	{
		core_y+=corei;	//���ƺ��ĵ��ٶ�
		if(corei>0)corei+=coreg;
		else corei=0;
	}

	for (loop=0;loop<PDD.MAX_PARTICLES;loop++)
	{
		//����������У����е����Ӷ��ǻ��ŵģ����ǿ�����������
		if (particle[loop].active)						// �鿴�����Ƿ�����
		{
			//���ӵ�λ��
			if(Isplay)
			{
				particle[loop].x+=particle[loop].xi/(PDD.slowdown*10);
				particle[loop].y+=particle[loop].yi/(PDD.slowdown*10)+corei;
				particle[loop].z+=particle[loop].zi/(PDD.slowdown*10);
				changeForce(loop);//�ı����ӵ�λ�á��ٶȺͼ��ٶ�
			}
			float x=particle[loop].x;				 
			float y=particle[loop].y;
			float z=particle[loop].z;

			float R=sqrt((PDD.star_x-x)*(PDD.star_x-x)+(PDD.star_z-z)*(PDD.star_z-z));
			CParticle::ExchangeShowXYZ(Tar2Cam,x,y,z,(R*0.5+0.02)*0.3);	//�ı���ͼ����
			//�����Ӹ��趯̬��ɫ
			changeColor(loop,1);

			//ÿ�����ӵ���״����һ�������Σ�������������������������ι��ɵ�
			//�������Լӿ� �Կ� �� CPU �������ٶȣ�ע��һ�£��������ε���ͼ����˳��
			glBegin(GL_TRIANGLE_STRIP);
				glTexCoord2d(1,1); glVertex3f(ParShowXYZ[0][0],	ParShowXYZ[0][1],	ParShowXYZ[0][2]); // Top Right//0
				glTexCoord2d(0,1); glVertex3f(ParShowXYZ[1][0],	ParShowXYZ[1][1],	ParShowXYZ[1][2]); // Top Left	//1
				glTexCoord2d(1,0); glVertex3f(ParShowXYZ[2][0],	ParShowXYZ[2][1],	ParShowXYZ[2][2]); // Bottom Right//2
				glTexCoord2d(0,0); glVertex3f(ParShowXYZ[3][0],	ParShowXYZ[3][1],	ParShowXYZ[3][2]); // Bottom Left//3
			glEnd();

		
			//���ӵ�������С
			if(Isplay)
				particle[loop].life-=particle[loop].fade;

			//û�б�Ҫ��������
			//�����ӵ�����������Ҫ��������������������������ˣ��ﲻ��ѭ����Ч����
			if (particle[loop].life<0.0f)
			{
				particle[loop].active=false;
				PDD.diecount++;//��������������
				if(PDD.diecount>=PDD.MAX_PARTICLES)//�������ȫ�������������ԴҲ������
					PDD.dead=true;
			}
		}
	}
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);							// ������Ȳ���(WWWWWWWWWWWWWWW)
	glDisable(GL_BLEND);								// ���û��ģʽ
	glDepthMask(GL_TRUE);
	glPopMatrix();

}

int CPrt_AB_BombCore::LoadGLTextures(void)//��������ͼ
{
	if(!CParticle::LoadGLTextures("������������.BMP",texture[0]))	//��0�Ų���װ����ͼ
	{AfxMessageBox("������������.BMP error!");return FALSE;}
	return TRUE;
}


//�������ӵ���ɫloop�����ӵı�ţ�modelΪȾɫģʽ
void CPrt_AB_BombCore::changeColor(int loop,int model)
{

	static GLfloat colors[5][3]=	//���ڱ�ըЧ����5����ɫ��Glfloatѡֵ��
	{
		{1.0f,0.996f,0.824f},		//ǳ�ƣ������ǰ�ɫ�Ļƣ�
		{0.953f,0.757f,0.125f},		//��ɫ��ƫ��ɫ��
		{0.965f,0.627f,0.09f},		//����ɫ�����ɫ��
		{0.965f,0.429f,0.09f},		//����ɫ�����ɫ��
		{0.965f,0.359f,0.09f},		//����ɫ�����ɫ��

	};
	int lifecolorset;					//������ɫѡȡֵ

	switch(model)
	{
	case 0:	//�����Ӹ����ʼ��ɫ
		particle[loop].r=colors[loop*(5/PDD.MAX_PARTICLES)][0];		// Select Red Rainbow Color
		particle[loop].g=colors[loop*(5/PDD.MAX_PARTICLES)][1];		// Select Red Rainbow Color
		particle[loop].b=colors[loop*(5/PDD.MAX_PARTICLES)][2];		// Select Red Rainbow Color
		break;
	case 1:
		if(particle[loop].life<=1.0f&&particle[loop].life>=0.9f)lifecolorset=0;
		if(particle[loop].life<0.9f&&particle[loop].life>=0.8f)lifecolorset=1;
		if(particle[loop].life<0.8f&&particle[loop].life>=0.6f)lifecolorset=2;
		if(particle[loop].life<0.6f&&particle[loop].life>=0.2f)lifecolorset=3;
		if(particle[loop].life<0.2f)lifecolorset=4;
		particle[loop].r=colors[lifecolorset][0];
		particle[loop].g=colors[lifecolorset][1];
		particle[loop].b=colors[lifecolorset][2];
		//��ÿ�����Ӹ���ɫ�ʣ�����������ֵ��ΪAlpha,���Կ����������
		glColor4f(particle[loop].r,particle[loop].g,particle[loop].b,(particle[loop].life+0.2)*0.5);
		break;
	default:
		particle[loop].r=colors[loop*(5/PDD.MAX_PARTICLES)][0];	
		particle[loop].g=colors[loop*(5/PDD.MAX_PARTICLES)][1];	
		particle[loop].b=colors[loop*(5/PDD.MAX_PARTICLES)][2];	
		break;
	}
}

void CPrt_AB_BombCore::changeForce(int loop)
{
	float R=sqrt((PDD.star_x-particle[loop].x)*(PDD.star_x-particle[loop].x)
		+(core_y-particle[loop].y)*(core_y-particle[loop].y)
		+(PDD.star_z-particle[loop].z)*(PDD.star_z-particle[loop].z));
	//////////////////////////////////////
	float	rotatespeed;	//���Ʒ����ٶ�
	rotatespeed=0.005;
	if(particle[loop].life<0.2)
		rotatespeed=0.002;

	if(particle[loop].life>0.98)
	{
		particle[loop].xg=0;
		particle[loop].yg=0;
		particle[loop].zg=0;

		particle[loop].xi+=particle[loop].xg;
		particle[loop].yi+=particle[loop].yg;
		particle[loop].zi+=particle[loop].zg;

	}
	else	if((particle[loop].life<=0.98)&&(particle[loop].life>=(0.99-particle[loop].fade)))
	{
		//�������ٶȽ�����
			particle[loop].xi=0;
			particle[loop].yi=0;
			particle[loop].zi=0;

	}
	else 	if((particle[loop].life<(0.99-particle[loop].fade))&&(particle[loop].life>0.02))
	{
		if(particle[loop].y>=core_y)	//�ϰ��򷭹��ٶ�
		{
			prtAy[loop]+=rotatespeed;
			particle[loop].x=PDD.star_x+R*cos(prtAxz[loop])*sin(prtAy[loop]);
			particle[loop].y=core_y+R*cos(prtAy[loop]);	
			particle[loop].z=PDD.star_z+R*sin(prtAxz[loop])*sin(prtAy[loop]);
		}
		else						//�°��򷭹��ٶȡ�
		{
			if(a[loop]<0)a[loop]=R;	//ֻ�ڵ�һ�ζ�������ϵ�İ뾶���и�ֵ
			prtAy[loop]+=rotatespeed;
			R=sqrt(-a[loop]*a[loop]*cos(2*prtAy[loop]));
			particle[loop].x=PDD.star_x+R*cos(prtAxz[loop])*sin(prtAy[loop]);
			particle[loop].y=core_y+R*cos(prtAy[loop]);
			particle[loop].z=PDD.star_z+R*sin(prtAxz[loop])*sin(prtAy[loop]);
		}

			particle[loop].xi=0;
			particle[loop].yi=0;
			particle[loop].zi=0;
	}
	else
	{
		particle[loop].xi=0;
		particle[loop].yi=0;
		particle[loop].zi=0;
	}

}

////////////////////////////////////////////////////////////////////////////////////////
//00000000000000000000000000000000000000000000000000000000000000000000000000000000000000
//������ʵ��
//00000000000000000000000000000000000000000000000000000000000000000000000000000000000000
////////////////////////////////////////////////////////////////////////////////////////
int CPrt_AB_BombCircle::Init(void)//��ʼ������ϵͳ������λ�á��ٶȡ�������
{

	//*******************************************************************************
	//��ʼ����������
		for (loop=0;loop<PDD.MAX_PARTICLES;loop++)
		{
				particle[loop].active=true;					// ʹ���е����Ӷ�������
				//����������˥����
				particle[loop].life=1.0f;					// �����е��������������1.0F���0.0f���
				particle[loop].fade=0.003f*PDD.lifefate;		// ͳһ������������

				//����λ�ã�����
				particle[loop].x=PDD.star_x;
				particle[loop].y=PDD.star_y;
				particle[loop].z=PDD.star_z;
				//���ӵ��ٶ�

				  axz=RandMaxMin(360,0)/180.0*PAI;			//��ը�ĽǶ���ȫ��λ��
				  ay=RandMaxMin(speed*2,speed);
				particle[loop].xi=ay*cos(axz);			
				particle[loop].zi=ay*sin(axz);
				particle[loop].yi=speed*0.005;

				PDD.speedMax=speed;
				PDD.speedMin=speed;
				//�����Ӹ�����ɫ
				changeColor(loop,0);			
		}
	return TRUE;										// ��ʼ�� OK
}


void CPrt_AB_BombCircle::draw(float *Tar2Cam,bool Isplay)//��ʾ����
{
	//*******************************************************************************
	//ѭ����ʾ�����£�ÿ������
	glPushMatrix();
	glEnable(GL_BLEND);									// ���û��ģʽ
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);	 
	glDepthMask(GL_FALSE);
	glBindTexture(GL_TEXTURE_2D, texture[0]);

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

			float R=sqrt((PDD.star_x-x)*(PDD.star_x-x)+(PDD.star_z-z)*(PDD.star_z-z));
			CParticle::ExchangeShowXYZ(Tar2Cam,x,y,z,(R*0.5+2)*0.3);	//�ı���ͼ����

			//�����Ӹ��趯̬��ɫ
			changeColor(loop,1);

			//ÿ�����ӵ���״����һ�������Σ�������������������������ι��ɵ�
			//�������Լӿ� �Կ� �� CPU �������ٶȣ�ע��һ�£��������ε���ͼ����˳��
			glBegin(GL_TRIANGLE_STRIP);
				glTexCoord2d(1,1); glVertex3f(ParShowXYZ[0][0],	ParShowXYZ[0][1],	ParShowXYZ[0][2]); 
				glTexCoord2d(0,1); glVertex3f(ParShowXYZ[1][0],	ParShowXYZ[1][1],	ParShowXYZ[1][2]); 
				glTexCoord2d(1,0); glVertex3f(ParShowXYZ[2][0],	ParShowXYZ[2][1],	ParShowXYZ[2][2]); 
				glTexCoord2d(0,0); glVertex3f(ParShowXYZ[3][0],	ParShowXYZ[3][1],	ParShowXYZ[3][2]); 
			glEnd();

			//������һ������Ļ���ֵ�λ�ã������ڵ�λ�ü����ٶȵ�������λ�á�
			if(Isplay)
			{

				particle[loop].x+=particle[loop].xi/(PDD.slowdown*100);	
				particle[loop].z+=particle[loop].zi/(PDD.slowdown*100);
				particle[loop].y+=particle[loop].yi;

				//�����ٶȵĸı䣬��������С��0.8���ٶ�Ҫ��ʱ������
				if((particle[loop].life<0.80)&&(particle[loop].life>0.80-particle[loop].fade))
				{
				particle[loop].xi*=-0.15;
				particle[loop].zi*=-0.15;			
				}
				//���ӵ�������С
				particle[loop].life-=particle[loop].fade;
			}
			//û�б�Ҫ��������
			//�����ӵ�����������Ҫ��������������������������ˣ��ﲻ��ѭ����Ч����
			if (particle[loop].life<0.0f)
			{
				//����������˥����
				particle[loop].active=false;
				PDD.diecount++;//��������������
				if(PDD.diecount>=PDD.MAX_PARTICLES)//�������ȫ�������������ԴҲ������
					PDD.dead=true;
			}
		}
	}
	glDisable(GL_TEXTURE_2D);

	//////////////////////////////////////////////////////////////////
	//�������ͼ
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glEnable(GL_TEXTURE_2D);
	if(Isplay)
		PDD.speedMin*=1.05;//������ͼ����ļ��ٶ�
	glColor4f(1.0,1.0,1.0,speed/PDD.speedMin+0.2);

	glBegin(GL_TRIANGLE_STRIP);
		glTexCoord2d(1,1); glVertex3f(PDD.speedMin,		PDD.star_y+PDD.speedMin*0.08,	PDD.speedMin); // Top Right//0
		glTexCoord2d(0,1); glVertex3f(-PDD.speedMin,	PDD.star_y+PDD.speedMin*0.08,	PDD.speedMin); // Top Left	//1
		glTexCoord2d(1,0); glVertex3f(PDD.speedMin,		PDD.star_y+PDD.speedMin*0.08,	-PDD.speedMin); // Bottom Right//2
		glTexCoord2d(0,0); glVertex3f(-PDD.speedMin,	PDD.star_y+PDD.speedMin*0.08,	-PDD.speedMin); // Bottom Left//3
	glEnd();

	
	glDisable(GL_TEXTURE_2D);
	//////////////////////////////////////////////////////////
	glEnable(GL_DEPTH_TEST);							// ������Ȳ���(WWWWWWWWWWWWWWW)
	glDisable(GL_BLEND);								// ���û��ģʽ
	glDepthMask(GL_TRUE);
	glPopMatrix();

}

int CPrt_AB_BombCircle::LoadGLTextures(void)//��������ͼ
{
	//������ͼ
	if(!CParticle::LoadGLTextures("������������.BMP",texture[0]))	//��0�Ų���װ����ͼ
	{AfxMessageBox("������������.BMP error!");return FALSE;}
	//�������ͼ
	if(!CParticle::LoadGLTextures("���������.bmp",texture[1]))	//��0�Ų���װ����ͼ
	{AfxMessageBox("���������.bmp error!");return FALSE;}
	return TRUE;
}


//�������ӵ���ɫloop�����ӵı�ţ�modelΪȾɫģʽ
void CPrt_AB_BombCircle::changeColor(int loop,int model)
{

	static GLfloat colors[5][3]=				//���ڱ�ըЧ����5����ɫ��Glfloatѡֵ��
	{
		{1.0f,0.996f,0.824f},		//ǳ�ƣ������ǰ�ɫ�Ļƣ�
		{0.953f,0.757f,0.125f},		//��ɫ��ƫ��ɫ��
		{0.965f,0.627f,0.09f},		//����ɫ�����ɫ��
		{0.965f,0.429f,0.09f},		//����ɫ�����ɫ��
		{0.965f,0.359f,0.09f}		//����ɫ�����ɫ��
	};
	int lifecolorset;					//������ɫѡȡֵ

	switch(model)
	{
	case 0:	//�����Ӹ����ʼ��ɫ
		particle[loop].r=colors[loop*(5/PDD.MAX_PARTICLES)][0];
		particle[loop].g=colors[loop*(5/PDD.MAX_PARTICLES)][1];
		particle[loop].b=colors[loop*(5/PDD.MAX_PARTICLES)][2];	
		break;
	case 1:
		if(particle[loop].life<=1.0f&&particle[loop].life>=0.9f)lifecolorset=0;
		if(particle[loop].life<0.9f&&particle[loop].life>=0.8f)lifecolorset=1;
		if(particle[loop].life<0.8f&&particle[loop].life>=0.6f)lifecolorset=2;
		if(particle[loop].life<0.6f&&particle[loop].life>=0.2f)lifecolorset=3;
		if(particle[loop].life<0.2f)lifecolorset=4;

		particle[loop].r=colors[lifecolorset][0];
		particle[loop].g=colors[lifecolorset][1];
		particle[loop].b=colors[lifecolorset][2];
		//��ÿ�����Ӹ���ɫ�ʣ�����������ֵ��ΪAlpha,���Կ����������
		glColor4f(particle[loop].r,particle[loop].g,particle[loop].b,(0.5-fabs(particle[loop].life-0.5))*1.0);
		break;
	default:
		particle[loop].r=colors[loop*(5/PDD.MAX_PARTICLES)][0];
		particle[loop].g=colors[loop*(5/PDD.MAX_PARTICLES)][1];
		particle[loop].b=colors[loop*(5/PDD.MAX_PARTICLES)][2];	
		break;
	}
}

////////////////////////////////////////////////////////////////////////////////////////
//00000000000000000000000000000000000000000000000000000000000000000000000000000000000000
//������ʵ��
//00000000000000000000000000000000000000000000000000000000000000000000000000000000000000
////////////////////////////////////////////////////////////////////////////////////////
int CPrt_AB_BombColumn::Init(void)//��ʼ������ϵͳ������λ�á��ٶȡ�������
{
	PDD.AngleYStar=speed/2;//���Ĵֶ�
	//*******************************************************************************
	//��ʼ����������
		for (loop=0;loop<1999;loop++)
		{
				particle[loop].active=true;					// ʹ���е����Ӷ�������
				//����������˥����
				particle[loop].life=1.0f;					// �����е��������������1.0F���0.0f���
				particle[loop].fade=0.003f*PDD.lifefate;	// ͳһ������������
				//����λ�ã�����
				 axz=RandMaxMin(360,0)/180.0*PAI;			//��ը�ĽǶ���ȫ��λ��
				  ay=RandMaxMin(speed*2,speed/2);
				particle[loop].x=PDD.star_x+ay*cos(axz);
				particle[loop].y=PDD.star_y;					
				particle[loop].z=PDD.star_z+ay*sin(axz);	
				//���ӵ��ٶ�

				particle[loop].xi=(PDD.star_x-particle[loop].x)*0.02;			
				particle[loop].zi=(PDD.star_z-particle[loop].z)*0.02;
				particle[loop].yi=0;

				//�����Ӹ�����ɫ
				changeColor(loop,1);			
		}
	return TRUE;										// ��ʼ�� OK
}


void CPrt_AB_BombColumn::draw(float *Tar2Cam,bool Isplay)//��ʾ����
{
	//*******************************************************************************
	//ѭ����ʾ�����£�ÿ������
	glPushMatrix();
	glEnable(GL_BLEND);									// ���û��ģʽ
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);	 
	glDepthMask(GL_FALSE);
	glBindTexture(GL_TEXTURE_2D, texture[0]);

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

			float R=sqrt((PDD.star_x-x)*(PDD.star_x-x)+(PDD.star_z-z)*(PDD.star_z-z));
			CParticle::ExchangeShowXYZ(Tar2Cam,x,y,z,0.8);	//�ı���ͼ����

			//�����Ӹ��趯̬��ɫ
			changeColor(loop,1);

			//ÿ�����ӵ���״����һ�������Σ�������������������������ι��ɵ�
			//�������Լӿ� �Կ� �� CPU �������ٶȣ�ע��һ�£��������ε���ͼ����˳��
			glBegin(GL_TRIANGLE_STRIP);
				glTexCoord2d(1,1); glVertex3f(ParShowXYZ[0][0],	ParShowXYZ[0][1],	ParShowXYZ[0][2]); // Top Right//0
				glTexCoord2d(0,1); glVertex3f(ParShowXYZ[1][0],	ParShowXYZ[1][1],	ParShowXYZ[1][2]); // Top Left	//1
				glTexCoord2d(1,0); glVertex3f(ParShowXYZ[2][0],	ParShowXYZ[2][1],	ParShowXYZ[2][2]); // Bottom Right//2
				glTexCoord2d(0,0); glVertex3f(ParShowXYZ[3][0],	ParShowXYZ[3][1],	ParShowXYZ[3][2]); // Bottom Left//3
			glEnd();

			//������һ������Ļ���ֵ�λ�ã������ڵ�λ�ü����ٶȵ�������λ�á�
			if(Isplay)
			{

				particle[loop].x+=particle[loop].xi/(PDD.slowdown*100);
				particle[loop].z+=particle[loop].zi/(PDD.slowdown*100);
				particle[loop].y+=particle[loop].yi/(PDD.slowdown*100);

				R=sqrt((PDD.star_x-particle[loop].x)*(PDD.star_x-particle[loop].x)
					+(PDD.star_z-particle[loop].z)*(PDD.star_z-particle[loop].z));
				if(R<=PDD.AngleYStar)//����뾶С�ڴֶȣ�����������
				{
					particle[loop].xi=(PDD.star_x-particle[loop].x)*0.3;			
					particle[loop].zi=(PDD.star_z-particle[loop].z)*0.3;
					particle[loop].yi=speed;
				}
				else
				{
				particle[loop].xi=(PDD.star_x-particle[loop].x)*0.4;			
				particle[loop].zi=(PDD.star_z-particle[loop].z)*0.4;
				particle[loop].yi=1/R*1.8;
				}
				particle[loop].life-=particle[loop].fade;
			}
			//û�б�Ҫ��������
			//�����ӵ�����������Ҫ��������������������������ˣ��ﲻ��ѭ����Ч����
			if (particle[loop].life<0.0f)
			{
				//����������˥����
				particle[loop].active=false;
				PDD.diecount++;//��������������
				if(PDD.diecount>=PDD.MAX_PARTICLES)//�������ȫ�������������ԴҲ������
					PDD.dead=true;
			}
		}
	}
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);							// ������Ȳ���(WWWWWWWWWWWWWWW)
	glDisable(GL_BLEND);								// ���û��ģʽ
	glDepthMask(GL_TRUE);
	glPopMatrix();

}

int CPrt_AB_BombColumn::LoadGLTextures(void)//��������ͼ
{
	if(!CParticle::LoadGLTextures("������������.BMP",texture[0]))	//��0�Ų���װ����ͼ
	{AfxMessageBox("������������.BMP error!");return FALSE;}
	return TRUE;
}


//�������ӵ���ɫloop�����ӵı�ţ�modelΪȾɫģʽ
void CPrt_AB_BombColumn::changeColor(int loop,int model)
{

	static GLfloat colors[5][3]=	//���ڱ�ըЧ����5����ɫ��Glfloatѡֵ��
	{
		{1.0f,0.996f,0.824f},		//ǳ�ƣ������ǰ�ɫ�Ļƣ�
		{0.953f,0.757f,0.125f},		//��ɫ��ƫ��ɫ��
		{0.965f,0.627f,0.09f},		//����ɫ�����ɫ��
		{0.965f,0.429f,0.09f},		//����ɫ�����ɫ��
		{0.965f,0.359f,0.09f}		//����ɫ�����ɫ��
	};
	int lifecolorset;					//������ɫѡȡֵ

	switch(model)
	{
	case 0:	//�����Ӹ����ʼ��ɫ
		particle[loop].r=colors[loop*(5/PDD.MAX_PARTICLES)][0];
		particle[loop].g=colors[loop*(5/PDD.MAX_PARTICLES)][1];
		particle[loop].b=colors[loop*(5/PDD.MAX_PARTICLES)][2];	
		break;
	case 1:
		
		if(particle[loop].life<=1.0f&&particle[loop].life>=0.9f)lifecolorset=0;
		if(particle[loop].life<0.9f&&particle[loop].life>=0.8f)lifecolorset=1;
		if(particle[loop].life<0.8f&&particle[loop].life>=0.6f)lifecolorset=2;
		if(particle[loop].life<0.6f&&particle[loop].life>=0.2f)lifecolorset=3;
		if(particle[loop].life<0.2f)lifecolorset=4;

		particle[loop].r=colors[lifecolorset][0];
		particle[loop].g=colors[lifecolorset][1];
		particle[loop].b=colors[lifecolorset][2];
		float g;
		if(particle[loop].life<=1.0f&&particle[loop].life>=0.5f)
		{
			g=(1-particle[loop].life)*1.0;

		}
		if(particle[loop].life<0.5f)
		{
			g=particle[loop].life*1.0;
		}
		//��ÿ�����Ӹ���ɫ�ʣ�����������ֵ��ΪAlpha,���Կ����������
		glColor4f(particle[loop].r,particle[loop].g,particle[loop].b,g);
		break;
	default:
		particle[loop].r=colors[loop*(5/PDD.MAX_PARTICLES)][0];	
		particle[loop].g=colors[loop*(5/PDD.MAX_PARTICLES)][1];	
		particle[loop].b=colors[loop*(5/PDD.MAX_PARTICLES)][2];	
		break;
	}
}
