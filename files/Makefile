OBJECTS=phidget-servo 

CFLAGS=-g -O0 -Wall 
LIBS= -lphidget21

all: $(OBJECTS)

%: %.c phidget21.h
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS) \\

clean:
	-rm *.o $(OBJECTS)
