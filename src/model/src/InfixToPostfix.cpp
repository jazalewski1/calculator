#include "math/Value.hpp"
#include "model/InfixSymbol.hpp"
#include "model/PostfixSymbol.hpp"
#include "model/InfixToPostfix.hpp"
#include <stack>

namespace model
{
namespace
{
PostfixSymbol::Operator infix_to_postfix_operator(InfixSymbol::Operator input)
{
	switch (input)
	{
		case InfixSymbol::Operator::SUBTRACTION: return PostfixSymbol::Operator::SUBTRACTION;
		case InfixSymbol::Operator::ADDITION: return PostfixSymbol::Operator::ADDITION;
		case InfixSymbol::Operator::DIVISION: return PostfixSymbol::Operator::DIVISION;
		case InfixSymbol::Operator::MULTIPLICATION: return PostfixSymbol::Operator::MULTIPLICATION;
	}
}

bool should_top_be_moved(InfixSymbol::Operator top, InfixSymbol::Operator current)
{
	const auto top_has_greater_precedence = precedence(top) > precedence(current);
	const auto top_has_equal_precedence = precedence(top) == precedence(current);
	constexpr auto token_is_left_associative = true; // temporary until operators with different associativity are used
	return (top_has_greater_precedence) or (top_has_equal_precedence and token_is_left_associative);
}
} // namespace

PostfixSymbols InfixToPostfixConverter::convert(const InfixSymbols& input)
{
	for (const auto& input_symbol : input)
	{
		std::visit([this](const auto& symbol){ process(symbol); }, input_symbol.data);
	}

	finish_process();

	return output;
}

void InfixToPostfixConverter::process(Value value)
{
	output.emplace_back(PostfixSymbol{math::Value{value}});
}

void InfixToPostfixConverter::process(Operator oper)
{
	while (not operator_stack.empty())
	{	
		const auto top_operator = operator_stack.top();
		if (should_top_be_moved(top_operator, oper))
		{
			operator_stack.pop();
			const auto converted_type = infix_to_postfix_operator(top_operator);
			output.emplace_back(PostfixSymbol{converted_type});
		}
		else
		{
			break;
		}
	}
	operator_stack.push(oper);
}

void InfixToPostfixConverter::finish_process()
{
	while (not operator_stack.empty())
	{
		const auto oper = operator_stack.top();
		operator_stack.pop();
		const auto infix_operator = infix_to_postfix_operator(oper);
		output.emplace_back(PostfixSymbol{infix_operator});
	}
}
} // namespace model