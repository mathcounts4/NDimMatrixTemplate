all:
	@clear
	@clear
	@g++ -std=c++14 TestMatrix.cpp -o testMatrix.out -D DEBUG -g
	@./testMatrix.out
