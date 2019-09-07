all:
	g++ -std="c++11" main.cpp draw.cpp point.cpp circle.cpp color.cpp -lGL -lGLU -lglut -o trabalhocg

clean:
	rm trabalhocg