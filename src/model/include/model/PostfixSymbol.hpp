#pragma once

#include "math/Value.hpp"
#include <vector>
#include <variant>

namespace model
{
struct PostfixSymbol
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

using PostfixSymbols = std::vector<PostfixSymbol>;

bool is_value(const PostfixSymbol&);

bool is_operator(const PostfixSymbol&);

PostfixSymbol::Operator get_operator(const PostfixSymbol&);

math::Value get_value(const PostfixSymbol&);
} // namespace model