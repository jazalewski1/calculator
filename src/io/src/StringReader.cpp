#include "io/StringReader.hpp"
#include <string>

namespace io
{
StringReader::StringReader(StringIterator begin, StringIterator end) :
	current{begin}, end{end}
{
}

void StringReader::move_forward()
{
	std::advance(current, 1);
}

char StringReader::next_character() const
{
	return *current;
}

bool StringReader::is_empty() const
{
	return current == end;
}
} // namespace io