// event_manager.hpp

#pragma once

#include <vector>
#include <unordered_map>
#include <functional>
#include "object.hpp"
#include "types.hpp"

namespace realware
{
    class cApplication;
    class cGameObject;
    class cBuffer;
    
    enum class eEventType
    {
        NONE,
        KEY_PRESS
    };

    using EventFunction = std::function<void(cBuffer* const data)>;

    class cEvent : public cObject
    {
        friend class mEvent;

    public:
        cEvent(eEventType type, const EventFunction& function);
        ~cEvent() = default;

        void Invoke(cBuffer* data);
        inline cGameObject* GetReceiver() const { return _receiver; }
        inline eEventType GetType() const { return _type; }
        inline EventFunction& GetFunction() const { return _function; }

    private:
        cGameObject* _receiver = nullptr;
        eEventType _type = eEventType::NONE;
        mutable EventFunction _function;
    };

    class mEvent : public cObject
    {
    public:
        explicit mEvent(cApplication* app);
        ~mEvent() = default;
            
        void Subscribe(const cGameObject* receiver, cEvent& event);
        void Unsubscribe(const cGameObject* receiver, cEvent& event);
        void Send(eEventType type);
        void Send(eEventType type, cBuffer* data);

    private:
        cApplication* _app = nullptr;
        std::unordered_map<eEventType, std::vector<cEvent>> _listeners;
    };
}