//PrtFirework.cpp
//�̻�������
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


CPrt_FireWork::CPrt_FireWork()//���캯��
{	
}
CPrt_FireWork::~CPrt_FireWork()
{
}

//////////////////////////////////////////
//��ʼ���̻�����
//////////////////////////////////////////
void CPrt_FireWork::GetInitInfo()
{
	CPrt_Explode::GetInitInfo();
}

void CPrt_FireWork::draw(float *Tar2Cam,bool Isplay)//��ʾ����
{
	CPrt_Explode::draw(Tar2Cam,Isplay);	
}
