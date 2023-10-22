/**
 * @file    Timer.hpp
 * @author  LaverWinEmpty@google.com
 * @brief   chornometer / timestamp utility
 * @version 1.0
 * @date    2023-10-19
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef LWE__TIMER_H__
#define LWE__TIMER_H__

#include "chrono"
#include "string"
#include "../../common/common/common.hpp"

class Timer
{
public:
    /**
     * @brief option used for timestamps
     */
    enum ETimeStampDateOrder
    {
        YYYY_MM_DD,
        MM_DD_YYYY,
        DD_MM_YYYY,
    };

    /**
     * @brief option used for timestamp: bit flag
     */
    enum ETimeStampShowTypeFlags
    {
        INITIALIZE_FALG     = 0,
        USE_MONTH_AS_STRING = (1 << 0),
        USE_12HOUR_CLOCK    = (1 << 1),
        HIDE_WEEKDAY        = (1 << 2),
        HIDE_ZERO           = (1 << 3),
        USE_EMPTY           = (1 << 4),
        HIDE_YEAR           = (1 << 5),
        HIDE_SECONDS        = (1 << 6),
    };

private:
    /**
     * @brief READONLY: string month list
     */
    static const char* MONS[];

    /**
     * @brief READONLY: string week list
     */
    static const char* DAYS[];

    /**
     * @brief READONLY: default delimiter between year, month, and day
     */
    static const char DATE_DELIMITER;

public:
    /**
     * @brief Construct a new Timer object
     */
    Timer();

    /**
     * @brief Construct a new Timer object
     *
     * @param order [in] enum
     * @param option [in] bit flag
     */
    Timer(IN ETimeStampDateOrder order, IN int option);

public:
    /**
     * @brief chronometer initializer
     */
    void Reset();

    /**
     * @brief
     *
     * @return float (get current sec)
     */
    float Stop();
    float GetLastStop();

public:
    /**
     * @brief calculate delta time
     *
     * @warning first call is initialize
     */
    void UpdateDelta();

public:
    /**
     *  @brief get timestamp from duration (of last Stop() call)
     *
     *  @return std::string (e.g. "999:59:59.99")
     */
    std::string Stamping() const;

    /**
     *  @brief get timestamp from duration (pre Stop() call)
     *
     *  @return std::string (e.g. "999:59:59.99")
     */
    std::string StampingWithStop();

public:
    /**
     *  @brief get timestamp from system time
     *
     *  @param delimiter [in] between year, month, day only
     *  @return std::string (e.g. "1900-01-01_23:59:99")
     */
    std::string StampingFromSystem(IN char delimiter = DATE_DELIMITER) const;

    /**
     * @brief get timestamp from system time (date only)
     *
     * @param delimiter [in] between year, month, day only
     * @return std::string (e.g. "1900-01-01")
     */
    std::string StampingFromSystemDate(IN char delimiter = DATE_DELIMITER) const;

    /**
     *  @brief get timestamp from system time(time only)
     *
     *  @return std::string (e.g. "23:59:59")
     */
    std::string StampingFromSystemTime() const;

public:
    /**
     * @brief STATIC: get timestamp from system time
     *
     * @param delimiter [in] between year, month, day only
     * @return std::string (e.g. "1900-01-01_23:59:99")
     */
    static std::string StampingFromSystemDefault(IN char delimiter = DATE_DELIMITER);

    /**
     * @brief STATIC: get timestamp from system time (date only)
     *
     * @param delimiter [in] between year, month, day only
     * @return std::string (e.g. "1900-01-01")
     */
    static std::string StampingFromSystemDateDefault(IN char delimiter = DATE_DELIMITER);

    /**
     * @brief STATIC: get timestamp from system time
     *
     * @return std::string (e.g. "23:59:59")
     */
    static std::string StampingFromSystemTimeDefault();

public:
    /**
     * @brief STATIC: get timestamp from seconds
     *
     * @param time [in] seconds, decimal part is sec, fractional part is ms
     * @return std::string (e.g. "999:59:59.99")
     *
     * @warning HIDE_SECONDS option not working
     */
    static std::string StampingFromSec(IN double time);

    /**
     * @brief get timestamp from seconds
     *
     * @param time [in] seconds for calculation
     * @param day [out] date from the overflowed time [optional]
     * @return std::string (e.g. "23:59:59.99")
     *
     * @warning HIDE_SECONDS option not working
     * @warning float max "23:59:58.00" based on day 0
     */
    static std::string StampingFromSec24(IN double time, OUT OPT int* day = nullptr);


public:
    float GetDeltaTimeMS() const;
    float GetDeltaTimeUS() const;
    float GetDeltaTimeNS() const;

public:
    prop(get = GetDeltaTimeMS) float DeltaMS;
    prop(get = GetDeltaTimeUS) float DeltaUS;
    prop(get = GetDeltaTimeNS) float DeltaNS;

public:
    void SetTimeStampDateOrder(IN ETimeStampDateOrder);
    void SetTimeStampShowTypes(IN int);
    void SetTimeStamp12HourClock(IN bool);
    void SetTimeStampMonthAsString(IN bool);
    void SetTimeStampHideZero(IN bool);
    void SetTimeStampShowWeekday(IN bool);
    void SetTimeStampUseEmpty(IN bool);

public:
    /**
     * @brief setter
     *
     * @param ETimStampDateOrder [in]
     */
    prop(put = SetTimeStampDateOrder) ETimeStampDateOrder Order;

    /**
     * @brief setter
     *
     * @param int [in] bit flag
     */
    prop(put = SetTimeStampShowTypes) int ShowTypeFlag;

    /**
     * @brief setter
     *
     * @param bool [in]
     */
    prop(put = SetTimeStampMonthAsString) bool UseMonthAsString;

    /**
     * @brief setter
     *
     * @param bool [in] true: 1:00:00 PM / false: 13:00:00
     */
    prop(put = SetTimeStamp12HourClock) bool Use12HourClock;

    /**
     * @brief setter
     *
     * @param bool [in] true: 01:00:00 / false 1:00:00
     */
    prop(put = SetTimeStampHideZero) bool HideZero;

    /**
     * @brief setter
     *
     * @param bool [in] true: 01-01_MON_ / false: 01-01_
     */
    prop(put = SetTimeStampShowWeekDay) bool HideWeekDay;

    /**
     * @brief setter
     *
     * @param bool [in] true: 01-01 1:00 / false: 01-01_1:00
     */
    prop(put = SetTimeStampUseEmpty) bool UseEmpty;

public:
    static void SetTimeStampDateOrderDefault(IN ETimeStampDateOrder);
    static void SetTimeStampShowTypesDefault(IN int);
    static void SetTimeStamp12HourClockDefault(IN bool);
    static void SetTimeStampMonthAsStringDefault(IN bool);
    static void SetTimeStampHideZeroDefault(IN bool);
    static void SetTimeStampShowWeekdayDefault(IN bool);
    static void SetTimeStampUseEmptyDefault(IN bool);

public:
    /**
     * @brief get program running time
     *
     * @return float (unit: sec)
     */
    static float GetRunningTime();

public:
    /**
     * @brief convert milli to sec
     *
     * @param double [in] ms
     * @return double
     */
    static double SecFromMS(IN double);

    /**
     * @brief convert micro to sec
     *
     * @param double [in] us
     * @return double
     */
    static double SecFromUS(IN double);

    /**
     * @brief convert nano to sec
     *
     * @param double [in] ns
     * @return double
     */
    static double SecFromNS(IN double);

public:
    /**
     * @brief read system time
     *
     * @return tm (current system time)
     */
    static tm ReadSystemTime();

private:
    /**
     * @brief get fractional part only
     *
     * @param sec [in]
     * @return int (e.g. arg 123.456 => 456)
     */
    static int FractionalToMS(IN double sec);

private:
    /**
     * @brief
     *
     * @param ETimeStampShowTypeFlags [in] just check USE_EMPTY
     * @return char
     */
    static char EmptyCharacter(IN ETimeStampShowTypeFlags);

private:
    /**
     * @brief date to timestamp
     *
     * @param tm [in] time info
     * @param ETimeStampDateOrder [in] year, month, day order
     * @param ETimeStampShowTypeFlags [in] options flag
     * @param dateDelim
     * @return std::string (e.g. "1900-01-01")
     */
    static std::string ToStringDate(IN tm*, IN ETimeStampDateOrder, IN ETimeStampShowTypeFlags, IN char dateDelim);

    /**
     * @brief time to timestamp
     *
     * @param tm [in] time info
     * @param ETimeStampShowTypeFlags [in] options flag
     * @return std::string (e.g. "23:59:59")
     */
    static std::string ToStringTime(IN tm*, IN ETimeStampShowTypeFlags);

private:
    /**
     * @brief progrma start time point
     */
    static const std::chrono::steady_clock::time_point beginPoint;

    /**
     * @brief last chronometer stop time point
     */
    std::chrono::steady_clock::time_point chronometerPoint;

    /**
     * @brief last updated delta time point
     */
    std::chrono::high_resolution_clock::time_point lastUpdatePoint;

    /**
     * @brief last caluclated delta time (ns)
     */
    std::chrono::nanoseconds lastDeltaTime;

    /**
     * @brief saved at the last Stop() call
     */
    float lastStopSec;

private:
    /**
     * @brief year, month, day order
     */
    ETimeStampDateOrder order;

    /**
     * @brief show option: bit flag
     *
     * @warning refer to the property
     */
    ETimeStampShowTypeFlags types;

private:
    /**
     * @brief STATIC: year, month, day order
     */
    static ETimeStampDateOrder orderDefault;

    /**
     * @brief STATIC: show option: bit flag
     */
    static ETimeStampShowTypeFlags typesDefault;
};

#endif