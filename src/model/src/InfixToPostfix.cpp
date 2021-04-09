#include "math/Value.hpp"
#include "model/InfixToken.hpp"
#include "model/InfixToPostfix.hpp"
#include "model/PostfixToken.hpp"
#include "util/Exception.hpp"
#include <stack>

namespace model
{
namespace
{
PostfixToken::Operator infix_to_postfix_operator(InfixToken::Operator input)
{
	switch (input)
	{
		case InfixToken::Operator::SUBTRACTION: return PostfixToken::Operator::SUBTRACTION;
		case InfixToken::Operator::ADDITION: return PostfixToken::Operator::ADDITION;
		case InfixToken::Operator::DIVISION: return PostfixToken::Operator::DIVISION;
		case InfixToken::Operator::MULTIPLICATION: return PostfixToken::Operator::MULTIPLICATION;
		default: throw util::BadAccessException{"Operator not found."};
	}
}
} // namespace

PostfixTokens InfixToPostfixConverter::convert(const InfixTokens& input)
{
	for (const auto& input_token : input)
	{
		std::visit([this](const auto& token){ process(token); }, input_token.data);
	}

	finish_process();

	return output;
}

void InfixToPostfixConverter::process(Value value)
{
	output.emplace_back(PostfixToken{value});
}

void InfixToPostfixConverter::process(InfixToken::Operator current_operator)
{
	while (not temporary_stack.empty())
	{	
		const auto top_token = temporary_stack.top();
		if (is_open_par(top_token))
		{
			break;
		}

		const auto top_operator = get_operator(top_token);

		const auto top_has_greater_precedence = precedence(top_operator) > precedence(current_operator);
		const auto top_has_equal_precedence = precedence(top_operator) == precedence(current_operator);
		constexpr auto top_is_left_associative = true; // temporary until operators with different associativity are used
		const auto should_top_be_moved = (top_has_greater_precedence) or (top_has_equal_precedence and top_is_left_associative);

		if (should_top_be_moved)
		{
			temporary_stack.pop();
			const auto postfix_operator = infix_to_postfix_operator(top_operator);
			output.emplace_back(PostfixToken{postfix_operator});
		}
		else
		{
			break;
		}
	}
	temporary_stack.push(InfixToken{current_operator});
}

void InfixToPostfixConverter::process(InfixToken::OpenPar open_par)
{
	temporary_stack.push(InfixToken{open_par});
}

void InfixToPostfixConverter::process(InfixToken::ClosePar close_par)
{
	while (not temporary_stack.empty())
	{
		const auto top_token = temporary_stack.top(); 
		if (is_open_par(top_token))
		{
			break;
		}

		temporary_stack.pop();

		const auto top_operator = get_operator(top_token);
		const auto postfix_operator = infix_to_postfix_operator(top_operator);
		output.emplace_back(PostfixToken{postfix_operator});
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
		const auto top_token = temporary_stack.top();
		temporary_stack.pop();
		if (is_open_par(top_token))
		{
			throw util::UnmatchedBracesException{"Unmatched left parenthesis."};
		}
		const auto infix_operator = get_operator(top_token);
		const auto postfix_operator = infix_to_postfix_operator(infix_operator);
		output.emplace_back(PostfixToken{postfix_operator});
	}
}
} // namespace model