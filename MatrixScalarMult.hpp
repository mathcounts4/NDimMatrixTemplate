#pragma once

#include "MatrixExpr.hpp"

// 3 * M
// T is data type of 3, E is expr type of M, T is data type of M
template<typename T, typename E, size_t... dims>
class MatrixScalarMultFirst : public MatrixExpr<MatrixScalarMultFirst<T,E,dims...>,
					       T,
					       dims...>
{
    typedef MatrixExpr<E,T,dims...> ME;
    
private:
    const T& val;
    const ME& m;

public:
    inline const T operator() (size_t indices[ME::numDims]) const
	{
	    return val * m(indices);
	}

    constexpr bool touches(const void* other) const
	{
	    return m.touches(other);
	}

    constexpr bool touchesOtherIndices(const void* other) const
	{
	    return m.touchesOtherIndices(other);
	}

    MatrixScalarMultFirst(const T& VAL,
			 const ME& M) :
	val(VAL),
	m(M)
	{ }
};

// Matrix Scalar Mult First formation
template<typename T, typename E, size_t... dims>
const MatrixScalarMultFirst<T,E,dims...>
operator*(const T& val,
	  const MatrixExpr<E,T,dims...>& m)
{
    return MatrixScalarMultFirst<T,E,dims...>(val,m);
}



// M * 3
// T is data type of 3, E is expr type of M, T is data type of M
template<typename T, typename E, size_t... dims>
class MatrixScalarMultSecond : public MatrixExpr<MatrixScalarMultSecond<T,E,dims...>,
						T,
						dims...>
{
    typedef MatrixExpr<E,T,dims...> ME;
    
private:
    const ME& m;
    const T& val;

public:
    inline const T operator() (size_t indices[ME::numDims]) const
	{
	    return m(indices) * val;
	}

    constexpr bool touches(const void* other) const
	{
	    return m.touches(other);
	}

    constexpr bool touchesOtherIndices(const void* other) const
	{
	    return m.touchesOtherIndices(other);
	}

    MatrixScalarMultSecond(const ME& M,
			  const T& VAL) :
	m(M),
	val(VAL)
	{ }
};

// Matrix Scalar Mult Second formation
template<typename T, typename E, size_t... dims>
const MatrixScalarMultSecond<T,E,dims...>
operator*(const MatrixExpr<E,T,dims...>& m,
	  const T& val)
{
    return MatrixScalarMultSecond<T,E,dims...>(m,val);
}
