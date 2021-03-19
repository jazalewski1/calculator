#include "math/Operation.hpp"
#include <gtest/gtest.h>

TEST(OperationTests, Addition)
{
	math::Value value1{69};
	math::Value value2{42};

	math::Addition sut{};

	constexpr auto expected = 111;
	const auto result = sut.execute(value1, value2);

	EXPECT_EQ(expected, result);
}

TEST(OperationTests, Multiplication)
{
	math::Value value1{69};
	math::Value value2{42};

	math::Multiplication sut{};

	constexpr auto expected = 2898;
	const auto result = sut.execute(value1, value2);

	EXPECT_EQ(expected, result);
}

TEST(OperationTests, Multiplication_by_zero)
{
	math::Value value1{69};
	math::Value value2{0};

	math::Multiplication sut{};

	constexpr auto expected = 0;
	const auto result = sut.execute(value1, value2);

	EXPECT_EQ(expected, result);
}