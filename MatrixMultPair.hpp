#pragma once

// MatrixMultPair Template:
template<size_t x, size_t y>
struct MatrixMultPair;

// MatrixMultPair with same values
template<size_t x>
struct MatrixMultPair<x,x>
{
    static constexpr size_t first = x;
    static constexpr size_t second = x;
    static constexpr size_t result = 1;
    static constexpr size_t max = x;
};

// MatrixMultPair with 1
template<size_t x>
struct MatrixMultPair<x,1>
{
    static constexpr size_t first = x;
    static constexpr size_t second = 1;
    static constexpr size_t result = x;
    static constexpr size_t max = 1;
};

// MatrixMultPair with 1
template<size_t x>
struct MatrixMultPair<1,x>
{
    static constexpr size_t first = 1;
    static constexpr size_t second = x;
    static constexpr size_t result = x;
    static constexpr size_t max = 1;
};

// MatrixMultPair with both 1's
template<>
struct MatrixMultPair<1,1>
{
    static constexpr size_t first = 1;
    static constexpr size_t second = 1;
    static constexpr size_t result = 1;
    static constexpr size_t max = 1;
};
