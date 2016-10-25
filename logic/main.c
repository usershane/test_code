
#include "exe.h"
#include "../farme/list.h"
#include "../farme/config.h"
#include "../farme/run_time.h"
#include "../farme/list_case.h"
#include "../share_h/base_type.h"


void
AddTestFunction( void )
{
	PList pNode = NULL;

	pNode = create_node( 0, 0 );
	if( NULL == pNode )
	{
		printf("Create Number-0 node failed\n" );
		exit(0);
	}
	pNode->sData.m_unFun.RVoid = rVoid;
	if( !add_list( g_pList, pNode ) )
	{
		printf("Add Number-0 node failed\n" );
		exit(0);
	}
	
	pNode = NULL;
	pNode = create_node( 1, 2 );
	if( NULL == pNode )
	{
		printf("Create Number-0 node failed\n" );
		exit(0);
	}
	pNode->sData.m_unFun.RIntInt = rInt_int;
	if( !add_list( g_pList, pNode ) )
	{
		printf("Add Number-0 node failed\n" );
		exit(0);
	}

	pNode = NULL;
	pNode = create_node( 3, 101 );
	if( NULL == pNode )
	{
		printf("Create Number-0 node failed\n" );
		exit(0);
	}
	pNode->sData.m_unFun.RIntInt = rInt_int;
	if( !add_list( g_pList, pNode ) )
	{
		printf("Add Number-0 node failed\n" );
		exit(0);
	}
/*
	pNode = NULL;
	pNode = create_node( 4, 2 );
	if( NULL == pNode )
	{
		printf("Create Number-0 node failed\n" );
		exit(0);
	}
	pNode->sData.m_unFun.RIntInt = rInt_int;
	if( !add_list( g_pList, pNode ) )
	{
		printf("Add Number-0 node failed\n" );
		exit(0);
	}
*/
}

int
main(void)
{
	if( !InitModeConfig() )
	{
		printf("Configuration module initialization failed\n");
		return -1;
	}
	if( !init_mode_list() )
	{
		printf("Function module initialization failed\n");
		return -2;	
	}

	AddTestFunction();

	run_test( g_pList->pNext, pcfgList );
	
	return 0;
}

