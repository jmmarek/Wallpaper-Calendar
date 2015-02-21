#ifndef DATE_H
#define DATE_H

#include <iostream>
#include <string>
#include <libical/ical.h>
#include <glibmm/i18n.h>

///Object which represents date and handles usefull methods for time
class Date
{
public:
    int getDay() const;

    int getMonth() const;

    int getYear() const;

    Date();
    void setTime(int month_delta=0);

    Date(const Date &date);
    void createFromicaltime(icaltimetype ical_time);
    icaltimetype createicaltime() const; ///<Creates icaltimetype from date
    long long getEpoch() const; ///<Gets Epoch
    void createFromEpoch(long long utime);
    void setDate(int d, int m, int y);
    bool operator==(const Date &date);
    bool operator>(const Date &date);
    bool operator<(const Date &date);
    std::string printString();
    void setDayAgo(int month_delta); ///<Moves day back \param number of days to move event
    int getTodayDayNum() const;

    int getFirstDayWeekOfTheMonth();
    int getLastDayOfTheMonth(int month_delta = 0);///<Number of days of each month \param month_delta if we want to know day number of last month, we could use month_delta = -1
    int getLastDayOfWeekEnd();///<First day on month calendar (from last month probably)?

    std::string monthName(int current=0);///<\param current if 0 then name of current month. If 1 it gets next month, if -1 then last etc.

private:
    time_t epoch_data;
    int month_delta;
};
#endif
