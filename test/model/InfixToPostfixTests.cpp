#include "math/Value.hpp"
#include "model/InfixToken.hpp"
#include "model/PostfixToken.hpp"
#include "model/InfixToPostfix.hpp"
#include "PostfixTokenOperators.hpp"
#include "util/Exception.hpp"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace model;
using testing::ElementsAre;

using Value = math::Value;

TEST(InfixToPostfixTests, Empty_input)
{
	const InfixTokens input {};
	
	InfixToPostfixConverter sut{};
	const auto result = sut.convert(input);

	EXPECT_TRUE(result.empty());
}

TEST(InfixToPostfixTests, Input_has_1_value_token)
{
	const InfixTokens input {InfixToken{Value{5}}};
	
	InfixToPostfixConverter sut{};
	const auto result = sut.convert(input);

	EXPECT_THAT(result, ElementsAre(PostfixToken{Value{5}}));
}

TEST(InfixToPostfixTests, Input_has_3_value_tokens)
{
	const InfixTokens input {
		InfixToken{Value{5}},
		InfixToken{Value{42}},
		InfixToken{Value{128}},
	};
	
	InfixToPostfixConverter sut{};
	const auto result = sut.convert(input);

	EXPECT_THAT(result, ElementsAre(PostfixToken{Value{5}}, PostfixToken{Value{42}}, PostfixToken{Value{128}}));
}

TEST(InfixToPostfixTests, Value_addition_value)
{
	const InfixTokens input {
		InfixToken{Value{42}},
		InfixToken{InfixToken::Operator::ADDITION},
		InfixToken{Value{69}},
	};
	
	InfixToPostfixConverter sut{};
	const auto result = sut.convert(input);

	EXPECT_THAT(
		result, 
		ElementsAre(
			PostfixToken{Value{42}},
			PostfixToken{Value{69}},
			PostfixToken{PostfixToken::Operator::ADDITION}
		)
	);
}

TEST(InfixToPostfixTests, Addition_four_times_in_a_row)
{
	const InfixTokens input {
		InfixToken{Value{42}},
		InfixToken{InfixToken::Operator::ADDITION},
		InfixToken{Value{69}},
		InfixToken{InfixToken::Operator::ADDITION},
		InfixToken{Value{17}},
		InfixToken{InfixToken::Operator::ADDITION},
		InfixToken{Value{128}},
	};
	
	InfixToPostfixConverter sut{};
	const auto result = sut.convert(input);

	EXPECT_THAT(
		result,
		ElementsAre(
			PostfixToken{Value{42}},
			PostfixToken{Value{69}},
			PostfixToken{PostfixToken::Operator::ADDITION},
			PostfixToken{Value{17}},
			PostfixToken{PostfixToken::Operator::ADDITION},
			PostfixToken{Value{128}},
			PostfixToken{PostfixToken::Operator::ADDITION}
		)
	);
}

TEST(InfixToPostfixTests, Multiplication_addition)
{
	const InfixTokens input {
		InfixToken{Value{2}},
		InfixToken{InfixToken::Operator::MULTIPLICATION},
		InfixToken{Value{3}},
		InfixToken{InfixToken::Operator::ADDITION},
		InfixToken{Value{5}},
	};
	
	InfixToPostfixConverter sut{};
	const auto result = sut.convert(input);

	EXPECT_THAT(
		result,
		ElementsAre(
			PostfixToken{Value{2}},
			PostfixToken{Value{3}},
			PostfixToken{PostfixToken::Operator::MULTIPLICATION},
			PostfixToken{Value{5}},
			PostfixToken{PostfixToken::Operator::ADDITION}
		)
	);
}

TEST(InfixToPostfixTests, Addition_multiplication)
{
	const InfixTokens input {
		InfixToken{Value{2}},
		InfixToken{InfixToken::Operator::ADDITION},
		InfixToken{Value{3}},
		InfixToken{InfixToken::Operator::MULTIPLICATION},
		InfixToken{Value{5}},
	};
	
	InfixToPostfixConverter sut{};
	const auto result = sut.convert(input);

	EXPECT_THAT(
		result,
		ElementsAre(
			PostfixToken{Value{2}},
			PostfixToken{Value{3}},
			PostfixToken{Value{5}},
			PostfixToken{PostfixToken::Operator::MULTIPLICATION},
			PostfixToken{PostfixToken::Operator::ADDITION}
		)
	);
}

TEST(InfixToPostfixTests, Multiplication_addition_multiplication)
{
	const InfixTokens input {
		InfixToken{Value{2}},
		InfixToken{InfixToken::Operator::MULTIPLICATION},
		InfixToken{Value{3}},
		InfixToken{InfixToken::Operator::ADDITION},
		InfixToken{Value{4}},
		InfixToken{InfixToken::Operator::MULTIPLICATION},
		InfixToken{Value{5}}
	};
	
	InfixToPostfixConverter sut{};
	const auto result = sut.convert(input);

	EXPECT_THAT(
		result,
		ElementsAre(
			PostfixToken{Value{2}},
			PostfixToken{Value{3}},
			PostfixToken{PostfixToken::Operator::MULTIPLICATION},
			PostfixToken{Value{4}},
			PostfixToken{Value{5}},
			PostfixToken{PostfixToken::Operator::MULTIPLICATION},
			PostfixToken{PostfixToken::Operator::ADDITION}
		)
	);
}

TEST(InfixToPostfixTests, Addition_multiplication_addition)
{
	const InfixTokens input {
		InfixToken{Value{2}},
		InfixToken{InfixToken::Operator::ADDITION},
		InfixToken{Value{3}},
		InfixToken{InfixToken::Operator::MULTIPLICATION},
		InfixToken{Value{4}},
		InfixToken{InfixToken::Operator::ADDITION},
		InfixToken{Value{5}}
	};
	
	InfixToPostfixConverter sut{};
	const auto result = sut.convert(input);

	EXPECT_THAT(
		result,
		ElementsAre(
			PostfixToken{Value{2}},
			PostfixToken{Value{3}},
			PostfixToken{Value{4}},
			PostfixToken{PostfixToken::Operator::MULTIPLICATION},
			PostfixToken{PostfixToken::Operator::ADDITION},
			PostfixToken{Value{5}},
			PostfixToken{PostfixToken::Operator::ADDITION}
		)
	);
}

TEST(InfixToPostfixTests, Addition_subtraction)
{
	const InfixTokens input {
		InfixToken{Value{2}},
		InfixToken{InfixToken::Operator::ADDITION},
		InfixToken{Value{3}},
		InfixToken{InfixToken::Operator::SUBTRACTION},
		InfixToken{Value{4}},
	};
	
	InfixToPostfixConverter sut{};
	const auto result = sut.convert(input);

	EXPECT_THAT(
		result,
		ElementsAre(
			PostfixToken{Value{2}},
			PostfixToken{Value{3}},
			PostfixToken{PostfixToken::Operator::ADDITION},
			PostfixToken{Value{4}},
			PostfixToken{PostfixToken::Operator::SUBTRACTION}
		)
	);
}

TEST(InfixToPostfixTests, Subtraction_addition)
{
	const InfixTokens input {
		InfixToken{Value{2}},
		InfixToken{InfixToken::Operator::SUBTRACTION},
		InfixToken{Value{3}},
		InfixToken{InfixToken::Operator::ADDITION},
		InfixToken{Value{4}},
	};
	
	InfixToPostfixConverter sut{};
	const auto result = sut.convert(input);

	EXPECT_THAT(
		result,
		ElementsAre(
			PostfixToken{Value{2}},
			PostfixToken{Value{3}},
			PostfixToken{PostfixToken::Operator::SUBTRACTION},
			PostfixToken{Value{4}},
			PostfixToken{PostfixToken::Operator::ADDITION}
		)
	);
}

TEST(InfixToPostfixTests, Addition_multiplication_subtraction)
{
	const InfixTokens input {
		InfixToken{Value{2}},
		InfixToken{InfixToken::Operator::ADDITION},
		InfixToken{Value{3}},
		InfixToken{InfixToken::Operator::MULTIPLICATION},
		InfixToken{Value{4}},
		InfixToken{InfixToken::Operator::SUBTRACTION},
		InfixToken{Value{5}},
	};
	
	InfixToPostfixConverter sut{};
	const auto result = sut.convert(input);

	EXPECT_THAT(
		result,
		ElementsAre(
			PostfixToken{Value{2}},
			PostfixToken{Value{3}},
			PostfixToken{Value{4}},
			PostfixToken{PostfixToken::Operator::MULTIPLICATION},
			PostfixToken{PostfixToken::Operator::ADDITION},
			PostfixToken{Value{5}},
			PostfixToken{PostfixToken::Operator::SUBTRACTION}
		)
	);
}

TEST(InfixToPostfix_ParenthesesTests, Empty_parentheses)
{
	const InfixTokens input {
		InfixToken{InfixToken::OpenPar{}},
		InfixToken{InfixToken::ClosePar{}},
	};
	
	InfixToPostfixConverter sut{};
	const auto result = sut.convert(input);
	EXPECT_TRUE(result.empty());
}

TEST(InfixToPostfix_ParenthesesTests, Value_in_parentheses)
{
	const InfixTokens input {
		InfixToken{InfixToken::OpenPar{}},
		InfixToken{Value{2}},
		InfixToken{InfixToken::ClosePar{}},
	};
	
	InfixToPostfixConverter sut{};
	const auto result = sut.convert(input);

	EXPECT_THAT(
		result,
		ElementsAre(PostfixToken{Value{2}})
	);
}

TEST(InfixToPostfix_ParenthesesTests, Addition_in_parentheses)
{
	const InfixTokens input {
		InfixToken{InfixToken::OpenPar{}},
		InfixToken{Value{2}},
		InfixToken{InfixToken::Operator::ADDITION},
		InfixToken{Value{3}},
		InfixToken{InfixToken::ClosePar{}},
	};
	
	InfixToPostfixConverter sut{};
	const auto result = sut.convert(input);

	EXPECT_THAT(
		result,
		ElementsAre(
			PostfixToken{Value{2}},
			PostfixToken{Value{3}},
			PostfixToken{PostfixToken::Operator::ADDITION}
		)
	);
}

TEST(InfixToPostfix_ParenthesesTests, When_addition_in_par_next_multiplication_then_addition_executes_first)
{
	const InfixTokens input {
		InfixToken{InfixToken::OpenPar{}},
		InfixToken{Value{2}},
		InfixToken{InfixToken::Operator::ADDITION},
		InfixToken{Value{3}},
		InfixToken{InfixToken::ClosePar{}},
		InfixToken{InfixToken::Operator::MULTIPLICATION},
		InfixToken{Value{5}},
	};
	
	InfixToPostfixConverter sut{};
	const auto result = sut.convert(input);

	EXPECT_THAT(
		result,
		ElementsAre(
			PostfixToken{Value{2}},
			PostfixToken{Value{3}},
			PostfixToken{PostfixToken::Operator::ADDITION},
			PostfixToken{Value{5}},
			PostfixToken{PostfixToken::Operator::MULTIPLICATION}
		)
	);
}

TEST(InfixToPostfix_ParenthesesTests, When_addition_next_multiplication_in_par_then_multiplication_executes_first)
{
	const InfixTokens input {
		InfixToken{Value{2}},
		InfixToken{InfixToken::Operator::ADDITION},
		InfixToken{InfixToken::OpenPar{}},
		InfixToken{Value{3}},
		InfixToken{InfixToken::Operator::MULTIPLICATION},
		InfixToken{Value{5}},
		InfixToken{InfixToken::ClosePar{}},
	};
	
	InfixToPostfixConverter sut{};
	const auto result = sut.convert(input);

	EXPECT_THAT(
		result,
		ElementsAre(
			PostfixToken{Value{2}},
			PostfixToken{Value{3}},
			PostfixToken{Value{5}},
			PostfixToken{PostfixToken::Operator::MULTIPLICATION},
			PostfixToken{PostfixToken::Operator::ADDITION}
		)
	);
}

TEST(InfixToPostfix_ParenthesesTests, When_multiplication_in_par_next_addition_then_multiplication_executes_first)
{
	const InfixTokens input {
		InfixToken{InfixToken::OpenPar{}},
		InfixToken{Value{2}},
		InfixToken{InfixToken::Operator::MULTIPLICATION},
		InfixToken{Value{3}},
		InfixToken{InfixToken::ClosePar{}},
		InfixToken{InfixToken::Operator::ADDITION},
		InfixToken{Value{5}},
	};
	
	InfixToPostfixConverter sut{};
	const auto result = sut.convert(input);

	EXPECT_THAT(
		result,
		ElementsAre(
			PostfixToken{Value{2}},
			PostfixToken{Value{3}},
			PostfixToken{PostfixToken::Operator::MULTIPLICATION},
			PostfixToken{Value{5}},
			PostfixToken{PostfixToken::Operator::ADDITION}
		)
	);
}

TEST(InfixToPostfix_ParenthesesTests, When_multiplication_next_addition_in_par_then_addition_executes_first)
{
	const InfixTokens input {
		InfixToken{Value{2}},
		InfixToken{InfixToken::Operator::MULTIPLICATION},
		InfixToken{InfixToken::OpenPar{}},
		InfixToken{Value{3}},
		InfixToken{InfixToken::Operator::ADDITION},
		InfixToken{Value{5}},
		InfixToken{InfixToken::ClosePar{}},
	};
	
	InfixToPostfixConverter sut{};
	const auto result = sut.convert(input);

	EXPECT_THAT(
		result,
		ElementsAre(
			PostfixToken{Value{2}},
			PostfixToken{Value{3}},
			PostfixToken{Value{5}},
			PostfixToken{PostfixToken::Operator::ADDITION},
			PostfixToken{PostfixToken::Operator::MULTIPLICATION}
		)
	);
}

TEST(InfixToPostfix_ParenthesesTests, Throws_when_unmatched_left_par)
{
	const InfixTokens input {
		InfixToken{Value{2}},
		InfixToken{InfixToken::Operator::ADDITION},
		InfixToken{InfixToken::OpenPar{}},
		InfixToken{Value{3}},
		InfixToken{InfixToken::Operator::MULTIPLICATION},
		InfixToken{Value{4}},
	};
	
	InfixToPostfixConverter sut{};
	EXPECT_THROW(sut.convert(input), util::UnmatchedBracesException);
}

TEST(InfixToPostfix_ParenthesesTests, Throws_when_one_par_pair_and_unmatched_left_par)
{
	const InfixTokens input {
		InfixToken{InfixToken::OpenPar{}},
		InfixToken{InfixToken::OpenPar{}},
		InfixToken{Value{2}},
		InfixToken{InfixToken::Operator::ADDITION},
		InfixToken{Value{3}},
		InfixToken{InfixToken::ClosePar{}},
		InfixToken{InfixToken::Operator::MULTIPLICATION},
		InfixToken{Value{4}},
	};
	
	InfixToPostfixConverter sut{};
	EXPECT_THROW(sut.convert(input), util::UnmatchedBracesException);
}

TEST(InfixToPostfix_ParenthesesTests, Throws_when_unmatched_right_par)
{
	const InfixTokens input {
		InfixToken{Value{2}},
		InfixToken{InfixToken::Operator::ADDITION},
		InfixToken{Value{3}},
		InfixToken{InfixToken::ClosePar{}},
		InfixToken{InfixToken::Operator::MULTIPLICATION},
		InfixToken{Value{4}},
	};
	
	InfixToPostfixConverter sut{};
	EXPECT_THROW(sut.convert(input), util::UnmatchedBracesException);
}

TEST(InfixToPostfix_ParenthesesTests, Throws_when_one_par_pair_and_unmatched_right_par)
{
	const InfixTokens input {
		InfixToken{InfixToken::OpenPar{}},
		InfixToken{Value{2}},
		InfixToken{InfixToken::Operator::ADDITION},
		InfixToken{Value{3}},
		InfixToken{InfixToken::ClosePar{}},
		InfixToken{InfixToken::Operator::MULTIPLICATION},
		InfixToken{Value{4}},
		InfixToken{InfixToken::ClosePar{}},
	};
	
	InfixToPostfixConverter sut{};
	EXPECT_THROW(sut.convert(input), util::UnmatchedBracesException);
}

TEST(InfixToPostfix_ParenthesesTests, Throws_when_parentheses_have_swapped_order)
{
	const InfixTokens input {
		InfixToken{Value{2}},
		InfixToken{InfixToken::Operator::SUBTRACTION},
		InfixToken{InfixToken::ClosePar{}},
		InfixToken{Value{3}},
		InfixToken{InfixToken::Operator::ADDITION},
		InfixToken{Value{4}},
		InfixToken{InfixToken::OpenPar{}},
		InfixToken{InfixToken::Operator::MULTIPLICATION},
		InfixToken{Value{5}},
	};
	
	InfixToPostfixConverter sut{};
	EXPECT_THROW(sut.convert(input), util::UnmatchedBracesException);
}
