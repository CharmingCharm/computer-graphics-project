// 3dsObject.cpp: implementation of the C3dsObject class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PrtSys.h"
#include "3dsObject.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

C3dsObject::C3dsObject()
{

}

C3dsObject::~C3dsObject()
{

}

// �����ļ���װ��3ds����
// �ɹ�����true ,ʧ�ܷ���false
BOOL C3dsObject::LoadFile(LPCTSTR lpszPathName)		
{
	m_triList.Init();
	char* file = new char[strlen(lpszPathName)];
	strcpy(file, lpszPathName);	

	C3dsReader Loader;
	BOOL result;
	if( m_triList.getNumObjects() > 0 ) m_triList.removeAllObjects();
	
	result = Loader.Reader(file, &m_triList);
	if( result) 
	{
		m_triList.doAfterMath();
	}
	return result;
}

//��ʾ���������ݲ�����ʾ���塣
//���Ĳ�������Ϊ ������ʾ��		Ϊ�棺������ʾ��Ϊ�٣�������ʾ
//				 �������ӣ�		Ҳ������ʾ��ģ����ԭ����ʵģ�͵�scale����
//				 ������ʾ��		Ϊ�棺���忴������Ϊ�٣����ü�
//				 ƽ�Ƶ����ݣ�	����3ds�������ĵ�λ��
//				 ��ת���ݣ�		����������XYZ�����ת���ĽǶȡ�
void C3dsObject::Draw(BOOL &IsLine,GLfloat &scale,BOOL &hide,TraData &t_data,RotData &r_data)
{
	if(!hide)//���û�����ؾ���ʾ
	{
	glPushMatrix();
		glTranslatef( t_data.x, t_data.y, t_data.z );//�ƶ�����
		glRotatef( r_data.Angle_x-90.0, 1.0F, 0.0F, 0.0F );	//��ת����
		glRotatef( r_data.Angle_y, 0.0F, 1.0F, 0.0F );
		glRotatef( r_data.Angle_z, 0.0F, 0.0F, 1.0F );
		m_triList.drawGL(IsLine,scale);//3DSģ�͵���ʾ
	glPopMatrix();
	}
}