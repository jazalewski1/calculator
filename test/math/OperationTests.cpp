#include "math/Operation.hpp"
#include <gtest/gtest.h>

TEST(OperationTests, Addition)
{
	math::ValuePtr value1{new int{69}};
	math::ValuePtr value2{new int{42}};

	math::Addition sut{value1, value2};

	constexpr auto expected = 111;
	const auto result = sut.execute();

	EXPECT_EQ(expected, result);
}

TEST(OperationTests, Multiplication)
{
	math::ValuePtr value1{new int{69}};
	math::ValuePtr value2{new int{42}};

	math::Multiplication sut{value1, value2};

	constexpr auto expected = 2898;
	const auto result = sut.execute();

	EXPECT_EQ(expected, result);
}

TEST(OperationTests, Multiplication_by_zero)
{
	math::ValuePtr value1{new int{69}};
	math::ValuePtr value2{new int{0}};

	math::Multiplication sut{value1, value2};

	constexpr auto expected = 0;
	const auto result = sut.execute();

	EXPECT_EQ(expected, result);
}

TEST(MultipleOperationTests, Next_operation_uses_running_total)
{
	math::ValuePtr value1{new int{2}};
	math::ValuePtr value2{new int{3}};
	math::ValuePtr value3{new int{4}};
	math::ValuePtr value4{new int{12}};
	math::ValuePtr running_total{new int{0}};

	math::Addition operation1{value1, value2};
	math::Multiplication operation2{running_total, value3};
	math::Addition operation3{value4, running_total};

	*running_total = operation1.execute(); // 2 + 3 = 5
	*running_total = operation2.execute(); // 5 * 4 = 20
	*running_total = operation3.execute(); // 20 + 12 = 32

	constexpr auto expected = 32;

	EXPECT_EQ(expected, *running_total);
}