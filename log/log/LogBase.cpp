#include "LogBase.hpp"

LogBase::LogBase(const std::wstring& directory):
    directory(directory), day(-1), timer(Timer::YYYY_MM_DD, Timer::HIDE_WEEKDAY), isExist(false)
{
    FixDirectory();
}

void LogBase::Initialize(const std::wstring& param)
{
    directory = param;
    FixDirectory();
    file = Path();
}

bool LogBase::Update()
{
    int temp = Timer::ReadSystemTime().tm_mday;

    TypeLock<LogBase>::Spin spin;

    if(day - temp) {
        day      = temp;   // update date
        file     = Path(); // udpate file name
        int code = New();  // craate directory

        if(code) {
            throw std::runtime_error(std::strerror(code));
        }
        return true;
    }
    return false;
}

int LogBase::New()
{
    TypeLock<LogBase>::Spin lock;

    if(isExist == false) {
        std::error_code code;

        // create folder, c++17
        std::filesystem::path dir = directory;
        std::filesystem::create_directories(dir, code);
        if(code) {
            return code.value();
        }
        isExist = true;
    }
}

std::wstring LogBase::Path()
{
    std::string timestamp = timer.StampingFromSystemDate();
    return directory + std::wstring(timestamp.begin(), timestamp.end()) + L".log";
}

void LogBase::FixDirectory()
{
    size_t loop = directory.size();
    FAST_LOOP(
        loop,
        int i = 0,
        if(directory[i] == '\\') { directory[i] = '/'; } ++i);

    if(directory.back() != '/') {
        directory.push_back('/');
    }
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