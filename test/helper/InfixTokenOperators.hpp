#include "model/InfixToken.hpp"
#include "math/Value.hpp"
#include <ostream>

namespace model
{
inline bool operator==(const InfixToken& lhs, const InfixToken& rhs)
{
	if (is_value(lhs) and is_value(rhs))
	{
		return get_value(lhs) == get_value(rhs);
	}
	if (is_operator(lhs) and is_operator(rhs))
	{
		return get_operator(lhs) == get_operator(rhs);
	}
	if (is_open_par(lhs) and is_open_par(rhs))
	{
		return true;
	}
	if (is_close_par(lhs) and is_close_par(rhs))
	{
		return true;
	}
	return false;
}

std::ostream& operator<<(std::ostream& stream, const InfixToken::Operator& token)
{
	switch (token)
	{
		case InfixToken::Operator::SUBTRACTION: return stream << "subtraction";
		case InfixToken::Operator::ADDITION: return stream << "addition";
		case InfixToken::Operator::DIVISION: return stream << "division";
		case InfixToken::Operator::MULTIPLICATION: return stream << "multiplication";
	}
	return stream << "unknown operator";
}

std::ostream& operator<<(std::ostream& stream, const InfixToken& token)
{
	if (is_value(token))
	{
		const auto value_variant = get_value(token);
		if (math::is_integer(value_variant))
		{
			return stream << math::get_integer(value_variant);
		}
		if (math::is_double(value_variant))
		{
			return stream << math::get_double(value_variant);
		}
	}
	if (is_operator(token))
	{
		return stream << get_operator(token);
	}
	if (is_open_par(token))
	{
		return stream << "open par";
	}
	if (is_close_par(token))
	{
		return stream << "close par";
	}
	return stream << "unknown token";
}
} // namespace model