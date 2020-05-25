#if !defined(AFX_GLO_H__A617780B_5DDA_4730_951D_ECB307C8D1AF__INCLUDED_)
#define AFX_GLO_H__A617780B_5DDA_4730_951D_ECB307C8D1AF__INCLUDED_
//ȫ�����ݽṹ
//����Max��Min֮���һ�������
double	RandMaxMin(double Max,double Min);

////////////////////////////////////////////////////////////////////////////////
struct TraData		//ƽ�Ƶ����ݣ�����3ds�������ĵ�λ��
{
	float x;
	float y;
	float z;
};

struct RotData		//��ת���ݣ�����������XYZ�����ת���ĽǶȡ�
{
	float Angle_x;
	float Angle_y;
	float Angle_z;
};

typedef struct 		//3ds����Ի�������
{
	BOOL		IsLine;
	GLfloat		scale;
	BOOL		hide;
	TraData		t_data;
	RotData		r_data;
}DlgData_3ds;


//*******************************************************************************
typedef struct			// һ�����ӵĽṹ
{
	bool	active;					// �Ƿ���ţ�Active (Yes/No)
	float	life;					// ���ӵ�������Particle Life
	float	fade;					// ���ӵ���ɫ�ٶ�Fade Speed����ʵ����Lifeÿ�εļ�����

	//���ӵ�ɫ�ʲ���
	float	r;					// 	��	
	float	g;					// 	��
	float	b;					// 	��

	//��������Ļ�ϵ�λ��
	float	x;
	float	y;
	float	z;

	//���ӵ��˶�����
	float	xi;
	float	yi;
	float	zi;

	//���ӵ���������
	float	xg;	
	float	yg;	
	float	zg;	
}particleModel;	

//888888888888888888888888888888888888888888888888888888888888888888888
//����������ɫ�Ľṹ������������������׶ε���ɫ��
typedef struct
{
	float	Red[6];
	float	Green[6];
	float	Blue[6];
}Dlg_COLOR_EDIT;

//�����ӶԻ������ݽṹ,���������Ի���ͨ
typedef struct 							
{
	unsigned int MAX_PARTICLES;			//���ӵ�����������ɳ���10000��

	float star_x;						//����Դ��λ��
	float star_y;
	float star_z;

	float	lifefate;					// �������ӵ���������ֵԼ�����ӵ�������Խ��

	float	slowdown;					// �������ӵ��ٶȣ���ֵԼ��Խ����ԽСԽ��
	float	speedMax;					// �ٶ����ֵ�������㣡���뷽���޹�
	float	speedMin;					// �ٶ���Сֵ�������㣡��

	float	AngleYStar;					//�ٶ�������Y��ļн�Star<End;
	float	AngleYEnd;					//�ٶ�������Y��ļн�(0~180)

	float	AngleXZStar;				//�ٶ�������XZƽ����X�ļнǣ���Y������˳ʱ�룩(0~360)
	float	AngleXZEnd;					//Star<End;
	
	float	GetXg;						//����ϵͳ�ܵ��Ŀռ���������ʸ����
	float	GetYg;
	float	GetZg;

	/////////////////////////////////////////////////
	float	TextWidth;					//��ͼ��С
	int		TextModel;					//��ͼ��ʽ�����5�� 0~4��
	Dlg_COLOR_EDIT	PrtColor;			//���ӵ���ɫ
}DlgData_SonPRT;


//���ӶԻ������ݽṹ,���������Ի���ͨ
typedef struct 							
{
	unsigned int MAX_PARTICLES;			//���ӵ�����������ɳ���10000��

	float star_x;						//����Դ��λ��
	float star_y;
	float star_z;

	float	lifefate;					// �������ӵ���������ֵԼ�����ӵ�������Խ��

	float	slowdown;					// �������ӵ��ٶȣ���ֵԼ��Խ����ԽСԽ��
	float	speedMax;					// �ٶ����ֵ�������㣡���뷽���޹�
	float	speedMin;					// �ٶ���Сֵ�������㣡��

	float	AngleYStar;					//�ٶ�������Y��ļн�Star<End;
	float	AngleYEnd;					//�ٶ�������Y��ļн�(0~180)

	float	AngleXZStar;				//�ٶ�������XZƽ����X�ļнǣ���Y������˳ʱ�룩(0~360)
	float	AngleXZEnd;					//Star<End;
	
	float	GetXg;						//����ϵͳ�ܵ��Ŀռ���������ʸ����
	float	GetYg;
	float	GetZg;

	/////////////////////////////////////////////////
	float	TextWidth;					//��ͼ��С
	int		TextModel;					//��ͼ��ʽ�����5�� 0~4��
	Dlg_COLOR_EDIT	PrtColor;			//���ӵ���ɫ
	DlgData_SonPRT	SonPDD;				//��������������Դ�����ԡ�

	/////////////////////////////////////////////////
	//�߼�����
	bool dead;							//������־�����������Ժ�������ɺ�ɱ������Դ
										//��kingwise��������У�����������ͳһ�Ŀ���ԭ�ӵ������ж�ͳһ
	unsigned int	diecount;			//����������������
	//////////////////////////////////////////////////
	//Ԥ���ӿ�,�ṩ��ĳЩ����ģ�͵�������Ҫ
	float pram[2];						//����������У�����ʹ��pram[0]��Ϊѩ����Ҷõ���ߵ�ת���ٶ�


}DlgData_PRT;

//�������ӿ�����Ľṹ�����ݸ��ֿ�����Ϣ
typedef struct
{
	bool	p_fire;			//������ʾ���أ�true��ʾ��
	bool	p_waterfall;	//�ٲ���ʾ����
	bool	p_firework;		//����ʾ����
	bool	p_atomicbomb;	//ԭ�ӵ���ʾ����
	bool	p_snow;			//ѩ����ʾ����
	bool	p_rain;			//����ʾ����
	bool	p_bmp;			//λͼ��ʾ����
	bool	IsPlay;			//������ͣ���ؿ���,TRUE ���Ŷ�����FALSE��ͣ������
	bool	p_demo;			//��ʾ����
}Dlg_PRT_Control;

typedef struct
{
	int Width;
	int Height;
	bool IsFullScreen;	//�Ƿ�ȫ����
}ScreenDataStruct;

#endif // !defined(AFX_GLO_H__A617780B_5DDA_4730_951D_ECB307C8D1AF__INCLUDED_)


