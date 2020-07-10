
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

CPrt_BMP::CPrt_BMP()
{

}

CPrt_BMP::~CPrt_BMP()
{

}
//��ȡBMP�ļ����λͼ��Ϣ Ŀǰֻ֧��256*256 24bit λͼ
bool CPrt_BMP::Read_BMP_Graph(char *BMPFileName)		
{
	FILE *fp;	//BMP�ļ�ָ��
	int fint;	//���ж�ȡ��ÿһ���ֽڣ�char�ͣ�
	fp=fopen(BMPFileName,"rb+");//�򿪡�Graph1.bmp��
	if(!fp)
	{
		AfxMessageBox("Missing BMP!");
		return false;
	}

	fseek(fp,0L,0);//�ҵ�BMPͼ��Ŀ�ͷ����ȡ�����Ϣ
	if(fgetc(fp)!='B'){AfxMessageBox("This Graph1.BMP is not a real BMP File!");return false;}
	if(fgetc(fp)!='M'){AfxMessageBox("This Graph1.BMP is not a real BMP File!");return false;}

	fseek(fp,0x12,0);//��ȡͼ����
	fint=fgetc(fp);
	if(fint>256){AfxMessageBox("Width can't more than 256!");return false;}
	else width=fint;

	fseek(fp,0x16,0);//��ȡͼ��߶�
	fint=fgetc(fp);
	if(fint>256){AfxMessageBox("Height can't more than 256!");return false;}
	else height=fint;
	
	fseek(fp,28L,0);//�ҵ���ɫλ����ַ,�鿴�Ƿ�Ϊ���ɫ
	fint=fgetc(fp);
	if(fint!=24){AfxMessageBox("This Graph1.BMP is not a 24 bit BMP File!");return false;}

	int i, j;//����
	int r, g, b, c;			//����������ɫ�ۺ�ֵ

	fseek(fp,54L,0);		//ͼ����Ϣ�����￪ʼ
	for (j=0; j<height;j++)	//�߶�
	{
		for (i=0; i<width; i++)	//���
		{
					b=fgetc(fp);
					g=fgetc(fp);
					r=fgetc(fp);
					c=(r<<16)+(g<<8)+b;
					Graphic_1[i][j]=c;		//���ǹ涨����ɫΪ͸��ɫ
		}
		if (j>=0)
			for (i=0; i<(width%4); i++) fgetc(fp);

	}

	fclose(fp);//�ر��ļ���Graph1.bmp��

	//��ʼλͼ����
	for (loop=0;loop<PDD.MAX_PARTICLES;loop++)
			particle[loop].active=false;

	return true;
}

//����һ�Ե������ʾ����GX��GY
void CPrt_BMP::GenRandGXGY(void)			
{
	while(1)
	{
		GX=rand()%(width-1);	//��������ѡһ����
		GY=rand()%(height-1);	//�߶������ѡһ����
		if(Graphic_1[GX][GY]!=0)break;
	}
}



void CPrt_BMP::draw(float *Tar2Cam,bool Isplay)//��ʾ����
{
	//*******************************************************************************
	//ѭ����ʾ�����£�ÿ������
	if(PDD.dead)//�����ļ�����
	{
		PDD.dead=false;
		if(!Read_BMP_Graph(BMP_FileName))
		{
			MessageBox(NULL,"λͼ�ļ���ȡʧ��!װ��Ĭ��λͼ!","��������",MB_OK|MB_ICONSTOP);

			//AfxMessageBox("λͼ�ļ���ȡʧ��!װ��Ĭ��λͼ!");
			if(!Read_BMP_Graph("kingwise.bmp"))
				AfxMessageBox("��ȷ�� Kingwise.bmp �Ƿ����! �����������!");
		}
		
	}
	glPushMatrix();
	glEnable(GL_BLEND);									// ���û��ģʽ
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);

	glDepthMask(GL_FALSE);
	glBindTexture(GL_TEXTURE_2D, texture[PDD.TextModel]);	//ѡ��ǰ��ͼ��ʽ
	glEnable(GL_TEXTURE_2D);
	glTranslatef(PDD.star_x,PDD.star_y,PDD.star_z);			//�ƶ�����Դ����λ��

	for (loop=0;loop<PDD.MAX_PARTICLES;loop++)
	{
		//����������У����е����Ӷ��ǻ��ŵģ����ǿ�����������
		if (particle[loop].active)						// �鿴�����Ƿ�����
		{
			//���ӵ�λ��
			CParticle::ExchangeShowXYZ(Tar2Cam,particle[loop].x,
				particle[loop].y,
				particle[loop].z,
				0.1*PDD.TextWidth);	//�ı���ͼ����

			glColor4f(particle[loop].r,particle[loop].g,particle[loop].b,particle[loop].life*0.8);

			//ÿ�����ӵ���״����һ�������Σ�������������������������ι��ɵ�
			//�������Լӿ� �Կ� �� CPU �������ٶȣ�ע��һ�£��������ε���ͼ����˳��
			glBegin(GL_TRIANGLE_STRIP);
				glTexCoord2d(1,1); glVertex3f(ParShowXYZ[0][0],	ParShowXYZ[0][1],	ParShowXYZ[0][2]); // Top Right//0
				glTexCoord2d(0,1); glVertex3f(ParShowXYZ[1][0],	ParShowXYZ[1][1],	ParShowXYZ[1][2]); // Top Left	//1
				glTexCoord2d(1,0); glVertex3f(ParShowXYZ[2][0],	ParShowXYZ[2][1],	ParShowXYZ[2][2]); // Bottom Right//2
				glTexCoord2d(0,0); glVertex3f(ParShowXYZ[3][0],	ParShowXYZ[3][1],	ParShowXYZ[3][2]); // Bottom Left//3
			glEnd();

			if(Isplay)//�����������������ӵĸ���
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
				particle[loop].active=false;
			}
		}
		else 
		{
			particle[loop].active=true;
			ReSatPrt(loop);
		}
	}
	/////////////////////////////////////////////////////
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);									// ���û��ģʽ
	glDepthMask(GL_TRUE);
	glPopMatrix();
}

void CPrt_BMP::changeForce(int loop)//�������ӵļ��ٶȣ��ٶ��ɼ��ٶȶ��ı䣩
{
		//���ӵĳ�ʼ��������(�������ٶ�)
		particle[loop].xg=PDD.GetXg;
		particle[loop].yg=PDD.GetYg;
		particle[loop].zg=PDD.GetZg;
}


void CPrt_BMP::ReSatPrt(int loop)
{
		particle[loop].life=1.0f;
		particle[loop].fade=float(((rand()%100)/1000.0f+0.003f)*PDD.lifefate);

		GenRandGXGY();//����һ������ɫ������GX��GY
		particle[loop].x=PDD.star_x+(GX-width/2)*PDD.pram[0];
		particle[loop].y=PDD.star_y+(GY-height/2)*PDD.pram[0];
		particle[loop].z=PDD.star_z+RandMaxMin(PDD.pram[1]/2.0,-PDD.pram[1]/2.0);

		//��ȡλͼ��ɫ
		int R,G,B;
		R=(Graphic_1[GX][GY]>>16)&255;
		G=(Graphic_1[GX][GY]>>8)&255;
		B=Graphic_1[GX][GY]&255;
		particle[loop].r=R/255.0;
		particle[loop].g=G/255.0;
		particle[loop].b=B/255.0;

		//���ӵ��ٶ�
		speed=RandMaxMin(PDD.speedMax,PDD.speedMin);//�ٶȵĴ�С
		   ay=RandMaxMin(PDD.AngleYEnd,PDD.AngleYStar)/180.0*PAI;//�ٶȵķ���
		  axz=RandMaxMin(PDD.AngleXZEnd,PDD.AngleXZStar)/180.0*PAI;
		particle[loop].xi=speed*sin(ay)*cos(axz);
		particle[loop].yi=speed*cos(ay);
		particle[loop].zi=speed*sin(ay)*sin(axz);

		//���ӵĳ�ʼ��������(�������ٶ�)
		particle[loop].xg=PDD.GetXg;
		particle[loop].yg=PDD.GetYg;
		particle[loop].zg=PDD.GetZg;
		changeForce(loop);
}


int CPrt_BMP::Init(void)//��ʼ������ϵͳ������λ�á��ٶȡ�������
{
	//װ�ز���
	if (!LoadGLTextures())
	{
		return FALSE;
	}	
	for (loop=0;loop<9999;loop++)
	{
		particle[loop].active=false;					// ʹ���е����Ӷ���������
	}
	return TRUE;										// ��ʼ�� OK
}


int CPrt_BMP::LoadGLTextures(void)//��������ͼ
{
	if(!CParticle::LoadGLTextures("Բ��.bmp",texture[0]))	//��0�Ų���װ����ͼ
	{AfxMessageBox("Բ��.bmp error!");return FALSE;}
	return true;
}


void CPrt_BMP::GetInitInfo(void)//��ó�ʼ������
{

	//��Ҫ��λͼ����������
	PDD.MAX_PARTICLES=7799;
	PDD.star_x=0;
	PDD.star_y=0;
	PDD.star_z=0;

	PDD.lifefate=9.4f;						// �������ӵ���������ֵԼ�����ӵ�������Խ��
	PDD.slowdown=2.8f;						// �������ӵ��ٶȣ���ֵԼ��Խ����ԽСԽ�죨�����������
	PDD.speedMax=150.0;						// �ٶȵ����ֵ
	PDD.speedMin=50.0;						// �ٶȵ���Сֵ

	PDD.GetXg=0.0;							//�����ܵ�����������ʸ����
	PDD.GetYg=2.0;
	PDD.GetZg=0.0;

	PDD.AngleYStar=0;						//Y����ŽǴ�С
	PDD.AngleYEnd=180;
	
	PDD.AngleXZStar=0;						//XZƽ���ͶӰ�ŽǴ�С
	PDD.AngleXZEnd=360;	

	PDD.TextModel=0;						//��ͼ��ʽ
	PDD.TextWidth=3.0;						//��ͼ��С

	PDD.pram[0]=0.1;						//����λͼ����,��ֵԽ��ͼ��Խ��
	PDD.pram[1]=0.1;						//ͼ��ĺ��
	PDD.dead=false;							//���ڼ���Ƿ����ļ��������
	strcpy(BMP_FileName,"kingwise.bmp");
	if(!Read_BMP_Graph(BMP_FileName))
			AfxMessageBox("λͼ�ļ���ȡʧ��!");
	Init();//��ʼ������ϵͳ������λ�á��ٶȡ�������
}

