#pragma once

namespace {
    // Has template
    template<size_t find, size_t... args>
    struct Has;

    // Has found it
    template<size_t find, size_t... args>
    struct Has<find,find,args...>
    { };

    // Has not found it
    template<size_t find, size_t other, size_t... args>
    struct Has<find,other,args...> : Has<find,args...>
    { };



    // HasAllAtMost template
    template<size_t find, size_t... args>
    struct HasAllAtMost : Has<find,args...>, HasAllAtMost<find-1,args...>
    { };

    // HasAllAtMost base case
    template<size_t... args>
    struct HasAllAtMost<0,args...> : Has<0,args...>
    { };
}



// Permutation template
template<size_t... args>
struct Permutation : HasAllAtMost<sizeof...(args)-1,args...>
{ };

// Permutation 0 elements case
template<>
struct Permutation<>
{ };
