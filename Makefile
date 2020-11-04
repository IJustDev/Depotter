depot: main.o stockUpdater.o
	g++ -pthread -lcurl --output depot main.o stockUpdater.o

main.o: main.cpp
	g++ -c main.cpp

stockUpdater.o: stockUpdater.cpp
	g++ -c stockUpdater.cpp

install: depot
	mv depot /usr/bin/depot

clean:
	rm *.o depot
