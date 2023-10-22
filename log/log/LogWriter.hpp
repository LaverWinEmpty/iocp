/**
 * @file    LogWriter.hpp
 * @author  LaverWinEmpty@google.com
 * @brief   log write utility
 * @version 1.0
 * @date    2023-10-22
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef LWE__LOGWRITER_H__
#define LWE__LOGWRITER_H__

#include "windows.h"
#include "iostream"
#include "fstream"
#include "../../utilities/utilities/Timer.hpp"
#include "../../utilities/utilities/LockGuard.hpp"

interface ILoggable abstract
{
protected:
    /**
     * @brief Construct a new ILoggable object
     *
     * @param to [in] result produced during object to string conversion
     */
    ILoggable(const char* to);

protected:
    /**
     * @brief STATIC: (default: ostream << a;)
     *
     * @param std::ostream [in] for use in operator<<
     */
    virtual void OnWrite(IN std::ostream&);

    /**
     * @brief STATIC: (default: ofstream << a;)
     *
     * @param std::ofstream [in] for use in operator<<
     */
    virtual void OnWrite(IN std::ofstream&);

    /**
     * @brief STATIC: (default: wostream << w;)
     *
     * @param std::wostream [in] for use in operator<<
     */
    virtual void OnWrite(IN std::wostream&);

    /**
     * @brief STATIC: (default: wofstrteam << w)
     *
     * @param std::wofstream [in] for use in operator<<
     */
    virtual void OnWrite(IN std::wofstream&);

public:
    friend std::ostream&   operator<<(IN std::ostream& os, IN ILoggable& ref);
    friend std::ofstream&  operator<<(IN std::ofstream& os, IN ILoggable& ref);
    friend std::wostream&  operator<<(IN std::wostream& os, IN ILoggable& ref);
    friend std::wofstream& operator<<(IN std::wofstream& os, IN ILoggable& ref);

private:
    /**
     * @brief to ascii string
     */
    const std::string a;

    /**
     * @brief to wide string
     */
    const std::wstring w;
};

class LogWriter
{
public:
    /**
     * @brief Construct a new Log Writer object
     */
    LogWriter();

    /**
     * @brief Construct a new Log Writer object
     *
     * @param directroy [in] folder path
     * @param locale [in]
     * @throw std::runtime_error
     *
     * @warning replace all \ with /
     * @warning if the directory end does not have '/' or '\\', then add '/'
     */
    LogWriter(IN const std::wstring& directroy, IN const char* locale);


public:
    /**
     * @brief Destroy the Log Writer object
     */
    ~LogWriter();

public:
    /**
     * @brief STATIC: output(write) utility class having variadic template methods
     */
    class Out
    {
    public:
        DECLARE_LIMIT_LIFECYCLE(Out);

    public:
        /**
         * @brief STATIC: ascii string write to console / variadic template method
         *
         * @tparam T
         * @param std::string [in] delemeter
         * @param T [in] parameter
         */
        template<typename T> static void ConsoleA(IN const std::string&, IN T);

        /**
         * @brief STATIC:  wide string write to console / variadic template method
         *
         * @tparam T
         * @param std::wstring [in] delemeter
         * @param T [in] parameter
         */
        template<typename T> static void ConsoleW(IN const std::wstring&, IN T);

        /**
         * @brief STATIC: ascii string write to console / variadic template method
         *
         * @tparam T
         * @param std::string [in] delemeter
         * @param T [in] parameter
         * @param Types [in] parameter pack
         */
        template<typename T, typename... Types> static void ConsoleA(IN const std::string&, IN T, IN Types...);

        /**
         * @brief STATIC: ascii string write to file / variadic template method
         *
         * @tparam T
         * @param std::string  [in] delemeter
         * @param T [in] parameter
         * @param Types [in] parameter pack
         */
        template<typename T, typename... Types> static void ConsoleW(IN const std::wstring&, IN T, IN Types...);

    public:
        /**
         * @brief STATIC: ascii string write to file / variadic template method
         *
         * @tparam T
         * @param std::string [in] delemeter
         * @param T [in] parameter
         */
        template<typename T> static void FileA(IN std::ofstream&, IN const std::string&, IN T);

        /**
         * @brief STATIC: wide string write to file / variadic template method
         *
         * @tparam T
         * @param std::wstring  [in] delemeter
         * @param T [in] parameter
         */
        template<typename T> static void FileW(IN std::wofstream&, IN const std::wstring&, IN T);

        /**
         * @brief STATIC: wide string write to console / variadic template method
         *
         * @tparam T
         * @param std::wstring [in] delemeter
         * @param T [in] parameter
         * @param Types [in] parameter pack
         */
        template<typename T, typename... Types>
        static void FileA(IN std::ofstream&, IN const std::string&, IN T, IN Types...);

        /**
         * @brief STATIC: wide string write to file / variadic template method
         *
         * @tparam T
         * @param std::wstring  [in] delemeter
         * @param T [in] parameter
         * @param Types [in] parameter pack
         */
        template<typename T, typename... Types>
        static void FileW(IN std::wofstream&, IN const std::wstring&, IN T, IN Types...);
    };

public:
    /**
     * @brief create new folder and file
     *
     * @param std::wstring [in] folder path
     * @throw std::runtime_error
     *
     * @warning replace all \ with /
     * @warning if the directory end does not have '/' or '\\', then add '/'
     */
    void ChangeDirectory(IN const std::wstring&);

public:
    /**
     * @brief set locale to fout
     *
     * @param char [in]
     */
    void SetLocale(IN const char*);

    /**
     * @brief STATIC: set lcale to cout / wcout
     *
     * @param char [in]
     */
    static void SetLocaleConsole(IN const char*);

    /**
     * @brief STATIC: set locale global
     *
     * @param char [in]
     */
    static void SetLocaleGlobal(IN const char*);

public:
    prop(put = SetLocale) const char* Locale;

public:
    /**
     * @brief create log file
     *
     * @throw std::runtime_error
     */
    void New();

private:
    /**
     * @brief day checking method used in Log() => when the day changes, a new log file is created.
     *
     * @throw std::runtime_error
     */
    void Update();

public:
    /**
     * @brief wrtie to the file (e.g. ["time"] => "content") / thread safe
     *
     * @tparam T [in] parameter
     * @tparam Types [in] parameter pack
     * @throw std::runtime_error
     *
     * @warning using FileW => std::wstring
     */
    template<typename T, typename... Types> void Log(IN T, IN Types...);

    /**
     * @brief wrtie to console (e.g. ["time"] => "content") / thread safe
     *
     * @tparam T [in] parameter
     * @tparam Types [in] parameter pack
     *
     * @warning using ConsolW => std::wstring
     */
    template<typename T, typename... Types> void Print(IN T, IN Types...);

private:
    /**
     * @brief folder path
     */
    std::wstring directory;

    /**
     * @brief
     */
    std::wofstream fout;

    /**
     * @brief for timestamp
     */
    Timer timer;

    /**
     * @brief for check day
     */
    int day;
};

#include "LogWriter.ipp"

#endif