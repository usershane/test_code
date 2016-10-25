
#include "list.h"


PFunInitCre init_list    = NULL; 
PFunInitCre create_node  = NULL;
PList g_pList = NULL;                                                                        

void
print_node( PList pNode )
{
	printf( "Node number = %d\n", pNode->m_nListNumb );
	printf( "Type of Function = %d\n ", pNode->sData.m_nType ) ;
	printf( "Function address = %x\n ", pNode->sData.m_unFun.RVoid ) ;
}

void
print_fun_list( PList pList )
{
	PList pTemList = pList;
	while( pTemList->pNext )
	{
		print_node( pTemList );
		pTemList = pTemList->pNext;
	}
}

bool
init_mode_list(void)
{
	init_list = init;   
	create_node = init; 
	g_pList = init_list( -1,0 );
	if( NULL != g_pList )
		return true;
	return false;
}

PList
init( int nListNumb, int nTypeNumb )
{
	PList pList = ( PList ) malloc( sizeof( *pList ) );
	if( !pList )
	{
		printf(" Initialization/Build node fialed\n");
		return NULL;
	}
	pList->m_nListNumb = nListNumb;
	pList->sData.m_nType = nTypeNumb;
	pList->sData.m_unFun.RVoid = NULL;
	pList->pNext = NULL;
	return pList;
}


bool
add_list( PList pList, PList pNode )
{
	PList pTmp = pList;

	if( !pNode && !pList )
	{
		printf( " Node is NULL\n " );
		return false;
	}
	
	while( pTmp->pNext )
		pTmp = pTmp->pNext;

	pTmp->pNext = pNode;
	return true;
}

void
run_test( PList pList, PCfgList pcfgList )
{
	PList pTemNode = pList;
	PCfgList pTemCfgNode = NULL;
	
	printf("%s: start\n",__func__);
	while( NULL != pTemNode->pNext )
	{
		int nNumb = pTemNode->m_nListNumb;
		pTemCfgNode = cfgFindNode( pcfgList, nNumb );
		switch( pTemNode->sData.m_nType )
		{
			case 0x00:
				case_rVoid( pTemNode, pTemCfgNode );
				break;

			case 0x02:
				case_rInt_int( pTemNode, pTemCfgNode );
				break;

			case 0x101:
				case_rVoid_int_pChar( pTemNode, pTemCfgNode );
				break;
			default:

				break;
		}
		pTemCfgNode = NULL;
		pTemNode = pTemNode->pNext;
	}
	printf("%s: end\n",__func__);
}

