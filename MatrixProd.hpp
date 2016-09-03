#pragma once

#include "MatrixExpr.hpp"
#include "MatrixMultPair.hpp"
#include "MatrixTemplate.hpp"
#include "TypeZero.hpp"

// Matrix prod template (two Matrices as args)
template<typename T, typename R, typename... rest> class MatrixProd;

template<typename T, typename R, size_t... first, size_t... second>
class MatrixProd<T,R,MatrixMultPair<first,second>...> : public MatrixExpr<MatrixProd<T,R,MatrixMultPair<first,second>...>,T,MatrixMultPair<first,second>::result...>
{
    typedef const Matrix<T,first...> M1;
    typedef const Matrix<R,second...> M2;

    static constexpr size_t numDims = sizeof...(first);

private:
    M1& lhs;
    M2& rhs;

public:
    inline const T operator() (size_t indices[numDims]) const
	{
	    T result = Zero<T>::get();
	    size_t lhsIndices[numDims];
	    size_t rhsIndices[numDims];
	    static constexpr size_t maxLhs[numDims] =
		{first...};
	    static constexpr size_t maxRhs[numDims] =
		{second...};
	    static constexpr size_t max[numDims] =
		{MatrixMultPair<first,second>::max...};

	    for (size_t i = 0; i < numDims; i++)
	    {
		if (maxLhs[i] > maxRhs[i])
		{
		    lhsIndices[i] = indices[i];
		    rhsIndices[i] = 0;
		}
		else if (maxRhs[i] > maxLhs[i])
		{
		    lhsIndices[i] = 0;
		    rhsIndices[i] = indices[i];
		}
		else
		{
		    lhsIndices[i] = 0;
		    rhsIndices[i] = 0;
		}
	    }

	    size_t index = numDims - 1;
	    while (true)
	    {
		result += (lhs(lhsIndices) * rhs(rhsIndices));

		while ((maxLhs[index] != maxRhs[index] ||
			lhsIndices[index] + 1 == maxLhs[index]) &&
		       index > 0)
		{
		    index--;
		}

		if (maxLhs[index] != maxRhs[index] ||
		    lhsIndices[index] + 1 == maxLhs[index])
		{
		    break;
		}

		lhsIndices[index]++;
		rhsIndices[index]++;

		index++;
		while (index < numDims)
		{
		    if (maxLhs[index] == maxRhs[index])
		    {
		        lhsIndices[index] = 0;
			rhsIndices[index] = 0;
		    }
		    index++;
		}
		index--;
	    }

	    return result;
	}

    constexpr bool touches(const void* other) const
	{
	    return lhs.touches(other) || rhs.touches(other);
	}

    constexpr bool touchesOtherIndices(const void* other) const
	{
	    return lhs.touches(other) || rhs.touches(other);
	}

    MatrixProd(M1& LHS, M2& RHS) :
	lhs(LHS), rhs(RHS)
	{ }
};

template<typename T, size_t... first, typename R, size_t... second>
const MatrixProd<T,R,MatrixMultPair<first,second>...>
operator*(const Matrix<T,first...>& lhs,
	  const Matrix<R,second...>& rhs)
{
    return MatrixProd<T,R,MatrixMultPair<first,second>...>(lhs,rhs);
}



// Matrix prod template (Matrix, MatrixExpr)
template<typename T, typename R, typename E2, typename... rest> class MatrixProdGoodBad;

template<typename T, typename R, typename E2, size_t... first, size_t... second>
class MatrixProdGoodBad<T,R,E2,MatrixMultPair<first,second>...> :
    public MatrixProd<T,R,MatrixMultPair<first,second>...>
{
    typedef const Matrix<T,first...> M1;
    typedef const Matrix<R,second...> M2;
    
private:
    M2 my_rhs;

public:
    MatrixProdGoodBad(M1& LHS, const MatrixExpr<E2,R,second...>& RHS) :
	MatrixProd<T,R,MatrixMultPair<first,second>...>(LHS,my_rhs), my_rhs(RHS)
	{ }
};

template<typename T, size_t... first, typename R, typename E2, size_t... second>
const MatrixProdGoodBad<T,R,E2,MatrixMultPair<first,second>...>
operator*(const Matrix<T,first...>& lhs,
	  const MatrixExpr<E2,R,second...>& rhs)
{
    return MatrixProdGoodBad<T,R,E2,MatrixMultPair<first,second>...>(lhs,rhs);
}



// Matrix prod template (MatrixExpr, Matrix)
template<typename T, typename R, typename E1, typename... rest> class MatrixProdBadGood;

template<typename T, typename R, typename E1, size_t... first, size_t... second>
class MatrixProdBadGood<T,R,E1,MatrixMultPair<first,second>...> :
    public MatrixProd<T,R,MatrixMultPair<first,second>...>
{
    typedef const Matrix<T,first...> M1;
    typedef const Matrix<R,second...> M2;
    
private:
    M1 my_lhs;

public:
    MatrixProdBadGood(const MatrixExpr<E1,T,first...>& LHS, M2& RHS) :
	MatrixProd<T,R,MatrixMultPair<first,second>...>(my_lhs,RHS), my_lhs(LHS)
	{ }
};

template<typename T, size_t... first, typename R, typename E1, size_t... second>
const MatrixProdBadGood<T,R,E1,MatrixMultPair<first,second>...>
operator*(const MatrixExpr<E1,T,first...>& lhs,
	  const Matrix<R,second...>& rhs)
{
    return MatrixProdBadGood<T,R,E1,MatrixMultPair<first,second>...>(lhs,rhs);
}



// Matrix prod template (MatrixExpr, MatrixExpr)
template<typename T, typename R, typename E1, typename E2, typename... rest> class MatrixProdBadBad;

template<typename T, typename R, typename E1, typename E2, size_t... first, size_t... second>
class MatrixProdBadBad<T,R,E1,E2,MatrixMultPair<first,second>...> :
    public MatrixProd<T,R,MatrixMultPair<first,second>...>
{
    typedef const Matrix<T,first...> M1;
    typedef const Matrix<R,second...> M2;
    
private:
    M1 my_lhs;
    M2 my_rhs;

public:
    MatrixProdBadBad(const MatrixExpr<E1,T,first...>& LHS,
		     const MatrixExpr<E2,R,second...>& RHS) :
	MatrixProd<T,R,MatrixMultPair<first,second>...>(my_lhs,my_rhs),
	my_lhs(LHS),
	my_rhs(RHS)
	{ }
};

template<typename T, size_t... first, typename R, typename E1, typename E2, size_t... second>
const MatrixProdBadBad<T,R,E1,E2,MatrixMultPair<first,second>...>
operator*(const MatrixExpr<E1,T,first...>& lhs,
	  const MatrixExpr<E2,R,second...>& rhs)
{
    return MatrixProdBadBad<T,R,E1,E2,MatrixMultPair<first,second>...>(lhs,rhs);
}
