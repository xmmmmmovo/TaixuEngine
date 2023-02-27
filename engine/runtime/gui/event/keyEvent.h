//
// Created by 程祎晗 on 2023/2/24.
//

#ifndef TAIXUENGINE_KEYEVENT_H
#define TAIXUENGINE_KEYEVENT_H
#include <sstream>

#include "event.h"
#include "gui/input/keyCodes.h"

namespace taixu::event{
    class KeyEvent : public Event
    {
    public:
        inline int GetKeyCode() const {return m_KeyCode;}

        EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput);
    protected:
        KeyEvent(int keycode)
            : m_KeyCode(keycode){}
        int m_KeyCode;
    };

    class KeyPressEvent : public KeyEvent
    {
    public:
        KeyPressEvent(int keycode, int repearCount)
            : KeyEvent(keycode), m_RepeatCount(repearCount){}
        inline int GetRepeatCount() const {return m_RepeatCount;}

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "KeyPressedEvent:" << m_KeyCode<<"("<<m_RepeatCount << "repeats)";
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyPressed)
     private:
        int m_RepeatCount;
    };

    class KeyReleasedEvent : public KeyEvent
    {
    public:
        KeyReleasedEvent(int keycode)
            : KeyEvent(keycode){}

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "KeyReleasedEvent:" << m_KeyCode;
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyReleased)
    };

    class KeyTypedEvent : public KeyEvent
    {
    public:
        explicit KeyTypedEvent(int keycode)
            : KeyEvent(keycode) {}

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "KeyTypedEvent: " << m_KeyCode;
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyTyped)
    };
}

#endif//TAIXUENGINE_KEYEVENT_H
