// GLO.cpp: implementation of the CCamEye class.
//ȫ�ֺ���˵����
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PrtSys.h"
#include <math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
//�������Max��Min֮���һ������ֵ
extern  double	RandMaxMin(double Max,double Min)
{
	if(Max<Min)Max=Min+0.0001f;
	return (rand()%100/100.0)*(Max-Min)+Min;
}

