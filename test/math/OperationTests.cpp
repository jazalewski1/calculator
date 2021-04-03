#include "math/Operation.hpp"
#include <gtest/gtest.h>

TEST(OperationTests, Addition_integer_and_integer_returns_integer)
{
	constexpr int value1{69};
	constexpr int value2{42};

	const math::Value expected{111};
	const auto result = math::addition(value1, value2);

	ASSERT_TRUE(math::is_integer(result));
	EXPECT_EQ(math::get_integer(expected), math::get_integer(result));
}

TEST(OperationTests, Addition_integer_and_double_returns_double)
{
	constexpr int value1{69};
	constexpr double value2{42.11};

	const math::Value expected{111.11};
	const auto result = math::addition(value1, value2);

	ASSERT_TRUE(math::is_double(result));
	EXPECT_DOUBLE_EQ(math::get_double(expected), math::get_double(result));
}

TEST(OperationTests, Subtraction_integer_and_integer_returns_integer)
{
	constexpr int value1{69};
	constexpr int value2{42};

	const math::Value expected{27};
	const auto result = math::subtraction(value1, value2);

	ASSERT_TRUE(math::is_integer(result));
	EXPECT_EQ(math::get_integer(expected), math::get_integer(result));
}

TEST(OperationTests, Subtraction_integer_and_double_returns_double)
{
	constexpr int value1{69};
	constexpr double value2{42.42}; 

	const math::Value expected{26.58};
	const auto result = math::subtraction(value1, value2);

	ASSERT_TRUE(math::is_double(result));
	EXPECT_EQ(math::get_double(expected), math::get_double(result));
}

TEST(OperationTests, Multiplication_integer_and_integer_returns_integer)
{
	constexpr int value1{69};
	constexpr int value2{42};

	const math::Value expected{2898};
	const auto result = math::multiplication(value1, value2);

	ASSERT_TRUE(math::is_integer(result));
	EXPECT_EQ(math::get_integer(expected), math::get_integer(result));
}

TEST(OperationTests, Multiplication_integer_and_double_returns_double)
{
	constexpr int value1{69};
	constexpr double value2{0.5};

	const math::Value expected{34.5};
	const auto result = math::multiplication(value1, value2);

	ASSERT_TRUE(math::is_double(result));
	EXPECT_DOUBLE_EQ(math::get_double(expected), math::get_double(result));
}

TEST(OperationTests, Multiplication_by_zero)
{
	constexpr auto value1{69};
	constexpr auto value2{0};

	const math::Value expected{0};
	const auto result = math::multiplication(value1, value2);

	EXPECT_EQ(expected, result);
}

TEST(OperationTests, Division_integer_and_integer_returns_double)
{
	constexpr int value1{20};
	constexpr int value2{4};

	const math::Value expected{5.0};
	const auto result = math::division(value1, value2);

	ASSERT_TRUE(math::is_double(result));
	EXPECT_DOUBLE_EQ(math::get_double(expected), math::get_double(result));
}

TEST(OperationTests, Division_integer_and_double_returns_double)
{
	constexpr int value1{15};
	constexpr double value2{2.5};

	const math::Value expected{6.0};
	const auto result = math::division(value1, value2);

	ASSERT_TRUE(math::is_double(result));
	EXPECT_DOUBLE_EQ(math::get_double(expected), math::get_double(result));
}