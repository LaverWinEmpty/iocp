#include "LogBase.hpp"

LogBase::LogBase(const std::wstring& directory):
    directory(directory), day(-1), timer(Timer::YYYY_MM_DD, Timer::HIDE_WEEKDAY), isExist(false)
{
    Initialize(directory);
}

void LogBase::Initialize(const std::wstring& param)
{
    directory = param;

    size_t loop = directory.size();
    FAST_LOOP(
        loop,
        int i = 0,
        if(directory[i] == '\\') { directory[i] = '/'; } ++i);

    isExist = false;

    if(directory.back() != '/') {
        directory.push_back('/');
    }
}

bool LogBase::Update()
{
    int temp = Timer::ReadSystemTime().tm_mday;
    if(day - temp) {
        day = temp;
        if(!New()) {
            throw std::runtime_error("failed to create the new file");
        }
        return true;
    }
    return false;
}

bool LogBase::New()
{
    TypeLock<LogBase>::Mutex lock;
    if(isExist == false) {
        // create folder, c++17
        std::filesystem::path dir = directory;
        if(!std::filesystem::exists(dir)) {
            std::filesystem::create_directories(dir);
            if(!std::filesystem::exists(dir)) {
                return false;
            }
        }
        isExist = true;
    }

    // create file
    std::ofstream file(Path(), std::ios_base::out | std::ios_base::app);
    if(!file.is_open()) {
        return false;
    }
    file.close();
    return true;
}

std::wstring LogBase::Path()
{
    std::string timestamp = timer.StampingFromSystemDate();
    return directory + std::wstring(timestamp.begin(), timestamp.end()) + L".log";
}

void LogBase::SetLocaleConsole(IN const char* param)
{
    std::cout.imbue(std::locale(param));
    std::wcout.imbue(std::locale(param));
}

void LogBase::SetLocaleGlobal(const char* param)
{
    std::locale::global(std::locale(param));
}