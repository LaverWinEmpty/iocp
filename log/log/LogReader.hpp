// temp source

/**
 * @file    LogReader.hpp
 * @author  LaverWinEmpty@google.com
 * @brief   log reader
 * @version 0.0.1
 * @date    2023-10-23
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef LWE__LOGREADER_HPP__
#define LWE__LOGREADER_HPP__

#include "thread"
#include "LogBase.hpp"

/**
 * @brief read the log file and display it on the console screen.
 *        used for real-time log monitoring from external sources.
 */
class LogReader: public LogBase
{
public:
    LogReader(IN const char* locale = "");
    LogReader(IN std::wstring directory, IN const char* locale = "");
    ~LogReader();

public:
    void Loop();

public:
    std::chrono::milliseconds cycle;
};

LogReader::LogReader(const char* locale): LogBase() {}

LogReader::LogReader(std::wstring dir, const char* locale): LogBase(dir) {}

LogReader::~LogReader() {}

void LogReader::Loop()
{
    std::ifstream  log;
    std::streampos last;
    std::string    line;

    while(true) {
        try {
            if(Update()) {
                if(log.is_open()) {
                    log.close();
                }

                log.open(file);
                while(!log.is_open()) {
                    log.open(file);
                    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                }
            }
        }

        catch(const std::runtime_error& e) {
            std::cout << e.what();
            while(std::cin.get() != '\n') continue; // press a key
            return;
        }

        log.clear();                       // init
        log.seekg(0, std::ios::end);       // move
        std::streampos curr = log.tellg(); // get

        if(curr != last) {
            log.seekg(last); // return

            // read
            while(std::getline(log, line)) {
                TypeLock<LogBase>::Spin lock;
                std::cout << line << std::endl;
            }

            last = curr; // set
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    if(log.is_open()) {
        log.close();
    }
}

#endif