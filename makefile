all: bj.so

bj.so: 
	g++ -o bj.so -shared bj.os -lboost_python -lpython2.7

bj.os: 
	g++ -std=c++11 -o bj.os -c -fPIC -I/usr/include/python2.7 BlackJack.cpp

clean:
	rm -f bj.os 
