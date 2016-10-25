
#include "run_time.h"


#define TEST_CODE

/*
 * describe: 
 *
 *	Get an algorithm running time.
 *
 *	@nnum	: running times
 *	@fun	: fnuction of algorithm
 *	@pdata	: function of data
 *	@nsize	: data of size
 *
 *	@retunr	: running time
 * ****************************************************/
double 
run_time( int nnum, void (*fun)( void *p, int n ), void *pdata, int nsize )
{
	clock_t start, stop;
	int i;
	double time = 0;

	start = clock();
	for( i = 0; i < nnum; i++ )
		fun( pdata, nsize );
	stop = clock();
	
	time = ( ( double ) ( stop - start ) ) / CLOCKS_PER_SEC;
	return time;
}


#ifdef TEST_CODE


/*
 * describe:
 *
 * 	With work to code the test code.
 *
 *
 * ************************************************************/

int
rule( int x, int y )
{
	return x - y;
}

void
test_fun( void* pdata, int nsize )
{
	int *pndata = (int*)pdata;
	int i,j;
        for( i = 0; i < nsize - 1 ; i++ )
        {
                int min = i;
                for( j = i + 1; j < nsize ; j++ )
                {
                        if( rule( pndata[j], pndata[min] ) < 0 )
                        {
                                min = j;
                        }
                }
                if( min != i )
                {
                        pndata[i]        = pndata[i] ^ pndata[min];
                        pndata[min]      = pndata[i] ^ pndata[min];
                        pndata[i]        = pndata[i] ^ pndata[min];
                }
        }
}

/*
int
main(void)
{
	double dotime = 0;
	int ndata[] = { 3, 7, 1, 6, 8, 2 , 9, 7, 0, 4 };
	
	dotime = run_time( 400000, test_fun, ndata, 10 );

	printf(" runing time = %lf\n",dotime );
	return 0;
}
*/

#endif
