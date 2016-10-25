tfun:config.o list.o list_case.o run_time.o main.o exe.o
	cc -o tfun config.o list.o list_case.o run_time.o main.o exe.o

config.o : farme/config.c farme/config.h
	cc -c farme/config.c

list.o : farme/list.c farme/list.h
	cc -c farme/list.c

list_case.o : farme/list_case.c farme/list_case.h
	cc -c farme/list_case.c

run_time.o : farme/run_time.c farme/run_time.h
	cc -c farme/run_time.c

main.o : logic/main.c
	cc -c logic/main.c

exe.o : logic/exe.c
	cc -c logic/exe.c

clean:
	rm *.o
