#include "math/Value.hpp"
#include "model/InfixSymbol.hpp"
#include "model/PostfixSymbol.hpp"
#include "model/InfixToPostfix.hpp"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

namespace model
{
inline bool operator==(const PostfixSymbol& lhs, const PostfixSymbol& rhs)
{
	if (is_value(lhs) and is_value(rhs))
	{
		return get_value(lhs) == get_value(rhs);
	}
	else if (is_operator(lhs) and is_operator(rhs))
	{
		return get_operator(lhs) == get_operator(rhs);
	}
	return false;
}

std::ostream& operator<<(std::ostream& stream, const PostfixSymbol::Operator& symbol)
{
	switch (symbol)
	{
		case PostfixSymbol::Operator::SUBTRACTION: return stream << "subtraction";
		case PostfixSymbol::Operator::ADDITION: return stream << "addition";
		case PostfixSymbol::Operator::DIVISION: return stream << "division";
		case PostfixSymbol::Operator::MULTIPLICATION: return stream << "multiplication";
	}
	return stream << "unknown";
}

std::ostream& operator<<(std::ostream& stream, const PostfixSymbol& symbol)
{
	if (is_value(symbol))
	{
		const auto value = get_value(symbol);
		return stream << "PostfixSymbol:" << (math::is_integer(value) ? math::get_integer(value) : math::get_double(value));
	}
	return stream << "PostfixSymbol:" << get_operator(symbol);
}
} // namespace model

using namespace model;
using testing::ElementsAre;

using Value = math::Value;

TEST(InfixToPostfixTests, Empty_input)
{
	const InfixSymbols input {};
	
	const auto result = infix_to_postfix(input);

	EXPECT_TRUE(result.empty());
}

TEST(InfixToPostfixTests, Input_has_1_value_symbol)
{
	const InfixSymbols input {InfixSymbol{Value{5}}};
	
	const auto result = infix_to_postfix(input);

	EXPECT_THAT(result, ElementsAre(PostfixSymbol{Value{5}}));
}

TEST(InfixToPostfixTests, Input_has_3_value_symbols)
{
	const InfixSymbols input {
		InfixSymbol{Value{5}},
		InfixSymbol{Value{42}},
		InfixSymbol{Value{128}},
	};
	
	const auto result = infix_to_postfix(input);

	EXPECT_THAT(result, ElementsAre(PostfixSymbol{Value{5}}, PostfixSymbol{Value{42}}, PostfixSymbol{Value{128}}));
}

TEST(InfixToPostfixTests, Value_addition_value)
{
	const InfixSymbols input {
		InfixSymbol{Value{42}},
		InfixSymbol{InfixSymbol::Operator::ADDITION},
		InfixSymbol{Value{69}},
	};
	
	const auto result = infix_to_postfix(input);

	EXPECT_THAT(
		result, 
		ElementsAre(
			PostfixSymbol{Value{42}},
			PostfixSymbol{Value{69}},
			PostfixSymbol{PostfixSymbol::Operator::ADDITION}
		)
	);
}

TEST(InfixToPostfixTests, Addition_four_times_in_a_row)
{
	const InfixSymbols input {
		InfixSymbol{Value{42}},
		InfixSymbol{InfixSymbol::Operator::ADDITION},
		InfixSymbol{Value{69}},
		InfixSymbol{InfixSymbol::Operator::ADDITION},
		InfixSymbol{Value{17}},
		InfixSymbol{InfixSymbol::Operator::ADDITION},
		InfixSymbol{Value{128}},
	};
	
	const auto result = infix_to_postfix(input);

	EXPECT_THAT(
		result,
		ElementsAre(
			PostfixSymbol{Value{42}},
			PostfixSymbol{Value{69}},
			PostfixSymbol{PostfixSymbol::Operator::ADDITION},
			PostfixSymbol{Value{17}},
			PostfixSymbol{PostfixSymbol::Operator::ADDITION},
			PostfixSymbol{Value{128}},
			PostfixSymbol{PostfixSymbol::Operator::ADDITION}
		)
	);
}

TEST(InfixToPostfixTests, Multiplication_addition)
{
	const InfixSymbols input {
		InfixSymbol{Value{2}},
		InfixSymbol{InfixSymbol::Operator::MULTIPLICATION},
		InfixSymbol{Value{3}},
		InfixSymbol{InfixSymbol::Operator::ADDITION},
		InfixSymbol{Value{5}},
	};
	
	const auto result = infix_to_postfix(input);

	EXPECT_THAT(
		result,
		ElementsAre(
			PostfixSymbol{Value{2}},
			PostfixSymbol{Value{3}},
			PostfixSymbol{PostfixSymbol::Operator::MULTIPLICATION},
			PostfixSymbol{Value{5}},
			PostfixSymbol{PostfixSymbol::Operator::ADDITION}
		)
	);
}

TEST(InfixToPostfixTests, Addition_multiplication)
{
	const InfixSymbols input {
		InfixSymbol{Value{2}},
		InfixSymbol{InfixSymbol::Operator::ADDITION},
		InfixSymbol{Value{3}},
		InfixSymbol{InfixSymbol::Operator::MULTIPLICATION},
		InfixSymbol{Value{5}},
	};
	
	const auto result = infix_to_postfix(input);

	EXPECT_THAT(
		result,
		ElementsAre(
			PostfixSymbol{Value{2}},
			PostfixSymbol{Value{3}},
			PostfixSymbol{Value{5}},
			PostfixSymbol{PostfixSymbol::Operator::MULTIPLICATION},
			PostfixSymbol{PostfixSymbol::Operator::ADDITION}
		)
	);
}

TEST(InfixToPostfixTests, Multiplication_addition_multiplication)
{
	const InfixSymbols input {
		InfixSymbol{Value{2}},
		InfixSymbol{InfixSymbol::Operator::MULTIPLICATION},
		InfixSymbol{Value{3}},
		InfixSymbol{InfixSymbol::Operator::ADDITION},
		InfixSymbol{Value{4}},
		InfixSymbol{InfixSymbol::Operator::MULTIPLICATION},
		InfixSymbol{Value{5}}
	};
	
	const auto result = infix_to_postfix(input);

	EXPECT_THAT(
		result,
		ElementsAre(
			PostfixSymbol{Value{2}},
			PostfixSymbol{Value{3}},
			PostfixSymbol{PostfixSymbol::Operator::MULTIPLICATION},
			PostfixSymbol{Value{4}},
			PostfixSymbol{Value{5}},
			PostfixSymbol{PostfixSymbol::Operator::MULTIPLICATION},
			PostfixSymbol{PostfixSymbol::Operator::ADDITION}
		)
	);
}

TEST(InfixToPostfixTests, Addition_multiplication_addition)
{
	const InfixSymbols input {
		InfixSymbol{Value{2}},
		InfixSymbol{InfixSymbol::Operator::ADDITION},
		InfixSymbol{Value{3}},
		InfixSymbol{InfixSymbol::Operator::MULTIPLICATION},
		InfixSymbol{Value{4}},
		InfixSymbol{InfixSymbol::Operator::ADDITION},
		InfixSymbol{Value{5}}
	};
	
	const auto result = infix_to_postfix(input);

	EXPECT_THAT(
		result,
		ElementsAre(
			PostfixSymbol{Value{2}},
			PostfixSymbol{Value{3}},
			PostfixSymbol{Value{4}},
			PostfixSymbol{PostfixSymbol::Operator::MULTIPLICATION},
			PostfixSymbol{PostfixSymbol::Operator::ADDITION},
			PostfixSymbol{Value{5}},
			PostfixSymbol{PostfixSymbol::Operator::ADDITION}
		)
	);
}

TEST(InfixToPostfixTests, Addition_subtraction)
{
	const InfixSymbols input {
		InfixSymbol{Value{2}},
		InfixSymbol{InfixSymbol::Operator::ADDITION},
		InfixSymbol{Value{3}},
		InfixSymbol{InfixSymbol::Operator::SUBTRACTION},
		InfixSymbol{Value{4}},
	};
	
	const auto result = infix_to_postfix(input);

	EXPECT_THAT(
		result,
		ElementsAre(
			PostfixSymbol{Value{2}},
			PostfixSymbol{Value{3}},
			PostfixSymbol{PostfixSymbol::Operator::ADDITION},
			PostfixSymbol{Value{4}},
			PostfixSymbol{PostfixSymbol::Operator::SUBTRACTION}
		)
	);
}

TEST(InfixToPostfixTests, Subtraction_addition)
{
	const InfixSymbols input {
		InfixSymbol{Value{2}},
		InfixSymbol{InfixSymbol::Operator::SUBTRACTION},
		InfixSymbol{Value{3}},
		InfixSymbol{InfixSymbol::Operator::ADDITION},
		InfixSymbol{Value{4}},
	};
	
	const auto result = infix_to_postfix(input);

	EXPECT_THAT(
		result,
		ElementsAre(
			PostfixSymbol{Value{2}},
			PostfixSymbol{Value{3}},
			PostfixSymbol{PostfixSymbol::Operator::SUBTRACTION},
			PostfixSymbol{Value{4}},
			PostfixSymbol{PostfixSymbol::Operator::ADDITION}
		)
	);
}

TEST(InfixToPostfixTests, Addition_multiplication_subtraction)
{
	const InfixSymbols input {
		InfixSymbol{Value{2}},
		InfixSymbol{InfixSymbol::Operator::ADDITION},
		InfixSymbol{Value{3}},
		InfixSymbol{InfixSymbol::Operator::MULTIPLICATION},
		InfixSymbol{Value{4}},
		InfixSymbol{InfixSymbol::Operator::SUBTRACTION},
		InfixSymbol{Value{5}},
	};
	
	const auto result = infix_to_postfix(input);

	EXPECT_THAT(
		result,
		ElementsAre(
			PostfixSymbol{Value{2}},
			PostfixSymbol{Value{3}},
			PostfixSymbol{Value{4}},
			PostfixSymbol{PostfixSymbol::Operator::MULTIPLICATION},
			PostfixSymbol{PostfixSymbol::Operator::ADDITION},
			PostfixSymbol{Value{5}},
			PostfixSymbol{PostfixSymbol::Operator::SUBTRACTION}
		)
	);
}