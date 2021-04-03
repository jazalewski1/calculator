#pragma once

#include "math/Value.hpp"
#include <vector>
#include <variant>

namespace model
{
struct PostfixSymbol
{
	enum class Type
	{
		SUBTRACTION,
		ADDITION,
		DIVISION,
		MULTIPLICATION
	};

	using Variant = std::variant<math::Value, Type>;
	const Variant data;
};

using PostfixSymbols = std::vector<PostfixSymbol>;

bool is_value(const PostfixSymbol&);

bool is_operation_type(const PostfixSymbol&);

PostfixSymbol::Type get_type(const PostfixSymbol&);

math::Value get_value(const PostfixSymbol&);
} // namespace model