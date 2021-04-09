#include "math/Value.hpp"
#include "model/PostfixToken.hpp"

namespace model
{
bool is_value(const PostfixToken& token)
{
	return std::holds_alternative<math::Value>(token.data);
}

bool is_operator(const PostfixToken& token)
{
	return std::holds_alternative<PostfixToken::Operator>(token.data);
}

PostfixToken::Operator get_operator(const PostfixToken& token)
{
	return std::get<PostfixToken::Operator>(token.data);
}

math::Value get_value(const PostfixToken& token)
{
	return std::get<math::Value>(token.data);
}
} // namespace model