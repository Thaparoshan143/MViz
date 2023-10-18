#pragma once

#include "./Event.h"

namespace Abs 
{
    class KeyButtonEvent : public Event 
    {
        public:
        KeyButtonEvent(int keycode): m_keycode{keycode} {}
        int GetKeyButton() {    return m_keycode;   }

        private:
        int m_keycode;
    };

    class KeyButtonPressedEvent : public KeyButtonEvent 
    {
        public:
        KeyButtonPressedEvent(int button) : KeyButtonEvent(button) {}

        EVENT_TYPE(KeyPressed) 
        EventType GetEventType() override { return EventType::KeyPressed; }
    };

    class KeyButtonReleasedEvent : public KeyButtonEvent 
    {
        public:
        KeyButtonReleasedEvent(int button) : KeyButtonEvent(button) {}

        EVENT_TYPE(KeyReleased)
        EventType GetEventType() override { return EventType::KeyReleased; }
    };
}


