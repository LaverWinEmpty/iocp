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