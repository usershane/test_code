
#include "../share_h/base_type.h"


void
rVoid( void )
{
	printf("RVoid eaddress = %x\n", rVoid );
	printf("Para is NULL\n");
}

int
rInt_int( int n )
{
	printf("rInt_int address = %x\n",__func__, rInt_int );
	printf("Para-1: %d\n",n );
	return n+1;
}

void
rVoid_int_pChar( int nNumb, char *pText )
{
	printf( "rVoid_int_pChar address = %x\n",__func__, rVoid_int_pChar );
	printf( "Para-1: %d\tPara-2: %s\n", nNumb, pText );
}

