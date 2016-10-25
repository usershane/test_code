
#ifndef __BASE_TYPE_H__
#define __BASE_TYPE_H__

/* Headef file section:
 *
 *      NULL
 *****************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* Compile section:
 *
 *  Compile switch。
 *
 *****************************************************/

#define CODE_TEST_OPEN	0x001


#define LIST_TEST 	0x010
#define CONFIE_TEST	0x011
#define RUN_TIME	0x012
#define LIST_CASE	0x013


/* Data struct section:
 *
 *    Basic data types
 *
 *****************************************************/


#define true 1
#define false 0

typedef int bool;
typedef unsigned char uchar;
typedef unsigned short uint_16;
typedef unsigned int uint;
typedef unsigned long long int ulint;


#endif
