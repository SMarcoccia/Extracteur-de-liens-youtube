
CC = gcc
CFLAGS = -O3 -Wall -Wextra -Werror -g  -DEBUG 
CCCOM = $(CC) $(CFLAGS) -std=c11

SRC = $(wildcard *.c)
OBJS = $(SRC:.c=.o) 

LDLIBS = -lmingw32
LDFLAGS = -L/mingw/lib

EXE = links
RM = del -f

all:  $(EXE) 
	
$(EXE):  $(OBJS)
	$(CCCOM) $(LDFLAGS) -o $@ $^ $(LDLIBS)

.PHONY: clean mrproper

clean:  
	$(RM) *.o *~ *.stackdump *.bak *.makefile 

mrproper: clean
	$(RM) *.exe
	

