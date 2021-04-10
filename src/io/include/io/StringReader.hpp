#pragma once

#include "model/Reader.hpp"
#include <string>

namespace io
{
class StringReader : public model::Reader
{
public:
	using StringIterator = std::string::const_iterator;
	StringReader(StringIterator, StringIterator);

private:
	StringIterator current;
	StringIterator end;

	void move_forward() override;

	char next_character() const override;

	bool is_empty() const override;
};
} // namespace io