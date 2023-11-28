#pragma once

#include"./Types.h"

namespace Abs
{
    enum AppRef
    {
        SELF = 1,
        WINDOW = 2,
        UI = 3
    };

    class Application
    {
        public:
        Application() {}

        virtual void Initialize() = 0;
        virtual void Loop() = 0;
        virtual void* GetReference(AppRef appRef) = 0;
    };
}