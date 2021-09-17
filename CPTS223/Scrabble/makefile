sfml-app: main.o Dictionary.o Board.o Game.o
	g++ -g -Wall -std=c++11 main.o Dictionary.o Board.o Game.o -L ///usr/include/SFML/lib -lsfml-graphics -lsfml-window -lsfml-system

main.o: main.cpp Game.h Dictionary.h Board.h
	g++ -g -c -Wall -std=c++11 main.cpp -I ///usr/include/SFML/include


Dictionary.o: Dictionary.cpp Game.h Dictionary.h Board.h
	g++ -g -c -Wall -std=c++11 Dictionary.cpp  -I ///usr/include/SFML/include

Board.o: Board.cpp Game.h Dictionary.h Board.h
	g++ -g -c -Wall -std=c++11 Board.cpp  -I ///usr/include/SFML/include

Game.o: Game.cpp Game.h Dictionary.h Board.h
	g++ -g -c -Wall -std=c++11 Game.cpp -I ///usr/include/SFML/include

clean: 
	-rm *.o

run: 
	@./sfml-app