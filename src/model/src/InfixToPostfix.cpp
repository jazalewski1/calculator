#include "math/Value.hpp"
#include "model/InfixSymbol.hpp"
#include "model/PostfixSymbol.hpp"
#include <stack>

namespace model
{
namespace
{
PostfixSymbol::Operator convert(InfixSymbol::Operator input)
{
	switch (input)
	{
		case InfixSymbol::Operator::SUBTRACTION: return PostfixSymbol::Operator::SUBTRACTION;
		case InfixSymbol::Operator::ADDITION: return PostfixSymbol::Operator::ADDITION;
		case InfixSymbol::Operator::DIVISION: return PostfixSymbol::Operator::DIVISION;
		case InfixSymbol::Operator::MULTIPLICATION: return PostfixSymbol::Operator::MULTIPLICATION;
	}
}

int precedence(InfixSymbol::Operator input)
{
	switch (input)
	{
		case InfixSymbol::Operator::SUBTRACTION: return 1;
		case InfixSymbol::Operator::ADDITION: return 1;
		case InfixSymbol::Operator::DIVISION: return 2;
		case InfixSymbol::Operator::MULTIPLICATION: return 2;
	}
}

bool should_top_be_moved(InfixSymbol::Operator top, InfixSymbol::Operator current)
{
	const auto top_has_greater_precedence = precedence(top) > precedence(current);
	const auto top_has_equal_precedence = precedence(top) == precedence(current);
	constexpr auto token_is_left_associative = true; // FDEV: temporary until operators with different associativity are used
	return (top_has_greater_precedence) or (top_has_equal_precedence and token_is_left_associative);
}
} // namespace

PostfixSymbols infix_to_postfix(const InfixSymbols& input)
{
	using Operator = InfixSymbol::Operator; // FDEV: should be replaced with Operator type with precedence and associativity info
	PostfixSymbols output;
	std::stack<Operator> operator_stack;

	for (const auto& input_symbol : input)
	{
		if (is_value(input_symbol))
		{
			const auto value = get_value(input_symbol);
			output.emplace_back(PostfixSymbol{math::Value{value}});
		}
		else if (is_operator(input_symbol))
		{
			const auto current_operator = get_operator(input_symbol);
			while (not operator_stack.empty())
			{	
				const auto top_operator = operator_stack.top();
				if (should_top_be_moved(top_operator, current_operator))
				{
					operator_stack.pop();
					const auto converted_type = convert(top_operator);
					output.emplace_back(PostfixSymbol{converted_type});
				}
				else
				{
					break;
				}
			}

			operator_stack.push(current_operator);
		}
	}

	while (not operator_stack.empty())
	{
		const auto oper = operator_stack.top();
		operator_stack.pop();
		const auto converted_type = convert(oper);
		output.emplace_back(PostfixSymbol{converted_type});
	}

	return output;
}
} // namespace model