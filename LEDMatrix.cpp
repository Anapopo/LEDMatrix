#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <cmath>
#include <iostream>
#include "Draw.cpp"
#include "CommandReader.cpp"
using namespace std;

class LEDMatrix {

public:
    Draw *drawInstance;

    LEDMatrix() {
        init();
        printf("Hello, the 8*8 LEDMatrix~ :)\n\r");
    }

    static void init() {
        wiringPiSetup();
        wiringPiSPISetup(0,500000);
        system("stty raw -echo -F /dev/tty");
    }

    void runDraw(Draw *draw) {
        this->drawInstance = draw;
        CommandReader::run(draw);

        while(1) {
            writeLED(draw->rgb[0],draw->rgb[1],draw->rgb[2]);
        }
    }

    void writeLED(uint8_t *red, uint8_t *green, uint8_t *blue) {
        uint8_t data[4] = {0x0,0x0,0x0,0x0};
        for (int j=0;j<8;j++) {
            data[0] = ~red[j];//Red
            data[1] = ~blue[j];//Blue
            data[2] = ~green[j];//Green
            data[3] = 0x01 << j;
            wiringPiSPIDataRW(0,data,sizeof(data));
            delay(1);
        }
    }
};

int main() {
    LEDMatrix mat;

    Point points[7] = {
        Point(0,1,Point::RED),
        Point(1,1,Point::GREEN),
        Point(2,1,Point::BLUE),
        Point(0,0,Point::WHITE),
        Point(1,0,Point::CYAN),
        Point(2,0,Point::PURPLE),
        Point(0,2,Point::YELLOW)
    };
    
    /*
    int values[64] = {
        0,0,0,0,0,0,0,0,
        0,1,0,0,0,0,1,0,
        1,0,1,0,0,1,0,1,
        0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,
        0,0,1,0,0,1,0,0,
        0,0,0,1,1,0,0,0,
        0,0,0,0,0,0,0,0
    };
    */
    //Draw draw2(values);
    Draw *draw1 = new Draw(points, 7);
    cout << *draw1;

    mat.runDraw(draw1);

    return 0;
}
