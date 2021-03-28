#include "math/Operation.hpp"
#include <gtest/gtest.h>

TEST(OperationTests, Addition)
{
	constexpr math::Value value1{69};
	constexpr math::Value value2{42};

	constexpr auto expected = 111;
	const auto result = math::addition(value1, value2);

	EXPECT_EQ(expected, result);
}

TEST(OperationTests, Subtraction)
{
	constexpr math::Value value1{69};
	constexpr math::Value value2{42};

	constexpr auto expected = 27;
	const auto result = math::subtraction(value1, value2);

	EXPECT_EQ(expected, result);
}


TEST(OperationTests, Multiplication)
{
	constexpr math::Value value1{69};
	constexpr math::Value value2{42};

	constexpr auto expected = 2898;
	const auto result = math::multiplication(value1, value2);;

	EXPECT_EQ(expected, result);
}

TEST(OperationTests, Multiplication_by_zero)
{
	constexpr math::Value value1{69};
	constexpr math::Value value2{0};

	constexpr auto expected = 0;
	const auto result = math::multiplication(value1, value2);

	EXPECT_EQ(expected, result);
}