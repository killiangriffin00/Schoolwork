prog: main.o twitterData.o
	g++ main.o twitterData.o

main.o: main.cpp twitterData.h
	g++ -c main.cpp twitterData.h

twitterData.o: twitterData.cpp twitterData.h
	g++ -c twitterData.cpp twitterData.h 

clean:
	rm *.o

run:
	@./a.out