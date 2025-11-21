// event_manager.hpp

#pragma once

#include <vector>
#include <unordered_map>
#include <functional>
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

    class cEvent
    {
        friend class mEvent;

    public:
        cEvent(const eEventType& type, const EventFunction& function);
        ~cEvent() = default;

        void Invoke(cBuffer* const data);
        inline cGameObject* GetReceiver() const { return _receiver; }
        inline eEventType GetType() const { return _type; }
        inline EventFunction& GetFunction() const { return _function; }

    private:
        cGameObject* _receiver = nullptr;
        eEventType _type = eEventType::NONE;
        mutable EventFunction _function;
    };

    class mEvent
    {
    public:
        explicit mEvent(const cApplication* const app);
        ~mEvent() = default;
            
        void Subscribe(const cGameObject* receiver, cEvent& event);
        void Unsubscribe(const cGameObject* receiver, cEvent& event);
        void Send(const eEventType& type);
        void Send(const eEventType& type, cBuffer* const data);

    private:
        cApplication* _app = nullptr;
        std::unordered_map<eEventType, std::vector<cEvent>> _listeners;
    };
}