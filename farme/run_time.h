
#ifndef __RUN_TIME_H__
#define __RUN_TIME_H__

#include <time.h>
#include <math.h>
#include "../share_h/base_type.h"

double run_time( int nnum, void (*fun)( void *p, int n ), void* pdata, int nsize );


#endif
