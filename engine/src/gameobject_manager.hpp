// gameobject_manager.hpp

#pragma once

#include <vector>
#include <string>
#include "../../thirdparty/glm/glm/glm.hpp"
#include "category.hpp"
#include "id_vec.hpp"
#include "types.hpp"

namespace realware
{
    class mPhysics;
    class cMemoryPool;
    class cPhysicsController;
    class cPhysicsActor;
    class cPhysicsSimulationScene;
    class cPhysicsSubstance;
    class cApplication;
    class cMaterial;
    struct sVertexBufferGeometry;
    struct sLight;
    struct sTransform;
    struct sText;
    
    class cGameObject : public cIdVecObject
    {
        friend class mGameObject;

    public:
        explicit cGameObject(const std::string& id, const cApplication* const app, const cMemoryPool* const memoryPool);
        ~cGameObject() = default;
            
        inline std::string GetID() const { return _id; }
        inline types::boolean GetVisible() const { return _isVisible; }
        inline types::boolean GetOpaque() const { return _isOpaque; }
        inline sVertexBufferGeometry* GetGeometry() const { return _geometry; }
        inline types::boolean GetIs2D() const { return _is2D; }
        const glm::vec3& GetPosition() const;
        const glm::vec3& GetRotation() const;
        const glm::vec3& GetScale() const;
        inline glm::mat4 GetWorldMatrix() const { return _world; }
        inline glm::mat4 GetViewProjectionMatrix() const { return _viewProjection; }
        inline sTransform* GetTransform() const { return _transform; }
        inline cMaterial* GetMaterial() const { return _material; }
        inline sText* GetText() const { return _text; }
        inline sLight* GetLight() const { return _light; }
        inline cPhysicsActor* GetPhysicsActor() const { return _actor; }
        inline cPhysicsController* GetPhysicsController() const { return _controller; }

        inline void SetVisible(const types::boolean isVisible) { _isVisible = isVisible; }
        inline void SetOpaque(const types::boolean isOpaque) { _isOpaque = isOpaque; }
        inline void SetGeometry(const sVertexBufferGeometry* const geometry) { _geometry = (sVertexBufferGeometry*)geometry; }
        inline void SetIs2D(const types::boolean is2D) { _is2D = is2D; }
        void SetPosition(const glm::vec3& position);
        void SetRotation(const glm::vec3& rotation);
        void SetScale(const glm::vec3& scale);
        inline void SetWorldMatrix(const glm::mat4& world) { _world = world; }
        inline void SetViewProjectionMatrix(const glm::mat4& viewProjection) { _viewProjection = viewProjection; }
        inline void SetMaterial(const cMaterial* const material) { _material = (cMaterial*)material; }
        inline void SetText(const sText* const text) { _text = (sText*)text; }
        inline void SetLight(const sLight* const light) { _light = (sLight*)light; }
        void SetPhysicsActor(const eCategory& staticOrDynamic, const eCategory& shapeType, const cPhysicsSimulationScene* const scene, const cPhysicsSubstance* const substance, const types::f32 mass);
        void SetPhysicsController(const types::f32 eyeHeight, const types::f32 height, const types::f32 radius, const glm::vec3& up, const cPhysicsSimulationScene* const scene, const cPhysicsSubstance* const substance);

    private:
        types::boolean _isVisible = types::K_TRUE;
        types::boolean _isOpaque = types::K_TRUE;
        sVertexBufferGeometry* _geometry = nullptr;
        types::boolean _is2D = types::K_FALSE;
        glm::mat4 _world = glm::mat4(1.0f);
        glm::mat4 _viewProjection = glm::mat4(1.0f);
        sTransform* _transform = nullptr;
        cMaterial* _material = nullptr;
        sText* _text = nullptr;
        sLight* _light = nullptr;
        cPhysicsActor* _actor = nullptr;
        cPhysicsController* _controller = nullptr;
    };

    class mGameObject
    {
    public:
        explicit mGameObject(const cApplication* const app);
        ~mGameObject() = default;

        cGameObject* CreateGameObject(const std::string& id);
        cGameObject* FindGameObject(const std::string& id);
        void DestroyGameObject(const std::string& id);

        inline cIdVec<cGameObject>& GetObjects() const { return _gameObjects; }

    private:
        cApplication* _app = nullptr;
        types::usize _maxGameObjectCount = 0;
        types::usize _gameObjectCount = 0;
        mutable cIdVec<cGameObject> _gameObjects;
    };
}