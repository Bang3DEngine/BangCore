#pragma once

#include <stack>

namespace Bang
{
template <class T>
struct StackAndValue
{
    T currentValue;
    std::stack<T> stack;
};
}
