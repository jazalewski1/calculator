#pragma once

#include "math/Value.hpp"
#include <functional>

namespace math
{
using OperationFunction = std::function<Value (Value, Value)>;

Value addition(Value, Value);

Value multiplication(Value, Value);
} // namespace math