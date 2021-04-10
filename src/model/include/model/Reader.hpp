#pragma once

namespace model
{
class Reader
{
public:
	char extract();

	char peek() const;

	bool empty() const;

private:
	virtual void move_forward() = 0;

	virtual char next_character() const = 0;

	virtual bool is_empty() const = 0;
};
} // namespace model