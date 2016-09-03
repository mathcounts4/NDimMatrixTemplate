#pragma once

#include "MatrixExpr.hpp"
#include <stdexcept>

// 3 / M
// T is data type of 3, E is expr type of M, T is data type of M
template<typename T, typename E, size_t... dims>
class MatrixScalarDivFirst : public MatrixExpr<MatrixScalarDivFirst<T,E,dims...>,
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
	    T item(m(indices));
	    T zero(Zero<T>::get());
	    if (item == zero)
	    {
		throw std::overflow_error("Divide by zero exception");
	    }
	    return val / item;
	}

    constexpr bool touches(const void* other) const
	{
	    return m.touches(other);
	}

    constexpr bool touchesOtherIndices(const void* other) const
	{
	    return m.touchesOtherIndices(other);
	}

    MatrixScalarDivFirst(const T& VAL,
			 const ME& M) :
	val(VAL),
	m(M)
	{ }
};

// Matrix Scalar Div First formation
template<typename T, typename E, size_t... dims>
const MatrixScalarDivFirst<T,E,dims...>
operator/(const T& val,
	  const MatrixExpr<E,T,dims...>& m)
{
    return MatrixScalarDivFirst<T,E,dims...>(val,m);
}



// M / 3
// T is data type of 3, E is expr type of M, T is data type of M
template<typename T, typename E, size_t... dims>
class MatrixScalarDivSecond : public MatrixExpr<MatrixScalarDivSecond<T,E,dims...>,
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
	    return m(indices) / val;
	}

    constexpr bool touches(const void* other) const
	{
	    return m.touches(other);
	}

    constexpr bool touchesOtherIndices(const void* other) const
	{
	    return m.touchesOtherIndices(other);
	}

    MatrixScalarDivSecond(const ME& M,
			  const T& VAL) :
	m(M),
	val(VAL)
	{ }
};

// Matrix Scalar Div Second formation
template<typename T, typename E, size_t... dims>
const MatrixScalarDivSecond<T,E,dims...>
operator/(const MatrixExpr<E,T,dims...>& m,
	  const T& val)
{
    T zero(Zero<T>::get());
    if (val == zero)
    {
	throw std::overflow_error("Divide by zero exception");
    }
    MatrixScalarDivSecond<T,E,dims...> ans(m,val);
    return ans;
}
