#include "model/Calculator.hpp"
#include <gtest/gtest.h>
#include <optional>

using namespace model;

TEST(CalculatorTests, Calculate_next_with_1_operation)
{
	// 6 * 7
	const OperationData input{OperationType::MULTIPLICATION, 6, 7};
	Calculator sut{};
	
	sut.calculate(input);
	const auto expected = 42;
	const auto result = sut.get_running_total();
	EXPECT_EQ(expected, result);
}

TEST(CalculatorTests, Calculate_next_with_2_operations)
{
	// 4 * (2 + 3)
	const OperationData input1{OperationType::ADDITION, 2, 3};
	const OperationData input2{OperationType::MULTIPLICATION, PreviousResult{}, 4};
	Calculator sut{};

	sut.calculate(input1); // 2 + 3 = 5
	const auto expected1 = 5;
	const auto result1 = sut.get_running_total();
	EXPECT_EQ(expected1, result1);

	sut.calculate(input2); // 5 * 4 = 20
	const auto expected2 = 20;
	const auto result2 = sut.get_running_total();
	EXPECT_EQ(expected2, result2);
}

TEST(CalculatorTests, Calculate_next_with_3_operations)
{
	// 2 * (5 * 3 + 4)
	const OperationData input1{OperationType::MULTIPLICATION, 5, 3};
	const OperationData input2{OperationType::ADDITION, PreviousResult{}, 4};
	const OperationData input3{OperationType::MULTIPLICATION, 2, PreviousResult{}};
	Calculator sut{};

	sut.calculate(input1); // 5 * 3 = 15
	const auto result1 = sut.get_running_total();
	const auto expected1 = 15;
	EXPECT_EQ(expected1, result1);

	sut.calculate(input2); // 15 + 4 = 19
	const auto result2 = sut.get_running_total();
	const auto expected2 = 19;
	EXPECT_EQ(expected2, result2);

	sut.calculate(input3); // 19 * 2 = 38
	const auto result3 = sut.get_running_total();
	const auto expected3 = 38;
	EXPECT_EQ(expected3, result3);
}