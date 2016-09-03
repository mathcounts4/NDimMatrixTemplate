#pragma once

// Get argument Template: GetArg<index,args...>::value
template<size_t index, size_t arg0, size_t... args>
struct GetArg;

// Base case: index = 0
template<size_t arg0, size_t... args>
struct GetArg<0,arg0,args...>
{
public:
    constexpr size_t value = arg0;
};

// Recursive case: chop off first arg and keep going
template<size_t index, size_t arg0, size_t... args>
struct GetArg
{
public:
    constexpr size_t value = Get_arg<index-1,args...>::value;
};
