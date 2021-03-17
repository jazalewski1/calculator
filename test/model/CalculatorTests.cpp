#include "model/Calculator.hpp"
#include <gtest/gtest.h>
#include <optional>

TEST(CalculatorTests, Calculate_next_with_1_operation)
{
	using namespace model;
	const OperationDataVector input
	{
		{OperationType::MULTIPLICATION, 6, 7}
	};

	Calculator sut{input};
	const auto result = sut.calculate_next();
	const auto expected = 42;
	EXPECT_EQ(result, expected);
}

TEST(CalculatorTests, Calculate_next_with_2_operations)
{
	using namespace model;
	const OperationDataVector input // 2 + 3 * 4 = 20
	{
		{OperationType::ADDITION, 2, 3},
		{OperationType::MULTIPLICATION, PreviousResult{}, 4},
	};

	Calculator sut{input};
	const auto result1 = sut.calculate_next(); // 2 + 3 = 5
	const auto expected1 = 5;
	EXPECT_EQ(result1, expected1);

	const auto result2 = sut.calculate_next(); // 5 * 4 = 20
	const auto expected2 = 20;
	EXPECT_EQ(result2, expected2);

	const auto total = sut.get_running_total();
	EXPECT_EQ(total, expected2);
}

TEST(CalculatorTests, Calculate_next_with_3_operations)
{
	using namespace model;
	const OperationDataVector input // 2 * (5 * 3 + 4) = 38
	{
		{OperationType::MULTIPLICATION, 5, 3},
		{OperationType::ADDITION, PreviousResult{}, 4},
		{OperationType::MULTIPLICATION, 2, PreviousResult{}},
	};

	Calculator sut{input};
	const auto result1 = sut.calculate_next(); // 5 * 3 = 15
	const auto expected1 = 15;
	EXPECT_EQ(result1, expected1);

	const auto result2 = sut.calculate_next(); // 15 + 4 = 19
	const auto expected2 = 19;
	EXPECT_EQ(result2, expected2);

	const auto result3 = sut.calculate_next(); // 19 * 2 = 38
	const auto expected3 = 38;
	EXPECT_EQ(result3, expected3);

	const auto total = sut.get_running_total();
	EXPECT_EQ(total, expected3);
}