all: LEDMatrix.cpp
	g++ LEDMatrix.cpp -o LEDMatrix -std=c++11 -pthread -lwiringPi -lm
clean:
	rm LEDMatrix
test:
	sudo ./LEDMatrix
