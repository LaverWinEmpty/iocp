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

LogWriter::LogWriter(const char* locale): LogBase()
{
    SetLocale(locale);
}

LogWriter::LogWriter(const std::wstring& dir, const char* locale): LogBase(dir)
{
    SetLocale(locale);
}

LogWriter::~LogWriter()
{
    fout.close();
}

void LogWriter::SetLocale(IN const char* param)
{
    fout.imbue(std::locale(param));
}

bool LogWriter::Update()
{
    bool isUpdated = LogBase::Update();
    if(isUpdated) {
        if(!fout.is_open()) {
            fout.open(Path(), std::ios_base::out | std::ios_base::app);
        }
    }
    return isUpdated;
}