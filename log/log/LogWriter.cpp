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
        TypeLock<LogBase>::Spin lock;
        if(fout.is_open()) {
            fout.close();
        }
        fout.open(Path(), std::ios_base::out | std::ios_base::app);
        if(!fout.is_open()) {
            throw std::strerror(fout.rdstate());
        }
    }
    return isUpdated;
}