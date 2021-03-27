#include "math/Value.hpp"
#include "model/Calculator.hpp"
#include "util/Exception.hpp"
#include <gtest/gtest.h>
#include <initializer_list>
#include <string_view>
#include <vector>
#include <iostream>

using namespace model;

namespace
{
using Value = math::Value;

void expect_results(Calculator& sut, std::initializer_list<Value> expected_results, std::string_view input_info)
{
	for (const auto& expected : expected_results)
	{
		const auto result = sut.calculate_next();
		EXPECT_EQ(result, expected) << "Input equation: " << input_info;
	}
}
} // namespace

TEST(CalculatorTests_Rpn, Empty_input_throws)
{
	std::vector<Symbol> input;
	Calculator sut{input};

	EXPECT_THROW(sut.calculate_next(), util::BadAccessException);
	EXPECT_TRUE(sut.has_finished());
}

TEST(CalculatorTests_Rpn, Single_value_returns_that_value)
{
	std::vector<Symbol> input
	{
		Symbol{Value{42}}
	};
	Calculator sut{input};

	EXPECT_FALSE(sut.has_finished());
	const auto expected_results = {42};
	expect_results(sut, expected_results, "42");
	EXPECT_TRUE(sut.has_finished());
}

TEST(CalculatorTests_Rpn, Addition)
{
	std::vector<Symbol> input
	{
		Symbol{Value{42}},
		Symbol{Value{69}},
		Symbol{OperationType::ADDITION},
	};
	Calculator sut{input};

	EXPECT_FALSE(sut.has_finished());
	const auto expected_results = {111};
	expect_results(sut, expected_results, "42 + 69");
	EXPECT_TRUE(sut.has_finished());
}

TEST(CalculatorTests_Rpn, Addition_four_times_in_a_row)
{
	std::vector<Symbol> input
	{
		Symbol{Value{42}},
		Symbol{Value{69}},
		Symbol{OperationType::ADDITION},
		Symbol{Value{17}},
		Symbol{OperationType::ADDITION},
		Symbol{Value{128}},
		Symbol{OperationType::ADDITION}
	};
	Calculator sut{input};

	EXPECT_FALSE(sut.has_finished());
	const auto expected_results = {111, 128, 256};
	expect_results(sut, expected_results, "42 + 69 + 17 + 128");
	EXPECT_TRUE(sut.has_finished());
}

TEST(CalculatorTests_Rpn, Multiplication_addition)
{
	std::vector<Symbol> input
	{
		Symbol{Value{2}},
		Symbol{Value{3}},
		Symbol{OperationType::MULTIPLICATION},
		Symbol{Value{5}},
		Symbol{OperationType::ADDITION},
	};

	Calculator sut{input};

	const auto expected_results = {6, 11};
	expect_results(sut, expected_results, "2 * 3 + 5");
}

TEST(CalculatorTests_Rpn, Addition_multiplication)
{
	std::vector<Symbol> input
	{
		Symbol{Value{2}},
		Symbol{Value{3}},
		Symbol{Value{5}},
		Symbol{OperationType::MULTIPLICATION},
		Symbol{OperationType::ADDITION},
	};
	Calculator sut{input};

	const auto expected_results = {15, 17};
	expect_results(sut, expected_results, "2 + 3 * 5");
}

TEST(CalculatorTests_Rpn, Multiplication_multiplication_addition)
{
	std::vector<Symbol> input
	{
		Symbol{Value{2}},
		Symbol{Value{3}},
		Symbol{OperationType::MULTIPLICATION},
		Symbol{Value{4}},
		Symbol{OperationType::MULTIPLICATION},
		Symbol{Value{5}},
		Symbol{OperationType::ADDITION},
	};

	Calculator sut{input};

	const auto expected_results = {6, 24, 29};
	expect_results(sut, expected_results, "2 * 3 * 4 + 5");
}

TEST(CalculatorTests_Rpn, Multiplication_addition_multiplication)
{
	std::vector<Symbol> input
	{
		Symbol{Value{2}},
		Symbol{Value{3}},
		Symbol{OperationType::MULTIPLICATION},
		Symbol{Value{4}},
		Symbol{Value{5}},
		Symbol{OperationType::MULTIPLICATION},
		Symbol{OperationType::ADDITION},
	};

	Calculator sut{input};

	const auto expected_results = {6, 20, 26};
	expect_results(sut, expected_results, "2 * 3 + 4 * 5");
}

TEST(CalculatorTests_Rpn, Addition_multiplication_multiplication)
{
	std::vector<Symbol> input
	{
		Symbol{Value{2}},
		Symbol{Value{3}},
		Symbol{Value{4}},
		Symbol{OperationType::MULTIPLICATION},
		Symbol{Value{5}},
		Symbol{OperationType::MULTIPLICATION},
		Symbol{OperationType::ADDITION},
	};

	Calculator sut{input};

	const auto expected_results = {12, 60, 62};
	expect_results(sut, expected_results, "2 + 3 * 4 * 5");
}

TEST(CalculatorTests_Rpn, Addition_addition_multiplication)
{
	std::vector<Symbol> input
	{
		Symbol{Value{2}},
		Symbol{Value{3}},
		Symbol{OperationType::ADDITION},
		Symbol{Value{4}},
		Symbol{Value{5}},
		Symbol{OperationType::MULTIPLICATION},
		Symbol{OperationType::ADDITION},
	};

	Calculator sut{input};

	const auto expected_results = {5, 20, 25};
	expect_results(sut, expected_results, "2 + 3 + 4 * 5");
}

TEST(CalculatorTests_Rpn, Addition_multiplication_addition)
{
	std::vector<Symbol> input
	{
		Symbol{Value{2}},
		Symbol{Value{3}},
		Symbol{Value{4}},
		Symbol{OperationType::MULTIPLICATION},
		Symbol{OperationType::ADDITION},
		Symbol{Value{5}},
		Symbol{OperationType::ADDITION},
	};

	Calculator sut{input};

	const auto expected_results = {12, 14, 19};
	expect_results(sut, expected_results, "2 + 3 * 4 + 5");
}

TEST(CalculatorTests_Rpn, Multiplication_addition_addition)
{
	std::vector<Symbol> input
	{
		Symbol{Value{2}},
		Symbol{Value{3}},
		Symbol{OperationType::MULTIPLICATION},
		Symbol{Value{4}},
		Symbol{OperationType::ADDITION},
		Symbol{Value{5}},
		Symbol{OperationType::ADDITION},
	};

	Calculator sut{input};

	const auto expected_results = {6, 10, 15};
	expect_results(sut, expected_results, "2 * 3 + 4 + 5");
}

TEST(CalculatorTests_Rpn, Wrong_input_with_not_enough_values_for_last_operation)
{
	std::vector<Symbol> input
	{
		Symbol{Value{2}},
		Symbol{Value{3}},
		Symbol{Value{4}},
		Symbol{OperationType::MULTIPLICATION},
		Symbol{Value{5}},
		Symbol{OperationType::ADDITION},
		Symbol{OperationType::ADDITION},
		Symbol{OperationType::MULTIPLICATION},
	};

	Calculator sut{input};

	EXPECT_NO_THROW(sut.calculate_next());
	EXPECT_NO_THROW(sut.calculate_next());
	EXPECT_NO_THROW(sut.calculate_next());
	EXPECT_THROW(sut.calculate_next(), util::InputErrorException);
}
