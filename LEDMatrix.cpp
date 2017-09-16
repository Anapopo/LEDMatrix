#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <cmath>
#include <iostream>
#include "Draw.cpp"
using namespace std;

class LEDMatrix {
public:
    int posX=0;
    int posY=0;
    bool canControl=false;
    uint8_t red[8]={0x18,0x3C,0x18,0x18,0x18,0x00,0x00,0x00};
    uint8_t green[8] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
    uint8_t blue[8] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
    LEDMatrix() {
        init();
        printf("Hello, the 8*8 LEDMatrix~ :)\n\r");
    }

    static void init() {
        wiringPiSetup();
        wiringPiSPISetup(0,500000);
        system("stty raw -echo -F /dev/tty");
    }

    void run() {
        if (canControl) tickKey();
        writeLED(red,green,blue);
    }

    void runDraw(Draw draw) {
        if (canControl) tickKey();
        writeLED(draw.rgb[0],draw.rgb[1],draw.rgb[2]);
    }

    void reset() {
        for (int i=0;i<8;i++) {
            red[i] = 0x00;
            green[i] = 0x00;
            blue[i] = 0x00;
        }
    }

    void setControlled(bool status) {
        canControl = status;
    }

    void setHeart() {
        reset();
        red[0] = 0x00;
        red[1] = 0x66;
        red[2] = 0xFF;
        red[3] = 0xFF;
        red[4] = 0xFF;
        red[5] = 0x7E;
        red[6] = 0x3C;
        red[7] = 0x18;
        printf("You can see a red heart.\n\r");
    }

private:
    void tickKey() {
        static int ch = 0;
        ch = readChar();
        //printf("char = (%c)\n",ch);
        if(ch) {
        switch(ch) {
            case 'd':
                posX = (posX+1)%8;
            break;
            case 'a':
                posX = (posX-1)%8;
                if (posX==-1) posX=7;
            break;
            case 'w':
                posY = (posY-1)%8;
                if(posY==-1) posY=7;
            break;
            case 's':
                posY = (posY+1)%8;
            break;
            case 3:
                system("stty -raw echo -F /dev/tty");
                exit(0);
            break;
        }
        reset();
        //int realX = (int) cos(M_PI/2)*posX+sin(M_PI/2)*posY;
        //int realY = (int) (cos(M_PI/2)*posY-sin(M_PI/2)*posX)+7;
        red[posY-1] = pow(2,posX);
        blue[posY] = pow(2,posX);
        green[posY] = pow(2,posX+1);
        //blue[(posY+1)%8]=pow(2,(posX+1)%8);
        
        printf("Current Postion is (%d:%d)\n\r",posX,posY);
       }
    }

    static int readChar() {
        fd_set rfds;
        struct timeval tv;
        int ch = 0;
    
        FD_ZERO(&rfds);
        FD_SET(0, &rfds);
        tv.tv_sec = 0;
        tv.tv_usec = 5; //设置等待超时时间
    
        //检测键盘是否有输入
        if (select(1, &rfds, NULL, NULL, &tv) > 0)
        {
            ch = getchar();
        }
        return ch;
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
    mat.setControlled(true);
    Point moe[7] = {
        Point(0,1,Point::RED),
        Point(1,1,Point::GREEN),
        Point(2,1,Point::BLUE),
        Point(0,0,Point::WHITE),
        Point(1,0,Point::CYAN),
        Point(2,0,Point::PURPLE),
        Point(0,2,Point::YELLOW)
    };
    Draw draw1(moe, 7);
    cout << draw1;
    while(1) mat.runDraw(draw1);
    return 0;
}
