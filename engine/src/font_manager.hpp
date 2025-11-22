// font_manager.hpp

#pragma once

#include <unordered_map>
#include <ft2build.h>
#include FT_FREETYPE_H
#include "../../thirdparty/glm/glm/glm.hpp"
#include "object.hpp"
#include "types.hpp"

namespace realware
{
    class iRenderContext;
    class cApplication;
    struct sTexture;

    struct sGlyph
    {
        types::u8 Character = 0;
        types::s32 Width = 0;
        types::s32 Height = 0;
        types::s32 Left = 0;
        types::s32 Top = 0;
        types::f32 AdvanceX = 0.0f;
        types::f32 AdvanceY = 0.0f;
        types::s32 AtlasXOffset = 0;
        types::s32 AtlasYOffset = 0;
        void* BitmapData = nullptr;
    };

    struct sFont
    {
        FT_Face Font = {};
        types::usize GlyphCount = 0;
        types::usize GlyphSize = 0;
        types::usize OffsetNewline = 0;
        types::usize OffsetSpace = 0;
        types::usize OffsetTab = 0;
        std::unordered_map<types::u8, sGlyph> Alphabet = {};
        sTexture* Atlas = nullptr;
    };

    struct sText
    {
        sFont* Font = nullptr;
        std::string Text = "";
    };

    class mFont : public cObject
    {
    public:
        mFont(cApplication* app, iRenderContext* context);
        ~mFont();

        sFont* CreateFontTTF(const std::string& filename, types::usize glyphSize);
        sText* CreateText(const sFont* font, const std::string& text);
        void DestroyFontTTF(sFont* font);
        void DestroyText(sText* text);
            
        types::f32 GetTextWidth(sFont* font, const std::string& text) const;
        types::f32 GetTextHeight(sFont* font, const std::string& text) const;
        types::usize GetCharacterCount(const std::string& text) const;
        types::usize GetNewlineCount(const std::string& text) const;

        static constexpr types::usize K_MAX_ATLAS_WIDTH = 2048;

    private:
        cApplication* _app = nullptr;
        types::boolean _initialized = types::K_FALSE;
        iRenderContext* _context = nullptr;
        FT_Library _lib = {};
    };
}