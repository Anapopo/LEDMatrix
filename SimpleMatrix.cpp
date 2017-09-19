#include <iostream>
#include <iomanip>
using namespace std;
class SimpleMatrix {

public:
    int rows=8;
    int columns=8;
    int **element;

    SimpleMatrix(int values[]) {
        this->init();
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < columns; j++)
                this->element[i][j] = values[i * columns + j];
    }
    //设置元素
    void set(int i, int j, int x)
    {
        if (i >= 0 && i < rows && j >= 0 && j < columns)
            this->element[i][j] = x;
        else throw out_of_range("i and j must be range from 0 to rows/columns");
    }
    //获取元素
    int get(int i, int j)
    {   
        if (i >= 0 && i < rows && j >= 0 && j < columns)
            return this->element[i][j];
        throw out_of_range("can not find the specify i and j!");
    }

    int getElementCount() {
        int count=0;
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < columns; j++)
                if(this->element[i][j] != 0)
                    count++;
        return count;
    }
    void transform() {
        //for (int i=0;i<8;i++)
        //    for (int j=0;j<8;j++)

    }

    //重载<<符号
    friend ostream& operator<<(ostream& out, SimpleMatrix &mat)
    {
        //printf();
        out << "SimpleMatrix (" << mat.rows << "X" << mat.columns << ") Points(" << mat.getElementCount() << ")" << endl;
        for (int i = 0; i < mat.rows; i++)
        {
            for (int j = 0; j < mat.columns; j++)
            {
                if (mat.element[i][j] == 0) out << setw(2) << "\033[37m□  \033[0m";
                //printf(" The ......\n");
                if (mat.element[i][j] == 1) out << setw(2) << "\033[32m■  \033[0m";
            }
                
            out << endl;
        }
        return out;
    }

private:
    void init() {//8*8
        this->element = new int*[8];
        for (int i=0;i<8;i++) this->element[i] = new int[8];
    }
};
