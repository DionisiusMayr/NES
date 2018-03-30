#include <iostream>
#include "gtest/gtest.h"

using std::cout;
using std::endl;

TEST(TestCase, TestName) {
    EXPECT_EQ(1, 1);
    EXPECT_GT(1, 0);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::FLAGS_gtest_death_test_style = "fast";
    return RUN_ALL_TESTS();
}
