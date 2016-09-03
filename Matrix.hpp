#pragma once

#include <iostream>
#include <stdexcept>

#include "MatrixOps.hpp"
#include "MatrixUtil.hpp"
#include "MatrixTemplate.hpp"

#ifdef DEBUG
#define CON std::cout << "--- CON --- " << __PRETTY_FUNCTION__ << std::endl;
#define DES std::cout << "--- DES --- " << __PRETTY_FUNCTION__ << std::endl;
#else
#define CON 0
#define DES 0
#endif


// Matrix Template
template<typename T, size_t... dims>
class Matrix : public MatrixExpr<Matrix<T,dims...>,T,dims...>
{
    typedef Product<dims...> P;
    typedef MatrixExpr<Matrix<T,dims...>,T,dims...> ME;
    
public:
    // Array on the stack of data
    T data[P::value];

public:

    // Array of indices
    // size_t indices[4] = [1,4,0,2];
    // M(indices) = 17.3
    inline T& operator() (size_t indices[ME::numDims])
	{
	    return data[P::getIndex(indices)];
	}

    // Array of indices
    // size_t indices[2] = [0,7];
    // x += M(indices)
    inline const T& operator() (size_t indices[ME::numDims]) const
	{
	    return data[P::getIndex(indices)];
	}
	
    // List of indices
    // M(1,4,0,2) = 17.3
    template<typename... SIZE_T>
    inline T& operator() (SIZE_T... indices)
	{
	    static constexpr size_t num_indices = sizeof...(indices);

	    if (num_indices < ME::numDims)
	    {
		throw std::invalid_argument(
		    "too few indices: " +
		    std::to_string(num_indices) +
		    " < " +
		    std::to_string(ME::numDims));
	    }
	    else if (num_indices > ME::numDims)
	    {
		throw std::invalid_argument(
		    "too many indices: " +
		    std::to_string(num_indices) +
		    " > " +
		    std::to_string(ME::numDims));
	    }

	    size_t local_indices[ME::numDims] = {static_cast<size_t>(indices)...};
	    
	    return data[P::getIndex(local_indices)];
	}

    // List of indices
    // x += M(0,7);
    template<typename... SIZE_T>
    inline const T operator() (SIZE_T... indices) const
	{
	    static constexpr size_t num_indices = sizeof...(indices);

	    if (num_indices < ME::numDims)
	    {
		throw std::invalid_argument(
		    "too few indices: " +
		    std::to_string(num_indices) +
		    " < " +
		    std::to_string(ME::numDims));
	    }
	    else if (num_indices > ME::numDims)
	    {
		throw std::invalid_argument(
		    "too many indices: " +
		    std::to_string(num_indices) +
		    " > " +
		    std::to_string(ME::numDims));
	    }

	    size_t local_indices[ME::numDims] = {static_cast<size_t>(indices)...};
	    
	    return data[P::getIndex(local_indices)];
	}

    constexpr bool touches(const void* other) const
	{
	    return (this == other);
	}

    constexpr bool touchesOtherIndices(const void* other) const
	{
	    return false;
	}

    // Default constructor: don't initialize anything
    Matrix() {CON; }

    // Destructor, don't do anything
    ~Matrix() {DES; }

    // Copy constructor
    Matrix(const Matrix& other)
	{
	    CON;
	    *this = other;
	}

    // MatrixExpr initialization
    template<typename E, typename R, size_t... otherDims>
    Matrix(const MatrixExpr<E,R,otherDims...>& other)
	{
	    CON;
	    *this = other;
	}

    // Init constructor: initialize everything to 'init'
    Matrix(const T& init)
	{
	    CON;
	    for (size_t i = 0; i < P::value; i++)
	    {
		data[i] = init;
	    }
	}

    // Copy assignment operator
    Matrix& operator=(const Matrix& other)
	{
	    if (this == &other)
	    {
		return *this;
	    }
	    
	    for (size_t i = 0; i < P::value; i++)
	    {
		data[i] = other.data[i];
	    }
	    return *this;
	}

    // MatrixExpr assignment operator
    template<typename E, typename R, size_t... otherDims>
    Matrix& operator=(const MatrixExpr<E,R,otherDims...>& other)
	{
	    if (other.touchesOtherIndices(static_cast<void*>(this)))
	    {
	        // X = expression with X touching non-identical indices
		// Cannot do this operation in-place

		// Create matrix of right side
		Matrix<R,otherDims...> fakeThis(other);

		// Check that sizes match
	        Matches<Product<otherDims...>::value,P::value>
		    compile_check; // ERROR: attempted Matrix cast has different total size
		
		for (size_t i = 0; i < P::value; i++)
		{
		    data[i] = fakeThis.data[i];
		}
	    }
	    else
	    {
		// Can do this operation in-place
		// Is more efficient to do so

		// Create reference to *this of right dimensions
		Matrix<T,otherDims...>& fakeThis(*this); // Cast this matrix to have the other's dimensions

		static constexpr size_t expected_dims = sizeof...(otherDims);

		if (expected_dims == 0)
		{
		    size_t empty[0];
		    fakeThis(empty) = other(empty);
		}
		else
		{
		    size_t local_indices[expected_dims] = {}; // 0-initialized
		    size_t max_indices[expected_dims] = {otherDims...};

		    size_t index = expected_dims - 1;
		    while (true)
		    {
			fakeThis(local_indices) = other(local_indices);
		    
			while (local_indices[index] + 1 == max_indices[index] &&
			       index > 0)
			{
			    index--;
			}

			if (local_indices[index] + 1 == max_indices[index])
			{
			    break;
			}

			local_indices[index]++;

			index++;
			while (index < expected_dims)
			{
			    local_indices[index] = 0;
			    index++;
			}
			index--;
		    }
		}
	    }
	    
	    return *this;
	}

    // Implicit size conversion:
    // Allow any conversion where the matrices have the same total size
    template<size_t... otherDims>
    inline operator Matrix<T,otherDims...>& ()
	{
	    Matches<Product<otherDims...>::value,P::value>
		compile_check; // ERROR: attempted Matrix cast has different total size
	    return reinterpret_cast<Matrix<T,otherDims...>&>(*this);
	}



    // Implicit size conversion:
    // Allow any conversion where the matrices have the same total size
    template<size_t... otherDims>
    inline operator const Matrix<T,otherDims...>& () const
	{
	    Matches<Product<otherDims...>::value,P::value>
		compile_check; // ERROR: attempted Matrix cast has different total size
	    return reinterpret_cast<const Matrix<T,otherDims...>&>(*this);
	}

    

    static inline const std::string getDims()
	{
	    return "(" + ArgsStr<dims...>::getStr() + ")";
	}
};

template<typename T, size_t... dims>
class Zero<Matrix<T,dims...> >
{
    static inline Matrix<T,dims...> get()
	{
	    return Matrix<T,dims...>(Zero<T>::get());
	}
};
/*
// Implicit size conversion:
// Allow any conversion where the matrices have the same total size
template<typename T, size_t... dims, size_t... otherDims>
operator const Matrix<T,otherDims...>& (const Matrix<T,dims...>& me)
{
    Matches<Product<otherDims...>::value,Product<dims...>::value>
	compile_check; // ERROR: attempted Matrix cast has different total size
    return reinterpret_cast<const Matrix<T,otherDims...>&>(me);
}
*/
