COMPILER = g++
EXE_NAME = test
MAIN_FILENAME = graph.c

default:
	$(COMPILER) positioning.c -c
	$(COMPILER) miguel_help.c -c
	$(COMPILER) $(MAIN_FILENAME) *.o -o $(EXE_NAME)
	rm *.o

execute:
	./$(EXE_NAME)