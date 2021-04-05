#pragma once

#include <string>

namespace util
{
class Exception
{
public:
	virtual ~Exception() {}

	std::string message() const
	{
		return std::string{get_name() + ": " + get_message()};
	}

private:
	virtual std::string get_name() const = 0;

	virtual std::string get_message() const = 0;
};

class BadAccessException : public Exception
{
public:
	BadAccessException(std::string message_string) : message_str{message_string} {}

private:
	const std::string message_str;

	std::string get_name() const override { return "BadAccessException"; }
	std::string get_message() const override { return message_str; }
};

class InputErrorException : public Exception
{
public:
	InputErrorException(std::string message_string) : message_str{message_string} {}

private:
	const std::string message_str;

	std::string get_name() const override { return "InputErrorException"; }
	std::string get_message() const override { return message_str; }
};

class UnmatchedBracesException : public Exception
{
public:
	UnmatchedBracesException(std::string message_string) : message_str{message_string} {}

private:
	const std::string message_str;

	std::string get_name() const override { return "UnmatchedBracesException"; }
	std::string get_message() const override { return message_str; }
};
} // namespace util