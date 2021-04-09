#pragma once

#include "math/Value.hpp"
#include <variant>
#include <vector>

namespace model
{
struct InfixToken
{
	enum class Operator
	{
		SUBTRACTION,
		ADDITION,
		DIVISION,
		MULTIPLICATION
	};

	struct OpenPar {};
	struct ClosePar {};

	using Variant = std::variant<math::Value, Operator, OpenPar, ClosePar>;
	const Variant data;
};

using InfixTokens = std::vector<InfixToken>;

int precedence(InfixToken::Operator input);

bool is_value(const InfixToken&);

bool is_operator(const InfixToken&);

bool is_open_par(const InfixToken&);

bool is_close_par(const InfixToken&);

InfixToken::Operator get_operator(const InfixToken&);

math::Value get_value(const InfixToken&);
} // namespace model