// thread_pool.hpp

#pragma once

#include <thread>
#include <queue>
#include <functional>
#include <mutex>
#include <memory>
#include <atomic>
#include "types.hpp"

namespace realware
{
    namespace app
    {
        class cApplication;
    }

    namespace utils
    {
        class cBuffer;

        using TaskFunction = std::function<void(cBuffer* const data)>;

        class cTask
        {
        public:
            cTask() = default;
            explicit cTask(const cBuffer* const data, TaskFunction&& function);
            ~cTask() = default;

            void Run();
            inline cBuffer* GetData() { return _data; }
            inline std::shared_ptr<TaskFunction> GetFunction() { return _function; }

        private:
            cBuffer* _data = nullptr;
            std::shared_ptr<TaskFunction> _function;
        };

        class mThread
        {
        public:
            explicit mThread(const app::cApplication* const app, const types::usize threadCount = std::thread::hardware_concurrency());
            ~mThread();
            
            void Submit(cTask& task);
            void Pause();
            void Resume();
            void Stop();

        private:
            app::cApplication* _app = nullptr;
            std::vector<std::thread> _threads = {};
            std::queue<cTask> _tasks = {};
            std::mutex _mtx;
            std::condition_variable _cv;
            std::atomic<types::boolean> _pause = types::K_FALSE;
            types::boolean _stop = types::K_FALSE;
        };
    }
}