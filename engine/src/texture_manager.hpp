// texture_manager.hpp

#pragma once

#include <string>
#include <vector>
#include "../../thirdparty/glm/glm/glm.hpp"
#include "id_vec.hpp"
#include "object.hpp"
#include "types.hpp"

namespace realware
{
    class iRenderContext;
    class cApplication;
    struct sTexture;

    class cTextureAtlasTexture : public cIdVecObject
    {
    public:
        cTextureAtlasTexture(const std::string& id, cApplication* app, types::boolean isNormalized, const glm::vec3& offset, const glm::vec2& size);
        ~cTextureAtlasTexture() = default;

        inline types::boolean IsNormalized() const { return _isNormalized; }
        inline const glm::vec3& GetOffset() const { return _offset; }
        inline const glm::vec2& GetSize() const { return _size; }

    private:
        types::boolean _isNormalized = types::K_FALSE;
        glm::vec3 _offset = glm::vec3(0.0f);
        glm::vec2 _size = glm::vec2(0.0f);
    };

    struct sTextureAtlasTextureGPU
    {
        glm::vec4 TextureInfo = glm::vec4(0.0f);
        types::f32 TextureLayerInfo = 0.0f;
    };

    class mTexture : public cObject
    {
    public:
        explicit mTexture(cApplication* app, iRenderContext* context);
        ~mTexture();

        cTextureAtlasTexture* CreateTexture(const std::string& id, const glm::vec2& size, types::usize channels, const types::u8* data);
        cTextureAtlasTexture* CreateTexture(const std::string& id, const std::string& filename);
        cTextureAtlasTexture* FindTexture(const std::string& id);
        void DestroyTexture(const std::string& id);

        cTextureAtlasTexture CalculateNormalizedArea(const cTextureAtlasTexture& area);

        sTexture* GetAtlas() const;
        types::usize GetWidth() const;
        types::usize GetHeight() const;
        types::usize GetDepth() const;

    protected:
        cApplication* _app = nullptr;
        iRenderContext* _context = nullptr;
        sTexture* _atlas = nullptr;
        cIdVec<cTextureAtlasTexture> _textures;
    };
}