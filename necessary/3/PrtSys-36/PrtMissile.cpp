
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


//��ʼ����������Ҫ�Ƕ�β�̽��г�ʼ��
void CPrt_Missile::Init(void)
{
	//��β�����ݽ��г�ʼ��
	RearFire.PDD.MAX_PARTICLES=1000;
	RearFire.PDD.star_x=0;
	RearFire.PDD.star_y=0;
	RearFire.PDD.star_z=0;
	RearFire.PDD.lifefate=1.0f;							// �������ӵ���������ֵԼ�����ӵ�������Խ��
	RearFire.PDD.slowdown=2.0f;							// �������ӵ��ٶȣ���ֵԼ��Խ����ԽСԽ�죨�����������
	RearFire.PDD.speedMax=10.0;							// �ٶȵ����ֵ
	RearFire.PDD.speedMin=0.0;							// �ٶȵ���Сֵ

	RearFire.PDD.AngleYStar=90;							// Y����ŽǴ�С
	RearFire.PDD.AngleYEnd=90;
	
	RearFire.PDD.AngleXZStar=0;							// XZƽ���ͶӰ�ŽǴ�С
	RearFire.PDD.AngleXZEnd=360;	
	
	RearFire.PDD.GetXg=20.0;							//�����ܵ�����������ʸ����
	RearFire.PDD.GetYg=0.0;
	RearFire.PDD.GetZg=0.0;

	////////////////////////////////////////////
	RearFire.PDD.TextModel=1;						//��ͼ��ʽ
	RearFire.PDD.TextWidth=1.0;						//��ͼ��С
	RearFire.InitColor();							//��ʼ����ɫ
	RearFire.Init();//��ʼ������ϵͳ������λ�á��ٶȡ�������
}



//��ʾ��������������
void CPrt_Missile::draw(float *Tar2Cam,bool &Isplay,float x,float y,float z)
{
	glPushMatrix();
		glTranslatef(x,y,z);//ƫ�Ƶ���
		glRotatef(-90,0,1,0);
		drawModel();		//��������
	glPopMatrix();
	RearFire.PDD.star_x=x+0.42;//����β��λ��
	RearFire.PDD.star_y=y;
	RearFire.PDD.star_z=z;
	RearFire.draw(Tar2Cam,Isplay);//����β�̡�
}

//������ģ��
void CPrt_Missile::drawModel(void)
{
	float scale=0.06;
	float P[3]={0*scale,0*scale,13*scale};	//��������

	float A[3]={ 1*scale, 1.732*scale, 7*scale};	//ǰ������
	float B[3]={ 2*scale, 0*scale    , 7*scale};
	float C[3]={ 1*scale,-1.732*scale, 7*scale};
	float D[3]={-1*scale,-1.732*scale, 7*scale};
	float E[3]={-2*scale, 0*scale    , 7*scale};
	float F[3]={-1*scale, 1.732*scale, 7*scale};

	float Ar[3]={ 1*scale, 1.732*scale, -7*scale};	//��������
	float Br[3]={ 2*scale, 0*scale    , -7*scale};
	float Cr[3]={ 1*scale,-1.732*scale, -7*scale};
	float Dr[3]={-1*scale,-1.732*scale, -7*scale};
	float Er[3]={-2*scale, 0*scale    , -7*scale};
	float Fr[3]={-1*scale, 1.732*scale, -7*scale};


	//�ĸ�β��ÿ��β��4����
	float WY[4][4][3]={
		{{2*scale  ,0*scale  ,3*scale},{3.5*scale  ,0*scale    ,-5.5*scale},{4*scale  ,0*scale    ,-9*scale},{2*scale   ,0*scale  ,-8*scale}},
		{{0*scale  ,1.732*scale  ,3*scale},{0*scale    ,3.5*scale  ,-5.5*scale},{0*scale    ,4*scale  ,-9*scale},{0*scale   ,1.732*scale  ,-8*scale}},
		{{-2*scale ,0*scale  ,3*scale},{-3.5*scale ,0*scale    ,-5.5*scale},{-4*scale ,0*scale    ,-9*scale},{-2*scale  ,0*scale  ,-8*scale}},
		{{0*scale  ,-1.732*scale ,3*scale},{0*scale    ,-3.5*scale ,-5.5*scale},{0*scale    ,-4*scale ,-9*scale},{0*scale   ,-1.732*scale ,-8*scale}}
	};	//1


		glColor3f(1,0,0);
		glBegin(GL_TRIANGLES);	//������=========================
			glVertex3fv(P);
			glVertex3fv(A);
			glVertex3fv(F);
		glEnd();
		glBegin(GL_TRIANGLES);
			glVertex3fv(P);
			glVertex3fv(F);
			glVertex3fv(E);
		glEnd();
		glBegin(GL_TRIANGLES);
			glVertex3fv(P);
			glVertex3fv(E);
			glVertex3fv(D);
		glEnd();
		glBegin(GL_TRIANGLES);
			glVertex3fv(P);
			glVertex3fv(D);
			glVertex3fv(C);
		glEnd();
		glBegin(GL_TRIANGLES);
			glVertex3fv(P);
			glVertex3fv(C);
			glVertex3fv(B);
		glEnd();
		glBegin(GL_TRIANGLES);
			glVertex3fv(P);
			glVertex3fv(B);
			glVertex3fv(A);
		glEnd();

		//������===================================
		glColor3f(0.5,0.5,0.5);
		glBegin(GL_QUADS);
			glVertex3fv(A);
			glVertex3fv(Ar);
			glVertex3fv(Fr);
			glVertex3fv(F);
		glEnd();
		glBegin(GL_QUADS);
			glVertex3fv(F);
			glVertex3fv(Fr);
			glVertex3fv(Er);
			glVertex3fv(E);
		glEnd();
		glBegin(GL_QUADS);
			glVertex3fv(E);
			glVertex3fv(Er);
			glVertex3fv(Dr);
			glVertex3fv(D);
		glEnd();
		glBegin(GL_QUADS);
			glVertex3fv(D);
			glVertex3fv(Dr);
			glVertex3fv(Cr);
			glVertex3fv(C);
		glEnd();
		glBegin(GL_QUADS);
			glVertex3fv(C);
			glVertex3fv(Cr);
			glVertex3fv(Br);
			glVertex3fv(B);
		glEnd();
		glBegin(GL_QUADS);
			glVertex3fv(B);
			glVertex3fv(Br);
			glVertex3fv(Ar);
			glVertex3fv(A);
		glEnd();

		//���׸�
		glBegin(GL_POLYGON);
			glVertex3fv(Ar);
			glVertex3fv(Br);
			glVertex3fv(Cr);
			glVertex3fv(Dr);
			glVertex3fv(Er);
			glVertex3fv(Fr);
		glEnd();

		//��β��========================================
		glColor3f(0.1,0.5,1.0);
		for(int i=0;i<=3;i++)
		{
		glBegin(GL_QUADS);
			glVertex3f(WY[i][0][0],WY[i][0][1],WY[i][0][2]);
			glVertex3f(WY[i][1][0],WY[i][1][1],WY[i][1][2]);
			glVertex3f(WY[i][2][0],WY[i][2][1],WY[i][2][2]);
			glVertex3f(WY[i][3][0],WY[i][3][1],WY[i][3][2]);
		glEnd();
		}
}