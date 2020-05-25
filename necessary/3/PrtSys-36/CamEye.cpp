// CamEye.cpp: implementation of the CCamEye class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PrtSys.h"
#include "CamEye.h"
#include <math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCamEye::CCamEye()
{

}

CCamEye::~CCamEye()
{

}

void CCamEye::InitCamera()					//��ʼ�������
{
	//��������۾�����λ��
	eyePos[0]	= 5.0f;		//x
	eyePos[1]	= 5.0f;	//y
	eyePos[2]	= 10.0f;	//z
	preeyePos_value[0] = 0.0f;//�洢������ת��ǰ�Ƕ�
	preeyePos_value[1] = 0.0f;//�洢������ת��ǰ�Ƕ�
	preeyePos_value[2] = 0.0f;//�洢������ת��ǰ�Ƕ�

	//Ŀ���λ��
	target[0]	= 0.0f;		//x
	target[1]	= 0.0f;		//y
	target[2]	= 0.0f;		//z

	//����������target�ľ���
	eyeRadius	=sqrt((eyePos[0]-target[0])*(eyePos[0]-target[0])
				+(eyePos[1]-target[1])*(eyePos[1]-target[1])
				+(eyePos[2]-target[2])*(eyePos[2]-target[2]));

	//����������Ϸ���
	eyeUp[0]	= 0.0f;		//x
	eyeUp[1]	= 1.0f;		//y
	eyeUp[2]	= 0.0f;		//z

	//�ƶ��ٶ�
	sliderspeed	= 0.1;
}





//�����������λ��
void CCamEye::SetEyePos(int axis, int value)
{
	switch(axis)
	{
		case 0:
			preeyePos_value[0]-=value;
			if(preeyePos_value[0]>360)preeyePos_value[0]-=360;
			if(preeyePos_value[0]<-360)preeyePos_value[0]+=360;
			eyePos[0]=target[0]+eyeRadius*sin(preeyePos_value[0]/180.0*PAI);//value/10.0f;
			eyePos[2]=target[2]+eyeRadius*cos(preeyePos_value[0]/180.0*PAI);//value/10.0f;
			break;
		case 1:
			
			preeyePos_value[1]+=value;
			if(preeyePos_value[1]>360)preeyePos_value[1]-=360;
			if(preeyePos_value[1]<-360)preeyePos_value[1]+=360;
			eyePos[1]=target[1]+eyeRadius*sin(preeyePos_value[1]/180.0*PAI);//value/10.0f;
			eyePos[0]=target[0]+eyeRadius*sin(preeyePos_value[0]/180.0*PAI)*cos(preeyePos_value[1]/180.0*PAI);//value/10.0f;
			eyePos[2]=target[2]+eyeRadius*cos(preeyePos_value[0]/180.0*PAI)*cos(preeyePos_value[1]/180.0*PAI);//value/10.0f;
			break;
		case 2:
			break;
		default:break;
	}
}

//�������ɾ���������������
void CCamEye::SetEyePos(float PX, float PY, float PZ)
{
	eyePos[0]=PX;
	eyePos[1]=PY;
	eyePos[2]=PZ;

	//���µ�Ŀ��ľ���
	eyeRadius	=sqrt((eyePos[0]-target[0])*(eyePos[0]-target[0])
				+(eyePos[1]-target[1])*(eyePos[1]-target[1])
				+(eyePos[2]-target[2])*(eyePos[2]-target[2]));

}

//������������ϵ���ã���TargetΪ���ġ�����λ�Ƕ���0��360�����ǻ���
void CCamEye::SetEyePosA(float Radius, float AngelY, float AngleXZ)
{
		eyeRadius=Radius;//���°뾶

		//����λ��
		eyePos[0]=target[0]+eyeRadius*cos(AngleXZ/180.0*PAI)*sin(AngelY/180.0*PAI);
		eyePos[1]=target[1]+eyeRadius*cos(AngelY/180.0*PAI);
		eyePos[2]=target[2]+eyeRadius*sin(AngleXZ/180.0*PAI)*sin(AngelY/180.0*PAI);

}



//////////////////////////////////////////////////////

//���������Ŀ��λ��
void CCamEye::SetTargetPos(int axis, int value)
{
	target[axis]+=value/100.0f;
}

void CCamEye::SetTargetPos(float PX, float PY, float PZ)
{
	target[0]=PX;
	target[1]=PY;
	target[2]=PZ;

	//���µ�������ľ���
	eyeRadius	=sqrt((eyePos[0]-target[0])*(eyePos[0]-target[0])
				+(eyePos[1]-target[1])*(eyePos[1]-target[1])
				+(eyePos[2]-target[2])*(eyePos[2]-target[2]));
}



//������������Ϸ���
void CCamEye::SetEyeUp(int axis, int value)
{
	//��ʱ����
}

//�����������Ŀ��ľ���
void CCamEye::SetEyeRadius(int value)
{
	//ֱ�ߵĲ�������(L,M,NΪ��������)
	/*
	X=x0+Lt;
	Y=y0+Mt;
	Z=z0+Nt;
	*/
	//�������λ��
	eyePos[0]+=((eyePos[0]-target[0])/eyeRadius) *(value/15.0f);
	eyePos[1]+=((eyePos[1]-target[1])/eyeRadius) *(value/15.0f);
	eyePos[2]+=((eyePos[2]-target[2])/eyeRadius) *(value/15.0f);

	//��Ŀ��ľ���
	eyeRadius	=sqrt((eyePos[0]-target[0])*(eyePos[0]-target[0])
				+(eyePos[1]-target[1])*(eyePos[1]-target[1])
				+(eyePos[2]-target[2])*(eyePos[2]-target[2]));
}

void CCamEye::SliderCamera(UINT nChar)
{
	//ֱ�ߵĲ�������(L,M,NΪ��������)
	/*
	X=x0+Lt;
	Y=y0+Mt;
	Z=z0+Nt;
	*/
	//L��M��N����Ŀ����
	float L=(eyePos[0]-target[0])/eyeRadius;
	float M=(eyePos[1]-target[1])/eyeRadius;
	float N=(eyePos[2]-target[2])/eyeRadius;

	//Li,Mi,Ni��ֱ�� ��Ŀ���������������������ɵ�ƽ��
	float Lt=M*eyeUp[2]-N*eyeUp[1];
	float Mt=N*eyeUp[0]-L*eyeUp[2];
	float Nt=L*eyeUp[1]-M*eyeUp[0];

	float D=sqrt(Lt*Lt+Mt*Mt+Nt*Nt);//�󳤶ȣ�׼����λ��

	float Li=Lt/D;
	float Mi=Mt/D;
	float Ni=Nt/D;

	switch(nChar)
	{
	case 'W' ://��ǰ������Ŀ������ͬʱ�ƶ��������Ŀ�꣬����֮����벻�䡣
		eyePos[0]-=L *sliderspeed;
		eyePos[1]-=M *sliderspeed;
		eyePos[2]-=N *sliderspeed;

		target[0]-=L *sliderspeed;
		target[1]-=M *sliderspeed;
		target[2]-=N *sliderspeed;
		break;
	case 'A' ://�������Ŵ�ֱ��Ŀ������ͬʱ�ƶ��������Ŀ�꣬����֮����벻�䡣
		eyePos[0]+=Li *sliderspeed;
		eyePos[1]+=Mi *sliderspeed;
		eyePos[2]+=Ni *sliderspeed;

		target[0]+=Li *sliderspeed;
		target[1]+=Mi *sliderspeed;
		target[2]+=Ni *sliderspeed;
		break;

	case 'S' ://���������Ŀ������ͬʱ�ƶ��������Ŀ�꣬����֮����벻�䡣
		eyePos[0]+=L *sliderspeed;
		eyePos[1]+=M *sliderspeed;
		eyePos[2]+=N *sliderspeed;

		target[0]+=L *sliderspeed;
		target[1]+=M *sliderspeed;
		target[2]+=N *sliderspeed;
		break;

	case 'D' ://�������Ŵ�ֱ��Ŀ������ͬʱ�ƶ��������Ŀ�꣬����֮����벻�䡣
		eyePos[0]-=Li *sliderspeed;
		eyePos[1]-=Mi *sliderspeed;
		eyePos[2]-=Ni *sliderspeed;

		target[0]-=Li *sliderspeed;
		target[1]-=Mi *sliderspeed;
		target[2]-=Ni *sliderspeed;
		break;

	default:break;
	}
}