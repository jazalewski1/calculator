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

struct PreviousResult {};

struct OperationData
{
	OperationData(OperationType type, int lhs, int rhs) :
		type{type}, lhs{lhs}, rhs{rhs}
	{
	}
	OperationData(OperationType type, int lhs, PreviousResult) :
		type{type}, lhs{lhs}, rhs{std::nullopt}
	{
	}
	OperationData(OperationType type, PreviousResult, int rhs) :
		type{type}, lhs{std::nullopt}, rhs{rhs}
	{
	}

	const OperationType type;
	const std::optional<int> lhs, rhs;
};
} // namespace model