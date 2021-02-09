#pragma  once

#include "dynalo/dynalo.hpp"

#include <thread>
#include <unordered_map>
#include <type_traits>
#include <filesystem>
namespace fs = std::filesystem;

#include <chrono>
using namespace std::chrono_literals;


typedef void (*FunctionPointer)(void);
static const char* OUTPUT_DIR = "./HotReloadedDLL/";

struct DLLHotReloader
{
    mutable std::unordered_map<std::string, FunctionPointer> mFunctionCache;
    dynalo::library* mLibrary;
    fs::file_time_type mLastUpdateTime;
    std::string mInputPath;
    std::string mOutputPath;

    fs::file_time_type lib_update_time;
    /*
    *  Name without extension
    *  @throw If dll can't be loaded
    */ 
    DLLHotReloader(const std::string& path)
        : mLibrary(nullptr)
    {
        // Directory where dll copies are stored
        if (!std::filesystem::exists(OUTPUT_DIR))
        {
            std::filesystem::create_directory(OUTPUT_DIR);
        }

        std::string name;
        std::string input_dir;
        int pos = path.find_last_of('/') + 1;

        if (pos != std::string::npos)
        {
            name = dynalo::to_native_name(path.substr(pos));
            input_dir = path.substr(0, pos);
        }
        else {
            name = dynalo::to_native_name(path);
        }

        mInputPath = input_dir + name;
        mOutputPath = OUTPUT_DIR + name;
        CheckForUpdate();
    }

    ~DLLHotReloader()
    {
        delete mLibrary;
    }

    /*
    *  @throw If dll can't be reloaded
    */
    void CheckForUpdate()
    {
        try
        {
            lib_update_time = fs::last_write_time(dynalo::to_native_name("../ui/UI").c_str());
        }
        catch (const std::exception& e)
        {}

        if (mLastUpdateTime != lib_update_time || mLibrary == nullptr)
        {
            std::this_thread::sleep_for(1ms);

            delete mLibrary;
            mLibrary = nullptr;
            fs::remove(mOutputPath);
            fs::copy(mInputPath, mOutputPath);
            mLibrary = new dynalo::library(mOutputPath);
            mLastUpdateTime = lib_update_time;
        }

    }

    template <typename FunctionSignature, typename ...Args>
    auto Call(const std::string& name, Args... args)
    {
        if (mFunctionCache.count(name))
        {
            auto func = reinterpret_cast<FunctionSignature*>(mFunctionCache[name]);
            return func(args...);
        }
        else {
            auto func = mLibrary->get_function<FunctionSignature>(name);
            mFunctionCache[name] = reinterpret_cast<FunctionPointer>(func);
            return func(args...);
        }
    }

    /*
    *  After hot reloading function pointer will be invalid
    */
    template <typename FunctionSignature>
    FunctionSignature* Get(const std::string& name)
    {
        return mLibrary->get_function<FunctionSignature>(name);
    }

};