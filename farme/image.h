
#ifndef IMAGE_H
#define IMAGE_H

#include "../share_h/base_type.h"
#include "config.h"


#define IMAGE_SIACE 15501


typedef s_image* PSImage

struct s_image
{
	int m_nNumb;				// 节点编号--对应函数列表的节点
	int m_nSize;				// 所读图片数据的大小	
	char m_arrRoute[81];			// 图片所存放的路径
	char m_arrName[21];			// 图片的命名规则
	struct image_data			// 
	{
		uchar m_arrData[ IMAGE_SIZE ];		// 图片数据的存方BUFF
		struct image_data* m_pNext;		// 下个图片存放的BUFF
	}*m_spList;
	struct s_image *m_pNext;
};

extern struct PSImage g_pImageList;

extern struct PList g_pList;


/* 描述：函数声明
 *
 * **************************************************/

PSImage
image_Init( char *pFile, PSImage  )

PSImage
image_AddList( PSImage pList, PSImage pNode );

PSImage
image_FindNode( PSImage pList, int nNumb  );



#endif
