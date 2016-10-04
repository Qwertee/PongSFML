all:
	g++ -std=c++11 -c Main.cpp Player.cpp
	g++ Main.o Player.o -o PongSFML -lsfml-graphics -lsfml-window -lsfml-system
	rm *.o
clean:
	rm PongSFML
