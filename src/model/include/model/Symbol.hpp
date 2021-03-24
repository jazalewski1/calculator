#pragma once

#include "math/Value.hpp"
#include <vector>
#include <variant>

namespace model
{
enum class OperationType
{
	ADDITION,
	MULTIPLICATION
};

struct Symbol
{
	using Variant = std::variant<math::Value, OperationType>;
	const Variant data;
};

using Symbols = std::vector<Symbol>;

bool is_value(const Symbol::Variant&);

bool is_operation_type(const Symbol::Variant&);

OperationType get_operation_type(const Symbol::Variant&);

math::Value get_value(const Symbol::Variant&);
} // namespace model