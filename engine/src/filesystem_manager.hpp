// filesystem_manager.hpp

#pragma once

#include "object.hpp"
#include "types.hpp"

namespace realware
{
    class cApplication;
        
    struct sFile
    {
        types::u8* Data = nullptr;
        types::usize DataByteSize = 0;
    };

    class mFileSystem : public cObject
    {
    public:
        explicit mFileSystem(cApplication* app);
        ~mFileSystem() = default;

        sFile* CreateDataFile(const std::string& filepath, types::boolean isString);
        void DestroyDataFile(sFile* buffer);

    private:
        cApplication* _app = nullptr;
    };
}