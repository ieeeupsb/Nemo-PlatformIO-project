# https://makefiletutorial.com/

LIB_DIR = libs
objects_list = info.o my_socket.o main.o

#CPP COMPILER AND FLAGS
CXX = g++
CXXFLAGS = -g -Wall -fstack-protector -O3

APP_NAME = program
src_ext = cpp
VALGRIND_MEM_FLAGS = --tool=memcheck --track-origins=yes
VALGRIND_LEAKS_FLAGS = --leak-check=full

all: help

help:
	@echo ''

$(objects_list): %.o: %.$(src_ext)

$(APP_NAME): $(objects_list)
	$(CXX) $(CXXFLAGS) main.o info.o my_socket.o -o $(APP_NAME)


gdb: $(APP_NAME)	
	gdb ./$(APP_NAME) $(ftp_add)

clean:
	rm -f $(APP_NAME) *.o

clear_terminal:
	clear

pipe.txt: $(APP_NAME)
	./$(APP_NAME) ftp://rcom:rcom@netlab1.fe.up.pt/pipe.txt

pub.txt: $(APP_NAME)
	valgrind $(VALGRIND_MEM_FLAGS) ./$(APP_NAME) download ftp://netlab1.fe.up.pt/pub.txt

valgrind:
	valgrind ./$(APP_NAME)


mem:
	clear
	make $(APP_NAME)
	valgrind $(VALGRIND_MEM_FLAGS) ./$(APP_NAME) ftp://rcom:rcom@netlab1.fe.up.pt/pipe.txt
	make clean

leaks:
	clear
	make $(APP_NAME)
	valgrind $(VALGRIND_LEAKS_FLAGS) ./$(APP_NAME) ftp://rcom:rcom@netlab1.fe.up.pt/pipe.txt
	make clean
# valgrind leaks:
# 	$(valgrind_leaks_flags) ./$(APP_NAME) ftp://netlab1.fe.up.pt/pub.txt

$(files_list): %.o: %.$(src_ext)

test1: clean clear_terminal $(APP_NAME) pub.txt
test2: clean clear_terminal $(APP_NAME) pipe.txt
exec_all: clear_terminal $(APP_NAME) pipe.txt pub.txt
val: clear_terminal $(APP_NAME) val_pipe val_pub clean 