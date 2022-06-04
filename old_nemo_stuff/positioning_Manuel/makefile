COMPILER = gcc
EXE_NAME = miguel_help_test
MAIN_FILENAME = main_test.c

default:
	$(COMPILER) miguel_help.c map.c -c
	$(COMPILER) $(MAIN_FILENAME) miguel_help.o map.o -o $(EXE_NAME)
	rm *.o

execute:
	./$(EXE_NAME)

valgrind:
	$(COMPILER) -c -g miguel_help.c map.c
	$(COMPILER) -g $(MAIN_FILENAME) miguel_help.o map.o -o $(EXE_NAME)
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full ./$(EXE_NAME)
	rm *.o
mem:
	$(COMPILER) -c -g miguel_help.c map.c
	$(COMPILER) -g $(MAIN_FILENAME) miguel_help.o map.o -o $(EXE_NAME)
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes ./$(EXE_NAME)
	rm *.o
leaks:
	$(COMPILER) -c -g miguel_help.c map.c
	$(COMPILER) -g $(MAIN_FILENAME) miguel_help.o -o $(EXE_NAME)
	valgrind --track-origins=yes --leak-check=full --show-leak-kinds=all ./$(EXE_NAME)
	rm *.o
clean:
	rm *.o
	rm $(EXE_NAME)
