
#ifndef __CONFIG_H__
#define __CONFIG_H__

#include "../share_h/base_type.h"
#include <regex.h>

typedef struct cfgList* PCfgList;


/*
   表 1
   -------------------------
   | 编号 |      类型      |
   -------------------------
   |  1   |     int        |
   -------------------------
   |  2   |     string	   |
   -------------------------
   |  3   |     uint       |
   -------------------------
   |  4   |     uchar      |
   -------------------------

 * **********************************************************/

struct cfgList{
	struct{
		int 	m_nType;		/* 数据类型的编号，参考 表1  */
		int 	m_nNumb;		/* CFG文件的节点编号 */
		char 	m_arrKey[21];		/* KEY存放的结构 */
		union{
			char m_arrValue[81];
			struct {
				int m_nMax;
				int m_nMin;
			}m_Size;
		}m_unValue;
	}m_sData;
	struct cfgList* m_pNext;
};


/*
 * 描述： 全局声明区
 *
 * **************************************************************/

extern PCfgList pcfgList;


/*
 * 描述： 外部接口，函数声明
 *
 * **************************************************************/

/*
 * 描述： 初始化本模块，使用本模块时应，
 *
 * 	首先调用。
 *
 * ***************************************/
bool
InitModeConfig(void);

/*
 * 描述：初始化，生成一条链表。 
 *
 * pFile	: 文件路径与文件名。
 * pList	: 用于存储文件数据的链表。
 * 
 *****************************************/
bool
cfgInit( char* pFile, PCfgList pList );


/*
 * 描述： 分解文件中的一行数据。
 *
 * in_pText	: 输入参数，文件中的一行数据
 * out_pKey	: 输出参数，KEY的值。
 * out_pValue	: 输出参数，VALUE的值。
 *
 * ****************************************/
bool
char_decom( char *in_pText, char** out_pKey, char** out_pValue );

/*
 * 描述		: 向链表中添加一个节点，并给
 *
 * 	节点的数据。在此函数中创建节点，并把节点添加到给定的链表中。
 *
 * pList	: 链表的头节点，
 * nNu		: 添加链表节点的，编号
 * nTy		: 添加链表节点的，类型
 * arrKey	: 添加链表节点的，字符的键值
 * nMa		: 添加链表节点的，整型，最大值
 * nMi		: 添加链表节点的，整型，最小值
 * arrVa	: 添加链表节点的，字符，值
 *
 * ****************************************/
bool
cfgAddList( PCfgList pList, int nNu, int nTy, char arrKey[], int nMa, int nMi, char arrVa[] )

/*
 * 描述		: 创建一个链表的节点，并返回。
 *
 * ****************************************/
PCfgList
cfgCreateNode( void )；

/*
 * 描述		: 查找链表中的一个节点。
 *
 * pList	: 所要查找链表的头节点。
 * nNumb	: 查找的节点编号
 *
 * ****************************************/
PCfgList
cfgFindNode( PCfgList pList ,int nNumb );

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
cfg_set_node( PCfgList pNode, int nNu, int nTy, char arrKey[], int nMa, int nMi, char arrVa[] );

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
cfg_get_node( PCfgList pNode, const int nNum, int *pMax, int *pMin, char *pValue);


#endif
