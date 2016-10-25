#!/usr/bin/python
import random

class builddata:
    '''build big data'''
    def __init__( self, fname, number ):
        self.number = number
	try:
	    self.fp = open(fname,'ab+')
	except IOError:
	    print "open failed"
	else:
	    print "open success"


    def build_data( self ):
	try:
            for i in range( 1,self.number + 1 ):
	        nu = "%.9d " % random.randint(0,410000000)
		self.fp.write(nu)
		if i % 12 == 0:
		    self.fp.write("\n");

	except IOError:
	    print "write error"
	else:
            print "write success"

    def __def__( self ):
        self.fp.close()

od = builddata( "data.txt",100008 )
od.build_data()

