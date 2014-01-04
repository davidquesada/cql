CFLAGS = -c -g -O0 --std=c++11 -Wall -Wextra -Wvla -pedantic -Wshadow
LFLAGS = 

OUT = test

OBJS = cql.o main.o coltype.o select.o

	
all: $(OBJS)
	g++ $(LFLAGS) $(OBJS) -o $(OUT)
	
clean:
	rm $(OUT) $(OBJS)
	
main.o: main.cpp cql.h coltype.h
	g++ $(CFLAGS) main.cpp
	
cql.o: cql.cpp cql.h coltype.h
	g++ $(CFLAGS) cql.cpp
	
coltype.o: coltype.cpp coltype.h cql.h
	g++ $(CFLAGS) coltype.cpp
	
select.o: select.cpp cql.h
	g++ $(CFLAGS) select.cpp