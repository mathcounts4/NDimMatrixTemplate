#pragma once

// ArgsStr Template: ArgsStr<dims>::getStr()
template<size_t... dims>
struct ArgsStr;

// Base case: no numbers, return "no_dims"
template<>
struct ArgsStr<>
{
public:
    static inline const std::string getStr()
	{
	    return "no dims";
	}
};

// Base case: last number, just return that
template<size_t dim>
struct ArgsStr<dim>
{
public:
    static inline const std::string getStr()
	{
	    return std::to_string(dim);
	}
};

// recursive case: add the first dim and a comma
template<size_t first, size_t second, size_t... dims>
struct ArgsStr<first,second,dims...>
{
public:
    static inline const std::string getStr()
	{
	    return
		std::to_string(first) +
		"," +
		ArgsStr<second,dims...>::getStr();
	}
};
