// CamEye.h: interface for the CCamEye class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CAMEYE_H__51245644_3691_4C6F_AD2A_DD3CCE052A9A__INCLUDED_)
#define AFX_CAMEYE_H__51245644_3691_4C6F_AD2A_DD3CCE052A9A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCamEye  
{
public:
	CCamEye();
	virtual ~CCamEye();

	float		eyePos[3];			//��������۾�����λ��
	float		preeyePos_value[3];	//�洢������ת��ǰ�Ƕ�
									//preeyePos_value[0]:���ڴ��X-Zƽ����ת���ĽǶ�
									//preeyePos_value[1]�����ڴ��z_yƽ����ת���ĽǶ�
									//preeyePos_value[2]
	float		eyeRadius;			//����������target�ľ���
	float		target[3];			//Ŀ���λ��
	float		eyeUp[3];			//����������Ϸ���
	float		sliderspeed;		//ƽ����������ٶȣ�����ÿһ���ƶ��ľ��롣

	//�����ӵ��һϵ�к���
	//
	void SetEyeUp(int axis, int value);		//������������ϵķ���,Ŀǰû��ʹ��

	//����Ŀ���һϵ�к���
	void SetTargetPos(int axis, int value);	//����Ŀ���λ�ã�Χ�������������ת��
	void SetTargetPos(float PX, float PY, float PZ);	//�������ɾ���������������

	//�����������λ�õ�һϵ�����غ���
	void SetEyePos(int axis, int value);				//����������϶����Ƶģ�Χ��Ŀ��������ת��
	void SetEyePos(float PX, float PY, float PZ);		//�������ɾ���������������

	//������������ϵ���ã���Ŀ��Ϊ����
	void SetEyePosA(float Radius, float AngelY, float AngleXZ);

	void SetEyeRadius(int value);			//�����������Ŀ��ľ���
	void InitCamera();						//��ʼ�������

	void SliderCamera(UINT nChar);			//���ݰ���ƽ���������WASDǰ�������󡢺��ˡ����ң�

};

#endif // !defined(AFX_CAMEYE_H__51245644_3691_4C6F_AD2A_DD3CCE052A9A__INCLUDED_)
