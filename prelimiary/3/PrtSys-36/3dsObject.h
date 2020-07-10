// 3dsObject.h: interface for the C3dsObject class.
// 3D�����࣬Ҳ����3D����
// ������ͳһ����3DS����Ķ�ȡ����ʾ
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_3DSOBJECT_H__E9508E48_2E44_440D_B416_524C5D2F1B19__INCLUDED_)
#define AFX_3DSOBJECT_H__E9508E48_2E44_440D_B416_524C5D2F1B19__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "glStructures.h"	// ���ݽṹ����
#include "3dsReader.h"		// C3dsReader˵���ļ�
#include "TriList.h"		// CTriList˵���ļ�
#include "glo.h"			// ȫ�ֽṹ�ͺ����Ķ���


////////////////////////////////////////////////////////////////
//3ds����������࣬һ������ʵ����һ��3ds����
class C3dsObject  
{
public:
	C3dsObject();
	virtual ~C3dsObject(); 

	BOOL LoadFile(LPCTSTR lpszPathName);		// �����ļ���װ��3ds����
												// �ɹ�����true ,ʧ�ܷ���false

//��ʾ���������ݲ�����ʾ���塣
//���Ĳ�������Ϊ ������ʾ��		Ϊ�棺������ʾ��Ϊ�٣�������ʾ
//				 �������ӣ�		Ҳ������ʾ��ģ����ԭ����ʵģ�͵�scale����
//				 ������ʾ��		Ϊ�棺���忴������Ϊ�٣����ü�
//				 ƽ�Ƶ����ݣ�	����3ds�������ĵ�λ��
//				 ��ת���ݣ�		����������XYZ�����ת���ĽǶȡ�
	void Draw(BOOL &IsLine,GLfloat &scale,BOOL &hide,TraData &t_data,RotData &r_data);
	CTriList			m_triList;	//3DS�����������б����
};

#endif // !defined(AFX_3DSOBJECT_H__E9508E48_2E44_440D_B416_524C5D2F1B19__INCLUDED_)
