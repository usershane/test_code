
/*
 * 描述： 本模块是用来处理，函数的描述文件。
 * 
 * 	函数的描述文件结构是单向连表结构，通过数据域的节点编号
 *
 * 来匹配函数链表节点的编号。根据节点的类型数据判断函数的参数类
 *
 * 型。
 *
 * 	主要描述：
 * 		
 * 		函数的名字，函数的编号，参数的类型，参数的值
 *
 * *******************************************************/

#include "config.h"

void
cfg_set_node( PCfgList, int, int, char*, int, int, char* );

PCfgList pcfgList = NULL;

/*
 * 描述		: 初始化函数描述文件链表 
 *
 * ****************************************/
bool
InitModeConfig(void)
{	
	pcfgList = cfgCreateNode();
	if( !cfgInit("./config/test_fun.cfg",pcfgList ) )
	{
		printf("%s: Init config-file fialed\n ");
		return false;
	}
	return true;
}


/*
 * 描述：打印一个节点。
 *
 *****************************************/

void
print_cfgnode( PCfgList pNode )
{
	printf( "Node number is %d\n",pNode->m_sData.m_nNumb );
	if(  1 == pNode->m_sData.m_nType || 3 == pNode->m_sData.m_nType )
	{
		printf( "Tpyt: int, key: %s, max: %d, min:%d\n ",pNode->m_sData.m_arrKey,
						pNode->m_sData.m_unValue.m_Size.m_nMax,
						pNode->m_sData.m_unValue.m_Size.m_nMin);
	}
	else if( 2 == pNode->m_sData.m_nType || 4 == pNode->m_sData.m_nType )
	{
		printf( "Tpyt: char, key: %s values: %s \n ",pNode->m_sData.m_arrKey,
						pNode->m_sData.m_unValue.m_arrValue);
	}else if( 0 == pNode->m_sData.m_nType )
	{
		printf("KEY = %s\n",pNode->m_sData.m_arrKey);
	}
}

/*
 * 描述：解析出节点编号。
 * 	
 *   pText	: cfg文件的节点字符，[TEST_NODE001]。
 *
 *   return 	: 返回字符中的节点编号。
 *
 *****************************************/
int
node_decom( char *pText )
{
	int nRet = -1;
	char pBuf[30] = {'\0'};
	strncpy( pBuf, pText + 10, 3 );
	nRet = atoi( pBuf );
	return nRet;
}

/*
 * 描述：对健值对的值，进行第二次解析。
 * 	
 * 		列：{int,01,10} {char,./config/tf.cfg}
 *
 *****************************************/
int
type_decom( char* in_pText,int *out_nMax, int *out_nMin, char* out_pValues )
{
	const char* pType[] = {
		"int",
		"cha",
		"uin",
		"uch",
		"nul"
	};
	int nType = 0;
	char arrBuf[201] = { '\0' };
	char* pValue = NULL;
	
	strncpy( arrBuf,in_pText+1,strlen( in_pText ) - 3 );
	
	while( pType[nType] ) // 判断数据类型
	{
		if(strncmp( pType[nType],arrBuf,3 ) == 0)
			break;
		nType++;
	}
	if( strncmp( pType[nType],"nul",3) == 0  )
		return -1;

	nType++;
	pValue = strtok( arrBuf,",");
	if( nType == 1 || nType == 3 )
	{
		pValue = strtok( NULL,"," );
		*out_nMax = atoi(pValue);
		pValue = strtok( NULL,"," );
		*out_nMin = atoi(pValue);
	}else if( nType == 2 || nType == 4 ){
		pValue = strtok( NULL,"," );
		strcpy( out_pValues, pValue );
	}
	
	return nType;
}

/*
 * 描述：解析一个健值对。
 * 	
 * 		列：para_01={int,01,10}
 *		
 *		key = para_01, value = {int,01,10}
 *
 *****************************************/
bool
char_decom( char *in_pText, char** out_pKey, char** out_pValue )
{	
	*out_pKey = strtok( in_pText, "=" );
	while( NULL != out_pKey )
	{
		*out_pValue = strtok(NULL,"=");
		return true;
	}
	return false;
}

/*
 * 描述：查找编号为nNumb节点的，第一个节点。
 *
 *****************************************/
PCfgList
cfgFindNode( PCfgList pList ,int nNumb )
{
	PCfgList pTem = pList;
	
	while( pTem->m_sData.m_nNumb != nNumb && pTem->m_pNext != NULL )
		pTem = pTem->m_pNext;

	if( pTem->m_sData.m_nNumb == nNumb )
		return pTem;
	
	return NULL;
}


/*
 * 描述：创建一个节点。
 *
 *****************************************/
PCfgList
cfgCreateNode( void )
{
	PCfgList pNode = (PCfgList) malloc( sizeof( *pNode ) );
	if( !pNode )
	{
		printf("malloc return NULL\n");
		return NULL;
	}
	memset( pNode, 0, sizeof( *pNode ) );
	return pNode;
}


/*
 * 描述：向连表中，添加一个节点。
 *
 *****************************************/
bool
cfgAddList( PCfgList pList, int nNu, int nTy, char arrKey[], int nMa, int nMi, char arrVa[] )
{
	PCfgList pNode = NULL,pTemp = pList;

	pNode = cfgCreateNode();
	if( !pNode )
	{
		printf("%s:Create node fialed\n");
		return false;
	}
	cfg_set_node( pNode, nNu, nTy, arrKey, nMa, nMi, arrVa);
	
	while( pTemp->m_pNext )
	{
		pTemp = pTemp->m_pNext;
	}
	pTemp->m_pNext = pNode;
	return true;
}


/*
 * 描述： 遍历整个文件，生成链表。
 *
 * pfi		:  cfg文件的描述符。
 * pList	: 把文件中的数据添加到此链表
 *
 * return	: 成功 treu, 失败 false。
 *
 *****************************************/
inline bool
traversal_file( FILE* pfi , PCfgList pList )
{
	int nMax = -1, nMin = -1;
	char arrBuf[201] = {'\0'};
	char *pKey = NULL, *pVal = NULL;
	char pValues[201] = {'\0'};
	int nNumb = 0;

	while( !feof(pfi) )
	{
		fgets(arrBuf,200,pfi);  //读取一行
		if( arrBuf[0] == '#' || arrBuf[0] == '\n' )
		{
			continue;
		}
		else if( arrBuf[0] == '[' ) // 节点 [NODE] 的处理 
		{
			nNumb = node_decom( arrBuf );
			if( !cfgAddList(pList,nNumb,0,arrBuf,0,0,"NULL"))
			{
				printf("%s: Add node fialed\n",__func__);
				return false;
			}
		}
		else if( strlen( arrBuf ) > 5 ) // KEY 和VALUE 的处理 
		{
			if( char_decom( arrBuf, &pKey, &pVal) )
			{
				int nType =  type_decom( pVal,&nMax, &nMin,pValues );
				if( !cfgAddList( pList,nNumb,nType,pKey,nMax,nMin,pValues))
				{
					printf("%s: Add node fialed\n",__func__);
					return false;
				}
			}else{
				printf("char_decom return false\n");
				return false;
			}
		}
		memset(arrBuf,'\0',201);
	}
	return true;
}

/*
 * 描述：根据指定的文件，生成一条连表。
 *
 * pFile	: 描述函数的cfg文件的路径和文件名。
 * pList	: 生成的链表的头节点。
 * 
 * return	: 成功 treu, 失败 false。
 *
 *****************************************/
bool
cfgInit( char* pFile, PCfgList pList )
{
	FILE* pf = NULL;
	int nNumber = 0;

	pf = fopen( pFile, "rt" );
	if( !pf )
	{
		printf("Open file faled\n");
		return false;
	}
	if( !traversal_file( pf,pList ) )
	{
		fclose( pf );
		printf("Init list fialed\n");
		return false;
	}
	fclose(pf);
	return true;
}

/*
 * 描述		: 对与一个链表的节点，进行赋值。
 * 
 * pNode	: 设置的节点。
 * nNu	`	: 节点的编号。
 * pNt	 	: 值的类型。
 * arrKey	: 键。
 * nMa		: 整型的最大值。
 * nMi		: 整型的最小值。
 * arrVa	: 字符的值。
 *
 * ****************************************/
void
cfg_set_node( PCfgList pNode, int nNu, int nTy, char arrKey[], int nMa, int nMi, char arrVa[] )
{
	pNode->m_sData.m_nNumb = nNu;
	pNode->m_sData.m_nType = nTy;
	strcpy(pNode->m_sData.m_arrKey,arrKey);
	if(  1 == nTy || 3 == nTy  )
	{
		pNode->m_sData.m_unValue.m_Size.m_nMax = nMa;
		pNode->m_sData.m_unValue.m_Size.m_nMin = nMi;
	}
	else if( 2 == nTy || 4 == nTy )
	{
		strcpy( pNode->m_sData.m_unValue.m_arrValue,arrVa );
	}
}

/*
 * 描述		: 获取一个函数节点的，参数。
 * 
 * pNode	: 函数所对应配置文件的节点。
 * nNum`	: 第几个参数 0 表示是返回值。
 * pMax 	: 输出参数，为整型是的最大值。
 * pMin		: 输出参数，为整型是的最小值。
 * pValue	: 输出参数，字符串的输出。
 *
 * return	: 返回值 参考 表1 。
 *
 * ****************************************/
int
cfg_get_node( PCfgList pNode, const int nNum, int *pMax, int *pMin, char *pValue)
{
	PCfgList pTemNode = pNode;
	int nTemNum = 0, nFlag = 1, nType = 0;
	char arrBuff[31] = {'\0'};

	
	if( NULL == pNode )
	{
		printf("%s: pNode node is NULL\n", __func__ );
		return -1;
	}

	if( 0 == nNum )
		snprintf( arrBuff, 30, "%s", "return" );

	else if( nNum > 0 && nNum < 20 )
		snprintf( arrBuff, 30, "para_%.02d", nNum );
	
	nTemNum = pTemNode->m_sData.m_nNumb;
	do
	{
		pTemNode = pTemNode->m_pNext;
		if( 0 == strcmp( pTemNode->m_sData.m_arrKey, arrBuff ) )
		{
			nType = pTemNode->m_sData.m_nType;
			if(  1 == nType || 3 == nType  )
			{
				*pMax = pTemNode->m_sData.m_unValue.m_Size.m_nMax;
				*pMin = pTemNode->m_sData.m_unValue.m_Size.m_nMin;
				nFlag = 0;
				break;
			}
			else if( 2 == nType || 4 == nType )
			{
				strncpy( pValue,pTemNode->m_sData.m_unValue.m_arrValue,80 );
				nFlag = 0;
				break;
			}
		}
	}while(  nTemNum == pTemNode->m_sData.m_nNumb && NULL != pTemNode->m_pNext );
	
	if( nFlag )
		return -2;

	return nType;
}
/*

int
main(void)
{

	PCfgList pList = cfgCreateNode();
	PCfgList pNode = NULL;
	int nMax = 100, nMin = 100, nRet = -100;
	char arrBuff[81] = {'\0'};

	cfgInit("../config/test_fun.cfg",pList);

	pNode = cfgFindNode(pList, 5);
	if( pNode )
		print_cfgnode(pNode);
	else
		printf("Node of not found\n");

	nRet = get_node( pNode, 1,&nMax, &nMin, arrBuff);

	printf(" return = %d Max = %d Min = %d Values = %s\n", nRet, nMax, nMin, arrBuff );

	return 0;
}
*/
