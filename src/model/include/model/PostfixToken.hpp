#pragma once

#include "math/Value.hpp"
#include <vector>
#include <variant>

namespace model
{
struct PostfixToken
{
	enum class Operator
	{
		SUBTRACTION,
		ADDITION,
		DIVISION,
		MULTIPLICATION
	};

	using Variant = std::variant<math::Value, Operator>;
	const Variant data;
};

using PostfixTokens = std::vector<PostfixToken>;

bool is_value(const PostfixToken&);

bool is_operator(const PostfixToken&);

PostfixToken::Operator get_operator(const PostfixToken&);

math::Value get_value(const PostfixToken&);
} // namespace model