CC = gcc
objects = main.o filedistance.o levensthein.o linked_list.o time.o recursive.o modfile.o

all : filedistance

filedistance : $(objects)
	$(CC) -o filedistance $(objects)

main.o : main.c

filedistance.o : filedistance.c time.h recursive.h modfile.h

levensthein.o : levensthein.c linked_list.h

linked_list.o : linked_list.c

recursive.o : recursive.c levensthein.h

modfile.o : modfile.c linked_list.h

time.o : time.c

clean :
	rm *.o filedistance *.bin
