/**
 * @file    LogBase.hpp
 * @author  LaverWinEmpty@google.com
 * @brief   log directory manager
 * @version 0.0.2
 * @date    2023-10-24
 *
 * @copyright Copyright (c) 2023
 */

#ifndef LWE__LOGBASE_HPP__
#define LWE__LOGBASE_HPP__

#include "iostream"
#include "string"
#include "fstream"
#include "filesystem"
#include "../../utilities/utilities/Timer.hpp"
#include "../../utilities/utilities/LockGuard.hpp"

class LogBase
{
public:
    /**
     * @brief create new folder and file
     * @note  refer to LogBase::Initialize()
     *
     * @param std::wstring [in] log files storage path
     * @throw std::runtime_error
     */
    LogBase(IN const std::wstring& = L"Log/");

public:
    /**
     * @brief create new folder and file
     * @note  replace all \ with /
     *
     * @param std::wstring [in] log files storage path
     */
    void Initialize(IN const std::wstring& dir);

public:
    /**
     * @brief   it switches to a new file when the date changes during reading and writing logs.
     * @warning if it's the same date in a different month, it doesn't change.
     *
     * @return true: updated / false: not work
     * @throw  std::runtime_error
     */
    bool Update();

protected:
    /**
     * @brief create the .log file
     *
     * @return 0: create succeed / else: failed, error code
     */
    int New();

protected:
    /**
     * @brief get the file path from time stamp
     *
     * @return std::wstring (e.g. "path/to/1900-01-01.log")
     */
    std::wstring Path();

private:
    /**
     * @brief replace all \ with /, and push back /
     */
    void FixDirectory();


public:
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

protected:
    /**
     * @brief folder path
     */
    std::wstring directory;

    /**
     * @brief file path
     */
    std::wstring file;

    /**
     * @brief for time stamp
     */
    Timer timer;

    /**
     * @brief for check day
     */
    int day;

    /**
     * @brief for diretory check
     */
    bool isExist;
};

#endif