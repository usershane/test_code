
#ifndef __LIST_H__
#define __LIST_H__

#include "../share_h/base_type.h"
#include "config.h"


typedef struct list*	PList;
typedef PList (*PFunInitCre)( int,int );

struct test_fun{

	int m_nType;						//函数类型的编号
	union
	{	
		/* 001 - 100*/
		int (*RIntVoid)(void);				// 001
		int (*RIntInt)( int );				// 002
		int (*RIntUCharUChar)( uchar,uchar );		// 003
		int (*RIntPUCharPUChar)( uchar*, uchar* );	// 004

		/* 101 - 200 */
		void (*RVoid)(void);				// 000
		void (*RVoidIntPChar)( int,char* );		// 101
	}m_unFun;
};

struct list{
	uint m_nListNumb;					//列表节点的编号
	struct test_fun sData;
	struct list* pNext;
};

/* 描述：全局变量
 *
 * **************************************************/
extern PFunInitCre init_list; 
extern PFunInitCre create_node;
extern PList g_pList;




/* 描述：函数声明
 *
 * **************************************************/


void
print_node( PList );

void
print_fun_list( PList );



/*
 * 描述： 初始化list模块
 * 
 *  return : 成功返回true, 失败返回false
 *
 * ******************************************/
bool
init_mode_list();

/*
 * 描述： 初始化与创建一个节点
 * 
 *  nNumb	: 链表节点编号。
 *  nType	: 函数的类型编号。
 *  return 	: 成功返回节点的地址, 失败返回NULL。
 *
 * ******************************************/
PList
init( int nNumb,int nType );

/*
 * 描述： 向链表中添加一个节点。
 * 
 *  pList	: 链表的头节点。
 *  pNode	: 向链表中添加的节点。
 *  return 	: 成功返回true, 失败返回false。
 *
 * ******************************************/
bool 
add_list( PList pList, PList pNode );


/*
 * 描述： 运行函数链表中的所有节点。
 * 
 *  pList	: 链表的头节点。
 *  pNode	: 向链表中添加的节点。
 *  return 	: 成功返回true, 失败返回false。
 *
 * ******************************************/
void
run_test( PList pList, PCfgList pcfgList );



#endif
