#pragma once

#include <variant>

namespace model
{
enum class OperationType
{
	ADDITION,
	MULTIPLICATION
};

using Value = int;

using SymbolVariant = std::variant<Value, OperationType>;

struct Symbol
{
	const SymbolVariant data;
};

bool is_value(const SymbolVariant&);

bool is_operation_type(const SymbolVariant&);

OperationType get_operation_type(const SymbolVariant&);

Value get_value(const SymbolVariant&);
} // namespace model