
#include "list_case.h"

/*
 * 描述：函数类型处理函数
 *
 * 类型：int fun( int );
 *
 * *****************************************/
int
case_rInt_int( PList pNode, PCfgList pcfgNode )
{
	int nPara = -1, nMax = 0, nMin = 0;
	int nType = -1, nRet = 0;
	int nNumb = 0;

	printf("%s: start\n",__func__);
	if( !pNode || !pcfgNode )
	{
		printf( "%s: Node is NULL\n", __func__ );
		return -1;
	}
	
	nType = cfg_get_node( pcfgNode, 0, &nMax, &nMin, NULL );
	if( nType < 0 )
	{
		printf( "%s:Failed to obtain parameters\n", __func__ );
		return -2;
	}

	nRet = pNode->sData.m_unFun.RIntInt( nMax );
	printf("%s: end\n",__func__);
	return nRet;
}

void
case_rVoid( PList pNode, PCfgList pcfgNode )
{
	printf("%s: start\n",__func__);
	if( !pNode || !pcfgNode )
	{
		printf( "%s: Node is NULL\n", __func__ );
		return ;
	}
	
	pNode->sData.m_unFun.RVoid();
	printf("%s: end\n",__func__);
}

void
case_rVoid_int_pChar( PList pList, PCfgList pcfgList )
{
	printf("%s: start\n",__func__);

	printf("%s: end\n",__func__);
}









