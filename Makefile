CC=g++
CFLAGS=-std=c++11 `pkg-config opencv --cflags --libs`
#$(CC) te.cpp steg.cpp other.cpp -o tee $(CFLAGS)   compile all

all: tee
	
tee: te.o steg.o other.o
	$(CC) te.o steg.o other.o -o tee  $(CFLAGS)

te.o: te.cpp
	$(CC) -c te.cpp  $(CFLAGS)

steg.o: steg.cpp
	$(CC) -c steg.cpp  $(CFLAGS)

other.o: other.cpp
	$(CC) -c other.cpp  $(CFLAGS)
	


clean:
	rm -rf *.o tee
