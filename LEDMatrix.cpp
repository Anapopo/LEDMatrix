#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <cmath>
#include <iostream>
using namespace std;

class LEDMatrix {
public:
    int posX=0;
    int posY=0;
    bool canControl=0;
    uint8_t heart[8]={0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
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
        writeLED();
    }

    void reset() {
        for (int i=0;i<8;i++)
            heart[i] = 0x00;
    }

    void setControlled(bool status) {
        canControl = status;
    }

    void setHeart() {
        heart[0] = 0x00;
        heart[1] = 0x66;
        heart[2] = 0xFF;
        heart[3] = 0xFF;
        heart[4] = 0xFF;
        heart[5] = 0x7E;
        heart[6] = 0x3C;
        heart[7] = 0x18;
        printf("The pixel is heart.\n\r");
    }

private:
    void tickKey() {
        static int ch = 0;
        ch = readChar();
        //printf("char = (%c)\n",ch);
        if(ch) {
        switch(ch) {
            case 'w':
                posY = (posY-1)%8;
                if(posY==-1) posY=7;
            break;
            case 's':
                posY = (posY+1)%8;
            break;
            case 'a':
                posX = (posX-1)%8;
                if(posX ==-1) posX=7;
            break;
            case 'd':
                posX = (posX+1)%8;
            break;
            case 3:
                system("stty -raw echo -F /dev/tty");
                exit(0);
            break;
        }
        printf("Current Postion is (%d:%d)\n\r",posX,posY);
        reset();
        heart[posY]=pow(2,posX);
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

    void writeLED() {
        uint8_t data[4] = {0x0,0x0,0x0,0x0};
        for (int j=0;j<8;j++) {
            data[0] = ~heart[j];
            data[1] = 0xFF;
            data[2] = 0xFF;
            data[3] = 0x01 << j;
            wiringPiSPIDataRW(0,data,sizeof(data));   
            delay(2); 
        }
    }
};

int main() {
    LEDMatrix mat;
    mat.setControlled(true);
    mat.setHeart();
    while(1) mat.run();

    return 0;
}
