#pragma once

#include<iostream>

#include"./Types.h"

namespace Abs
{
    class Application
    {
        public:
        Application() {}

        virtual void Initialize() = 0;
        virtual void Loop() = 0;
    };
}