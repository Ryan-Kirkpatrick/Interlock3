#pragma once
#include <gtest/gtest.h>

#define SUITE_NAME Example

TEST(SUITE_NAME, TestName) {
    EXPECT_EQ(1, 2);
}
