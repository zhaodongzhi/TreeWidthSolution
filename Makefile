CC = gcc
LD = gcc
CFLAGS		= -I include/ -c -w  -Ofast 
LDFLAGS		= -s

MAIN = main

OBJS = source/main.o source/global.o source/eliminate.o source/graph.o 
SOURCE = source/main.cpp source/global.cpp source/eliminate.cpp source/graph.cpp 


everything : $(MAIN)

depend : $(SOURCE) 
	rm -f .depend
	$(CC) -MM $^ -I include > .depend
	./completedepend

all : realclean everything 

clean :
	rm -f $(OBJS) */*~

realclean :
	rm -f $(OBJS) $(MAIN)

open:
	gvim -p `ls include/*.h`
	gvim -p $(SOURCE)	

$(MAIN) : $(OBJS)
	$(LD) $(LDFLAGS) -o $(MAIN) $(OBJS)

-include .depend


