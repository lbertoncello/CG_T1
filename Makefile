all:
	g++ -std="c++11" main.cpp circle.cpp -lGL -lGLU -lglut -o trabalhocg

clean:
	rm trabalhocg