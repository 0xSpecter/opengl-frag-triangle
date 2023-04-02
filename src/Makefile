CC = clang
CXX = clang++
CFLAGS = -g -O -I../include -I../include/** -L../lib -Wall 

all: 
	@$(CXX) $(CFLAGS) -std=c++17 -c ./*.cpp 
	@$(CC) $(CFLAGS) -std=c11 -pedantic-errors -O3 -c glad.c -o glad.o
	@$(CXX) $(CFLAGS) -std=c++17 main.o glad.o -l glfw3 -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo -o main
	@./main
	@rm -f main.o
	@rm -f glad.o

c:
	@rm -f main.o
	@rm -f glad.o
	@rm -f main