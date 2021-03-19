#pragma once

#include "math/Operation.hpp"
#include "model/OperationData.hpp"

namespace model
{
class Calculator
{
public:
	using Result = int;

	Calculator() = default;

	void calculate(const OperationData&);

	Result get_running_total() const;

private:
	Result running_total;
};
} // namespace model