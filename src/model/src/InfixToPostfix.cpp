#include "math/Value.hpp"
#include "model/InfixSymbol.hpp"
#include "model/InfixToPostfix.hpp"
#include "model/PostfixSymbol.hpp"
#include "util/Exception.hpp"
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
		default: throw util::BadAccessException{"Operator not found."};
	}
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
	output.emplace_back(PostfixSymbol{value});
}

void InfixToPostfixConverter::process(InfixSymbol::Operator current_operator)
{
	while (not temporary_stack.empty())
	{	
		const auto top_symbol = temporary_stack.top();
		if (is_open_par(top_symbol))
		{
			break;
		}

		const auto top_operator = get_operator(top_symbol);

		const auto top_has_greater_precedence = precedence(top_operator) > precedence(current_operator);
		const auto top_has_equal_precedence = precedence(top_operator) == precedence(current_operator);
		constexpr auto top_is_left_associative = true; // temporary until operators with different associativity are used
		const auto should_top_be_moved = (top_has_greater_precedence) or (top_has_equal_precedence and top_is_left_associative);

		if (should_top_be_moved)
		{
			temporary_stack.pop();
			const auto postfix_operator = infix_to_postfix_operator(top_operator);
			output.emplace_back(PostfixSymbol{postfix_operator});
		}
		else
		{
			break;
		}
	}
	temporary_stack.push(InfixSymbol{current_operator});
}

void InfixToPostfixConverter::process(InfixSymbol::OpenPar open_par)
{
	temporary_stack.push(InfixSymbol{open_par});
}

void InfixToPostfixConverter::process(InfixSymbol::ClosePar close_par)
{
	while (not temporary_stack.empty())
	{
		const auto top_symbol = temporary_stack.top(); 
		if (is_open_par(top_symbol))
		{
			break;
		}

		temporary_stack.pop();

		const auto top_operator = get_operator(top_symbol);
		const auto postfix_operator = infix_to_postfix_operator(top_operator);
		output.emplace_back(PostfixSymbol{postfix_operator});
	}

	if (not temporary_stack.empty() and is_open_par(temporary_stack.top()))
	{
		temporary_stack.pop();
	}
	else
	{
		throw util::UnmatchedBracesException{"Unmatched right parenthesis."};
	}
}

void InfixToPostfixConverter::finish_process()
{
	while (not temporary_stack.empty())
	{
		const auto top_symbol = temporary_stack.top();
		temporary_stack.pop();
		if (is_open_par(top_symbol))
		{
			throw util::UnmatchedBracesException{"Unmatched left parenthesis."};
		}
		const auto infix_operator = get_operator(top_symbol);
		const auto postfix_operator = infix_to_postfix_operator(infix_operator);
		output.emplace_back(PostfixSymbol{postfix_operator});
	}
}
} // namespace model