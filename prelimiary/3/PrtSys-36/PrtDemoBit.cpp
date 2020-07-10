
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


CPrt_Demo_BIT::CPrt_Demo_BIT()
{

}

CPrt_Demo_BIT::~CPrt_Demo_BIT()
{

}


void CPrt_Demo_BIT::GetInitInfo(void)						//��ó�ʼ������
{
	//��Ҫ��λͼ����������
	PDD.MAX_PARTICLES=5000;
	PDD.star_x=0;
	PDD.star_y=0;
	PDD.star_z=0;

	PDD.lifefate=3.0f;						// �������ӵ���������ֵԼ�����ӵ�������Խ��
	PDD.slowdown=2.0f;						// �������ӵ��ٶȣ���ֵԼ��Խ����ԽСԽ�죨�����������
	PDD.speedMax=150.0;						// �ٶȵ����ֵ
	PDD.speedMin=50.0;						// �ٶȵ���Сֵ

	PDD.GetXg=0.0;							//�����ܵ�����������ʸ����
	PDD.GetYg=2.0;
	PDD.GetZg=0.0;

	PDD.AngleYStar=0;						// Y����ŽǴ�С
	PDD.AngleYEnd=180;
	
	PDD.AngleXZStar=0;						// XZƽ���ͶӰ�ŽǴ�С
	PDD.AngleXZEnd=360;	

	PDD.TextModel=0;						//��ͼ��ʽ
	PDD.TextWidth=3.0;						//��ͼ��С

	PDD.pram[0]=0.1;						//����λͼ����,��ֵԽ��ͼ��Խ��

	/////////////////////////////////////////////////
	//С���ǵ���������
	PDD.SonPDD.MAX_PARTICLES=100;
	PDD.SonPDD.lifefate=2.0;
	PDD.SonPDD.slowdown=0.5;

	PDD.SonPDD.GetXg=0;
	PDD.SonPDD.GetYg=0;
	PDD.SonPDD.GetZg=0;

	PDD.SonPDD.speedMax=10;
	PDD.SonPDD.speedMin=1;

	PDD.SonPDD.TextModel=0;
	PDD.SonPDD.TextWidth=0.8;

	PDD.pram[1]=8.0;			//���ǻ��ư뾶
	/////////////////////////////////////////////////

	Init();
}

void CPrt_Demo_BIT::Init(void)
{
	//װ�ز���
	LoadGLTextures();

	FrameCount=2728;		//��0֡��ʼ��ÿ����һ��draw��֡������һ
	FrameENDCount=5030;		//����֡
	CartoonEnd=false;		//û���Զ���ʾ����
}


////////////////////////////////////////////////////////////////////////
//�ܿ���ʾ
void CPrt_Demo_BIT::draw(CCamEye &camera,bool &Isplay,bool &DemoAutoFinish)
{
	/////////////////////////////////////////////////
	//����������ʾ����ʼ�ͽ���֡��������ʼ�ĵ�һ֡������г�ʼ����
	unsigned int Snow[2]={1400,1850};	//ѩ����ʾ��ʼ������֡��
	unsigned int Rain[2]={1800,2600};	//����ʾ��ʼ������֡��
	unsigned int F16[2]={2730,4501};	//F16ս����ʾ��ʼ������֡��
	unsigned int BITlogo[2]={10,3500};	//У����ʾ��ʼ������֡��

	//�����ֵ���ʼ�ͽ���֡
	unsigned int Text[5][2]={{2000,2099},		//0����������ѧ
							{2100,2229},		//1-2004��ҵ���
							{2230,2329},		//2-kingwise
							{2330,2429},		//3-����
							{2500,2599}
							};

	float px;//��ʱ������������ô���Գ���Ϊ׼
	float py;//��ʱ������
	float pz;//��ʱ������	
	int i;//��ʱѭ������
	if(FrameCount==2728)
	{
		camera.SetTargetPos(0,0,0);		//����Ŀ������
		camera.SetEyePos(0,0,10);		//�������λ��
		glClearColor(0,0,0,0.5);		//�����Ļ
	}

	for(i=0;i<=2;i++)
		Tar2Cam[i]=camera.eyePos[i]-camera.target[i];	//��������λ��
	/////////////////////////////////////////////////
	//ս��������
	if(FrameCount==F16[0])
	{
		Init_Plane();//��ʼ��ս�����������
		camera.SetEyePos(-1000,10,0);//���������
		for(i=0;i<=2;i++)
			Tar2Cam[i]=camera.eyePos[i]-camera.target[i];	//����������׼����
	}

	if((FrameCount>F16[0])&&(FrameCount<=F16[1]))//ս�����Ķ������������ɻ��ڵ�����ײΪֹ
	{
		//pz=����������ʼ����/(Text[0][1]-Text[0][0])*(FrameCount-Text[0][0])+��ʼ
		//px�������Ʒɻ���ǰ��
		//px=(-500-(-1000))/(float)(F16[1]-F16[0])*(float)(FrameCount-F16[0])-1000;
		//py�������Ʒɻ����½�
		draw_world();//���������
		if(FrameCount<=(100+F16[0]))//ʹ��100֡���ڷɻ����½�
		{
			px=(-990-(-1000))/100.0*(float)(FrameCount-F16[0])-1000;
			py=(8.5-(11))/100.0*(float)(FrameCount-F16[0])+11;
			glPushMatrix();
			glTranslatef(px,py,0);			//�ƶ�����Դ����λ��
				Demo_3DSobj.Draw(D_IsLine,D_scale,D_hide,D_t_data,D_r_data);
				Demo_Fire.draw(Tar2Cam,Isplay);
			glPopMatrix();
		}

		if( (FrameCount>(100+F16[0])) && (FrameCount<(200+F16[0])) )//ʹ��100֡����ս������ֱ��ǰ��
		{
			px=(-850-(-990))/100.0*(float)(FrameCount-F16[0]-100)-990;
			py=8.5;
			glPushMatrix();
			glTranslatef(px,py,0);			//�ƶ�����Դ����λ��
				Demo_3DSobj.Draw(D_IsLine,D_scale,D_hide,D_t_data,D_r_data);
				Demo_Fire.draw(Tar2Cam,Isplay);
			glPopMatrix();
		}


		//ʹ��300֡�����������ŷɻ������Ļ��ͬʱ�ɻ�������������
		if( (FrameCount>=(200+F16[0])) && (FrameCount<(500+F16[0])) )//ʹ��300֡����ս������ֱ��ǰ��
		{

			//�������÷ɻ��ڣ�-1000��0��0����λ�÷ɵ�800
			px=(-800-(-1000))/300.0*(float)(FrameCount-F16[0]-200)-1000;
			py=0;
			camera.SetTargetPos(px,py,0);//����������Ľ���
			camera.SetEyePos(-900,10,10);//���������
			for(i=0;i<=2;i++)
				Tar2Cam[i]=camera.eyePos[i]-camera.target[i];	//����������׼����
			D_r_data.Angle_x+=2;

			glPushMatrix();
			glTranslatef(px,py,0);			//�ƶ�����Դ����λ��
				Demo_3DSobj.Draw(D_IsLine,D_scale,D_hide,D_t_data,D_r_data);
				Demo_Fire.draw(Tar2Cam,Isplay);
			glPopMatrix();
		}

		//�������ֳ�ʼ������
		if(FrameCount==(500+F16[0]))
		{
			for(i=0;i<=5;i++)
			{
				Demo_Missile[i].Init();//��ʼ��������
				Demo_Missile[i].pos[0]=RandMaxMin(1000,990);//x
				Demo_Missile[i].pos[1]=RandMaxMin(2.5,-2.5);//y
				Demo_Missile[i].pos[2]=RandMaxMin(2.5,-2.5);//z
				Demo_Missile[i].speed[0]=RandMaxMin(3,3);//�ٶ�X
			}
			camera.SetTargetPos(990,0,0);//����������Ľ���
			camera.SetEyePos(1000,50,50);//���������
			for(i=0;i<=2;i++)
				Tar2Cam[i]=camera.eyePos[i]-camera.target[i];	//����������׼����
		}
		//��������,500֡
		if( (FrameCount>(500+F16[0])) && (FrameCount<(1000+F16[0])) )
		{
			for(i=0;i<=5;i++)
			{
				Demo_Missile[i].draw(Tar2Cam,Isplay,Demo_Missile[i].pos[0],Demo_Missile[i].pos[1],Demo_Missile[i].pos[2]);
				Demo_Missile[i].pos[0]-=Demo_Missile[i].speed[0];
			}
			camera.SetTargetPos(Demo_Missile[0].pos[0],0,0);//����������Ľ���
			pz=360.0/500.0*(float)(FrameCount-F16[0]-500);//ʹ�����Χ�ŵ���ת
			camera.SetEyePosA(10,90, pz);
			for(i=0;i<=2;i++)
				Tar2Cam[i]=camera.eyePos[i]-camera.target[i];	//����������׼����
		}

		if(FrameCount==(1000+F16[0]))//��ʼ���ɻ��͵�������ʱ�ľ�ͷ
		{
			for(i=0;i<=5;i++)
			{
				Demo_Missile[i].pos[0]=RandMaxMin(250,245);//���·��䵼��X����
				Demo_Missile[i].speed[0]=RandMaxMin(0.83,0.82);	//�ٶ�X
			}
			D_r_data.Angle_x=0;//ʹ�ɻ��ǶȻָ�
			camera.SetTargetPos(0,0,0);//����������Ľ���
			for(i=0;i<=2;i++)
				Tar2Cam[i]=camera.eyePos[i]-camera.target[i];	//����������׼����
		}
		//ʹ��500֡���ɻ��ڵ�����ײ
		if( (FrameCount>(1000+F16[0])) && (FrameCount<(1500+F16[0])) )//��������
		{
			//����������300֡��д�ɻ��ڵ���ֱײ
			if( (FrameCount>(1000+F16[0])) && (FrameCount<(1300+F16[0])) )
			{
				//�������÷ɻ�
				px=(-10-(-200))/300.0*(float)(FrameCount-F16[0]-1000)-200;

				//���������λ�þ���ԭ���λ��
				py=(20-(500))/300.0*(float)(FrameCount-F16[0]-1000)+500;
				camera.SetEyePosA(py,80,90);//���������
				for(i=0;i<=2;i++)
					Tar2Cam[i]=camera.eyePos[i]-camera.target[i];	//����������׼����

				//���ɻ�
				glPushMatrix();
				glTranslatef(px,0,0);			//�ƶ�����Դ����λ��
					Demo_3DSobj.Draw(D_IsLine,D_scale,D_hide,D_t_data,D_r_data);
					Demo_Fire.draw(Tar2Cam,Isplay);
				glPopMatrix();

				//������
				for(i=0;i<=5;i++)
				{
					Demo_Missile[i].draw(Tar2Cam,Isplay,Demo_Missile[i].pos[0],Demo_Missile[i].pos[1],Demo_Missile[i].pos[2]);
					Demo_Missile[i].pos[0]-=Demo_Missile[i].speed[0];
				}
			}
			//ʹ��150֡���ֺڿ�ת
			if( (FrameCount>=(1300+F16[0])) 
				&&(FrameCount<(1450+F16[0]))
				)
			{
				//pz=����������ʼ����/(Text[0][1]-Text[0][0])*(FrameCount-Text[0][0])+��ʼ
				pz=(810-(90))/150*(float)(FrameCount-1300-F16[0])+90;
				camera.SetEyePosA(20,80, pz);
				for(i=0;i<=2;i++)
					Tar2Cam[i]=camera.eyePos[i]-camera.target[i];	//����������׼����

				//���ɻ�
				glPushMatrix();
				glTranslatef(-10,0,0);			//�ƶ�����Դ����λ��
					Demo_3DSobj.Draw(D_IsLine,D_scale,D_hide,D_t_data,D_r_data);
					Demo_Fire.draw(Tar2Cam,Isplay);
				glPopMatrix();

				//������
				for(i=0;i<=5;i++)
				{
					Demo_Missile[i].draw(Tar2Cam,Isplay,Demo_Missile[i].pos[0],Demo_Missile[i].pos[1],Demo_Missile[i].pos[2]);
				}

			}//�ڿ�ת

			//����������50֡��д�ɻ��ڵ�����ײ
			if( (FrameCount>=(1450+F16[0])) && (FrameCount<(1500+F16[0])) )
			{
				//�������÷ɻ�
				px=(-5-(-10))/50.0*(float)(FrameCount-F16[0]-1450)-10;
				//���ɻ�
				glPushMatrix();
				glTranslatef(px,0,0);			//�ƶ�����Դ����λ��
					Demo_3DSobj.Draw(D_IsLine,D_scale,D_hide,D_t_data,D_r_data);
					Demo_Fire.draw(Tar2Cam,Isplay);
				glPopMatrix();
				//������
				for(i=0;i<=5;i++)
				{
					Demo_Missile[i].draw(Tar2Cam,Isplay,Demo_Missile[i].pos[0],Demo_Missile[i].pos[1],Demo_Missile[i].pos[2]);
					Demo_Missile[i].pos[0]-=0.1;
				}
			}

		}//ʹ��500֡���ɻ��ڵ�����ײ

		//չ��ԭ�ӵ�
		if( FrameCount==(1500+F16[0])) //��ʼԭ�ӵ�
		{
			Demo_AtomicBomb.GetInitInfo();
			
			camera.SetEyePos(0,-9, 20);
			camera.SetTargetPos(0,-10,0);//����������Ľ���
				for(i=0;i<=2;i++)
					Tar2Cam[i]=camera.eyePos[i]-camera.target[i];	//����������׼����
					
		}
		if(  (FrameCount>(1500+F16[0])) && (FrameCount<(1800+F16[0]))) //��ʾԭ�ӵ�
		{
			//pz=����������ʼ����/(Text[0][1]-Text[0][0])*(FrameCount-Text[0][0])+��ʼ
			pz=(50.0-(20.0))/300.0*(float)(FrameCount-1500-F16[0])+20.0;
			px=(5.0-(-10.0))/300.0*(float)(FrameCount-1500-F16[0])-10;
			camera.SetTargetPos(0,px,0);//����������Ľ���
			camera.SetEyePos(0,-9, pz);
				for(i=0;i<=2;i++)
					Tar2Cam[i]=camera.eyePos[i]-camera.target[i];	//����������׼����
			Demo_AtomicBomb.draw(Tar2Cam,Isplay);
		}

	}//�ɻ�������ԭ�ӵ���ʾ


	//=============================================
	//У�ն���
	if(FrameCount==(1790+F16[0]))//��ʼ���񻨺�BIT��Ļ
	{
		Init_BITlogo();	//��ʼ��У��
		Init_FireWork();//��ʼ����
		camera.SetEyePos(0,0, 10);
		camera.SetTargetPos(0,0,-20);//����������Ľ���
		for(i=0;i<=2;i++)
					Tar2Cam[i]=camera.eyePos[i]-camera.target[i];	//����������׼����
		glClearColor(0,0,0,0.5);		//�����Ļ
	}
	if(  (FrameCount>(1790+F16[0])) && (FrameCount<(2300+F16[0])) )
	{
		//pz=����������ʼ����/(Text[0][1]-Text[0][0])*(FrameCount-Text[0][0])+��ʼ
		pz=(810-(90))/500*(float)(FrameCount-1300-F16[0])+90;
		camera.SetEyePosA(30,80, pz);
		for(i=0;i<=2;i++)
		Tar2Cam[i]=camera.eyePos[i]-camera.target[i];	//����������׼����

		glPushMatrix();
		glTranslatef(0,0,-20);			//�ƶ�����Դ����λ��
			draw_BITlogo(Tar2Cam,Isplay);
		glPopMatrix();

		Demo_FireWork[0].draw(Tar2Cam,Isplay);
		Demo_FireWork[1].draw(Tar2Cam,Isplay);

	}

	//////////////////////////////////////////////////////////////////////////////
	FrameCount++;
	if(FrameCount>=FrameENDCount)
	{
		CartoonEnd=true;//��ʾ����
		DemoAutoFinish=true;
		camera.InitCamera();//��ʼ�����
		glClearColor(0,0,0,0.5);		//�����Ļ
	}

}


//��ʼ��У�գ�������������������������������������������������������
void CPrt_Demo_BIT::Init_BITlogo(void)
{
	if(!Read_BMP_Graph("BIT.BMP"))
			AfxMessageBox("BIT.BMP Read ERROR!");

	//С���ǵĳ�ʼ�� 4��
	for (loop=0;loop<4;loop++)
	{
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

		//ָ��������
		ex_Rot[loop][0]=RandMaxMin(135,45)/180.0f*PAI;
		ex_Rot[loop][1]=RandMaxMin(360,0)/180.0f*PAI;
		ret[loop]=1;
		explodePar[loop].PDD.star_x=PDD.star_x+PDD.pram[1]*sin(ex_Rot[loop][0])*cos(ex_Rot[loop][1]);
		explodePar[loop].PDD.star_y=PDD.star_y+PDD.pram[1]*cos(ex_Rot[loop][0]);
		explodePar[loop].PDD.star_z=PDD.star_z+PDD.pram[1]*sin(ex_Rot[loop][0])*sin(ex_Rot[loop][1]);

		explodePar[loop].texture[0]=&texture[0];
		//������ɫ
		for(int i=0;i<=4;i++)
		{
			explodePar[loop].PDD.PrtColor.Red[i]=1.0;
			explodePar[loop].PDD.PrtColor.Green[i]=0.1;
			explodePar[loop].PDD.PrtColor.Blue[i]=0.1;
		}
		explodePar[loop].Init();
	}
}


//У�ն���
void CPrt_Demo_BIT::draw_BITlogo(float *Tar2Cam,bool &Isplay)
{

	draw_PrtBMP(Tar2Cam,Isplay);//��ʾλͼ

	///////////////////////////////////////////////////

	for (loop=0;loop<4;loop++)
	{
		//��ʾ����
		explodePar[loop].draw(Tar2Cam,Isplay,explodePar[loop].life);

		if(Isplay)
			{
			//����y��ķ���
			if(ex_Rot[loop][0]>(135/180.0f*PAI) )
			{
				ex_Rot[loop][0]=135/180.0f*PAI;ret[loop]*=-1;
			}
			if( ex_Rot[loop][0]<(45/180.0f*PAI))
			{
				ex_Rot[loop][0]=45/180.0f*PAI;ret[loop]*=-1;
			}
			ex_Rot[loop][0]+=0.01*ret[loop];
			ex_Rot[loop][1]+=0.05;

			explodePar[loop].PDD.star_x=PDD.star_x+PDD.pram[1]*sin(ex_Rot[loop][0])*cos(ex_Rot[loop][1]);
			explodePar[loop].PDD.star_y=PDD.star_y+PDD.pram[1]*cos(ex_Rot[loop][0]);
			explodePar[loop].PDD.star_z=PDD.star_z+PDD.pram[1]*sin(ex_Rot[loop][0])*sin(ex_Rot[loop][1]);

			}

	}

}

void CPrt_Demo_BIT::ReSatPrt(int loop)
{
		particle[loop].life=1.0f;
		particle[loop].fade=float(((rand()%100)/1000.0f+0.003f)*PDD.lifefate);

		GenRandGXGY();//����һ������ɫ������GX��GY
		particle[loop].x=PDD.star_x+(GX-width/2)*PDD.pram[0];
		particle[loop].y=PDD.star_y+(GY-height/2)*PDD.pram[0];
		particle[loop].z=PDD.star_z;

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

}

///////////////////////////////////////////////////
//��ʼ���ɻ��������
void CPrt_Demo_BIT::Init_Plane(void)					
{
	if(!Demo_3DSobj.LoadFile("F16.3DS"))
		AfxMessageBox("F16.3DS Read ERROR!");//��ȡս����
		D_IsLine=FALSE;	//��ʼ���ɻ�����
		D_scale=0.1;
		D_hide=FALSE;
		D_t_data.x=5.7;
		D_t_data.y=0.0;
		D_t_data.z=0.0;
		D_r_data.Angle_x=0.0;
		D_r_data.Angle_z=90.0;
		D_r_data.Angle_y=0.0;


	Demo_Fire.PDD.MAX_PARTICLES=1200;
	Demo_Fire.PDD.star_x=0;
	Demo_Fire.PDD.star_y=0.0;
	Demo_Fire.PDD.star_z=0;
	Demo_Fire.PDD.lifefate=8.5f;							// �������ӵ���������ֵԼ�����ӵ�������Խ��
	Demo_Fire.PDD.slowdown=2.0f;							// �������ӵ��ٶȣ���ֵԼ��Խ����ԽСԽ�죨�����������
	Demo_Fire.PDD.speedMax=400.0;							// �ٶȵ����ֵ
	Demo_Fire.PDD.speedMin=380.0;							// �ٶȵ���Сֵ

	Demo_Fire.PDD.AngleYStar=90;							// Y����ŽǴ�С
	Demo_Fire.PDD.AngleYEnd=90;
	
	Demo_Fire.PDD.AngleXZStar=179;							// XZƽ���ͶӰ�ŽǴ�С
	Demo_Fire.PDD.AngleXZEnd=181;	
	
	Demo_Fire.PDD.GetXg=-46.0;								//�����ܵ�����������ʸ����
	Demo_Fire.PDD.GetYg=0.0;
	Demo_Fire.PDD.GetZg=0.0;

	////////////////////////////////////////////
	Demo_Fire.PDD.TextModel=0;						//��ͼ��ʽ
	Demo_Fire.PDD.TextWidth=2.4551;						//��ͼ��С
	//������ɫ����
	Demo_Fire.PDD.PrtColor.Red[0]=1.0f;		//ǳ�ƣ������ǰ�ɫ�Ļƣ�
	Demo_Fire.PDD.PrtColor.Green[0]=0.996f;
	Demo_Fire.PDD.PrtColor.Blue[0]=0.953f;

	Demo_Fire.PDD.PrtColor.Red[1]=0.153f;	//��ɫ��ƫ��ɫ��
	Demo_Fire.PDD.PrtColor.Green[1]=0.157f;
	Demo_Fire.PDD.PrtColor.Blue[1]=1.0f;

	Demo_Fire.PDD.PrtColor.Red[2]=0.165f;	//����ɫ�����ɫ��
	Demo_Fire.PDD.PrtColor.Green[2]=0.127f;
	Demo_Fire.PDD.PrtColor.Blue[2]=1.0f;

	Demo_Fire.PDD.PrtColor.Red[3]=0.843f;	//�Ұ�ɫ
	Demo_Fire.PDD.PrtColor.Green[3]=0.816f;
	Demo_Fire.PDD.PrtColor.Blue[3]=0.784f;

	Demo_Fire.PDD.PrtColor.Red[4]=0.001;	//��ɫ
	Demo_Fire.PDD.PrtColor.Green[4]=0.001f;
	Demo_Fire.PDD.PrtColor.Blue[4]=0.001f;

	Demo_Fire.Init();//��ʼ������ϵͳ������λ�á��ٶȡ�������
	
}

void CPrt_Demo_BIT::Init_FireWork(void)				//��ʼ����
{
	/////////////////////////////////////////
	//��һ
	Demo_FireWork[0].PDD.MAX_PARTICLES=50;			//100��С������Դ
	Demo_FireWork[0].PDD.star_x=-10;				//��λ��
	Demo_FireWork[0].PDD.star_y=7;
	Demo_FireWork[0].PDD.star_z=-20;
	Demo_FireWork[0].PDD.lifefate=0.5f;				// �������ӵ���������ֵԼ�����ӵ�������Խ��
	Demo_FireWork[0].PDD.slowdown=1.0f;				// �������ӵ��ٶȣ���ֵԼ��Խ����ԽСԽ��

	Demo_FireWork[0].PDD.speedMax=100.0;			// ��ը�ٶȵ�ֵ
	Demo_FireWork[0].PDD.speedMin=100.0;
	Demo_FireWork[0].PDD.AngleYStar=0;				// Y����ŽǴ�С
	Demo_FireWork[0].PDD.AngleYEnd=180;
	
	Demo_FireWork[0].PDD.AngleXZStar=0;				// XZƽ���ͶӰ�ŽǴ�С
	Demo_FireWork[0].PDD.AngleXZEnd=360;	

	Demo_FireWork[0].PDD.GetXg=0.0f;				//�����ܵ�����������ʸ����
	Demo_FireWork[0].PDD.GetYg=-15.0f;
	Demo_FireWork[0].PDD.GetZg=0.0f;

	Demo_FireWork[0].PDD.TextWidth=1.0;
	Demo_FireWork[0].PDD.TextModel=0;

	/////////////////////////////////////// //��ɫ
	Demo_FireWork[0].PDD.PrtColor.Red[0]=1.0f;
	Demo_FireWork[0].PDD.PrtColor.Green[0]=1.0f;
	Demo_FireWork[0].PDD.PrtColor.Blue[0]=1.0f;

	Demo_FireWork[0].PDD.PrtColor.Red[1]=1.0f;
	Demo_FireWork[0].PDD.PrtColor.Green[1]=0.706f;
	Demo_FireWork[0].PDD.PrtColor.Blue[1]=0.706f;

	Demo_FireWork[0].PDD.PrtColor.Red[2]=1.0f;
	Demo_FireWork[0].PDD.PrtColor.Green[2]=0.392f;
	Demo_FireWork[0].PDD.PrtColor.Blue[2]=0.392f;

	Demo_FireWork[0].PDD.PrtColor.Red[3]=0.843f;	
	Demo_FireWork[0].PDD.PrtColor.Green[3]=0.392f;
	Demo_FireWork[0].PDD.PrtColor.Blue[3]=0.784f;

	Demo_FireWork[0].PDD.PrtColor.Red[4]=0.196;
	Demo_FireWork[0].PDD.PrtColor.Green[4]=0.95f;
	Demo_FireWork[0].PDD.PrtColor.Blue[4]=0.390f;

	/////////////////////////////////////////////////////////////
	//�����������ӵ�����
	Demo_FireWork[0].PDD.SonPDD.MAX_PARTICLES=80;
	Demo_FireWork[0].PDD.SonPDD.lifefate=2.0;				// �������ӵ���������ֵԼ�����ӵ�������Խ��
	Demo_FireWork[0].PDD.SonPDD.slowdown=0.5;				// �������ӵ��ٶȣ���ֵԼ��Խ����ԽСԽ��

	Demo_FireWork[0].PDD.SonPDD.GetXg=0;
	Demo_FireWork[0].PDD.SonPDD.GetYg=0;
	Demo_FireWork[0].PDD.SonPDD.GetZg=0;

	Demo_FireWork[0].PDD.SonPDD.speedMax=1;
	Demo_FireWork[0].PDD.SonPDD.speedMin=1;

	Demo_FireWork[0].Init();

	///////////////////////////////////////////////////////////
	//�񻨶�
	//////////////////////////////////////////////////////////
	Demo_FireWork[1].PDD.MAX_PARTICLES=50;			//100��С������Դ
	Demo_FireWork[1].PDD.star_x=10;					//��λ��
	Demo_FireWork[1].PDD.star_y=5;
	Demo_FireWork[1].PDD.star_z=-20;
	Demo_FireWork[1].PDD.lifefate=0.5f;				// �������ӵ���������ֵԼ�����ӵ�������Խ��
	Demo_FireWork[1].PDD.slowdown=1.0f;				// �������ӵ��ٶȣ���ֵԼ��Խ����ԽСԽ��

	Demo_FireWork[1].PDD.speedMax=100.0;			// ��ը�ٶȵ�ֵ
	Demo_FireWork[1].PDD.speedMin=100.0;

	Demo_FireWork[1].PDD.AngleYStar=0;				// Y����ŽǴ�С
	Demo_FireWork[1].PDD.AngleYEnd=180;
	
	Demo_FireWork[1].PDD.AngleXZStar=0;				// XZƽ���ͶӰ�ŽǴ�С
	Demo_FireWork[1].PDD.AngleXZEnd=360;	

	Demo_FireWork[1].PDD.GetXg=0.0f;				//�����ܵ�����������ʸ����
	Demo_FireWork[1].PDD.GetYg=-15.0f;
	Demo_FireWork[1].PDD.GetZg=0.0f;

	Demo_FireWork[1].PDD.TextWidth=1.0;
	Demo_FireWork[1].PDD.TextModel=0;

	/////////////////////////////////////// //��ɫ
	Demo_FireWork[1].PDD.PrtColor.Red[0]=1.0f;
	Demo_FireWork[1].PDD.PrtColor.Green[0]=1.0f;
	Demo_FireWork[1].PDD.PrtColor.Blue[0]=1.0f;

	Demo_FireWork[1].PDD.PrtColor.Red[1]=1.0f;
	Demo_FireWork[1].PDD.PrtColor.Green[1]=1.0f;
	Demo_FireWork[1].PDD.PrtColor.Blue[1]=0.501961f;

	Demo_FireWork[1].PDD.PrtColor.Red[2]=0.501961f;
	Demo_FireWork[1].PDD.PrtColor.Green[2]=1.0f;
	Demo_FireWork[1].PDD.PrtColor.Blue[2]=0.501961f;

	Demo_FireWork[1].PDD.PrtColor.Red[3]=0.501961f;	
	Demo_FireWork[1].PDD.PrtColor.Green[3]=0.501961f;
	Demo_FireWork[1].PDD.PrtColor.Blue[3]=1.0f;

	Demo_FireWork[1].PDD.PrtColor.Red[4]=1.0f;
	Demo_FireWork[1].PDD.PrtColor.Green[4]=0.501961f;
	Demo_FireWork[1].PDD.PrtColor.Blue[4]=0.501961f;

	////////////////
	//�����������ӵ�����
	Demo_FireWork[1].PDD.SonPDD.MAX_PARTICLES=80;
	Demo_FireWork[1].PDD.SonPDD.lifefate=2.0;				// �������ӵ���������ֵԼ�����ӵ�������Խ��
	Demo_FireWork[1].PDD.SonPDD.slowdown=0.5;				// �������ӵ��ٶȣ���ֵԼ��Խ����ԽСԽ��

	Demo_FireWork[1].PDD.SonPDD.GetXg=0;
	Demo_FireWork[1].PDD.SonPDD.GetYg=0;
	Demo_FireWork[1].PDD.SonPDD.GetZg=0;

	Demo_FireWork[1].PDD.SonPDD.speedMax=1;
	Demo_FireWork[1].PDD.SonPDD.speedMin=1;

	Demo_FireWork[1].Init();
}


/////////////////////////////////////////////////////////////////////////////

int CPrt_Demo_BIT::LoadGLTextures(void)					//��������ͼ
{
	if(!CParticle::LoadGLTextures("Բ��.bmp",texture[0]))	//��0�Ų���װ����ͼ
	{AfxMessageBox("��ʾԲ��.bmp error!");return FALSE;}

	if(!CParticle::LoadGLTextures("W_Ground.bmp",WorldTexture[0]))	//��0�Ų���װ����ͼ
	{AfxMessageBox("W_Ground.bmp error!");return FALSE;}
	if(!CParticle::LoadGLTextures("W_Sky1.bmp",WorldTexture[1]))	//��1�Ų���װ����ͼ
	{AfxMessageBox("W_Sky1.bmp error!");return FALSE;}
	if(!CParticle::LoadGLTextures("W_Sky2.bmp",WorldTexture[2]))	//��2�Ų���װ����ͼ
	{AfxMessageBox("W_Sky2.bmp error!");return FALSE;}
	if(!CParticle::LoadGLTextures("W_Sky3.bmp",WorldTexture[3]))	//��3�Ų���װ����ͼ
	{AfxMessageBox("W_Sky3.bmp error!");return FALSE;}
	if(!CParticle::LoadGLTextures("W_Sky4.bmp",WorldTexture[4]))	//��4�Ų���װ����ͼ
	{AfxMessageBox("W_Sky4.bmp error!");return FALSE;}
	if(!CParticle::LoadGLTextures("W_Sky5.bmp",WorldTexture[5]))	//��5�Ų���װ����ͼ
	{AfxMessageBox("W_Sky5.bmp error!");return FALSE;}

	return TRUE;
}



void CPrt_Demo_BIT::GenRandGXGY(void)			//����һ�Ե������ʾ����GX��GY
{
	while(1)
	{
		GX=rand()%(width-1);	//��������ѡһ����
		GY=rand()%(height-1);	//�߶������ѡһ����
		if(Graphic_1[GX][GY]!=0)break;
	}
}

bool CPrt_Demo_BIT::Read_BMP_Graph(char *BMPFileName)		//��ȡBMP�ļ����λͼ��Ϣ Ŀǰֻ֧��128*128 24bit λͼ
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
	for (j=0; j<height; j++)	//�߶�
	{
		for (i=0; i<width; i++)	//���
		{
					b=fgetc(fp);
					g=fgetc(fp);
					r=fgetc(fp);
					c=(r<<16)+(g<<8)+b;
					Graphic_1[i][j]=c;		//���ǹ涨����ɫΪ͸��ɫ
		}
		if (j>0)
			for (i=0; i<(width%4); i++) fgetc(fp);

	}

	fclose(fp);//�ر��ļ���Graph1.bmp��

	//��ʼλͼ����
	for (loop=0;loop<PDD.MAX_PARTICLES;loop++)
			particle[loop].active=false;
	return true;
}



//��ʾ��ǰλͼ
void CPrt_Demo_BIT::draw_PrtBMP(float *Tar2Cam,bool &Isplay)
{
	//*******************************************************************************
	//ѭ����ʾ�����£�ÿ������
	glPushMatrix();
	glEnable(GL_BLEND);									// ���û��ģʽ
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);					// Type Of Blending To Perform

	glDepthMask(GL_FALSE);
	glBindTexture(GL_TEXTURE_2D, texture[PDD.TextModel]);	//ѡ��ǰ��ͼ��ʽ
	glEnable(GL_TEXTURE_2D);

	for (loop=0;loop<PDD.MAX_PARTICLES;loop++)				// Loop Through All The Particles
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
			glBegin(GL_TRIANGLE_STRIP);				// Build Quad From A Triangle Strip
				glTexCoord2d(1,1); glVertex3f(ParShowXYZ[0][0],	ParShowXYZ[0][1],	ParShowXYZ[0][2]); // Top Right//0
				glTexCoord2d(0,1); glVertex3f(ParShowXYZ[1][0],	ParShowXYZ[1][1],	ParShowXYZ[1][2]); // Top Left	//1
				glTexCoord2d(1,0); glVertex3f(ParShowXYZ[2][0],	ParShowXYZ[2][1],	ParShowXYZ[2][2]); // Bottom Right//2
				glTexCoord2d(0,0); glVertex3f(ParShowXYZ[3][0],	ParShowXYZ[3][1],	ParShowXYZ[3][2]); // Bottom Left//3
			glEnd();								// Done Building Triangle Strip

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
			particle[loop].life-=particle[loop].fade;		// Reduce Particles Life By 'Fade'
			}
			//�����ӵ�����������Ҫ��������������������������ˣ��ﲻ��ѭ����Ч����
			if (particle[loop].life<0.0f)					// If Particle Is Burned Out
			{
				//ReSatPrt(loop);
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
	/////////////////////////////////////////////////////
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);									// ���û��ģʽ
	glDepthMask(GL_TRUE);
	glPopMatrix();
}



void CPrt_Demo_BIT::draw_world(void)//�������
{

	float a=3000.0f;
	float het=3000.0f;//�߶�
	float bot=-400.0f;			//�ײ�λ��
	//���������ͼ������
	float WorldTP[6][4][3]={
		{{a,bot,a},{a,bot,-a},{-a,bot,a},{-a,bot,-a}},//��0123
		{{a,bot+het,a},{a,bot+het,-a},{a,bot,a},{a,bot,-a}},//��1
		{{-a,bot+het,a},{a,bot+het,a},{-a,bot,a},{a,bot,a}},//��2
		{{-a,bot+het,-a},{-a,bot+het,a},{-a,bot,-a},{-a,bot,a}},//��3
		{{a,bot+het,-a},{-a,bot+het,-a},{a,bot,-a},{-a,bot,-a}},//��4
		{{a,bot+het,a},{a,bot+het,-a},{-a,bot+het,a},{-a,bot+het,-a}}//�춥
	};
	//*******************************************************************************
	//ѭ����ʾ�����£�ÿ������
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	for(int i=0;i<=5;i++)
	{
	glBindTexture(GL_TEXTURE_2D, WorldTexture[i]);	//ѡ��ǰ��ͼ��ʽ
	glColor4f(1,1,1,1);
	glBegin(GL_TRIANGLE_STRIP);	
		glTexCoord2d(1,1); glVertex3f(WorldTP[i][0][0],	WorldTP[i][0][1],	WorldTP[i][0][2]); // Top Right//0
		glTexCoord2d(0,1); glVertex3f(WorldTP[i][1][0],	WorldTP[i][1][1],	WorldTP[i][1][2]); // Top Left	//1
		glTexCoord2d(1,0); glVertex3f(WorldTP[i][2][0],	WorldTP[i][2][1],	WorldTP[i][2][2]); // Bottom Right//2
		glTexCoord2d(0,0); glVertex3f(WorldTP[i][3][0],	WorldTP[i][3][1],	WorldTP[i][3][2]); // Bottom Left//3
	glEnd();								// Done Building Triangle Strip
	}
	/////////////////////////////////////////////////////
	glPopMatrix();
}












