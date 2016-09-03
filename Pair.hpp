#pragma once

// Pair Template:
template<size_t x, size_t y>
struct Pair
{
    static constexpr size_t first = x;
    static constexpr size_t second = y;
};
