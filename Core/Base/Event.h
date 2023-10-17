#pragma once

#include "./Types.h"
#include <string>

namespace Abs {
    enum class EventType {
        None = 0,
        KeyPressed,
        KeyReleased,
        MouseButtonPressed,
        MouseButtonReleased,
        MouseScrolled,
        MouseMoved
    };

    #define EVENT_TYPE(type) static EventType GetStaticEventType() { return EventType::type; }

    class Event {
        public:
            virtual ~Event() = default;

            virtual EventType GetEventType() = 0;

            bool Handled = false;
    };
}

