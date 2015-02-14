#include <iostream>
#include <string>
#include <libical/ical.h>
#include <boost/date_time.hpp>
#include "ui/Color.h"
#include "Date.h"

#ifndef CALENDARV_H
#define CALENDARV_H

using namespace std;

///This class represents Calendar as parent of Events. In this app event belongs to specified calendar
class CalendarV
{
public:
    CalendarV() {
        id = -1;
    };

    int getId() const;
    void setId(int id);

    void setName(string name);
    string getName() const;
    void setBgColor(Gdk::Color color);///<Sets background color. Events which belong to this calendar, are going to be that color
    const Color getBgColor() const;
    void addParameter(std::string key, std::string value);///<Adds parameter using key - value. Usefull when parsing from DB
private:
    int id; /* CalendarV id in database */
    Color bg_color;
    string name;
};

#endif
