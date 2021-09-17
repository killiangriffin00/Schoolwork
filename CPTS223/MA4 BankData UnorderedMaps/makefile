prog: main.o BankData.o
	g++ -g main.o BankData.o

main.o: main.cpp BankData.hpp
	g++ -g -c main.cpp

BankData.o: BankData.cpp BankData.hpp
	g++ -g -c BankData.cpp

clear: 
	-rm *.o

run:
	@./a.out