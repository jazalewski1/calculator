#pragma once

namespace model
{
class Calculator
{
public:
	virtual ~Calculator();

	using OperationResult = int;
	OperationResult calculate_next();

	bool has_finished() const;

private:
	virtual OperationResult do_calculate_next() = 0;

	virtual bool do_has_finished() const = 0;
};
} // namespace model