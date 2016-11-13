CFLAGS=-std=c++11 -O3
run: test
	./test
test: test.h test.cpp network.o layer.o sigmoid.o
	g++ $(CFLAGS) -o test test.cpp network.o layer.o sigmoid.o
network.o: network.h network.cpp
	g++ $(CFLAGS) -c network.cpp -o network.o
layer.o: layer.h layer.cpp
	g++ $(CFLAGS) -c layer.cpp -o layer.o
sigmoid.o: sigmoid.h sigmoid.cpp
	g++ $(CFLAGS) -c sigmoid.cpp -o sigmoid.o
clean:
	rm -f test sigmoid.o layer.o network.o
