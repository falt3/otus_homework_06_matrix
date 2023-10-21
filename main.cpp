#include "matrix.h"


int main() 
{
    Matrix<int, 2, 0> mm;


    for (int i = 0; i < 10; ++i)
        mm[i][i] = i;
    for (int i = 0; i < 10; ++i)
        mm[9-i][i] = 9-i;


    for (int i = 1; i < 9; ++i) {
        for (int j = 1; j < 9; ++j) {
            std::cout << mm[i][j] << ' ';
        }
        std::cout << std::endl;
    }  

    std::cout << "size = " << mm.size() << std::endl;

    ((mm[100][100] = 314) = 0) = 217;

    for (auto el : mm) {
        size_t x, y;
        int v;
        std::tie(x, y, v) = el;
        std::cout << "[" << x << "][" << y << "] = " << v << std::endl;
    }

    return 0;
}