#pragma once

// Product Template: Product<dims>::value
template<size_t... dims>
struct Product;

// Base case: no arguments -> product of 1
template<>
struct Product<>
{
public:
    static constexpr size_t value = 1;
    static inline size_t getIndex(size_t[0])
	{
	    return 0;
	}
};

// Recursive case: multiply by the first value
template<size_t firstDim, size_t... dims>
struct Product<firstDim,dims...>
{
public:
    static constexpr size_t value = firstDim * Product<dims...>::value;
    static inline const size_t getIndex(size_t indices[sizeof...(dims)+1])
	{
	    if (indices[0] >= firstDim)
	    {
		throw std::out_of_range(
		    std::to_string(indices[0]) +
		    " (index) >= " +
		    std::to_string(firstDim) +
		    " (size)");
	    }
	    return indices[0] * Product<dims...>::value +
		Product<dims...>::getIndex(indices + 1);
	}
};
