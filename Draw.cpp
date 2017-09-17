#include <iostream>
#include "Point.cpp"
#include "SimpleMatrix.cpp"

using namespace std;
class Draw {

public:
    int pointCount=0;
    SimpleMatrix *pointMatrix;
    //SimpleMatrix colorMatrix;
    int boundary[4];//up down left right
    uint8_t **rgb;

    Draw(int values[]) {
        pointMatrix = new SimpleMatrix(values);
        pointCount = pointMatrix->getElementCount();
        cout << (*pointMatrix);
        
        initRGB();
        updateRGB();
    }

    Draw(Point *moe, int count) {
        initRGB();
        updateBoundary();
        pointCount = count;

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
    void resetRGB() {
        for (int i=0;i<3;i++)
            for (int j=0;j<8;j++)
                rgb[i][j]=0x00;
    }

    void initRGB() {
        this->rgb = new uint8_t*[3];
        for (int i = 0; i < 3; i++)
            this->rgb[i] = new uint8_t[8];
        resetRGB();
    }

    void updateRGB() {
        resetRGB();
        for (int i=0;i<8;i++)//row=j
            for (int j=0;j<8;j++)//colomn=x
                if (pointMatrix->get(i,j) == 1) rgb[0][i] += pow(2,j);

    }

    void updateBoundary() {
        //boundary[]
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