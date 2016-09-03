#pragma once

#include "MatrixExpr.hpp"

// Matrix dif template
template<typename E1, typename E2, typename T, typename R, size_t... dims>
class MatrixDif : public MatrixExpr<MatrixDif<E1,E2,T,R,dims...>,
				    T,
				    dims...>
{
    typedef MatrixExpr<E1,T,dims...> ME1;
    typedef MatrixExpr<E2,R,dims...> ME2;
    
private:
    const ME1& lhs;
    const ME2& rhs;

public:
    inline const T operator() (size_t indices[ME1::numDims]) const
	{
	    return lhs(indices) - rhs(indices);
	}

    constexpr bool touches(const void* other) const
	{
	    return lhs.touches(other) || rhs.touches(other);
	}

    constexpr bool touchesOtherIndices(const void* other) const
	{
	    return lhs.touchesOtherIndices(other) || rhs.touchesOtherIndices(other);
	}

    MatrixDif(const ME1& LHS,
	      const ME2& RHS) :
	lhs(LHS),
	rhs(RHS)
	{ }
};

// Matrix dif formation
template<typename E1, typename E2, typename T, typename R, size_t... dims>
const MatrixDif<E1,E2,T,R,dims...>
operator-(const MatrixExpr<E1,T,dims...>& lhs,
	  const MatrixExpr<E2,R,dims...>& rhs)
{
    return MatrixDif<E1,E2,T,R,dims...>(lhs,rhs);
}
