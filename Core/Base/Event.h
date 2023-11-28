#pragma once

#include "./Types.h"

namespace Abs 
{
    enum class EventType 
    {
        None = 0,
        KeyPressed, KeyReleased,
        MouseButtonPressed, MouseButtonReleased, MouseScrolled, MouseMoved
    };

    #define EVENT_TYPE(type) static EventType GetStaticEventType() { return EventType::type; }

    class Event 
    {
        public:
        virtual EventType GetEventType() = 0;

        bool Handled = false;
    };
}

