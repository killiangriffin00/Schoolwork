prog: main.o CancerData.o
	g++ -g main.o CancerData.o 

main.o: main.cpp AVLTree.h AVLNode.h CancerData.h
	g++ -g -c main.cpp 

CancerData.o: CancerData.cpp CancerData.h AVLTree.h AVLNode.h
	g++ -g -c CancerData.cpp 

clean:
	-rm *.o

run:
	@./a.out