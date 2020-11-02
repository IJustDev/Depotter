depot: main.o
	g++ -pthread --output depot main.o

main.o: main.cpp
	g++ -c main.cpp

clean:
	rm *.o depot
