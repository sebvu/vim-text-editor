all: hello # just runs hello:

hello: main.cpp # requires main.cpp
	g++ -lncurses main.cpp -o ./src/main

editor: ./src/editor.cpp
	g++ -lncurses ./src/editor.cpp -o ./src/editor
