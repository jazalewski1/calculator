#pragma once

#include "math/Value.hpp"
#include <functional>

namespace math
{
using OperationFunction = std::function<Value (Value, Value)>;

template <typename LhsType, typename RhsType>
Value subtraction(LhsType lhs, RhsType rhs)
{
	return {lhs - rhs};
}

template <typename LhsType, typename RhsType>
Value addition(LhsType lhs, RhsType rhs)
{
	return {lhs + rhs};
}

template <typename LhsType, typename RhsType>
Value division(LhsType lhs, RhsType rhs)
{
	return Value{std::in_place_type<double>, lhs / rhs};
}

template <typename LhsType, typename RhsType>
Value multiplication(LhsType lhs, RhsType rhs)
{
	return {lhs * rhs};
}
} // namespace math