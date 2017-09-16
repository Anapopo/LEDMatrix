#include <iostream>
#include "Point.cpp"
using namespace std;
class Draw {
public:
    int pointCount;
    int up;
    int down;
    int left;
    int right;
    uint8_t **rgb;

    Draw(Point *moe, int count) {
        initRGB();
        pointCount = count;
        //up=down   =moe[0].getY();
        //left=right=moe[0].getX();
        for (int i=0;i<count;i++) {
            //if (moe[i].getX() < left) left = moe[i].getX();
            //if (moe[i].getX() > right) right = moe[i].getX();
            //if (moe[i].getY() < up) up = moe[i].getY();
            //if (moe[i].getY() > down) down = moe[i].getY();

            if(moe[i].getRed()) rgb[0][moe[i].getY()] += pow(2,moe[i].getX());
            if(moe[i].getGreen()) rgb[1][moe[i].getY()] += pow(2,moe[i].getX());
            if(moe[i].getBlue()) rgb[2][moe[i].getY()] += pow(2,moe[i].getX());
        }
    }

    void initRGB() {
        this->rgb = new uint8_t*[3];
        for (int i = 0; i < 3; i++)
            this->rgb[i] = new uint8_t[8];
        for (int i=0;i<3;i++)
            for (int j=0;j<8;j++)
                rgb[i][j]=0x00;
    }
    /* for some new feature
    int getUp() { return up; }
    int getDown() { return down; }
    int getLeft() { return left; }
    int getRight() { return right; }
    */
    friend ostream& operator<<(ostream& out, Draw &draw) {
        printf("RGB输出:\n\r");
        for (int i=0;i<3;i++) {
            for (int j=0;j<8;j++)
                printf("0x%02X ", draw.rgb[i][j]);
                //out << draw.rgb[i][j] << " ";
            printf("\n\r");
        }
        return out; 
    }

};