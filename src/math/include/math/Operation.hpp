#pragma once

#include <functional>

namespace math
{
using Value = int;
using OperationFunction = std::function<Value (Value, Value)>;

Value addition(Value, Value);

Value multiplication(Value, Value);
} // namespace math