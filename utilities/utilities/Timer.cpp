/**
 * @file    Timer.cpp
 * @author  LaverWinEmpty@google.com
 * @brief   timer definition
 * @version 0.0.2
 * @date    2023-10-23
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "Timer.hpp"

DEFINE_ENUM_TO_FLAG(Timer::ETimeStampDisplayFlag);

const char* Timer::MONS[] = { "JAN", "FEB", "MAR", "APR", "MAY", "JUN", "JUL", "AUG", "SEP", "OCT", "NOV", "DEC" };
const char* Timer::DAYS[] = { "SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT" };

const char Timer::DATE_DELIMITER = '-';

Timer::ETimeStampDateOrder   Timer::orderDefault;
Timer::ETimeStampDisplayFlag Timer::typesDefault;

const std::chrono::steady_clock::time_point Timer::beginPoint = std::chrono::steady_clock::now();

Timer::Timer():
    chronometerPoint(std::chrono::steady_clock::now()), lastUpdatePoint(std::chrono::steady_clock::now()),
    lastDeltaTime(0), lastStopSec(0), order(orderDefault), types(typesDefault)
{}

Timer::Timer(ETimeStampDateOrder order, ETimeStampDisplayFlag types):
    chronometerPoint(std::chrono::steady_clock::now()), lastUpdatePoint(std::chrono::steady_clock::now()),
    lastDeltaTime(0), lastStopSec(0), order(order), types(types)
{}

void Timer::Reset()
{
    chronometerPoint = std::chrono::steady_clock::now();
}

float Timer::Stop()
{
    std::chrono::duration<float> temp =
        std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now() - chronometerPoint);
    lastStopSec = static_cast<float>(temp.count());
    return lastStopSec;
}

float Timer::GetLastStop()
{
    return lastStopSec;
}

void Timer::UpdateDelta()
{
    std::chrono::high_resolution_clock::time_point curr;

    curr            = std::chrono::high_resolution_clock::now();
    lastDeltaTime   = curr - lastUpdatePoint;
    lastUpdatePoint = curr;
}

std::string Timer::StampingFromSec(double time)
{
    // ABS:: To calculate the date
    if(time < 0) {
        time *= -1;
    }

    uint64_t nTime = static_cast<uint64_t>(time);
    uint64_t hour  = static_cast<int>(nTime / 3600);
    unsigned min   = (nTime / 60) % 60;
    unsigned sec   = nTime % 60;
    unsigned ms    = FractionalToMS(time);

    // "00:00'00", 9 byte
    char buffer[DEF_BUF_SIZE];

    if(hour != 0) {
        sprintf_s(buffer, "%02lld:%02d:%02d.%02d", hour, min, sec, ms);
    }

    else if(min != 0) {
        sprintf_s(buffer, "%02d:%02d.%02d", min, sec, ms);
    }

    else {
        sprintf_s(buffer, "%02d.%02d", sec, ms);
    }

    return buffer;
}

std::string Timer::StampingFromSec24(double time, int* day)
{
    // ABS:: To calculate the date
    if(time < 0) {
        time *= -1;
    }

    tm     temp;
    time_t sec = static_cast<time_t>(time);
    int    ms  = FractionalToMS(time);
    gmtime_s(&temp, &sec);

    // "00:00:00'00", 12 byte
    char buffer[12];
    sprintf_s(buffer, "%02d:%02d:%02d.%02d", temp.tm_hour, temp.tm_min, temp.tm_sec, ms);
    if(day) {
        *day = temp.tm_yday;
    }

    return buffer;
}

std::string Timer::Stamping() const
{
    return StampingFromSec(lastStopSec);
}

std::string Timer::StampingWithStop()
{
    return StampingFromSec(Stop());
}

std::string Timer::StampingFromSystem(char delimiter) const
{
    tm   temp  = ReadSystemTime();
    char empty = EmptyCharacter(types);
    return ToStringDate(&temp, order, types, delimiter) + empty + ToStringTime(&temp, types);
}

std::string Timer::StampingFromSystemDate(char delimiter) const
{
    tm temp = ReadSystemTime();
    return ToStringDate(&temp, order, types, delimiter);
}

std::string Timer::StampingFromSystemTime() const
{
    tm temp = ReadSystemTime();
    return ToStringTime(&temp, types);
}

std::string Timer::StampingFromSystemDefault(char delimiter)
{
    tm   temp  = ReadSystemTime();
    char empty = EmptyCharacter(typesDefault);
    return ToStringDate(&temp, orderDefault, typesDefault, delimiter) + empty + ToStringTime(&temp, typesDefault);
}

std::string Timer::StampingFromSystemDateDefault(char delimiter)
{
    tm temp = ReadSystemTime();
    return ToStringDate(&temp, orderDefault, typesDefault, delimiter);
}

std::string Timer::StampingFromSystemTimeDefault()
{
    tm temp = ReadSystemTime();
    return ToStringTime(&temp, typesDefault);
}

float Timer::GetDeltaTimeMS() const
{
    return static_cast<float>(std::chrono::duration_cast<std::chrono::milliseconds>(lastDeltaTime).count());
}

float Timer::GetDeltaTimeUS() const
{
    return static_cast<float>(std::chrono::duration_cast<std::chrono::microseconds>(lastDeltaTime).count());
}

float Timer::GetDeltaTimeNS() const
{
    return static_cast<float>(lastDeltaTime.count());
}

void Timer::SetTimeStampDateOrder(ETimeStampDateOrder param)
{
    order = param;
}

void Timer::SetTimeStampShowTypes(int param)
{
    types = static_cast<ETimeStampDisplayFlag>(param);
}

void Timer::SetTimeStamp12HourClock(IN bool param)
{
    SET_BIT_FLAG(types, ETimeStampDisplayFlag::USE_12HOUR_CLOCK, param);
}

void Timer::SetTimeStampMonthAsString(bool param)
{
    SET_BIT_FLAG(types, ETimeStampDisplayFlag::USE_MONTH_AS_STRING, param);
}

void Timer::SetTimeStampHideZero(bool param)
{
    SET_BIT_FLAG(types, ETimeStampDisplayFlag::HIDE_ZERO, param);
}

void Timer::SetTimeStampShowWeekday(bool param)
{
    SET_BIT_FLAG(types, ETimeStampDisplayFlag::HIDE_WEEKDAY, param);
}

void Timer::SetTimeStampUseEmpty(bool param)
{
    SET_BIT_FLAG(types, ETimeStampDisplayFlag::USE_EMPTY, param);
}

void Timer::SetTimeStampDateOrderDefault(ETimeStampDateOrder param)
{
    orderDefault = param;
}

void Timer::SetTimeStampShowTypesDefault(int param)
{
    typesDefault = static_cast<ETimeStampDisplayFlag>(param);
}

void Timer::SetTimeStamp12HourClockDefault(bool param)
{
    SET_BIT_FLAG(typesDefault, ETimeStampDisplayFlag::USE_12HOUR_CLOCK, param);
}

void Timer::SetTimeStampMonthAsStringDefault(bool param)
{
    SET_BIT_FLAG(typesDefault, ETimeStampDisplayFlag::USE_MONTH_AS_STRING, param);
}

void Timer::SetTimeStampHideZeroDefault(bool param)
{
    SET_BIT_FLAG(typesDefault, ETimeStampDisplayFlag::HIDE_ZERO, param);
}

void Timer::SetTimeStampShowWeekdayDefault(bool param)
{
    SET_BIT_FLAG(typesDefault, ETimeStampDisplayFlag::HIDE_WEEKDAY, param);
}

void Timer::SetTimeStampUseEmptyDefault(bool param)
{
    SET_BIT_FLAG(typesDefault, ETimeStampDisplayFlag::USE_EMPTY, param);
}

float Timer::GetRunningTime()
{
    return static_cast<float>(
        std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - beginPoint).count());
}

double Timer::SecFromMS(double param)
{
    return param * 1e-3;
}

double Timer::SecFromUS(double param)
{
    return param * 1e-6;
}

double Timer::SecFromNS(double param)
{
    return param * 1e-9;
}

tm Timer::ReadSystemTime()
{
    tm     temp;
    time_t curr;

    time(&curr);
    localtime_s(&temp, &curr);

    return temp;
}

int Timer::FractionalToMS(IN double time)
{
    return static_cast<int>((time - floor(time)) * 100);
}

char Timer::EmptyCharacter(ETimeStampDisplayFlag types)
{
    if(types & ETimeStampDisplayFlag::USE_EMPTY) {
        return ' ';
    }
    return '_';
}

std::string Timer::ToStringDate(tm* param, ETimeStampDateOrder order, ETimeStampDisplayFlag types, char dateDelim)
{
    // "1900_MON_00" <= 12byte
    char buffer[12] = { 0 };

    char day[3] = { 0 };
    char mon[4] = { 0 };

    if(types & ETimeStampDisplayFlag::USE_MONTH_AS_STRING) {
        sprintf_s(mon, "%s", MONS[param->tm_mon]);
    }

    else {
        int nMon = param->tm_mon + 1;
        if(types & ETimeStampDisplayFlag::HIDE_ZERO) {
            sprintf_s(mon, "%d", nMon);
        }
        else {
            sprintf_s(mon, "%02d", nMon);
        }
    }

    if(types & ETimeStampDisplayFlag::HIDE_ZERO) {
        sprintf_s(day, "%d", param->tm_mday);
    }
    else {
        sprintf_s(day, "%02d", param->tm_mday);
    }

    if(types & HIDE_YEAR) {
        switch(order) {
            case ETimeStampDateOrder::YYYY_MM_DD:
                sprintf_s(buffer, "%s%c%s", mon, dateDelim, day);
                break;
            case ETimeStampDateOrder::MM_DD_YYYY:
                sprintf_s(buffer, "%s%c%s", mon, dateDelim, day);
                break;
            case ETimeStampDateOrder::DD_MM_YYYY:
                sprintf_s(buffer, "%s%c%s", day, dateDelim, mon);
                break;
        }
    }
    else {
        int year = param->tm_year + 1900;
        switch(order) {
            case ETimeStampDateOrder::YYYY_MM_DD:
                sprintf_s(buffer, "%d%c%s%c%s", year, dateDelim, mon, dateDelim, day);
                break;
            case ETimeStampDateOrder::MM_DD_YYYY:
                sprintf_s(buffer, "%s%c%s%c%d", mon, dateDelim, day, dateDelim, year);
                break;
            case ETimeStampDateOrder::DD_MM_YYYY:
                sprintf_s(buffer, "%s%c%s%c%d", day, dateDelim, mon, dateDelim, year);
                break;
        }
    }

    if(types & ETimeStampDisplayFlag::HIDE_WEEKDAY) {
        return buffer;
    }

    std::string result = buffer;
    result.push_back(EmptyCharacter(types));
    return result + DAYS[param->tm_wday];
}

std::string Timer::ToStringTime(tm* param, ETimeStampDisplayFlag types)
{
    // "00:00:00 AM" <= 12
    char buffer[12] = { 0 };

    int         hour = param->tm_hour;
    const char* noon = "AM";

    if(types & ETimeStampDisplayFlag::USE_12HOUR_CLOCK) {
        // Check AM / PM
        if(hour >= 12) {
            noon = "PM";
        }

        // Divide AM / PM
        if(hour == 0) {
            hour = 24;
        }

        if(hour > 12) {
            hour -= 12;
        }
    }

    std::string format;
    if(types & ETimeStampDisplayFlag::HIDE_SECONDS) {
        if(types & ETimeStampDisplayFlag::HIDE_ZERO) {
            format = "%d:%d";
        }
        else {
            format = "%02d:%02d";
        }

        if(types & ETimeStampDisplayFlag::USE_12HOUR_CLOCK) {
            char empty = EmptyCharacter(types);
            sprintf_s(buffer, (format + "%c%s").c_str(), hour, param->tm_min, empty, noon);
        }
        else {
            sprintf_s(buffer, format.c_str(), hour, param->tm_min);
        }
    }
    else {
        if(types & ETimeStampDisplayFlag::HIDE_ZERO) {
            format = "%d:%d:%d";
        }
        else {
            format = "%02d:%02d:%02d";
        }

        if(types & ETimeStampDisplayFlag::USE_12HOUR_CLOCK) {
            char empty = EmptyCharacter(types);
            sprintf_s(buffer, (format + "%c%s").c_str(), hour, param->tm_min, param->tm_sec, empty, noon);
        }
        else {
            sprintf_s(buffer, format.c_str(), hour, param->tm_min, param->tm_sec);
        }
    }

    return buffer;
}