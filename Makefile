all: hello # just runs hello:

hello: main.cpp # requires main.cpp
	g++ -lncurses main.cpp -o main

editor: editor.cpp
	g++ -lncurses editor.cpp -o editor
