#pragma once

#include "MatrixExpr.hpp"

// 3 + M
// T is data type of 3, E is expr type of M, T is data type of M
template<typename T, typename E, size_t... dims>
class MatrixScalarSumFirst : public MatrixExpr<MatrixScalarSumFirst<T,E,dims...>,
					       T,
					       dims...>
{
private:
    typedef MatrixExpr<E,T,dims...> ME;
    
    const T& val;
    const ME& m;

public:
    inline const T operator() (size_t indices[ME::numDims]) const
	{
	    return val + m(indices);
	}

    constexpr bool touches(const void* other) const
	{
	    return m.touches(other);
	}

    constexpr bool touchesOtherIndices(const void* other) const
	{
	    return m.touchesOtherIndices(other);
	}

    MatrixScalarSumFirst(const T& VAL,
			 const ME& M) :
	val(VAL),
	m(M)
	{ }
};

// Matrix Scalar Sum First formation
template<typename T, typename E, size_t... dims>
const MatrixScalarSumFirst<T,E,dims...>
operator+(const T& val,
	  const MatrixExpr<E,T,dims...>& m)
{
    return MatrixScalarSumFirst<T,E,dims...>(val,m);
}



// M + 3
// T is data type of 3, E is expr type of M, T is data type of M
template<typename T, typename E, size_t... dims>
class MatrixScalarSumSecond : public MatrixExpr<MatrixScalarSumSecond<T,E,dims...>,
						T,
						dims...>
{
private:
    typedef MatrixExpr<E,T,dims...> ME;
    
    const ME& m;
    const T& val;

public:
    inline const T operator() (size_t indices[ME::numDims]) const
	{
	    return m(indices) + val;
	}

    constexpr bool touches(const void* other) const
	{
	    return m.touches(other);
	}

    constexpr bool touchesOtherIndices(const void* other) const
	{
	    return m.touchesOtherIndices(other);
	}

    MatrixScalarSumSecond(const ME& M,
			  const T& VAL) :
	m(M),
	val(VAL)
	{ }
};

// Matrix Scalar Sum Second formation
template<typename T, typename E, size_t... dims>
const MatrixScalarSumSecond<T,E,dims...>
operator+(const MatrixExpr<E,T,dims...>& m,
	  const T& val)
{
    return MatrixScalarSumSecond<T,E,dims...>(m,val);
}
