#include <iostream>
#include "Point.cpp"
#include "SimpleMatrix.cpp"
using namespace std;

class Draw {
/*
heart:00 66 FF FF FF 7E 3C 18
*/
public:
    int pointCount=0;

    const static int MOVE_UP   =0;
    const static int MOVE_DOWN =1;
    const static int MOVE_LEFT =2;
    const static int MOVE_RIGHT=3;

    SimpleMatrix *pointMatrix;
    Point *points;
    //SimpleMatrix colorMatrix;
    int boundary[4];//up down left right
    uint8_t **rgb;

    Draw(int values[], int count) { //for points

    }

    Draw(int values[]) {//For Matrix
        pointMatrix = new SimpleMatrix(values);
        pointCount = pointMatrix->getElementCount();
        cout << (*pointMatrix);
        initRGB();
        updateRGB();
    }

    Draw(Point *points, int count) {
        initRGB();
        //updateBoundary();
        this->pointCount = count;
        this->points = points;
        this->updateRGB();
    }

    void initRGB() {
        this->rgb = new uint8_t*[3];
        for (int i = 0; i < 3; i++)
            this->rgb[i] = new uint8_t[8];
    }

    void updateRGB() {
        this->resetRGB();
        for (int i=0;i<pointCount;i++) {
            if(points[i].hasRed())   rgb[0][points[i].getY()] += pow(2,points[i].getX());
            if(points[i].hasGreen()) rgb[1][points[i].getY()] += pow(2,points[i].getX());
            if(points[i].hasBlue())  rgb[2][points[i].getY()] += pow(2,points[i].getX());
        }
    }

    void moveRight() { move(Draw::MOVE_RIGHT); }
    void moveLeft() { move(Draw::MOVE_LEFT); }
    void moveUp() {move(Draw::MOVE_UP); }
    void moveDown() { move(Draw::MOVE_DOWN); }

    void lightPoint(Point p) {

    }

    void updateBoundary() {
        //boundary[]
        //if (moe[i].getX() < left) left = moe[i].getX();
        //if (moe[i].getX() > right) right = moe[i].getX();
        //if (moe[i].getY() < up) up = moe[i].getY();
        //if (moe[i].getY() > down) down = moe[i].getY();       
    }
    void shutdown() {
        this->resetRGB();
    }

    /* for some new feature
    int getUp() { return up; }
    int getDown() { return down; }
    int getLeft() { return left; }
    int getRight() { return right; }
    */
private:

    void resetRGB() {
        for (int i=0;i<3;i++)
            for (int j=0;j<8;j++)
                rgb[i][j]=0x00;
    }

    void move(int moveType) {
        switch(moveType) {
            case Draw::MOVE_UP:
                for (int i=0;i<pointCount;i++) 
                    points[i].setPosition(points[i].getX(), points[i].getY()-1);
            break;
            case Draw::MOVE_DOWN:
                for (int i=0;i<pointCount;i++) 
                    points[i].setPosition(points[i].getX(), points[i].getY()+1);
            break;
            case Draw::MOVE_LEFT:
                for (int i=0;i<pointCount;i++) 
                    points[i].setPosition(points[i].getX()-1, points[i].getY());
            break;
            case Draw::MOVE_RIGHT:
                for (int i=0;i<pointCount;i++) 
                    points[i].setPosition(points[i].getX()+1, points[i].getY());
            break;
        }
        updateRGB();
    }

    void rotate() {
        //:TODO
    }

public:
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
