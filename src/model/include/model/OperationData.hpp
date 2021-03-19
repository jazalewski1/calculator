#pragma once

#include <optional>
#include <iostream>

namespace model
{
enum class OperationType
{
	ADDITION,
	MULTIPLICATION
};

struct LhsOperand
{
	int value;
};
struct RhsOperand
{
	int value;
};

struct OperationData
{
	OperationData(OperationType type, LhsOperand lhs, RhsOperand rhs) :
		type{type}, lhs{lhs.value}, rhs{rhs.value}
	{
	}
	OperationData(OperationType type, LhsOperand operand) :
		type{type}, lhs{operand.value}, rhs{std::nullopt}
	{
	}
	OperationData(OperationType type, RhsOperand operand) :
		type{type}, lhs{std::nullopt}, rhs{operand.value}
	{
	}

	const OperationType type;
	const std::optional<int> lhs, rhs;
};
} // namespace model