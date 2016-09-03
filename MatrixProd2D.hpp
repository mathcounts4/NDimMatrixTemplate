#pragma once

#include "MatrixExpr.hpp"
#include "TypeZero.hpp"
#include "Matrix.hpp"

template<typename T, size_t X1, size_t X2, typename R, size_t Y2>
class MatrixProd2D : public MatrixExpr<MatrixProd2D<T,X1,X2,R,Y2>,T,X1,Y2>
{
    // If values are used more than once, the following should be Matrix references
    // If used only once, they can be any MatrixExpr
    typedef const Matrix<T,X1,X2> M1;
    typedef const Matrix<R,X2,Y2> M2;

private:
    M1& lhs;
    M2& rhs;

public:
    inline const T operator() (size_t indices[2]) const
	{
	    T result = Zero<T>::get();
	    
	    size_t lhsIndices[2] = {indices[0],0};
	    size_t rhsIndices[2] = {0,indices[1]};

	    for (size_t i = 0; i < X2; i++)
	    {
		lhsIndices[1] = i;
		rhsIndices[0] = i;
		result += (lhs(lhsIndices) * rhs(rhsIndices));
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

    MatrixProd2D(M1& LHS, M2& RHS) :
	lhs(LHS), rhs(RHS)
	{ }
};

template<typename T, size_t X1, size_t X2, typename R, size_t Y2>
const MatrixProd2D<T,X1,X2,R,Y2>
operator*(const Matrix<T,X1,X2>& lhs,
	  const Matrix<R,X2,Y2>& rhs)
{
    return MatrixProd2D<T,X1,X2,R,Y2>(lhs,rhs);
}

template<typename T, size_t X2, typename R, size_t Y2>
const MatrixProd2D<T,1,X2,R,Y2>
operator*(const Matrix<T,X2>& lhs,
	  const Matrix<R,X2,Y2>& rhs)
{
    return MatrixProd2D<T,1,X2,R,Y2>(lhs,rhs);
}

template<typename T, size_t X1, size_t X2, typename R>
const MatrixProd2D<T,X1,X2,R,1>
operator*(const Matrix<T,X1,X2>& lhs,
	  const Matrix<R,X2>& rhs)
{
    return MatrixProd2D<T,X1,X2,R,1>(lhs,rhs);
}



// Matrix prod 2D template (Matrix, MatrixExpr)
template<typename T, size_t X1, size_t X2, typename R, size_t Y2, typename E2>
class MatrixProd2DGoodBad :
    public MatrixProd2D<T,X1,X2,R,Y2>
{
    typedef const Matrix<T,X1,X2> M1;
    typedef const Matrix<R,X2,Y2> M2;

private:
    M2 my_rhs;

public:
    MatrixProd2DGoodBad(M1& LHS, const MatrixExpr<E2,R,X2,Y2>& RHS) :
	MatrixProd2D<T,X1,X2,R,Y2>(LHS,my_rhs), my_rhs(RHS)
	{ }
};

template<typename T, size_t X1, size_t X2, typename R, size_t Y2, typename E2>
const MatrixProd2DGoodBad<T,X1,X2,R,Y2,E2>
operator*(const Matrix<T,X1,X2>& lhs,
	  const MatrixExpr<E2,R,X2,Y2>& rhs)
{
    return MatrixProd2DGoodBad<T,X1,X2,R,Y2,E2>(lhs,rhs);
}



// Matrix prod 2D template (MatrixExpr, Matrix)
template<typename T, size_t X1, size_t X2, typename R, size_t Y2, typename E1>
class MatrixProd2DBadGood :
    public MatrixProd2D<T,X1,X2,R,Y2>
{
    typedef const Matrix<T,X1,X2> M1;
    typedef const Matrix<R,X2,Y2> M2;

private:
    M1 my_lhs;

public:
    MatrixProd2DBadGood(const MatrixExpr<E1,T,X1,X2>& LHS, M2& RHS) :
	MatrixProd2D<T,X1,X2,R,Y2>(my_lhs,RHS), my_lhs(LHS)
	{ }
};

template<typename T, size_t X1, size_t X2, typename R, size_t Y2, typename E1>
const MatrixProd2DBadGood<T,X1,X2,R,Y2,E1>
operator*(const MatrixExpr<E1,T,X1,X2>& lhs,
	  const Matrix<R,X2,Y2>& rhs)
{
    return MatrixProd2DBadGood<T,X1,X2,R,Y2,E1>(lhs,rhs);
}



// Matrix prod 2D template (MatrixExpr, MatrixExpr)
template<typename T, size_t X1, size_t X2, typename R, size_t Y2, typename E1, typename E2>
class MatrixProd2DBadBad :
    public MatrixProd2D<T,X1,X2,R,Y2>
{
    typedef const Matrix<T,X1,X2> M1;
    typedef const Matrix<R,X2,Y2> M2;

private:
    M1 my_lhs;
    M2 my_rhs;

public:
    MatrixProd2DBadBad(const MatrixExpr<E1,T,X1,X2>& LHS,
			const MatrixExpr<E2,R,X2,Y2>& RHS) :
	MatrixProd2D<T,X1,X2,R,Y2>(my_lhs,my_rhs), my_lhs(LHS), my_rhs(RHS)
	{ }
};

template<typename T, size_t X1, size_t X2, typename R, size_t Y2, typename E1, typename E2>
const MatrixProd2DBadBad<T,X1,X2,R,Y2,E1,E2>
operator*(const MatrixExpr<E1,T,X1,X2>& lhs,
	  const MatrixExpr<E2,R,X2,Y2>& rhs)
{
    return MatrixProd2DBadBad<T,X1,X2,R,Y2,E1,E2>(lhs,rhs);
}
