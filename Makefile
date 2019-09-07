all:
	g++ -std="c++11" main.cpp -lGL -lGLU -lglut -o trabalhocg

clean:
	rm trabalhocg