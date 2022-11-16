#include <gtest/gtest.h>
#include "vobo.h"

TEST(Test, TestingOne) {
	ASSERT_TRUE(true);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}