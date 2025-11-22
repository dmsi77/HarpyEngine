// sound_manager.hpp

#pragma once

#include <vector>
#include <string>
#include "../../thirdparty/glm/glm/glm.hpp"
#include "category.hpp"
#include "object.hpp"
#include "id_vec.hpp"
#include "types.hpp"

namespace realware
{
    class cApplication;
    class iSoundContext;

    struct sWAVStructure
    {
        types::u8 Type[5];
        types::u8 Format[5];
        types::u8 Subchunk1ID[5];
        types::u8 Subchunk2ID[5];
        types::u32 ChunkSize;
        types::u32 Subchunk1Size;
        types::u32 SampleRate;
        types::u32 ByteRate;
        types::u32 Subchunk2Size;
        types::u16 AudioFormat;
        types::u16 NumChannels;
        types::u16 BlockAlign;
        types::u16 BitsPerSample;
        types::u32 NumSamples;
        types::u32 DataByteSize;
        types::u16* Data;
    };

    class cSound : public cIdVecObject
    {
    public:
        explicit cSound(const std::string& id, cApplication* app, types::u32 source, types::u32 buffer);
        ~cSound();

        inline eCategory GetFormat() const { return _format; }
        inline sWAVStructure* GetFile() const { return _file; }
        inline types::u32 GetSource() const { return _source; }
        inline types::u32 GetBuffer() const { return _buffer; }

    private:
        eCategory _format = eCategory::SOUND_FORMAT_WAV;
        sWAVStructure* _file = nullptr;
        types::u32 _source = 0;
        types::u32 _buffer = 0;
    };

    class mSound : public cObject
    {
    public:
        mSound(cApplication* app, iSoundContext* context);
        ~mSound() = default;

        cSound* CreateSound(const std::string& id, const std::string& filename, eCategory format);
        cSound* FindSound(const std::string& id);
        void DestroySound(const std::string& id);

    private:
        cApplication* _app = nullptr;
        iSoundContext* _context = nullptr;
        cIdVec<cSound> _sounds;
    };
}