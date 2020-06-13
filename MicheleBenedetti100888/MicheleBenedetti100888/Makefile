CC = gcc
objects = main.o filedistance.o levensthein.o linked_list.o time.o

all : filedistance

filedistance : $(objects)
	$(CC) -o filedistance $(objects)

main.o : main.c

filedistance.o : filedistance.c time.h linked_list.h

levensthein.o : levensthein.c linked_list.h

linked_list.o : linked_list.c

time.o : time.c

clean :
	rm *.o filedistance *.bin output.txt
