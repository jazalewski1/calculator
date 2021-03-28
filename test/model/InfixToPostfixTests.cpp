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
	else if (is_operation_type(lhs) and is_operation_type(rhs))
	{
		return get_type(lhs) == get_type(rhs);
	}
	return false;
}

std::ostream& operator<<(std::ostream& stream, const PostfixSymbol::Type& symbol)
{
	switch (symbol)
	{
		case PostfixSymbol::Type::ADDITION: return stream << "addition";
		case PostfixSymbol::Type::SUBTRACTION: return stream << "subtraction";
		case PostfixSymbol::Type::MULTIPLICATION: return stream << "multiplication";
	}
	return stream << "unknown";
}

std::ostream& operator<<(std::ostream& stream, const PostfixSymbol& symbol)
{
	if (is_value(symbol))
	{
		return stream << "PostfixSymbol:" << get_value(symbol);
	}
	return stream << "PostfixSymbol:" << get_type(symbol);
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
		InfixSymbol{InfixSymbol::Type::ADDITION},
		InfixSymbol{Value{69}},
	};
	
	const auto result = infix_to_postfix(input);

	EXPECT_THAT(
		result, 
		ElementsAre(
			PostfixSymbol{Value{42}},
			PostfixSymbol{Value{69}},
			PostfixSymbol{PostfixSymbol::Type::ADDITION}
		)
	);
}

TEST(InfixToPostfixTests, Addition_four_times_in_a_row)
{
	const InfixSymbols input {
		InfixSymbol{Value{42}},
		InfixSymbol{InfixSymbol::Type::ADDITION},
		InfixSymbol{Value{69}},
		InfixSymbol{InfixSymbol::Type::ADDITION},
		InfixSymbol{Value{17}},
		InfixSymbol{InfixSymbol::Type::ADDITION},
		InfixSymbol{Value{128}},
	};
	
	const auto result = infix_to_postfix(input);

	EXPECT_THAT(
		result,
		ElementsAre(
			PostfixSymbol{Value{42}},
			PostfixSymbol{Value{69}},
			PostfixSymbol{PostfixSymbol::Type::ADDITION},
			PostfixSymbol{Value{17}},
			PostfixSymbol{PostfixSymbol::Type::ADDITION},
			PostfixSymbol{Value{128}},
			PostfixSymbol{PostfixSymbol::Type::ADDITION}
		)
	);
}

TEST(InfixToPostfixTests, Multiplication_addition)
{
	const InfixSymbols input {
		InfixSymbol{Value{2}},
		InfixSymbol{InfixSymbol::Type::MULTIPLICATION},
		InfixSymbol{Value{3}},
		InfixSymbol{InfixSymbol::Type::ADDITION},
		InfixSymbol{Value{5}},
	};
	
	const auto result = infix_to_postfix(input);

	EXPECT_THAT(
		result,
		ElementsAre(
			PostfixSymbol{Value{2}},
			PostfixSymbol{Value{3}},
			PostfixSymbol{PostfixSymbol::Type::MULTIPLICATION},
			PostfixSymbol{Value{5}},
			PostfixSymbol{PostfixSymbol::Type::ADDITION}
		)
	);
}

TEST(InfixToPostfixTests, Addition_multiplication)
{
	const InfixSymbols input {
		InfixSymbol{Value{2}},
		InfixSymbol{InfixSymbol::Type::ADDITION},
		InfixSymbol{Value{3}},
		InfixSymbol{InfixSymbol::Type::MULTIPLICATION},
		InfixSymbol{Value{5}},
	};
	
	const auto result = infix_to_postfix(input);

	EXPECT_THAT(
		result,
		ElementsAre(
			PostfixSymbol{Value{2}},
			PostfixSymbol{Value{3}},
			PostfixSymbol{Value{5}},
			PostfixSymbol{PostfixSymbol::Type::MULTIPLICATION},
			PostfixSymbol{PostfixSymbol::Type::ADDITION}
		)
	);
}

TEST(InfixToPostfixTests, Multiplication_addition_multiplication)
{
	const InfixSymbols input {
		InfixSymbol{Value{2}},
		InfixSymbol{InfixSymbol::Type::MULTIPLICATION},
		InfixSymbol{Value{3}},
		InfixSymbol{InfixSymbol::Type::ADDITION},
		InfixSymbol{Value{4}},
		InfixSymbol{InfixSymbol::Type::MULTIPLICATION},
		InfixSymbol{Value{5}}
	};
	
	const auto result = infix_to_postfix(input);

	EXPECT_THAT(
		result,
		ElementsAre(
			PostfixSymbol{Value{2}},
			PostfixSymbol{Value{3}},
			PostfixSymbol{PostfixSymbol::Type::MULTIPLICATION},
			PostfixSymbol{Value{4}},
			PostfixSymbol{Value{5}},
			PostfixSymbol{PostfixSymbol::Type::MULTIPLICATION},
			PostfixSymbol{PostfixSymbol::Type::ADDITION}
		)
	);
}

TEST(InfixToPostfixTests, Addition_multiplication_addition)
{
	const InfixSymbols input {
		InfixSymbol{Value{2}},
		InfixSymbol{InfixSymbol::Type::ADDITION},
		InfixSymbol{Value{3}},
		InfixSymbol{InfixSymbol::Type::MULTIPLICATION},
		InfixSymbol{Value{4}},
		InfixSymbol{InfixSymbol::Type::ADDITION},
		InfixSymbol{Value{5}}
	};
	
	const auto result = infix_to_postfix(input);

	EXPECT_THAT(
		result,
		ElementsAre(
			PostfixSymbol{Value{2}},
			PostfixSymbol{Value{3}},
			PostfixSymbol{Value{4}},
			PostfixSymbol{PostfixSymbol::Type::MULTIPLICATION},
			PostfixSymbol{PostfixSymbol::Type::ADDITION},
			PostfixSymbol{Value{5}},
			PostfixSymbol{PostfixSymbol::Type::ADDITION}
		)
	);
}

TEST(InfixToPostfixTests, Addition_subtraction)
{
	const InfixSymbols input {
		InfixSymbol{Value{2}},
		InfixSymbol{InfixSymbol::Type::ADDITION},
		InfixSymbol{Value{3}},
		InfixSymbol{InfixSymbol::Type::SUBTRACTION},
		InfixSymbol{Value{4}},
	};
	
	const auto result = infix_to_postfix(input);

	EXPECT_THAT(
		result,
		ElementsAre(
			PostfixSymbol{Value{2}},
			PostfixSymbol{Value{3}},
			PostfixSymbol{PostfixSymbol::Type::ADDITION},
			PostfixSymbol{Value{4}},
			PostfixSymbol{PostfixSymbol::Type::SUBTRACTION}
		)
	);
}

TEST(InfixToPostfixTests, Subtraction_addition)
{
	const InfixSymbols input {
		InfixSymbol{Value{2}},
		InfixSymbol{InfixSymbol::Type::SUBTRACTION},
		InfixSymbol{Value{3}},
		InfixSymbol{InfixSymbol::Type::ADDITION},
		InfixSymbol{Value{4}},
	};
	
	const auto result = infix_to_postfix(input);

	EXPECT_THAT(
		result,
		ElementsAre(
			PostfixSymbol{Value{2}},
			PostfixSymbol{Value{3}},
			PostfixSymbol{PostfixSymbol::Type::SUBTRACTION},
			PostfixSymbol{Value{4}},
			PostfixSymbol{PostfixSymbol::Type::ADDITION}
		)
	);
}

TEST(InfixToPostfixTests, Addition_multiplication_subtraction)
{
	const InfixSymbols input {
		InfixSymbol{Value{2}},
		InfixSymbol{InfixSymbol::Type::ADDITION},
		InfixSymbol{Value{3}},
		InfixSymbol{InfixSymbol::Type::MULTIPLICATION},
		InfixSymbol{Value{4}},
		InfixSymbol{InfixSymbol::Type::SUBTRACTION},
		InfixSymbol{Value{5}},
	};
	
	const auto result = infix_to_postfix(input);

	EXPECT_THAT(
		result,
		ElementsAre(
			PostfixSymbol{Value{2}},
			PostfixSymbol{Value{3}},
			PostfixSymbol{Value{4}},
			PostfixSymbol{PostfixSymbol::Type::MULTIPLICATION},
			PostfixSymbol{PostfixSymbol::Type::ADDITION},
			PostfixSymbol{Value{5}},
			PostfixSymbol{PostfixSymbol::Type::SUBTRACTION}
		)
	);
}