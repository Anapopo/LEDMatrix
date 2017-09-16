#include <stdio.h>

class Point {

private:
    int posX=0;
    int posY=0;
    bool boolRGB[3]={0};

public:
    const static int RED=0;//红色
    const static int GREEN=1;//绿色
    const static int BLUE=2;//蓝色
    const static int YELLOW=3;//黄色=红+绿
    const static int PURPLE=4;//紫色=红+蓝
    const static int CYAN=5;//青色=绿+蓝
    const static int WHITE=6;//白色=红绿蓝
    const static int NOCOLOR=7;

    Point(){
        posX=posY=0;
    }

    Point(int x, int y) {
        posX=x;
        posY=y;
    }

    Point(int x, int y, int color) {
        this->posX=x;
        this->posY=y;
        switch(color) {
            case Point::RED://100
                boolRGB[0]=1;
            break;
            case Point::GREEN://010
                boolRGB[1]=1;
            break;
            case Point::BLUE://001
                boolRGB[2]=1;
            break;
            case Point::YELLOW://110
                boolRGB[0]=1;
                boolRGB[1]=1;
            break;
            case Point::PURPLE://101
                boolRGB[0]=1;
                boolRGB[2]=1;
            break;
            case Point::CYAN://011
                boolRGB[1]=1;
                boolRGB[2]=1;
            break;
            case Point::WHITE://111
                boolRGB[0]=1;
                boolRGB[1]=1;
                boolRGB[2]=1;
            break;
            case Point::NOCOLOR://000
                //do nothing
            break;
        }
    }

    void setPosition(int x, int y) {
        posX=x;
        posY=y;
    }

    int getX() { return posX; }
    int getY() { return posY; }
    bool getRed() { return boolRGB[0]; }
    bool getGreen() { return boolRGB[1]; }
    bool getBlue() { return boolRGB[2]; }
};
