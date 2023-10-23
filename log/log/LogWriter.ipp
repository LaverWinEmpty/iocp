/**
 * @file    LogWriter.ipp
 * @author  LaverWinEmpty@google.com
 * @brief   log writer definiton
 * @version 0.0.2
 * @date    2023-10-23
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef LWE__LOGWRITER_INL__
#define LWE__LOGWRITER_INL__

template<typename T, typename... Types> void LogWriter::Log(T arg, Types... args)
{
    TypeLock<LogWriter>::Mutex lock;

    Update();
    std::string  temp = timer.StampingFromSystemTime();
    std::wstring timestamp(temp.begin(), temp.end());

    fout << L'[' << timestamp << "] => ";
    Out::FileW(fout, L"", arg, args...);
}

template<typename T, typename... Types> void LogWriter::Print(T arg, Types... args)
{
    TypeLock<LogWriter>::Mutex lock;

    std::string  temp = timer.StampingFromSystemTime();
    std::wstring timestamp(temp.begin(), temp.end());

    std::wcout << L'[' << timestamp << "] => ";
    Out::ConsoleW(L"", arg, args...);
}

template<typename T> void LogWriter::Out::ConsoleA(const std::string& delimiter, T arg)
{
    std::cout << arg << std::endl;
}

template<typename T> void LogWriter::Out::ConsoleW(const std::wstring& delimiter, T arg)
{
    std::wcout << arg << std::endl;
}

template<typename T, typename... Types>
void LogWriter::Out::ConsoleA(const std::string& delimiter, T arg, Types... args)
{
    std::cout << arg;
    if(delimiter.size()) {
        std::cout << delimiter;
    }
    ConsoleA(delimiter, args...);
}

template<typename T, typename... Types>
void LogWriter::Out::ConsoleW(const std::wstring& delimiter, T arg, Types... args)
{
    std::wcout << arg;
    if(delimiter.size()) {
        std::wcout << delimiter;
    }
    ConsoleW(delimiter, args...);
}

template<typename T> void LogWriter::Out::FileA(std::ofstream& fout, const std::string& delimiter, T arg)
{
    fout << arg << std::endl;
}

template<typename T> void LogWriter::Out::FileW(std::wofstream& fout, const std::wstring& delimiter, T arg)
{
    fout << arg << std::endl;
}

template<typename T, typename... Types>
void LogWriter::Out::FileA(std::ofstream& fout, const std::string& delimiter, T arg, Types... args)
{
    fout << arg;
    if(delimiter.size()) {
        fout << delimiter;
    }
    FileA(fout, delimiter, args...);
}

template<typename T, typename... Types>
void LogWriter::Out::FileW(std::wofstream& fout, const std::wstring& delimiter, T arg, Types... args)
{
    fout << arg;
    if(delimiter.size()) {
        fout << delimiter;
    }
    FileW(fout, delimiter, args...);
}

#endif