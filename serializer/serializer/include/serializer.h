#pragma once
#include<iostream>
#include<string>

enum class Error {
	NoError,
	CorruptedArchive
};

template<typename T>
class Serializer {
private:
	std::ostream& out_;
	static constexpr char Separator = ' ';

	template <class T, class... ArgsT>
	Error process(T&& value, ArgsT&&... args)
	{
		if (process(std::forward<T>(value)) == Error::NoError)
		{
			out_ << Separator;
			return process(std::forward<ArgsT>(args)...);
		}
		return Error::CorruptedArchive;
	}

	Error process(uint64_t value)
	{
		out_ << value;
		return Error::NoError;
	}

	Error process(bool value)
	{
		out_ << (value ? "true" : "false");
		return Error::NoError;
	}

	Error process()
	{
		return Error::NoError;
	}

public:
	Serializer(std::ostream& out) : out_(out) {};
	
	Error save(T& object) {
		return object.serialize(*this);
	}

	template<typename... argsT>
	Error operator()(argsT... args) {
		return process(std::forward<argsT>(args)...);
	}
};

class Deserializer
{
    static constexpr char Separator = ' ';

public:
    explicit Deserializer(std::istream& in)
        : in_(in)
    {
    }

    template <class T>
    Error load(T& object)
    {
        return object.serialize(*this);
    }

    template <class... ArgsT>
    Error operator()(ArgsT&... args)
    {
        return process(args...);
    }

private:
    std::istream& in_;

    template <class T, class... ArgsT>
    Error process(T& value, ArgsT&... args)
    {
        if (process(value) == Error::NoError)
        {
            return process(args...);
        }
        return Error::CorruptedArchive;
    }

    Error process(uint64_t& value)
    {
        std::string text;
        in_ >> text;
        try
        {
            value = std::stoull(text);
        }
        catch (...)
        {
            return Error::CorruptedArchive;
        }
        return Error::NoError;
    }

    Error process(bool& value)
    {
        std::string text;
        in_ >> text;

        if (text == "true")
            value = true;
        else if (text == "false")
            value = false;
        else
            return Error::CorruptedArchive;

        return Error::NoError;
    }

    Error process()
    {
        return Error::NoError;
    }
};