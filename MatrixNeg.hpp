#pragma once

#include "MatrixExpr.hpp"

// Matrix neg template
template<typename E, typename T, size_t... dims>
class MatrixNeg : public MatrixExpr<MatrixNeg<E,T,dims...>,
				    T,
				    dims...>
{
    typedef MatrixExpr<E,T,dims...> ME;
    
    const ME& m;

public:
    inline const T operator() (size_t indices[ME::numDims]) const
	{
	    return -(m(indices));
	}

    constexpr bool touches(const void* other) const
	{
	    return m.touches(other);
	}

    constexpr bool touchesOtherIndices(const void* other) const
	{
	    return m.touchesOtherIndices(other);
	}

    MatrixNeg(const ME& M) : m(M) { }
};

template<typename E, typename T, size_t... dims>
const MatrixNeg<E,T,dims...>
operator-(const MatrixExpr<E,T,dims...>& m)
{
    return MatrixNeg<E,T,dims...>(m);
}
