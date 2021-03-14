#include "math/Operation.hpp"
#include <gtest/gtest.h>

TEST(OperationTests, Addition)
{
	EXPECT_EQ(math::addition(69, 42), 111);
}

TEST(OperationTests, Multiplication)
{
	EXPECT_EQ(math::multiplication(69, 42), 2898);
}

TEST(OperationTests, Multiplication_by_zero)
{
	EXPECT_EQ(math::multiplication(69, 0), 0);
}