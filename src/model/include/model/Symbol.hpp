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
} // namespace model