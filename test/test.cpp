#include "matrix.h"
#include "gtest/gtest.h"


TEST(Matrix, empty) 
{
    Matrix<int, 2, 0> mm;
    int res = mm[2][2];
    ASSERT_EQ(res, 0);
    ASSERT_EQ(mm.size(), 0);
}

TEST(Matrix, notEmpty) 
{
    Matrix<int, 2, 0> mm;
    mm[1][2] = 2;
    int res = mm[1][2];
    ASSERT_EQ(res, 2);
}

TEST(Matrix, size) 
{
    Matrix<int, 2, 0> mm;
    mm[1][2] = 2;
    mm[3][2] = 2;
    ASSERT_EQ(mm.size(), 2);
}