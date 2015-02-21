#include "Date.h"

Date::Date()
{
    month_delta = 0;
    createFromEpoch(time(0));
}

Date::Date(const Date &date)
{
    epoch_data = date.epoch_data;
}

int Date::getDay() const
{
    struct tm *time = localtime(&epoch_data);
    return time->tm_mday;
}

int Date::getMonth() const
{
    struct tm *time = localtime(&epoch_data);
    return time->tm_mon + 1;
}

int Date::getYear() const
{
    struct tm *time = localtime(&epoch_data);
    return time->tm_year + 1900;
}

void Date::setTime(int month_delta)
{
    time_t now = time(0);
    struct tm tstruct = *localtime(&now);
    this->month_delta=month_delta;
    if(month_delta!=1)tstruct.tm_mday=1;
    int tmp=tstruct.tm_mon+month_delta;
    if(tmp==12) {
        tstruct.tm_mon=0;
        tstruct.tm_year++;
    } else if(tmp==-1) {
        tstruct.tm_mon=11;
        tstruct.tm_year--;
    } else {
        tstruct.tm_mon=tmp;
    }
    epoch_data = mktime ( &tstruct );
}

void Date::createFromicaltime(icaltimetype ical_time)
{
    struct tm time = {0};
    time.tm_year =ical_time.year- 1900;
    time.tm_mon =ical_time.month- 1;
    time.tm_mday = ical_time.day;
    epoch_data = mktime(&time);
}

icaltimetype Date::createicaltime() const ///<Creates icaltimetype from date
{
    icaltimetype time = icaltime_null_date();
    time.year = getYear();
    time.month = getMonth();
    time.day = getDay();
    return time;
}

long long Date::getEpoch() const ///<Gets Epoch
{
    return epoch_data;
}

void Date::createFromEpoch(long long utime)
{
    epoch_data = utime;
}

void Date::setDate(int d, int m, int y)
{
    struct tm time = {0};
    time.tm_year =y- 1900;
    time.tm_mon =m- 1;
    time.tm_mday = d;
    epoch_data = mktime(&time);
}

bool Date::operator==(const Date &date)
{
    return (getYear()==date.getYear())&&(getMonth()==date.getMonth())&&(getDay()==date.getDay());
}

bool Date::operator>(const Date &date)
{
    return getYear()>date.getYear()||(getYear()==date.getYear()&&getMonth()>date.getMonth())||(getYear()==date.getYear()&&getMonth()==date.getMonth()&&getDay()>date.getDay());
}

bool Date::operator<(const Date &date)
{
    return !((*this)>date) && !((*this)==date);
}

std::string Date::printString()
{
    return std::to_string(getDay())+"."+std::to_string(getMonth())+"."+std::to_string(getYear());
}

void Date::setDayAgo(int month_delta)  ///<Moves day back \param number of days to move event
{
    long long seconds_epoch = getEpoch();
    seconds_epoch -= month_delta*60*60*24;
    createFromEpoch(seconds_epoch);
}

int Date::getFirstDayWeekOfTheMonth()
{
    struct tm tstruct = *localtime(&epoch_data);
    tstruct.tm_mday=1;

    mktime ( &tstruct );
    return tstruct.tm_wday;
}

int Date::getTodayDayNum() const
{
    if(month_delta)return -1;

    time_t now = time(0);
    struct tm *time = localtime(&now);

    return time->tm_mday;
}

int Date::getLastDayOfTheMonth(int month_delta) ///<Number of days of each month \param month_delta if we want to know day number of last month, we could use month_delta = -1
{
    switch (getMonth()+month_delta) {
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
        return 31;
        break;
    case 2:
        if(getYear()%4!=0)
            return 28;
        else
            return 29;
    default:
        return 30;
        break;
    }
}

int Date::getLastDayOfWeekEnd() ///<First day on month calendar (from last month probably)?
{
    return getLastDayOfTheMonth(-1);
}

std::string Date::monthName(int current) ///<\param current if 0 then name of current month. If 1 it gets next month, if -1 then last etc.
{
    switch (getMonth()+current) {
    case 0:
        return _("December");
    case 1:
        return _("January");
    case 2:
        return _("February");
    case 3:
        return _("March");
    case 4:
        return _("April");
    case 5:
        return _("Mai");
    case 6:
        return _("June");
    case 7:
        return _("July");
    case 8:
        return _("August");
    case 9:
        return _("September");
    case 10:
        return _("October");
    case 11:
        return _("November");
    case 12:
        return _("December");
    default:
        return _("January");
    }
}
