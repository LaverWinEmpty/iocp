/**
 * @file    LogWriter.hpp
 * @author  LaverWinEmpty@google.com
 * @brief   log write utility
 * @version 0.0.3
 * @date    2023-10-24
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef LWE__LOGWRITER_H__
#define LWE__LOGWRITER_H__

#include "windows.h"
#include "iostream"
#include "fstream"
#include "LogBase.hpp"
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

class LogWriter: public LogBase
{
public:
    /**
     * @brief log writer constructor with set locale
     *
     * @param locale [in]
     * @throw std::runtime_error
     */
    LogWriter(IN const char* locale = "");

    /**
     * @brief log writer constructor with set locale
     * @note  refer to LogBase::Initialize()
     *
     * @param directroy [in] folder path
     * @param locale    [in]
     * @throw std::runtime_error
     */
    LogWriter(IN const std::wstring& directroy, IN const char* locale = "");


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
         * @param T           [in] parameter
         */
        template<typename T> static void ConsoleA(IN const std::string&, IN T);

        /**
         * @brief STATIC:  wide string write to console / variadic template method
         *
         * @tparam T
         * @param std::wstring [in] delemeter
         * @param T            [in] parameter
         */
        template<typename T> static void ConsoleW(IN const std::wstring&, IN T);

        /**
         * @brief STATIC: ascii string write to console / variadic template method
         *
         * @tparam T
         * @param std::string [in] delemeter
         * @param T           [in] parameter
         * @param Types       [in] parameter pack
         */
        template<typename T, typename... Types> static void ConsoleA(IN const std::string&, IN T, IN Types...);

        /**
         * @brief STATIC: ascii string write to file / variadic template method
         *
         * @tparam T
         * @param std::string [in] delemeter
         * @param T           [in] parameter
         * @param Types       [in] parameter pack
         */
        template<typename T, typename... Types> static void ConsoleW(IN const std::wstring&, IN T, IN Types...);

    public:
        /**
         * @brief STATIC: ascii string write to file / variadic template method
         *
         * @tparam T
         * @param std::string [in] delemeter
         * @param T           [in] parameter
         */
        template<typename T> static void FileA(IN std::ofstream&, IN const std::string&, IN T);

        /**
         * @brief STATIC: wide string write to file / variadic template method
         *
         * @tparam T
         * @param std::wstring  [in] delemeter
         * @param T             [in] parameter
         */
        template<typename T> static void FileW(IN std::wofstream&, IN const std::wstring&, IN T);

        /**
         * @brief STATIC: wide string write to console / variadic template method
         *
         * @tparam T
         * @param std::wstring [in] delemeter
         * @param T            [in] parameter
         * @param Types        [in] parameter pack
         */
        template<typename T, typename... Types>
        static void FileA(IN std::ofstream&, IN const std::string&, IN T, IN Types...);

        /**
         * @brief STATIC: wide string write to file / variadic template method
         *
         * @tparam T
         * @param std::wstring [in] delemeter
         * @param T            [in] parameter
         * @param Types        [in] parameter pack
         */
        template<typename T, typename... Types>
        static void FileW(IN std::wofstream&, IN const std::wstring&, IN T, IN Types...);
    };


public:
    /**
     * @brief set locale to fout
     *
     * @param chconst char*r [in]
     */
    void SetLocale(IN const char*);

public:
    prop(put = SetLocale) const char* Locale;

public:
    /**
     * @brief wrtie to the file (e.g. ["time"] => "content") / thread safe
     * @warning using FileW => std::wstring
     *
     * @tparam T [in] parameter
     * @tparam Types [in] parameter pack
     * @throw std::runtime_error
     */
    template<typename T, typename... Types> void Log(IN T, IN Types...);

    /**
     * @brief wrtie to console (e.g. ["time"] => "content") / thread safe
     * @warning using ConsolW => std::wstring
     *
     * @tparam T [in] parameter
     * @tparam Types [in] parameter pack
     */
    template<typename T, typename... Types> void Print(IN T, IN Types...);

public:
    /**
     * @brief check date
     * @note  LogBase::Update override
     *
     * @return true: updated / false: not work
     * @throw  std::runtime_error
     */
    bool Update();


private:
    /**
     * @brief
     */
    std::wofstream fout;
};

#include "LogWriter.ipp"

#endif