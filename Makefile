depotter: depotter.o stockUpdater.o
	g++ -pthread -lcurl -lcjson --output depotter depotter.o stockUpdater.o

depotter.o: src/depotter.cpp
	g++ -c src/depotter.cpp

stockUpdater.o: src/stockUpdater.cpp
	g++ -c -lcjson src/stockUpdater.cpp

install: depot
	mv depot /usr/bin/depot

clean:
	rm *.o depotter
