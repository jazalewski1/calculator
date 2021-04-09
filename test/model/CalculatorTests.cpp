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

void expect_results(Calculator& sut, const std::initializer_list<Value>& expected_results, std::string_view input_info)
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
	std::vector<PostfixToken> input;
	Calculator sut{input};

	EXPECT_THROW(sut.calculate_next(), util::BadAccessException);
	EXPECT_TRUE(sut.has_finished());
}

TEST(CalculatorTests_Rpn, Single_value_returns_that_value)
{
	std::vector<PostfixToken> input
	{
		PostfixToken{Value{42}}
	};
	Calculator sut{input};

	EXPECT_FALSE(sut.has_finished());
	const auto expected_results = {Value{42}};
	expect_results(sut, expected_results, "42");
	EXPECT_TRUE(sut.has_finished());
}

TEST(CalculatorTests_Rpn, Addition)
{
	std::vector<PostfixToken> input
	{
		PostfixToken{Value{42}},
		PostfixToken{Value{69}},
		PostfixToken{PostfixToken::Operator::ADDITION},
	};
	Calculator sut{input};

	EXPECT_FALSE(sut.has_finished());
	const auto expected_results = {Value{111}};
	expect_results(sut, expected_results, "42 + 69");
	EXPECT_TRUE(sut.has_finished());
}

TEST(CalculatorTests_Rpn, Addition_four_times_in_a_row)
{
	std::vector<PostfixToken> input
	{
		PostfixToken{Value{42}},
		PostfixToken{Value{69}},
		PostfixToken{PostfixToken::Operator::ADDITION},
		PostfixToken{Value{17}},
		PostfixToken{PostfixToken::Operator::ADDITION},
		PostfixToken{Value{128}},
		PostfixToken{PostfixToken::Operator::ADDITION}
	};
	Calculator sut{input};

	EXPECT_FALSE(sut.has_finished());
	const auto expected_results = {Value{111}, Value{128}, Value{256}};
	expect_results(sut, expected_results, "42 + 69 + 17 + 128");
	EXPECT_TRUE(sut.has_finished());
}

TEST(CalculatorTests_Rpn, Addition_subtraction)
{
	std::vector<PostfixToken> input
	{
		PostfixToken{Value{42}},
		PostfixToken{Value{69}},
		PostfixToken{PostfixToken::Operator::ADDITION},
		PostfixToken{Value{11}},
		PostfixToken{PostfixToken::Operator::SUBTRACTION},
	};

	Calculator sut{input};

	const auto expected_results = {Value{111}, Value{100}};
	expect_results(sut, expected_results, "42 + 69 - 11");
}

TEST(CalculatorTests_Rpn, Subtraction_addition)
{
	std::vector<PostfixToken> input
	{
		PostfixToken{Value{69}},
		PostfixToken{Value{42}},
		PostfixToken{PostfixToken::Operator::SUBTRACTION},
		PostfixToken{Value{23}},
		PostfixToken{PostfixToken::Operator::ADDITION},
	};

	Calculator sut{input};

	const auto expected_results = {Value{27}, Value{50}};
	expect_results(sut, expected_results, "69 - 42 + 23");
}

TEST(CalculatorTests_Rpn, Multiplication_addition)
{
	std::vector<PostfixToken> input
	{
		PostfixToken{Value{2}},
		PostfixToken{Value{3}},
		PostfixToken{PostfixToken::Operator::MULTIPLICATION},
		PostfixToken{Value{5}},
		PostfixToken{PostfixToken::Operator::ADDITION},
	};

	Calculator sut{input};

	const auto expected_results = {Value{6}, Value{11}};
	expect_results(sut, expected_results, "2 * 3 + 5");
}

TEST(CalculatorTests_Rpn, Addition_multiplication)
{
	std::vector<PostfixToken> input
	{
		PostfixToken{Value{2}},
		PostfixToken{Value{3}},
		PostfixToken{Value{5}},
		PostfixToken{PostfixToken::Operator::MULTIPLICATION},
		PostfixToken{PostfixToken::Operator::ADDITION},
	};
	Calculator sut{input};

	const auto expected_results = {Value{15}, Value{17}};
	expect_results(sut, expected_results, "2 + 3 * 5");
}

TEST(CalculatorTests_Rpn, Multiplication_multiplication_addition)
{
	std::vector<PostfixToken> input
	{
		PostfixToken{Value{2}},
		PostfixToken{Value{3}},
		PostfixToken{PostfixToken::Operator::MULTIPLICATION},
		PostfixToken{Value{4}},
		PostfixToken{PostfixToken::Operator::MULTIPLICATION},
		PostfixToken{Value{5}},
		PostfixToken{PostfixToken::Operator::ADDITION},
	};

	Calculator sut{input};

	const auto expected_results = {Value{6}, Value{24}, Value{29}};
	expect_results(sut, expected_results, "2 * 3 * 4 + 5");
}

TEST(CalculatorTests_Rpn, Multiplication_addition_multiplication)
{
	std::vector<PostfixToken> input
	{
		PostfixToken{Value{2}},
		PostfixToken{Value{3}},
		PostfixToken{PostfixToken::Operator::MULTIPLICATION},
		PostfixToken{Value{4}},
		PostfixToken{Value{5}},
		PostfixToken{PostfixToken::Operator::MULTIPLICATION},
		PostfixToken{PostfixToken::Operator::ADDITION},
	};

	Calculator sut{input};

	const auto expected_results = {Value{6}, Value{20}, Value{26}};
	expect_results(sut, expected_results, "2 * 3 + 4 * 5");
}

TEST(CalculatorTests_Rpn, Addition_multiplication_multiplication)
{
	std::vector<PostfixToken> input
	{
		PostfixToken{Value{2}},
		PostfixToken{Value{3}},
		PostfixToken{Value{4}},
		PostfixToken{PostfixToken::Operator::MULTIPLICATION},
		PostfixToken{Value{5}},
		PostfixToken{PostfixToken::Operator::MULTIPLICATION},
		PostfixToken{PostfixToken::Operator::ADDITION},
	};

	Calculator sut{input};

	const auto expected_results = {Value{12}, Value{60}, Value{62}};
	expect_results(sut, expected_results, "2 + 3 * 4 * 5");
}

TEST(CalculatorTests_Rpn, Addition_addition_multiplication)
{
	std::vector<PostfixToken> input
	{
		PostfixToken{Value{2}},
		PostfixToken{Value{3}},
		PostfixToken{PostfixToken::Operator::ADDITION},
		PostfixToken{Value{4}},
		PostfixToken{Value{5}},
		PostfixToken{PostfixToken::Operator::MULTIPLICATION},
		PostfixToken{PostfixToken::Operator::ADDITION},
	};

	Calculator sut{input};

	const auto expected_results = {Value{5}, Value{20}, Value{25}};
	expect_results(sut, expected_results, "2 + 3 + 4 * 5");
}

TEST(CalculatorTests_Rpn, Addition_multiplication_addition)
{
	std::vector<PostfixToken> input
	{
		PostfixToken{Value{2}},
		PostfixToken{Value{3}},
		PostfixToken{Value{4}},
		PostfixToken{PostfixToken::Operator::MULTIPLICATION},
		PostfixToken{PostfixToken::Operator::ADDITION},
		PostfixToken{Value{5}},
		PostfixToken{PostfixToken::Operator::ADDITION},
	};

	Calculator sut{input};

	const auto expected_results = {Value{12}, Value{14}, Value{19}};
	expect_results(sut, expected_results, "2 + 3 * 4 + 5");
}

TEST(CalculatorTests_Rpn, Multiplication_addition_addition)
{
	std::vector<PostfixToken> input
	{
		PostfixToken{Value{2}},
		PostfixToken{Value{3}},
		PostfixToken{PostfixToken::Operator::MULTIPLICATION},
		PostfixToken{Value{4}},
		PostfixToken{PostfixToken::Operator::ADDITION},
		PostfixToken{Value{5}},
		PostfixToken{PostfixToken::Operator::ADDITION},
	};

	Calculator sut{input};

	const auto expected_results = {Value{6}, Value{10}, Value{15}};
	expect_results(sut, expected_results, "2 * 3 + 4 + 5");
}

TEST(CalculatorTests_Rpn, Wrong_input_with_not_enough_values_for_last_operation)
{
	std::vector<PostfixToken> input
	{
		PostfixToken{Value{2}},
		PostfixToken{Value{3}},
		PostfixToken{Value{4}},
		PostfixToken{PostfixToken::Operator::MULTIPLICATION},
		PostfixToken{Value{5}},
		PostfixToken{PostfixToken::Operator::ADDITION},
		PostfixToken{PostfixToken::Operator::ADDITION},
		PostfixToken{PostfixToken::Operator::MULTIPLICATION},
	};

	Calculator sut{input};

	EXPECT_NO_THROW(sut.calculate_next());
	EXPECT_NO_THROW(sut.calculate_next());
	EXPECT_NO_THROW(sut.calculate_next());
	EXPECT_THROW(sut.calculate_next(), util::InputErrorException);
}
