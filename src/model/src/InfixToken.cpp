#include "model/InfixToken.hpp"

namespace model
{
int precedence(InfixToken::Operator input)
{
	switch (input)
	{
		case InfixToken::Operator::SUBTRACTION: return 1;
		case InfixToken::Operator::ADDITION: return 1;
		case InfixToken::Operator::DIVISION: return 2;
		case InfixToken::Operator::MULTIPLICATION: return 2;
	}
}

bool is_value(const InfixToken& token)
{
	return std::holds_alternative<math::Value>(token.data);
}

bool is_operator(const InfixToken& token)
{
	return std::holds_alternative<InfixToken::Operator>(token.data);
}

bool is_open_par(const InfixToken& token)
{
	return std::holds_alternative<InfixToken::OpenPar>(token.data);
}

bool is_close_par(const InfixToken& token)
{
	return std::holds_alternative<InfixToken::ClosePar>(token.data);
}

InfixToken::Operator get_operator(const InfixToken& token)
{
	return std::get<InfixToken::Operator>(token.data);
}

math::Value get_value(const InfixToken& token)
{
	return std::get<math::Value>(token.data);
}
} // namespace model