prog: main.o InventoryRecord.o
	g++ -g main.o InventoryRecord.o

main.o: main.cpp InventoryRecord.h RedBlackNode.h RedBlackTree.h
	g++ -g -c main.cpp InventoryRecord.h RedBlackNode.h RedBlackTree.h

InventoryRecord.o: InventoryRecord.cpp InventoryRecord.h
	g++ -g -c InventoryRecord.cpp InventoryRecord.h

clean:
	-rm *.o

run:
	@./a.out