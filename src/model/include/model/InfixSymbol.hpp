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
		MULTIPLICATION
	};

	struct OpenPar {};
	struct ClosePar {};

	using Variant = std::variant<math::Value, Operator, OpenPar, ClosePar>;
	const Variant data;
};

using InfixSymbols = std::vector<InfixSymbol>;

int precedence(InfixSymbol::Operator input);

bool is_value(const InfixSymbol&);

bool is_operator(const InfixSymbol&);

bool is_open_par(const InfixSymbol&);

bool is_close_par(const InfixSymbol&);

InfixSymbol::Operator get_operator(const InfixSymbol&);

math::Value get_value(const InfixSymbol&);
} // namespace model