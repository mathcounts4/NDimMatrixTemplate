#pragma once

#include "MatrixExpr.hpp"
#include "Permutation.hpp"

// Reorder args template
// PAIRS = (dimension, permutation)...
//       = Pair<dim1,perm1>, Pair<dim2,perm2>, ...
// So we want to map Matrix<int,2,3,5,7> to Matrix<double,3,7,5,2>
// This would be called with E = Matrix, T = double, R = int, PAIRS = Pair<2,3>, Pair<3,0>, Pair<5,2>, Pair<7,1>
template<typename E, typename T, typename R, typename... TRIPLES>
class MatrixReorder : public MatrixExpr<MatrixReorder<E,T,R,TRIPLES...>,
					T,
					TRIPLES::second...>, private Permutation<TRIPLES::second...>
{
    typedef MatrixExpr<E,T,TRIPLES::first...> ME;
    
    const ME& m;

/*    public:
      inline const T operator() (size_t indices[ME::numDims]) const
      {

    constexpr bool touches(const void* other) const
	{
	    return m.touches(other);
	}

    constexpr bool touchesOtherIndices(const void* other) const
	{
	    return m.touches(other);
	}
*/		
};
