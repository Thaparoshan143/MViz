#pragma once

#include "./Event.h"

namespace Abs 
{
    typedef enum MouseCode
    {
        BUTTON_LEFT = 0,
        BUTTON_RIGHT,
        BUTTON_MIDDLE
    };

    class MouseMovedEvent : public Event 
    {
        public:
        MouseMovedEvent(double x, double y) : m_mouseX(x), m_mouseY(y) {}

        EVENT_TYPE(MouseMoved)
        EventType GetEventType() override { return EventType::MouseMoved; }

        private:
        double m_mouseX, m_mouseY;
    };

    class MouseButtonEvent : public Event 
    {
        public:
        MouseButtonEvent(MouseCode button) : m_button(button) {}
        MouseCode GetMouseButton() { return m_button; }

        private:
        MouseCode m_button;
    };

    class MouseButtonPressedEvent : public MouseButtonEvent 
    {
        public:
        MouseButtonPressedEvent(MouseCode button) : MouseButtonEvent(button) {}

        EVENT_TYPE(MouseButtonPressed) 
        EventType GetEventType() override { return EventType::MouseButtonPressed; }
    };

    class MouseButtonReleasedEvent : public MouseButtonEvent 
    {
        public:
        MouseButtonReleasedEvent(MouseCode button) : MouseButtonEvent(button) {}

        EVENT_TYPE(MouseButtonReleased)
        EventType GetEventType() override { return EventType::MouseButtonReleased; }
    };
}


