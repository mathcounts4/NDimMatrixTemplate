#pragma once

// Matrix Expression Template
template<typename E, typename T, size_t... dims>
class MatrixExpr
{
public:
    static constexpr size_t numDims = sizeof...(dims);
    
    inline const T operator() (size_t indices[numDims]) const
	{
	    return static_cast<const E&>(*this)(indices);
	}

    constexpr bool touches(const void* other) const
	{
	    return static_cast<const E&>(*this).touches(other);
	}

    constexpr bool touchesOtherIndices(const void* other) const
	{
	    return static_cast<const E&>(*this).touchesOtherIndices(other);
	}
};
