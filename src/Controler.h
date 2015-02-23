#include <iostream>
#include <string>
#include <libical/ical.h>
#include <boost/date_time.hpp>

#include "CalendarV.h"
#include "Date.h"
#include "Event.h"
#include "DB.h"
#include "ui/Day.h"

#ifndef CONTROLER_H
#define CONTROLER_H

using namespace std;

///Controler of event management. Proxy to using database and server synchronization. It's singleton
class Controler
{
public:
    static Controler* getInstance(std::string path = "");
    static void deleteInstance();

    static void setInstance();
    void getEventsForEachDay(Day *day);///<Inserts events to days which are displayed
    void updateEvent(const Event &e);///<Updates event
    void insertEvent(Event &e, bool sync = true);///<\param e event \param sync whether synchronize after insertion
    void deleteEvent(Event &e);///<Deletes event
    void deleteOlderThan(Date date);///<Remove older events than specified

    CalendarV getCalendar(int id);///<Gets calendar using its id
    void getCalendars();///<Obtains calendars from database and updates them (when from database)
    void updateCalendar(const CalendarV &calendar);///<Updates calendar in db
    void insertCalendar(CalendarV &calendar);///<Inserts calendar to db
    void deleteCalendar(CalendarV &calendar);///<Deletes calendar from db

    vector<CalendarV> calendars;///<Vector with calendars
private:
    static Controler *controler;

    Controler(std::string path = "");
    ~Controler();
    Controler() = delete;

    DB *db;
};

#endif
