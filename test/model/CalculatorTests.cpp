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
	expect_results(sut, {42}, "42");
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
	expect_results(sut, {111}, "42 + 69");
	EXPECT_TRUE(sut.has_finished());
}

TEST(CalculatorTests_Rpn, Addition_four_times_in_a_row)
{
	std::vector<Symbol> input
	{
		Symbol{Value{42}},
		Symbol{Value{69}},
		Symbol{Value{17}},
		Symbol{Value{128}},
		Symbol{OperationType::ADDITION},
		Symbol{OperationType::ADDITION},
		Symbol{OperationType::ADDITION},
	};
	Calculator sut{input};

	EXPECT_FALSE(sut.has_finished());
	expect_results(sut, {145, 214, 256}, "42 + 69 + 17 + 128");
	EXPECT_TRUE(sut.has_finished());
}

TEST(CalculatorTests_Rpn, Multiplication_before_addition_when_multiplication_is_first)
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

	expect_results(sut, {6, 11}, "2 * 3 + 5");
}

TEST(CalculatorTests_Rpn, Multiplication_before_addition_when_addition_is_first)
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

	expect_results(sut, {15, 17}, "2 + 3 * 5");
}

TEST(CalculatorTests_Rpn, Addition_in_parentheses_before_multiplication)
{
	std::vector<Symbol> input
	{
		Symbol{Value{2}},
		Symbol{Value{3}},
		Symbol{OperationType::ADDITION},
		Symbol{Value{5}},
		Symbol{OperationType::MULTIPLICATION},
	};

	Calculator sut{input};

	expect_results(sut, {5, 25}, "(2 + 3) * 5");
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

	expect_results(sut, {6, 20, 26}, "2 * 3 + 4 * 5");
}

TEST(CalculatorTests_Rpn, Addition_multiplication_addition)
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
	};

	Calculator sut{input};

	expect_results(sut, {12, 17, 19}, "2 + 3 * 4 + 5");
}

TEST(CalculatorTests_Rpn, Wrong_input_with_not_enough_values_for_last_operations)
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
