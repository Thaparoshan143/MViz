#include<iostream>

namespace Util
{
    template<class T>
    class Vec2
    {
        Vec2() : x(0), y(0) {}
        Vec2(T x, T y) : x(x), y(y) {}
        Vec2(T c) : x(c), y(c) {}
    };
}