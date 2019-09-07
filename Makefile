all:
	g++ -std="c++11" tinystr.cpp tinyxml.cpp tinyxmlerror.cpp tinyxmlparser.cpp main.cpp draw.cpp point.cpp circle.cpp color.cpp -lGL -lGLU -lglut -o trabalhocg

clean:
	rm trabalhocg