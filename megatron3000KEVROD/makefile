all: megatron3000KEVROD

megatron3000KEVROD: megatron3000KEVROD.o esquema.o MenteMaestra.o
    g++ -std=c++11 -Wall -o megatron3000KEVROD megatron3000KEVROD.o esquema.o MenteMaestra.o

megatron3000KEVROD.o: megatron3000KEVROD.cpp MenteMaestra.h
    g++ -std=c++11 -Wall -c megatron3000KEVROD.cpp

esquema.o: esquema.cpp esquema.h
    g++ -std=c++11 -Wall -c esquema.cpp

MenteMaestra.o: MenteMaestra.cpp MenteMaestra.h esquema.h
    g++ -std=c++11 -Wall -c MenteMaestra.cpp

clean:
    rm -f *.o megatron3000KEVROD
