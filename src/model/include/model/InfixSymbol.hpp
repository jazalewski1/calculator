#pragma once

#include "math/Value.hpp"
#include <variant>
#include <vector>

namespace model
{
struct InfixSymbol
{
	enum class Operator
	{
		SUBTRACTION,
		ADDITION,
		DIVISION,
		MULTIPLICATION,
		OPEN_PAR,
		CLOSE_PAR
	};

	using Variant = std::variant<math::Value, Operator>;
	const Variant data;
};

using InfixSymbols = std::vector<InfixSymbol>;

int precedence(InfixSymbol::Operator input);

bool is_value(const InfixSymbol&);

bool is_operator(const InfixSymbol&);

InfixSymbol::Operator get_operator(const InfixSymbol&);

math::Value get_value(const InfixSymbol&);
} // namespace model