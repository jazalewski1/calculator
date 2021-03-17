#pragma once

#include "math/Operation.hpp"
#include "model/OperationData.hpp"
#include <memory>
#include <vector>

namespace model
{
using Result = int;
using OperationDataVector = std::vector<OperationData>;

class Calculator
{
public:
	Calculator(const OperationDataVector&);

	Result calculate_next();

	Result get_running_total() const;

	bool finished() const;

private:
	using OperationPtr = std::shared_ptr<math::Operation>;
	using OperationPtrs = std::vector<OperationPtr>;
	using TotalPtr = std::shared_ptr<int>;

	OperationPtrs operations;
	OperationPtrs::iterator current_operation_iter;
	TotalPtr running_total;
};
} // namespace model