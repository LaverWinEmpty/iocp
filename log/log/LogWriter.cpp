/**
 * @file    LogWriter.cpp
 * @author  LaverWinEmpty@google.com
 * @brief   log writer definition
 * @version 1.0
 * @date    2023-10-22
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "LogWriter.hpp"

ILoggable::ILoggable(const char* to): a(to), w(a.begin(), a.end()) {}

void ILoggable::OnWrite(std::ostream& os)
{
    os << a;
}

void ILoggable::OnWrite(std::ofstream& ofs)
{
    ofs << a;
}

void ILoggable::OnWrite(std::wostream& wos)
{
    wos << w;
}

void ILoggable::OnWrite(std::wofstream& wfos)
{
    wfos << w;
}

LogWriter::LogWriter():
    directory(L"./Log/"), day(Timer::ReadSystemTime().tm_mday), timer(Timer::YYYY_MM_DD, Timer::HIDE_WEEKDAY)
{
    New();
}

LogWriter::LogWriter(const std::wstring& dir, const char* locale):
    day(Timer::ReadSystemTime().tm_mday), timer(Timer::YYYY_MM_DD, Timer::HIDE_WEEKDAY)
{
    ChangeDirectory(dir);
}

LogWriter::~LogWriter()
{
    fout.close();
}

void LogWriter::ChangeDirectory(const std::wstring& param)
{
    directory = param;

    size_t loop = directory.size();
    FAST_LOOP(
        loop,
        int i = 0,
        if(directory[i] == '\\') { directory[i] = '/'; } ++i);

    char last = directory.back();
    if(last != '/' && last != '\\') {
        directory.push_back('/');
    }

    New();
}

void LogWriter::SetLocale(IN const char* param)
{
    fout.imbue(std::locale(param));
}

void LogWriter::SetLocaleConsole(IN const char* param)
{
    std::cout.imbue(std::locale(param));
    std::wcout.imbue(std::locale(param));
}

void LogWriter::SetLocaleGlobal(const char* param)
{
    std::locale::global(std::locale(param));
}

void LogWriter::New()
{
    CreateDirectoryW(directory.c_str(), nullptr);

    if(fout.is_open()) {
        fout.close();
    }

    std::string timestamp = timer.StampingFromSystemDate();
    fout.open(directory + std::wstring(timestamp.begin(), timestamp.end()) + L".log",
              std::ios_base::out | std::ios_base::app);

    if(!fout.is_open()) {
        throw std::runtime_error("log file create failed");
    }
}

void LogWriter::Update()
{
    int temp = Timer::ReadSystemTime().tm_mday;
    if(day == temp) {
        return;
    }

    // next day
    day = temp;
    New();
}