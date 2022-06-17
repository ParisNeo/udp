LIBS 	= 
CFLAGS	= -Wall -I inc
LDFLAGS	= -rcs
CC	= gcc   # compiler name
LD	= ar

TARGET	= libudp.a

OBJ := $(patsubst %.c,%.o,$(wildcard src/*.c))

all: $(TARGET) 


$(TARGET): $(OBJ)
	$(LD) $(LDFLAGS) -o $@ $(OBJ) $(LIBS)
	
src/%.o : src/%.c makefile
	$(CC) -MMD -MP -c $<  -o $@ $(CFLAGS) 
clean:
	rm -f $(TARGET)  $(OBJ) #This way is cleaner than your clean

install:
	cp libudp.a /lib/
	cp inc/udp.h /usr/include/

uninstall:
	rm /lib/libudp.a
	cp /usr/include/udp.h
