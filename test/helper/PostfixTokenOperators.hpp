#include "model/PostfixToken.hpp"
#include <ostream>

namespace model
{
inline bool operator==(const PostfixToken& lhs, const PostfixToken& rhs)
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

std::ostream& operator<<(std::ostream& stream, const PostfixToken::Operator& token)
{
	switch (token)
	{
		case PostfixToken::Operator::SUBTRACTION: return stream << "subtraction";
		case PostfixToken::Operator::ADDITION: return stream << "addition";
		case PostfixToken::Operator::DIVISION: return stream << "division";
		case PostfixToken::Operator::MULTIPLICATION: return stream << "multiplication";
	}
	return stream << "unknown";
}

std::ostream& operator<<(std::ostream& stream, const PostfixToken& token)
{
	if (is_value(token))
	{
		const auto value = get_value(token);
		return stream << "PostfixToken:" << (math::is_integer(value) ? math::get_integer(value) : math::get_double(value));
	}
	return stream << "PostfixToken:" << get_operator(token);
}
} // namespace model