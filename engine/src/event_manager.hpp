// event_manager.hpp

#pragma once

#include <memory>
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
    
    enum class eEvent
    {
        NONE,
        KEY_PRESS
    };

    using EventFunction = std::function<void(cBuffer* const data)>;

    class cEvent : public cObject
    {
        friend class mEvent;

    public:
        cEvent(eEvent type, EventFunction&& function);
        ~cEvent() = default;

        void Invoke(cBuffer* data);
        inline cGameObject* GetReceiver() const { return _receiver; }
        inline eEvent GetEventType() const { return _type; }
        inline std::shared_ptr<EventFunction> GetFunction() const { return _function; }

    private:
        cGameObject* _receiver = nullptr;
        eEvent _type = eEvent::NONE;
        mutable std::shared_ptr<EventFunction> _function;
    };

    class mEvent : public cObject
    {
    public:
        explicit mEvent(cApplication* app);
        ~mEvent() = default;
        
        void Subscribe(cGameObject* receiver, cEvent& event);
        void Unsubscribe(const cGameObject* receiver, const cEvent& event);
        void Send(eEvent type);
        void Send(eEvent type, cBuffer* data);

    private:
        cApplication* _app = nullptr;
        std::unordered_map<eEvent, std::vector<cEvent>> _listeners;
    };
}