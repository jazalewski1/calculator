#pragma once

#include "math/Value.hpp"
#include <variant>
#include <vector>

namespace model
{


struct InfixSymbol
{
	enum class Type
	{
		ADDITION,
		MULTIPLICATION,
	};

	using Variant = std::variant<math::Value, Type>;
	const Variant data;
};

using InfixSymbols = std::vector<InfixSymbol>;

bool is_value(const InfixSymbol&);

bool is_operation_type(const InfixSymbol&);

InfixSymbol::Type get_type(const InfixSymbol&);

math::Value get_value(const InfixSymbol&);
} // namespace model