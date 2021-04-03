#include "math/Value.hpp"
#include "model/InfixSymbol.hpp"
#include "model/PostfixSymbol.hpp"
#include <stack>

namespace model
{
namespace
{
PostfixSymbol::Type convert(InfixSymbol::Type input)
{
	switch (input)
	{
		case InfixSymbol::Type::SUBTRACTION: return PostfixSymbol::Type::SUBTRACTION;
		case InfixSymbol::Type::ADDITION: return PostfixSymbol::Type::ADDITION;
		case InfixSymbol::Type::DIVISION: return PostfixSymbol::Type::DIVISION;
		case InfixSymbol::Type::MULTIPLICATION: return PostfixSymbol::Type::MULTIPLICATION;
	}
}

int precedence(InfixSymbol::Type input)
{
	switch (input)
	{
		case InfixSymbol::Type::SUBTRACTION: return 1;
		case InfixSymbol::Type::ADDITION: return 1;
		case InfixSymbol::Type::DIVISION: return 2;
		case InfixSymbol::Type::MULTIPLICATION: return 2;
	}
}

bool should_top_be_moved(InfixSymbol::Type top, InfixSymbol::Type current)
{
	const auto top_has_greater_precedence = precedence(top) > precedence(current);
	const auto top_has_equal_precedence = precedence(top) == precedence(current);
	constexpr auto token_is_left_associative = true; // FDEV: temporary until operators with different associativity are used
	return (top_has_greater_precedence) or (top_has_equal_precedence and token_is_left_associative);
}
} // namespace

PostfixSymbols infix_to_postfix(const InfixSymbols& input)
{
	using Operator = InfixSymbol::Type; // FDEV: should be replaced with Operator type with precedence and associativity info
	PostfixSymbols output;
	std::stack<Operator> operators;

	for (const auto& input_symbol : input)
	{
		if (is_value(input_symbol))
		{
			const auto value = get_value(input_symbol);
			output.emplace_back(PostfixSymbol{math::Value{value}});
		}
		else if (is_operation_type(input_symbol))
		{
			const auto current_operator = get_type(input_symbol);
			while (not operators.empty())
			{	
				const auto top_operator = operators.top();
				if (should_top_be_moved(top_operator, current_operator))
				{
					operators.pop();
					const auto converted_type = convert(top_operator);
					output.emplace_back(PostfixSymbol{converted_type});
				}
				else
				{
					break;
				}
			}

			operators.push(current_operator);
		}
	}

	while (not operators.empty())
	{
		const auto oper = operators.top();
		operators.pop();
		const auto converted_type = convert(oper);
		output.emplace_back(PostfixSymbol{converted_type});
	}

	return output;
}
} // namespace model