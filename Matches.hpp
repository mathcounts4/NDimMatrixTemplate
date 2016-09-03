#pragma once

// Matches Template:
template<size_t v1,size_t v2>
struct Matches;

// Only provide a template for matching values
template<size_t val>
struct Matches<val,val> { };
