// camera_manager.hpp

#pragma once

#include "../../thirdparty/glm/glm/glm.hpp"
#include "category.hpp"
#include "component.hpp"
#include "math.hpp"
#include "types.hpp"

namespace triton
{
    class cCamera : public cComponent
    {
        TRITON_OBJECT(cCamera)

    public:
        explicit cCamera(cContext* context);
        virtual ~cCamera() override final = default;

        void Update();
        void AddEuler(eCategory angle, types::f32 value);
        void Move(types::f32 value);
        void Strafe(types::f32 value);
        void Lift(types::f32 value);

        inline const cMatrix4& GetViewProjectionMatrix() const { return _viewProjection; }
        inline types::f32 GetMouseSensitivity() const { return _mouseSensitivity; }
        inline types::f32 GetMoveSpeed() const { return _moveSpeed; }
        inline void SetMouseSensitivity(types::f32 value) { _mouseSensitivity = value; }
        inline void SetMoveSpeed(types::f32 value) { _moveSpeed = value; }

    private:
        cTransform _transform;
        cVector3 _euler = cVector3(0.0f);
        cVector3 _direction = cVector3(0.0f);
        cMatrix4 _view = cMatrix4(1.0f);
        cMatrix4 _projection = cMatrix4(1.0f);
        cMatrix4 _viewProjection = cMatrix4(1.0f);
        types::f32 _fov = 60.0f;
        types::f32 _zNear = 0.01f;
        types::f32 _zFar = 100.0f;
        types::f32 _mouseSensitivity = 1.0f;
        types::f32 _moveSpeed = 1.0f;
        types::boolean _isMoving = types::K_FALSE;
        cVector2 _cursorPosition = cVector2(0.0f);
        cVector2 _prevCursorPosition = _cursorPosition;
    };
}